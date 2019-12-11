#ifndef __FINAL_PROJECT_CASHIER_H_
#define __FINAL_PROJECT_CASHIER_H_

#include <omnetpp.h>

#include "priorityQueue.h"
#include "fifoQueue.h"
#include "serviceCenter.h"

using namespace omnetpp;

class Cashier : public ServiceCenter
{
  protected:
    virtual void completeOrder(Order* order) override;
    virtual GenericQueue* createQueue() override;
};

#endif
