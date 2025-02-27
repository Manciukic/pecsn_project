#include "customerSpawn.h"
#include "order_m.h"

Define_Module(CustomerSpawn);

void CustomerSpawn::initialize()
{
    double vipRate, normalRate;

    pCompound = par("pCompound").doubleValue();
    vipOffset = par("vipOffset").doubleValue();
    randFunc = par("randFunc").stringValue();
    vipRate = par("vipRate").doubleValue();
    normalRate = par("normalRate").doubleValue();
    rngIdxCompound = par("rngIdxCompound").intValue();
    rngIdxNormal = par("rngIdxNormal").intValue();
    rngIdxVip = par("rngIdxVip").intValue();

    if (vipRate != 0){
        vipInterval = 1/vipRate;
        vipTimer = new cMessage("vipTimerMsg");
        scheduleTimer(vipTimer, vipInterval+vipOffset, rngIdxVip);
    } else{ // if rate is null, no timer is to be scheduled
        vipTimer = nullptr;
    }

    if (normalRate != 0){
        normalInterval = 1/normalRate;
        normalTimer = new cMessage("normalTimerMsg");
        scheduleTimer(normalTimer, normalInterval, rngIdxNormal);
    } else{ // if rate is null, no timer is to be scheduled
        normalTimer = nullptr;
    }
}

void CustomerSpawn::handleMessage(cMessage *msg)
{
    if (msg->isName("vipTimerMsg")){
        handleTimerMessage(msg, true);
    } else if (msg->isName("normalTimerMsg")){
        handleTimerMessage(msg, false);
    } else{
        EV << "Received unknown message: " << msg->getName() << endl;
    }
}

void CustomerSpawn::handleTimerMessage(cMessage *msg, bool vip)
{
    Order* order = new Order("orderMsg");
    order->setVip(vip);
    order->setCompound(pCompound >= uniform(0,1,rngIdxCompound));
    order->setCreationTime(simTime());

    send(order, "out");

    CounterChecker* counterChecker = check_and_cast<CounterChecker*>(getModuleByPath("counterChecker"));
    counterChecker->count(INo, order);

    if (vip){
        scheduleTimer(vipTimer, vipInterval, rngIdxVip);
    } else {
        scheduleTimer(normalTimer, normalInterval, rngIdxNormal);
    }
}


void CustomerSpawn::scheduleTimer(cMessage* timer, double avgInterval, int rngIdx)
{
    double interval;
    if (randFunc.compare("const") == 0){
        interval = avgInterval;
    }
    else if (randFunc.compare("exp") == 0){
        interval = exponential(avgInterval, rngIdx);
    }
    else if(randFunc.compare("working-day") == 0){
        int hour = ((int)simTime().dbl())/60;
        if(hour > 17)
            hour = 17;
        EV<<"ora: "<<hour<<endl;
        avgInterval = 1/((1/avgInterval)*customHourScaling[hour]);
        interval = exponential(avgInterval, rngIdx);
    }
    else {
        EV << "Unrecognized random function: " << randFunc << endl;
        return;
    }

    scheduleAt(simTime() + interval, timer);
}

void CustomerSpawn::finish()
{
    cancelAndDelete(normalTimer);
    cancelAndDelete(vipTimer);
}
