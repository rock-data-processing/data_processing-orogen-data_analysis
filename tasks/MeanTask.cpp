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

    if(std::isinf((double)_window_size.get()))
        window_size = std::numeric_limits<int>::max();
    else
        window_size = (int)_window_size.get();
    for(auto c : _port_config.get())
        cmp_interfaces.push_back(std::make_shared<MeanCmpInterface>(c.portname, window_size, this));

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
    cmp_interfaces.clear();
}

void MeanTask::process(){
    for(size_t i = 0; i < _port_config.get().size(); i++){
        if(isUpdated(i)){
            resetIsUpdated(i);
            getVector(i, input_data);
            cmp_interfaces[i]->update(input_data);
        }
    }
void MeanTask::reset(){
    for(auto &c : cmp_interfaces)
        c->reset(window_size);
}


