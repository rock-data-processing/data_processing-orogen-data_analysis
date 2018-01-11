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

    int window_size;
    if(std::isinf((double)_window_size.get()))
        window_size = std::numeric_limits<int>::max();
    else
        window_size = (int)_window_size.get();
    min_max = std::make_shared<MinMax>(window_size);

    return true;
}

bool MinMaxTask::startHook(){
    if (! MinMaxTaskBase::startHook())
        return false;
    return true;
}

void MinMaxTask::updateHook(){
    MinMaxTaskBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData){
        _min_coef.write(input_data.minCoeff());
        _max_coef.write(input_data.maxCoeff());

        double min,max;
        min_max->update(input_data, min, max);
        _min.write(min);
        _max.write(max);
    }
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
