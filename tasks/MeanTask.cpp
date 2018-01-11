/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "MeanTask.hpp"

using namespace data_analysis;

MeanTask::MeanTask(std::string const& name, TaskCore::TaskState initial_state)
    : MeanTaskBase(name, initial_state){
}

MeanTask::MeanTask(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MeanTaskBase(name, engine, initial_state){
}

MeanTask::~MeanTask(){
}

bool MeanTask::configureHook(){
    if (! MeanTaskBase::configureHook())
        return false;

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

    if(_input_data.readNewest(input_data) == RTT::NewData){
        mean_cmp->update(input_data, mean, std_dev);
        _mean.write(mean);
        _std_dev.write(std_dev);
        _mean_element.write(input_data.mean());
        _n_data.write(mean_cmp->nData());
    }
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
