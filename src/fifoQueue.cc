#include "fifoQueue.h"

Order* FifoQueue::next(){
    if (!queue.empty()){
        Order* result = queue.front();
        queue.pop();
        return result;
    } else {
        return nullptr;
    }
}

void FifoQueue::push(Order* order){
    queue.push(order);
}

int FifoQueue::getQueueLength(bool vip){
    return queue.size();
}

