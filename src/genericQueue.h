#ifndef GENERICQUEUE_H_
#define GENERICQUEUE_H_

#include <omnetpp.h>
#include "order_m.h"

using namespace omnetpp;

class GenericQueue {
  public:
    virtual Order* next() = 0;
    virtual void push(Order* order) = 0;
    virtual double getQueueLength(bool vip) = 0;
};

#endif /* GENERICQUEUE_H_ */
