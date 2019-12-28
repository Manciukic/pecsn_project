/**
 * Abstract service center class
 *
 * A service center services orders at a certain rate and queues
 * incoming orders if one order is already being serviced.
 *
 * Implementations of this class must implement the abstract methods
 * completeOrder and createQueue.
 *
 * Parameters (inherited from TimerModule):
 *  - rate: average timer rate
 *  - randFunc: random function to be used (const or exp)
 *  - rngIdx: index of the RNG to be used
 */

#ifndef SERVICECENTER_H_
#define SERVICECENTER_H_

#include <omnetpp.h>

#include "priorityQueue.h"
#include "timerModule.h"

using namespace omnetpp;

class ServiceCenter : public TimerModule
{
  private:
    simsignal_t normalWaitingTimeSignal;
    simsignal_t vipWaitingTimeSignal;
    simsignal_t normalQueueLength;
    simsignal_t vipQueueLength;
    simsignal_t fifoQueueLength;

    /**
     * Emit the "*QueueLength" signals with the current queue state
     */
    void emitQueuesLength(bool vip);

    /**
     * Puts the given order under service
     */
    void serveOrder(Order* order);
  protected:
    GenericQueue* queue;
    Order* servicingOrder;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleTimerMessage(cMessage *msg);
    void handleOrderMessage(cMessage *msg);
    virtual void finish() override;

    /**
     * Does something with the completed order
     *
     * This method is called when the order under service finishes
     * its execution.
     */
    virtual void completeOrder(Order* order) = 0;

    /**
     * Create the queue
     *
     * This method is called on initialization.
     */
    virtual GenericQueue* createQueue() = 0;
};

#endif /* SERVICECENTER_H_ */
