/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Sum.hpp"

using namespace data_analysis;

Sum::Sum(std::string const& name, TaskCore::TaskState initial_state)
    : SumBase(name, initial_state){
}

Sum::Sum(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : SumBase(name, engine, initial_state){
}

Sum::~Sum(){
}

bool Sum::configureHook(){
    if (! SumBase::configureHook())
        return false;
    return true;
}

bool Sum::startHook(){
    if (! SumBase::startHook())
        return false;
    return true;
}

void Sum::updateHook(){
    SumBase::updateHook();

    if(_summand_one.readNewest(summand_one) != RTT::NoData &&
       _summand_two.readNewest(summand_two) != RTT::NoData)
        _sum.write(summand_one+summand_two);
}

void Sum::errorHook(){
    SumBase::errorHook();
}

void Sum::stopHook(){
    SumBase::stopHook();
}

void Sum::cleanupHook(){
    SumBase::cleanupHook();
}
