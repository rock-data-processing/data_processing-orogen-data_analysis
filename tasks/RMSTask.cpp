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

    if(std::isinf((double)_window_size.get()))
        window_size = std::numeric_limits<int>::max();
    else
        window_size = (int)_window_size.get();
    for(auto c : _port_config.get())
        cmp_interfaces.push_back(std::make_shared<RMSCmpInterface>(c.portname, window_size, this));

    return true;
}

bool RMSTask::startHook(){
    if (! RMSTaskBase::startHook())
        return false;
    return true;
}

void RMSTask::updateHook(){
    RMSTaskBase::updateHook();
    for(size_t i = 0; i < _port_config.get().size(); i++){
        if(isUpdated(i)){
            resetIsUpdated(i);
            getVector(i, input_data);
            cmp_interfaces[i]->update(input_data);
        }
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
    cmp_interfaces.clear();
}

void RMSTask::process(){
    /* process() is only triggered if ALL input ports have data. Here, we want to trigger the computation, whenever ANY
     input port has data. Thus, this computation is done in the updateHook() */
}

void RMSTask::reset(){
    for(auto &c : cmp_interfaces)
        c->reset(window_size);
}
