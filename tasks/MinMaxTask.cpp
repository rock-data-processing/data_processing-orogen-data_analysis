/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "MinMaxTask.hpp"

using namespace data_analysis;

MinMaxTask::MinMaxTask(std::string const& name, TaskCore::TaskState initial_state)
    : MinMaxTaskBase(name, initial_state){
}

MinMaxTask::MinMaxTask(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MinMaxTaskBase(name, engine, initial_state){
}

MinMaxTask::~MinMaxTask(){
}

bool MinMaxTask::configureHook(){
    if (! MinMaxTaskBase::configureHook())
        return false;
    return true;
}

bool MinMaxTask::startHook(){
    if (! MinMaxTaskBase::startHook())
        return false;
    return true;
}

void MinMaxTask::updateHook(){
    MinMaxTaskBase::updateHook();
}

void MinMaxTask::errorHook(){
    MinMaxTaskBase::errorHook();
}

void MinMaxTask::stopHook(){
    MinMaxTaskBase::stopHook();
}

void MinMaxTask::cleanupHook(){
    MinMaxTaskBase::cleanupHook();
}
