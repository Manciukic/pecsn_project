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

  protected:
    virtual void initialize() override;
    virtual void finish() override;
    void scheduleTimer();
};

#endif /* TIMERMODULE_H_ */
