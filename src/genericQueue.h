/**
 * Abstract queue
 */

#ifndef GENERICQUEUE_H_
#define GENERICQUEUE_H_

#include <omnetpp.h>
#include "order_m.h"

using namespace omnetpp;

class GenericQueue {
  public:
    /**
     * Returns and pops the first element in the queue
     */
    virtual Order* next() = 0;

    /**
     * Pushes the new element to the end of the queue.
     */
    virtual void push(Order* order) = 0;

    /**
     * Returns the length of the normal or VIP queue (if any).
     */
    virtual int getQueueLength(bool vip) = 0;
};

#endif /* GENERICQUEUE_H_ */
