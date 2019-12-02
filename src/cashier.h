#ifndef __FINAL_PROJECT_CASHIER_H_
#define __FINAL_PROJECT_CASHIER_H_

#include <omnetpp.h>
#include "timerModule.h"
#include "customerQueues.h"

using namespace omnetpp;

class Cashier : public TimerModule
{
  private:
    CustomerQueues queues;
    Order* servicingOrder;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleTimerMessage(cMessage *msg);
    void handleOrderMessage(cMessage *msg);
    void serveOrder(Order* order);
    virtual void finish() override;
};

#endif
