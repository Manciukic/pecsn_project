#include "cashier.h"

Define_Module(Cashier);

GenericQueue* Cashier::createQueue(){
    return new PriorityQueue;
}

void Cashier::completeOrder(Order* order){
    if (servicingOrder->getCompound()){
        send(servicingOrder, "outKitchen");
    } else{
        send(servicingOrder, "outExit");
    }
}
