#include "cashier.h"

Define_Module(Cashier);

GenericQueue* Cashier::createQueue(){
    return new PriorityQueue;
}

void Cashier::completeOrder(Order* order){
    if (order->getCompound()){
        send(order, "outKitchen");
    } else{
        send(order, "outExit");
    }
}
