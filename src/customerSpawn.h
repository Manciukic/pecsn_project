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

#include "counterChecker.h"

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
    double customHourScaling[18] = {0.164705882,0.229411765,0.294117647,0.552941176,0.811764706,1.005882353,0.747058824,0.552941176,0.358823529,0.294117647,0.552941176,0.876470588,1.070588235,1.2,1.070588235,0.876470588,0.617647059,0.358823529};
  protected:
    virtual void initialize() override;
    virtual void finish() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleTimerMessage(cMessage *msg, bool vip);
    void scheduleTimer(cMessage* timer, double interval, int rngIdx);
};

#endif
