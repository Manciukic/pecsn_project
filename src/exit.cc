#include "exit.h"

Define_Module(Exit);

void Exit::initialize()
{
    simpleNormalResponseTimeSignal = registerSignal("simpleNormalResponseTime");
    simpleVipResponseTimeSignal = registerSignal("simpleVipResponseTime");
    compoundNormalResponseTimeSignal = registerSignal("compoundNormalResponseTime");
    compoundVipResponseTimeSignal = registerSignal("compoundVipResponseTime");
}

void Exit::handleMessage(cMessage *msg)
{
    if (!msg->isName("orderMsg")){
        EV << "Received unknown message: " << msg->getName() << endl;
        return;
    }

    Order* order = check_and_cast<Order*>(msg);
    double responseTime = (simTime() - order->getCreationTime()).dbl();
    if (order->getVip()){
        if (order->getCompound()){
            emit(compoundVipResponseTimeSignal, responseTime);
        } else{
            emit(simpleVipResponseTimeSignal, responseTime);
        }
    } else{
        if (order->getCompound()){
            emit(compoundNormalResponseTimeSignal, responseTime);
        } else{
            emit(simpleNormalResponseTimeSignal, responseTime);
        }
    }

    CounterChecker* counterChecker = check_and_cast<CounterChecker*>(getModuleByPath("counterChecker"));
    counterChecker->count(OUTo, order);

    cancelAndDelete(order);
}


