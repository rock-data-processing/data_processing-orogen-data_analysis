/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "WeightedSum.hpp"

using namespace data_analysis;

WeightedSum::WeightedSum(std::string const& name, TaskCore::TaskState initial_state)
    : WeightedSumBase(name, initial_state){
}

WeightedSum::WeightedSum(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : WeightedSumBase(name, engine, initial_state){
}

WeightedSum::~WeightedSum(){
}

bool WeightedSum::configureHook()
{
    if (! WeightedSumBase::configureHook())
        return false;

    weights = _weights.get();
    for(int i = 0; i <  weights.size(); i++){
        PortInterface *pi = new PortInterface(i, this);
        input_ports.push_back(pi);
    }
    return true;
}

bool WeightedSum::startHook(){
    if (! WeightedSumBase::startHook())
        return false;
    return true;
}

void WeightedSum::updateHook(){
    WeightedSumBase::updateHook();

    for(size_t i = 0; i < input_ports.size(); i++){
        PortInterface* pi = input_ports[i];
        if(!pi->new_data){
            if(pi->port->read(pi->value) == RTT::NewData){
                pi->new_data = true;
            }
        }
    }

    bool all_data = true;
    for(size_t i = 0; i < input_ports.size(); i++)
        all_data = all_data && input_ports[i]->new_data;

    if(all_data){
        double weighted_sum = 0;
        for(size_t i = 0; i < input_ports.size(); i++){
            weighted_sum += weights(i) * input_ports[i]->value;
            input_ports[i]->new_data = false;
        }
        _weighted_sum.write(weighted_sum);
    }
}

void WeightedSum::errorHook(){
    WeightedSumBase::errorHook();
}

void WeightedSum::stopHook(){
    WeightedSumBase::stopHook();
}

void WeightedSum::cleanupHook(){
    WeightedSumBase::cleanupHook();

     for(size_t i = 0; i < input_ports.size(); i++)
        delete input_ports[i];
    input_ports.clear();
}
