#ifndef __FINAL_PROJECT_KITCHEN_H_
#define __FINAL_PROJECT_KITCHEN_H_

#include <omnetpp.h>
#include <queue>
#include "timerModule.h"
#include "order_m.h"


using namespace omnetpp;

class Kitchen : public TimerModule
{
  private:
    std::queue<Order*> queue;
    Order* servicingOrder;
  protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleOrderMessage(cMessage *msg);
    void handleTimerMessage(cMessage *msg);
    void serveOrder(Order* order);
};

#endif
