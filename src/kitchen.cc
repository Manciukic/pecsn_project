#include "kitchen.h"

Define_Module(Kitchen);

GenericQueue* Kitchen::createQueue(){
    string queueType = par("queueType").stringValue();
    if (queueType.compare("fifo") == 0){
        return new FifoQueue;
    } else if (queueType.compare("priority") == 0){
        return new PriorityQueue;
    } else{
        EV << "Undefined queue type: " << queueType << endl;
        return nullptr;
    }
}

void Kitchen::completeOrder(Order* order){
    send(servicingOrder, "out");
}
