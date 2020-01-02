/**
 * Customer statistics aggregator.
 *
 * After service, customers are sent to this node in order
 * to collect statistics about their response time.
 */

#ifndef __FINAL_PROJECT_EXIT_H_
#define __FINAL_PROJECT_EXIT_H_

#include <omnetpp.h>

#include "counterChecker.h"
#include "order_m.h"

using namespace omnetpp;

class Exit : public cSimpleModule
{
  private:
    simsignal_t simpleNormalResponseTimeSignal;
    simsignal_t simpleVipResponseTimeSignal;
    simsignal_t compoundNormalResponseTimeSignal;
    simsignal_t compoundVipResponseTimeSignal;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
