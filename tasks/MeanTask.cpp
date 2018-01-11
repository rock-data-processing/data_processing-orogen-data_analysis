/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "MeanTask.hpp"
#include <base-logging/Logging.hpp>

using namespace data_analysis;

MeanTask::MeanTask(std::string const& name)
    : MeanTaskBase(name){
}

MeanTask::MeanTask(std::string const& name, RTT::ExecutionEngine* engine)
    : MeanTaskBase(name, engine){
}

MeanTask::~MeanTask(){
}

bool MeanTask::configureHook(){
    if (! MeanTaskBase::configureHook())
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
    mean_cmp = std::make_shared<Mean>(window_size);

    return true;
}

bool MeanTask::startHook(){
    if (! MeanTaskBase::startHook())
        return false;
    return true;
}

void MeanTask::updateHook(){
    MeanTaskBase::updateHook();
}

void MeanTask::errorHook(){
    MeanTaskBase::errorHook();
}

void MeanTask::stopHook(){
    MeanTaskBase::stopHook();
}

void MeanTask::cleanupHook(){
    MeanTaskBase::cleanupHook();
    mean_cmp.reset();
}

void MeanTask::process(){
    if(isFilled(0)){
        getVector(0,input_data);
        mean_cmp->update(input_data, mean, std_dev);
        _mean.write(mean);
        _std_dev.write(std_dev);
        _mean_element.write(input_data.mean());
        _n_data.write(mean_cmp->nData());
    }
}

