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
    for(size_t i = 0; i < _port_config.get().size(); i++){
        if(isUpdated(i)){
            resetIsUpdated(i);
            getVector(i, input_data);
            cmp_interfaces[i]->update(input_data);
        }
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
    cmp_interfaces.clear();
}

void MinMaxTask::process(){
    /* process() is only triggered if ALL input ports have data. Here, we want to trigger the computation, whenever ANY
     input port has data. Thus, this computation is done in the updateHook() */
}

void MinMaxTask::reset(){
    for(auto &c : cmp_interfaces)
        c->reset(window_size);
}

