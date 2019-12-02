#include "cashier.h"

Define_Module(Cashier);

void Cashier::initialize(){
    TimerModule::initialize();

    servicingOrder = nullptr;
}

void Cashier::handleMessage(cMessage *msg)
{
    if (msg->isName("orderMsg")){
        handleOrderMessage(msg);
    } else if (msg->isName("timerMsg")){
        handleTimerMessage(msg);
    } else{
        EV << "Received unknown message: " << msg->getName() << endl;
    }
}

void Cashier::handleOrderMessage(cMessage *msg){
    Order* order = check_and_cast<Order*>(msg);
    if (servicingOrder == nullptr){
        serveOrder(order);
    } else {
        queues.enqueue(order);
    }
}


void Cashier::handleTimerMessage(cMessage *msg){
    if (servicingOrder->getCompound()){
        send(servicingOrder, "outKitchen");
    } else{
        send(servicingOrder, "outExit");
    }

    Order* next = queues.next();
    if (next != nullptr){
        serveOrder(next);
    } else {
        servicingOrder = nullptr;
    }
}


void Cashier::serveOrder(Order* order){
    servicingOrder = order;
    scheduleTimer();
}

void Cashier::finish(){
    TimerModule::finish();

    Order* next;
    while ((next = queues.next()) != nullptr){
        cancelAndDelete(next);
    }

    if (servicingOrder != nullptr){
        cancelAndDelete(servicingOrder);
    }
}
