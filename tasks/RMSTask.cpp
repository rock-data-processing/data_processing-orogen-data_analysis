/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "RMSTask.hpp"

using namespace data_analysis;

RMSTask::RMSTask(std::string const& name, TaskCore::TaskState initial_state)
    : RMSTaskBase(name, initial_state){
}

RMSTask::RMSTask(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : RMSTaskBase(name, engine, initial_state){
}

RMSTask::~RMSTask(){
}

bool RMSTask::configureHook(){
    if (! RMSTaskBase::configureHook())
        return false;

    int window_size;
    if(std::isinf((double)_window_size.get()))
        window_size = std::numeric_limits<int>::max();
    else
        window_size = (int)_window_size.get();
    rms_cmp = std::make_shared<RMS>(window_size);

    return true;
}

bool RMSTask::startHook(){
    if (! RMSTaskBase::startHook())
        return false;
    return true;
}

void RMSTask::updateHook(){
    RMSTaskBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData){
        double rms = rms_cmp->update(input_data);
        _rms.write(rms);
        _n_data.write(rms_cmp->nData());
    }
}

void RMSTask::errorHook(){
    RMSTaskBase::errorHook();
}

void RMSTask::stopHook(){
    RMSTaskBase::stopHook();
}

void RMSTask::cleanupHook(){
    RMSTaskBase::cleanupHook();
    rms_cmp.reset();
}
