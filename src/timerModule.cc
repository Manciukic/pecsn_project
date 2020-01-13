#include "timerModule.h"

Define_Module(TimerModule);

void TimerModule::initialize()
{
    avgInterval = 1/par("rate").doubleValue();
    randFunc = par("randFunc").stringValue();
    rngIdx = par("rngIdx").intValue();

    timer = new cMessage("timerMsg");
}

void TimerModule::scheduleTimer()
{
    double interval;
    if (randFunc.compare("const") == 0){
        interval = avgInterval;
    } else if (randFunc.compare("exp") == 0 || randFunc.compare("working-day") == 0){
        interval = exponential(avgInterval, rngIdx);
    } else {
        EV << "Unrecognized random function: " << randFunc << endl;
        return;
    }

    scheduleAt(simTime() + interval, timer);
}

void TimerModule::finish()
{
    cancelAndDelete(timer);
}
