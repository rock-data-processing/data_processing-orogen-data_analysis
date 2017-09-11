/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "MaxValue.hpp"

using namespace data_analysis;

MaxValue::MaxValue(std::string const& name, TaskCore::TaskState initial_state)
    : MaxValueBase(name, initial_state){
}

MaxValue::MaxValue(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MaxValueBase(name, engine, initial_state){
}

MaxValue::~MaxValue(){
}

bool MaxValue::configureHook(){
    if (! MaxValueBase::configureHook())
        return false;
    return true;
}

bool MaxValue::startHook(){
    if (! MaxValueBase::startHook())
        return false;
    return true;
}

void MaxValue::updateHook(){
    MaxValueBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData)
        _max_value.write(input_data.maxCoeff());
}

void MaxValue::errorHook(){
    MaxValueBase::errorHook();
}

void MaxValue::stopHook(){
    MaxValueBase::stopHook();
}

void MaxValue::cleanupHook(){
    MaxValueBase::cleanupHook();
}
