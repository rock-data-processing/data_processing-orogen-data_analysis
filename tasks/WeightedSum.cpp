/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "WeightedSum.hpp"

using namespace data_analysis;

WeightedSum::WeightedSum(std::string const& name)
    : WeightedSumBase(name){
}

WeightedSum::WeightedSum(std::string const& name, RTT::ExecutionEngine* engine)
    : WeightedSumBase(name, engine){
}

WeightedSum::~WeightedSum(){
}

bool WeightedSum::configureHook(){
    if (! WeightedSumBase::configureHook())
        return false;

    weights = _weights.get();
    if(getDataVectorCount() != weights.size()){
        LOG_ERROR("Size of weight vector has to be same as port_config vector size. Check you config!");
        return false;
    }
    summands.resize(getDataVectorCount());

    return true;
}

bool WeightedSum::startHook(){
    if (! WeightedSumBase::startHook())
        return false;
    return true;
}

void WeightedSum::updateHook(){
    WeightedSumBase::updateHook();
}

void WeightedSum::errorHook(){
    WeightedSumBase::errorHook();
}

void WeightedSum::stopHook(){
    WeightedSumBase::stopHook();
}

void WeightedSum::cleanupHook(){
    WeightedSumBase::cleanupHook();
    summands.clear();
}

void WeightedSum::process(){
    weighted_sum.setZero();
    for(int i=0; i < getDataVectorCount(); i++ ){
        if(!isFilled(i)){
            LOG_WARN("No data on input port %s", _port_config.get()[i].portname.c_str());
            return;
        }
        getVector(i, summands[i]);
        weighted_sum += weights(i) * summands[i];
    }
    _weighted_sum.write(weighted_sum);
}


