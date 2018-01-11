/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Norm.hpp"
#include "type_to_vector/TypeToVectorTypes.hpp"
#include <base/Float.hpp>

using namespace data_analysis;

Norm::Norm(std::string const& name, TaskCore::TaskState initial_state)
    : NormBase(name, initial_state){
}

Norm::Norm(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : NormBase(name, engine, initial_state){
}

Norm::~Norm(){
}

bool Norm::configureHook(){
    if (! NormBase::configureHook())
        return false;

    p = _p.get();
    norm_vector.resize(1);

    return true;
}

bool Norm::startHook(){
    if (! NormBase::startHook())
        return false;
    return true;
}
void Norm::updateHook(){
    NormBase::updateHook();
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

void Norm::errorHook(){
    NormBase::errorHook();
}

void Norm::stopHook(){
    NormBase::stopHook();
}

void Norm::cleanupHook(){
    NormBase::cleanupHook();
}
