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

    if(_port_config.get().size() != 1){
        LOG_ERROR("Size of port_config property has to be 1 for this task!");
        return false;
    }

    p = _p.get();

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
}

void NormTask::process(){
    if(isFilled(0)){
        getVector(0,input_data);
        double norm;
        if(p == 1) // Sum norm
            norm = input_data.lpNorm<1>();
        else if(p == 2)
            norm = input_data.lpNorm<2>();
        else if(p == std::numeric_limits<int>::max())
            norm = input_data.lpNorm<Eigen::Infinity>();
        else
            throw std::runtime_error("Invalid norm exponent p: Should be within [1,2,Inf], but is " + std::to_string(p));

        _norm.write(norm);
    }
}

