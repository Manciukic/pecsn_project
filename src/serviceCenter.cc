#include "serviceCenter.h"

void ServiceCenter::initialize(){
    TimerModule::initialize();

    servicingOrder = nullptr;
    queue = createQueue();
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
    if (servicingOrder == nullptr){
        serveOrder(order);
    } else {
        queue->push(order);
    }
}


void ServiceCenter::handleTimerMessage(cMessage *msg){
    completeOrder(servicingOrder);

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
