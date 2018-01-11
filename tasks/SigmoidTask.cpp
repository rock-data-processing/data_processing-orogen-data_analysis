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

bool SigmoidTask::configureHook(){
    if (! SigmoidTaskBase::configureHook())
        return false;

    sigmoid.setParams(_sigmoid_params.get());

    return true;
}

bool SigmoidTask::startHook(){
    if (! SigmoidTaskBase::startHook())
        return false;
    return true;
}

void SigmoidTask::updateHook(){
    SigmoidTaskBase::updateHook();

    double input_data;
    if(_input_data.readNewest(input_data) == RTT::NewData)
        _sigmoid.write(sigmoid.compute(input_data));
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

void SigmoidTask::writeToFile(::std::string const & filename, double range_min, double range_max, double step_size){
    sigmoid.writeToFile(filename, range_min, range_max, step_size);
}
