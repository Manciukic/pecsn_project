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

void ServiceCenter::handleOrderMessage(cMessage *msg){
    Order* order = check_and_cast<Order*>(msg);
    order->setArrivalTime(simTime());
    if (servicingOrder == nullptr){
        serveOrder(order);
    } else {
        if(dynamic_cast<PriorityQueue*>(queue)){
            if (order->getVip()){
                   emit(vipQueueLength, queue->getQueueLength(true));
               } else{
                   emit(normalQueueLength, queue->getQueueLength(false));
               }
        }
        else{
            emit(fifoQueueLength, queue->getQueueLength(true));
        }
        queue->push(order);
    }
}


void ServiceCenter::handleTimerMessage(cMessage *msg){
    completeOrder(servicingOrder);
    if(dynamic_cast<PriorityQueue*>(queue)){
        emit(vipQueueLength, queue->getQueueLength(true));
        emit(normalQueueLength, queue->getQueueLength(false));
    }
    else
        emit(fifoQueueLength, queue->getQueueLength(true));

    Order* next = queue->next();
    if (next != nullptr){
        serveOrder(next);
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

    Order* next;
    while ((next = queue->next()) != nullptr){
        cancelAndDelete(next);
    }

    if (servicingOrder != nullptr){
        cancelAndDelete(servicingOrder);
    }
}
