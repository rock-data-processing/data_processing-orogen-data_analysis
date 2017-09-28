/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "RMS.hpp"

using namespace data_analysis;

RMS::RMS(std::string const& name, TaskCore::TaskState initial_state)
    : RMSBase(name, initial_state){
}

RMS::RMS(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : RMSBase(name, engine, initial_state){
}

RMS::~RMS(){
}

bool RMS::configureHook(){
    if (! RMSBase::configureHook())
        return false;
    return true;
}

bool RMS::startHook(){
    if (! RMSBase::startHook())
        return false;
    return true;
}

void RMS::updateHook(){
    RMSBase::updateHook();
    while(_input_data.read(input_data) == RTT::NewData){
        double sum = 0;
        for(int i = 0; i < input_data.size(); i++)
            sum += input_data(i)*input_data(i);
        double rms = sum / (double)input_data.size();
        rms = sqrt(rms);
        _rms.write(rms);
    }
}

void RMS::errorHook(){
    RMSBase::errorHook();
}

void RMS::stopHook(){
    RMSBase::stopHook();
}

void RMS::cleanupHook(){
    RMSBase::cleanupHook();
}
