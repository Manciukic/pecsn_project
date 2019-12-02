#include "customerQueues.h"

Order* CustomerQueues::next(){
    if (!vipQueue.empty()){
        Order* result = vipQueue.front();
        vipQueue.pop();
        return result;
    } else if (!normQueue.empty()){
        Order* result = normQueue.front();
        normQueue.pop();
        return result;
    } else {
        return nullptr;
    }
}

void CustomerQueues::enqueue(Order* order){
    if (order->getVip()){
        vipQueue.push(order);
    } else{
        normQueue.push(order);
    }
}
