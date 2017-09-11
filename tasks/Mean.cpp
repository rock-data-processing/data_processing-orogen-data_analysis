/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Mean.hpp"

using namespace data_analysis;

Mean::Mean(std::string const& name, TaskCore::TaskState initial_state)
    : MeanBase(name, initial_state){
}

Mean::Mean(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MeanBase(name, engine, initial_state){
}

Mean::~Mean(){
}

bool Mean::configureHook(){
    if (! MeanBase::configureHook())
        return false;
    return true;
}

bool Mean::startHook(){
    if (! MeanBase::startHook())
        return false;
    return true;
}

void Mean::updateHook(){
    MeanBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData)
        _mean.write(input_data.mean());
}

void Mean::errorHook(){
    MeanBase::errorHook();
}

void Mean::stopHook(){
    MeanBase::stopHook();
}

void Mean::cleanupHook()
{
    MeanBase::cleanupHook();
}
