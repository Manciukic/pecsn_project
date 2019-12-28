/**
 * Distribution generator for customers.
 *
 * Customers are generated using the distribution set by the parameters:
 *  - vipRate: rate of vip customers
 *  - normalRate: rate of normal customers
 *  - vipOffset: offset of vip (used in conjunction with constant inter-arrival times).
 *  - randFunc: distribution of customers inter-arrival times (const or exp)
 *  - pCompound: ratio of compound orders over the total (i.e. probability of being compound)
 *  - rngIdxCompound, rngIdxNormal, rngIdxVip: indices for the RNGs to be used
 */

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
    int rngIdxCompound;
    int rngIdxNormal;
    int rngIdxVip;
  protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleTimerMessage(cMessage *msg, bool vip);
    void scheduleTimer(cMessage* timer, double interval, int rngIdx);
};

#endif
