/**
 * Kitchen
 *
 * The kitchen is a service center with a configurable
 * queuing strategy: head-of-line priority or FIFO.
 *
 * Parameters (inherited from ServiceCenter):
 *  - rate: average timer rate
 *  - randFunc: random function to be used (const or exp)
 *  - rngIdx: index of the RNG to be used
 *
 * Parameters:
 *  - queueType: "fifo" or "priority"
 */

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
