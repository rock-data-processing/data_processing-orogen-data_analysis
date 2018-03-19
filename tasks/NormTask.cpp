/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "NormTask.hpp"
#include <base-logging/Logging.hpp>

using namespace data_analysis;

NormTask::NormTask(std::string const& name)
    : NormTaskBase(name){
}

NormTask::NormTask(std::string const& name, RTT::ExecutionEngine* engine)
    : NormTaskBase(name, engine){
}

NormTask::~NormTask(){
}

bool NormTask::configureHook(){
    if (! NormTaskBase::configureHook())
        return false;

    for(auto c : _port_config.get())
        cmp_interfaces.push_back(std::make_shared<NormCmpInterface>(c.portname, _p.get(), this));

    return true;
}

bool NormTask::startHook(){
    if (! NormTaskBase::startHook())
        return false;
    return true;
}

void NormTask::updateHook(){
    NormTaskBase::updateHook();
}

void NormTask::errorHook(){
    NormTaskBase::errorHook();
}

void NormTask::stopHook(){
    NormTaskBase::stopHook();
}

void NormTask::cleanupHook(){
    NormTaskBase::cleanupHook();
    cmp_interfaces.clear();
}

void NormTask::process(){
    for(size_t i = 0; i < _port_config.get().size(); i++){
        if(isUpdated(i)){
            resetIsUpdated(i);
            getVector(i, input_data);
            cmp_interfaces[i]->update(input_data);
        }
    }
}

