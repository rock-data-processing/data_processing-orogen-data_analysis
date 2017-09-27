/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "EuclideanNorm.hpp"
#include <limits>

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
    min_norm = INFINITY;
    max_norm = -INFINITY;
    return true;
}

bool EuclideanNorm::startHook(){
    if (! EuclideanNormBase::startHook())
        return false;
    return true;
}

void EuclideanNorm::updateHook(){
    EuclideanNormBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData){
        double norm = input_data.norm();
        if(norm > max_norm)
            max_norm = norm;
        if(norm < min_norm)
            min_norm = norm;

        _norm.write(norm);
        _max_norm.write(max_norm);
        _min_norm.write(min_norm);
    }
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
