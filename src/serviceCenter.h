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

    void emitQueuesLength(bool vip);
  protected:
    GenericQueue* queue;
    Order* servicingOrder;

    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleTimerMessage(cMessage *msg);
    void handleOrderMessage(cMessage *msg);
    void serveOrder(Order* order);
    virtual void finish() override;

    virtual void completeOrder(Order* order) = 0;
    virtual GenericQueue* createQueue() = 0;
};

#endif /* SERVICECENTER_H_ */
