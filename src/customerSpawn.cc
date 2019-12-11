#include "customerSpawn.h"
#include "order_m.h"

Define_Module(CustomerSpawn);

void CustomerSpawn::initialize()
{
    pCompound = par("pCompound").doubleValue();

    vipOffset = par("vipOffset").doubleValue();
    vipInterval = 1/par("vipRate").doubleValue();
    normalInterval = 1/par("normalRate").doubleValue();
    randFunc = par("randFunc").stringValue();

    vipTimer = new cMessage("vipTimerMsg");
    normalTimer = new cMessage("normalTimerMsg");

    scheduleTimer(vipTimer, vipInterval+vipOffset);
    scheduleTimer(normalTimer, normalInterval);
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
    order->setCompound(pCompound >= uniform(0,1));
    order->setCreationTime(simTime());

    send(order, "out");

    if (vip){
        scheduleTimer(vipTimer, vipInterval);
    } else {
        scheduleTimer(normalTimer, normalInterval);
    }
}


void CustomerSpawn::scheduleTimer(cMessage* timer, double avgInterval)
{
    double interval;
    if (randFunc.compare("const") == 0){
        interval = avgInterval;
    } else if (randFunc.compare("exp") == 0){
        interval = exponential(avgInterval);
    } else {
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
