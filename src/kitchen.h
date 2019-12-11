#ifndef __FINAL_PROJECT_KITCHEN_H_
#define __FINAL_PROJECT_KITCHEN_H_

#include <omnetpp.h>

#include <string>

#include "priorityQueue.h"
#include "fifoQueue.h"
#include "serviceCenter.h"

using namespace omnetpp;

class Kitchen : public ServiceCenter
{
  protected:
    virtual void completeOrder(Order* order) override;
    virtual GenericQueue* createQueue() override;
};

#endif
