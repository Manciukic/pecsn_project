#ifndef __FINAL_PROJECT_CUSTOMERSPAWN_H_
#define __FINAL_PROJECT_CUSTOMERSPAWN_H_

#include <omnetpp.h>

using namespace omnetpp;

class CustomerSpawn : public cSimpleModule
{
  private:
    double vipInterval;
    double vipOffset;
    double normalInterval;
    double pCompound;
    std::string randFunc;
    cMessage* normalTimer;
    cMessage* vipTimer;
  protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleTimerMessage(cMessage *msg, bool vip);
    void scheduleTimer(cMessage* timer, double interval);
};

#endif
