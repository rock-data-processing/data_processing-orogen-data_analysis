/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Abs.hpp"

using namespace data_analysis;

Abs::Abs(std::string const& name, TaskCore::TaskState initial_state)
    : AbsBase(name, initial_state){
}

Abs::Abs(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : AbsBase(name, engine, initial_state){
}

Abs::~Abs(){
}

bool Abs::configureHook(){
    if (! AbsBase::configureHook())
        return false;
    return true;
}

bool Abs::startHook(){
    if (! AbsBase::startHook())
        return false;
    return true;
}

void Abs::updateHook(){
    AbsBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData)
        _abs.write(input_data.cwiseAbs());
}

void Abs::errorHook(){
    AbsBase::errorHook();
}

void Abs::stopHook(){
    AbsBase::stopHook();
}

void Abs::cleanupHook(){
    AbsBase::cleanupHook();
}
