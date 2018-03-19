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
    for(auto c : _port_config.get())
        cmp_interfaces.push_back(std::make_shared<MinMaxCmpInterface>(c.portname, window_size, this));

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
    cmp_interfaces.clear();
}

void MinMaxTask::process(){
    for(size_t i = 0; i < _port_config.get().size(); i++){
        if(isFilled(i)){
            getVector(i, input_data);
            cmp_interfaces[i]->update(input_data);
        }
    }
}
