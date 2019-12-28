/**
 * Abstract timer module class
 *
 * This class implements a simple module that sends to itself
 * a message with the given average interval and time distribution.
 *
 * Parameters:
 *  - rate: average timer rate
 *  - randFunc: random function to be used (const or exp)
 *  - rngIdx: index of the RNG to be used
 */

#ifndef TIMERMODULE_H_
#define TIMERMODULE_H_

#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class TimerModule : public cSimpleModule {
  private:
    double avgInterval;
    string randFunc;
    cMessage* timer;
    int rngIdx;

  protected:
    virtual void initialize() override;
    virtual void finish() override;

    /**
     * Schedule a message to be sent to the module itself
     * after a random amount of time (depending on the random function).
     */
    void scheduleTimer();
};

#endif /* TIMERMODULE_H_ */
