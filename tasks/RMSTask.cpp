/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "RMSTask.hpp"
#include <base-logging/Logging.hpp>

using namespace data_analysis;

RMSTask::RMSTask(std::string const& name)
    : RMSTaskBase(name){
}

RMSTask::RMSTask(std::string const& name, RTT::ExecutionEngine* engine)
    : RMSTaskBase(name, engine){
}

RMSTask::~RMSTask(){
}

bool RMSTask::configureHook(){
    if (! RMSTaskBase::configureHook())
        return false;

    if(_port_config.get().size() != 1){
        LOG_ERROR("Size of port_config property has to be 1 for this task!");
        return false;
    }

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

void RMSTask::process(){
    if(isFilled(0)){
        getVector(0,input_data);
        double rms = rms_cmp->update(input_data);
        _rms.write(rms);
        _norm.write(input_data.norm());
        _n_data.write(rms_cmp->nData());
    }
}

