#include "priorityQueue.h"

Order* PriorityQueue::next(){
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

void PriorityQueue::push(Order* order){
    if (order->getVip()){
        vipQueue.push(order);
    } else{
        normQueue.push(order);
    }
}

int PriorityQueue::getQueueLength(bool vip){
    if(vip==true){
        return vipQueue.size();
    }
    else {
        return normQueue.size();
    }
}
