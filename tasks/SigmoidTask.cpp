/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "SigmoidTask.hpp"

using namespace data_analysis;

SigmoidTask::SigmoidTask(std::string const& name, TaskCore::TaskState initial_state)
    : SigmoidTaskBase(name, initial_state){
}

SigmoidTask::SigmoidTask(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : SigmoidTaskBase(name, engine, initial_state){
}

SigmoidTask::~SigmoidTask(){
}

void SigmoidTask::writeToFile(::std::string const & filename, double range_min, double range_max, double step_size){
}

bool SigmoidTask::configureHook(){
    if (! SigmoidTaskBase::configureHook())
        return false;
    return true;
}

bool SigmoidTask::startHook(){
    if (! SigmoidTaskBase::startHook())
        return false;
    return true;
}

void SigmoidTask::updateHook(){
    SigmoidTaskBase::updateHook();
}

void SigmoidTask::errorHook(){
    SigmoidTaskBase::errorHook();
}

void SigmoidTask::stopHook(){
    SigmoidTaskBase::stopHook();
}

void SigmoidTask::cleanupHook(){
    SigmoidTaskBase::cleanupHook();
}
