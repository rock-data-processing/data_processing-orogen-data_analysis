/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "EuclideanNorm.hpp"

using namespace data_analysis;

EuclideanNorm::EuclideanNorm(std::string const& name, TaskCore::TaskState initial_state)
    : EuclideanNormBase(name, initial_state){
}

EuclideanNorm::EuclideanNorm(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : EuclideanNormBase(name, engine, initial_state){
}

EuclideanNorm::~EuclideanNorm(){
}

bool EuclideanNorm::configureHook(){
    if (! EuclideanNormBase::configureHook())
        return false;
    return true;
}

bool EuclideanNorm::startHook(){
    if (! EuclideanNormBase::startHook())
        return false;
    return true;
}

void EuclideanNorm::updateHook(){
    EuclideanNormBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData)
        _norm.write(input_data.norm());
}

void EuclideanNorm::errorHook(){
    EuclideanNormBase::errorHook();
}

void EuclideanNorm::stopHook(){
    EuclideanNormBase::stopHook();
}

void EuclideanNorm::cleanupHook(){
    EuclideanNormBase::cleanupHook();
}
