#ifndef CUSTOMERQUEUES_H_
#define CUSTOMERQUEUES_H_

#include <omnetpp.h>
#include <queue>
#include "order_m.h"

using namespace omnetpp;

class CustomerQueues {
  private:
    std::queue<Order*> vipQueue;
    std::queue<Order*> normQueue;
  public:
    Order* next();
    void enqueue(Order* order);
};

#endif /* CUSTOMERQUEUES_H_ */
