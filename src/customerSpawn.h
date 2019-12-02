#ifndef __FINAL_PROJECT_CUSTOMERSPAWN_H_
#define __FINAL_PROJECT_CUSTOMERSPAWN_H_

#include <omnetpp.h>
#include "timerModule.h"

using namespace omnetpp;

class CustomerSpawn : public TimerModule
{
  private:
    double pVip;
    double pCompound;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleTimerMessage(cMessage *msg);
};

#endif
