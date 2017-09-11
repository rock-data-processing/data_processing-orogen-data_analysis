/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Difference.hpp"

using namespace data_analysis;

Difference::Difference(std::string const& name, TaskCore::TaskState initial_state)
    : DifferenceBase(name, initial_state){
}

Difference::Difference(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : DifferenceBase(name, engine, initial_state){
}

Difference::~Difference(){
}

bool Difference::configureHook(){
    if (! DifferenceBase::configureHook())
        return false;
    return true;
}

bool Difference::startHook(){
    if (! DifferenceBase::startHook())
        return false;
    return true;
}

void Difference::updateHook(){
    DifferenceBase::updateHook();

    if(_minuend.readNewest(minuend)       != RTT::NoData &&
       _subtrahend.readNewest(subtrahend) != RTT::NoData)
        _difference.write(minuend-subtrahend);
}

void Difference::errorHook(){
    DifferenceBase::errorHook();
}

void Difference::stopHook(){
    DifferenceBase::stopHook();
}

void Difference::cleanupHook(){
    DifferenceBase::cleanupHook();
}
