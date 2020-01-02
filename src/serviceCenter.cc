#include "serviceCenter.h"

void ServiceCenter::initialize(){
    TimerModule::initialize();

    servicingOrder = nullptr;
    queue = createQueue();

    normalWaitingTimeSignal = registerSignal("normalWaitingTime");
    vipWaitingTimeSignal = registerSignal("vipWaitingTime");
    normalQueueLength = registerSignal("normalQueueLength");
    vipQueueLength = registerSignal("vipQueueLength");
    fifoQueueLength = registerSignal("fifoQueueLength");

    emit(vipQueueLength, 0);
    emit(normalQueueLength, 0);
    emit(fifoQueueLength, 0);
}

void ServiceCenter::handleMessage(cMessage *msg)
{
    if (msg->isName("orderMsg")){
        handleOrderMessage(msg);
    } else if (msg->isName("timerMsg")){
        handleTimerMessage(msg);
    } else{
        EV << "Received unknown message: " << msg->getName() << endl;
    }
}

void ServiceCenter::emitQueuesLength(bool vip){
    emit(fifoQueueLength, queue->getQueueLength(true));

    if (vip){
        emit(vipQueueLength, queue->getQueueLength(true));
    } else{
        emit(normalQueueLength, queue->getQueueLength(false));
    }
}


void ServiceCenter::handleOrderMessage(cMessage *msg){
    Order* order = check_and_cast<Order*>(msg);
    order->setArrivalTime(simTime());

    if (servicingOrder == nullptr){
        serveOrder(order);
    } else {
        queue->push(order);
        emitQueuesLength(order->getVip());
    }
}


void ServiceCenter::handleTimerMessage(cMessage *msg){
    completeOrder(servicingOrder);

    Order* next = queue->next();
    if (next != nullptr){
        serveOrder(next);
        emitQueuesLength(next->getVip());
    } else {
        servicingOrder = nullptr;
    }
}


void ServiceCenter::serveOrder(Order* order){
    servicingOrder = order;
    scheduleTimer();

    double waitingTime = (simTime()-servicingOrder->getArrivalTime()).dbl();

    if (servicingOrder->getVip()){
        emit(vipWaitingTimeSignal, waitingTime);
    } else{
        emit(normalWaitingTimeSignal, waitingTime);
    }
}

void ServiceCenter::finish(){
    TimerModule::finish();

    CounterChecker* counterChecker = check_and_cast<CounterChecker*>(getModuleByPath("counterChecker"));

    Order* next;
    while ((next = queue->next()) != nullptr){
        counterChecker->count(WIPo, next);
        cancelAndDelete(next);
    }

    if (servicingOrder != nullptr){
        counterChecker->count(WIPo, servicingOrder);
        cancelAndDelete(servicingOrder);
    }

    counterChecker->markFinished();
}
