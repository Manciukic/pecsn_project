/**
 * FIFO Queue
 *
 * Orders are queued in a FIFO-fashion with no distinction
 * between vip and normal orders.
 */

#ifndef FIFOQUEUE_H_
#define FIFOQUEUE_H_

#include <omnetpp.h>
#include <queue>
#include "genericQueue.h"
#include "order_m.h"

using namespace omnetpp;

class FifoQueue : public GenericQueue {
  private:
    std::queue<Order*> queue;
  public:
    virtual Order* next() override;
    virtual void push(Order* order) override;
    virtual int getQueueLength(bool vip) override;
};

#endif /* FIFOQUEUE_H_ */
