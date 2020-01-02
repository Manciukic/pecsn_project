/*
 * counterChecker.cc
 *
 *  Created on: Dec 28, 2019
 *      Author: up
 */

#include "counterChecker.h"

Define_Module(CounterChecker);

OrderType determineType(Order* order){
    if (order->getVip()){
        if (order->getCompound()){
            return VIP_COMPOUND;
        } else{
            return VIP_SIMPLE;
        }
    } else {
        if (order->getCompound()){
            return NORMAL_COMPOUND;
        } else{
            return NORMAL_SIMPLE;
        }
    }
}

std::string getStrType(OrderType type){
    switch(type){
    case NORMAL_SIMPLE:
        return "normal simple";
    case NORMAL_COMPOUND:
        return "normal compound";
    case VIP_SIMPLE:
        return "VIP simple";
    case VIP_COMPOUND:
        return "VIP compound";
    default:
        return "";
    }
}

void CounterChecker::initialize(){
    for (int i=0; i<4; i++){
        for (int j=0; j<3; j++){
            counter[i][j] = 0;
        }
    }
    finishCount = 0;
}

void CounterChecker::count(OrderLocation location, Order* order){
    if (order == nullptr)
        return;

    OrderType type = determineType(order);
    counter[type][location] ++;
}

void CounterChecker::printStats(){
    for (int i = 0; i < 4; i++){
        EV << getStrType((OrderType)i) << ": ";
        EV << "IN " << counter[i][INo] << ", ";
        EV << "OUT " << counter[i][OUTo] << ", ";
        EV << "WIP " << counter[i][WIPo] << ": ";
        if (counter[i][INo] == counter[i][OUTo] + counter[i][WIPo]){
            EV << "OK";
        } else{
            EV << "ERROR";
        }
        EV << endl;
    }

    int nTot = counter[NORMAL_SIMPLE][INo] + counter[NORMAL_COMPOUND][INo] + counter[VIP_SIMPLE][INo] + counter[VIP_COMPOUND][INo];
    int nCompound = counter[NORMAL_COMPOUND][INo] + counter[VIP_COMPOUND][INo];
    int nVip = counter[VIP_SIMPLE][INo] + counter[VIP_COMPOUND][INo];

    double rCompound = nCompound / (double)nTot;
    double rVip = nVip / (double)nTot;

    EV << "Compound are " << rCompound << " of total" << endl;
    EV << "VIP are " << rVip << " of total" << endl;
}

void CounterChecker::markFinished(){
    finishCount++;
    if (finishCount >= FINISH_COUNT){
        printStats();
    }
}

