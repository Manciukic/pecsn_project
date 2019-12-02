#include "customerSpawn.h"
#include "order_m.h"

Define_Module(CustomerSpawn);

void CustomerSpawn::initialize()
{
    pVip = par("pVip").doubleValue();
    pCompound = par("pCompound").doubleValue();

    TimerModule::initialize();

    scheduleTimer();
}

void CustomerSpawn::handleMessage(cMessage *msg)
{
    if (msg->isName("timerMsg")){
        handleTimerMessage(msg);
    } else{
        EV << "Received unknown message: " << msg->getName() << endl;
    }
}

void CustomerSpawn::handleTimerMessage(cMessage *msg)
{
    Order* order = new Order("orderMsg");
    order->setVip(pVip >= uniform(0,1));
    order->setCompound(pCompound >= uniform(0,1));
    order->setCreationTime(simTime());

    send(order, "out");

    scheduleTimer();
}
