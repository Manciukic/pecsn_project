/*
 * counterChecker.h
 *
 *  Created on: Dec 28, 2019
 *      Author: up
 */

#ifndef COUNTERCHECKER_H_
#define COUNTERCHECKER_H_

#include <omnetpp.h>

#include "order_m.h"

#define FINISH_COUNT 2

using namespace omnetpp;

enum OrderLocation {IN, OUT, WIP};
enum OrderType {NORMAL_SIMPLE, NORMAL_COMPOUND, VIP_SIMPLE, VIP_COMPOUND};

OrderType determineType(Order* order);
std::string getStrType(OrderType type);

class CounterChecker : public cSimpleModule {
  private:
    int counter[4][3];
    int finishCount;
    void printStats();
  protected:
    virtual void initialize() override;
  public:
    void count(OrderLocation location, Order* order);
    void markFinished();
};

#endif /* COUNTERCHECKER_H_ */
