/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "NormTask.hpp"

using namespace data_analysis;

NormTask::NormTask(std::string const& name, TaskCore::TaskState initial_state)
    : NormTaskBase(name, initial_state){
}

NormTask::NormTask(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : NormTaskBase(name, engine, initial_state){
}

NormTask::~NormTask(){
}

bool NormTask::configureHook(){
    if (! NormTaskBase::configureHook())
        return false;

    p = _p.get();
    norm_vector.resize(1);

    return true;
}

bool NormTask::startHook(){
    if (! NormTaskBase::startHook())
        return false;
    return true;
}

void NormTask::updateHook(){
    NormTaskBase::updateHook();
    if(_input_data.readNewest(input_data) == RTT::NewData){
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

        norm_vector.setConstant(norm);
        _norm_vector.write(norm_vector);
    }
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
