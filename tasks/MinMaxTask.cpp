/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "MinMaxTask.hpp"
#include <base-logging/Logging.hpp>

using namespace data_analysis;

MinMaxTask::MinMaxTask(std::string const& name)
    : MinMaxTaskBase(name){
}

MinMaxTask::MinMaxTask(std::string const& name, RTT::ExecutionEngine* engine)
    : MinMaxTaskBase(name, engine){
}

MinMaxTask::~MinMaxTask(){
}

bool MinMaxTask::configureHook(){
    if (! MinMaxTaskBase::configureHook())
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

void MinMaxTask::process(){
    if(isFilled(0)){
        getVector(0,input_data);
        _min_coef.write(input_data.minCoeff());
        _max_coef.write(input_data.maxCoeff());

        double min,max;
        min_max->update(input_data, min, max);
        _min.write(min);
        _max.write(max);
    }
}
