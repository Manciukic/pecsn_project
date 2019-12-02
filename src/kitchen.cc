#include "kitchen.h"

Define_Module(Kitchen);

void Kitchen::initialize(){
    TimerModule::initialize();

    servicingOrder = nullptr;
}


void Kitchen::handleMessage(cMessage *msg)
{
    if (msg->isName("orderMsg")){
        handleOrderMessage(msg);
    } else if (msg->isName("timerMsg")){
        handleTimerMessage(msg);
    } else{
        EV << "Received unknown message: " << msg->getName() << endl;
    }
}

void Kitchen::handleOrderMessage(cMessage *msg){
    Order* order = check_and_cast<Order*>(msg);
    if (servicingOrder == nullptr){
        serveOrder(order);
    } else {
        queue.push(order);
    }
}


void Kitchen::handleTimerMessage(cMessage *msg){
    send(servicingOrder, "out");

    if (!queue.empty()){
        Order* next = queue.front();
        queue.pop();
        serveOrder(next);
    } else {
        servicingOrder = nullptr;
    }
}


void Kitchen::serveOrder(Order* order){
    servicingOrder = order;
    scheduleTimer();
}

void Kitchen::finish(){
    TimerModule::finish();

    while (!queue.empty()){
        cancelAndDelete(queue.front());
        queue.pop();
    }

    if (servicingOrder != nullptr){
        cancelAndDelete(servicingOrder);
    }
}
