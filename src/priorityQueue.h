/**
 * Head-of-Line priority queuing without preemption
 *
 * There are two queues: one for VIP and one for normal customers.
 * The next customer to be served is the next VIP if any, otherwise
 * the next normal.
 */

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <omnetpp.h>
#include <queue>
#include "genericQueue.h"
#include "order_m.h"

using namespace omnetpp;

class PriorityQueue : public GenericQueue {
  private:
    std::queue<Order*> vipQueue;
    std::queue<Order*> normQueue;
  public:
    virtual Order* next() override;
    virtual void push(Order* order) override;
    virtual int getQueueLength(bool vip) override;
};

#endif /* PRIORITYQUEUE_H_ */
