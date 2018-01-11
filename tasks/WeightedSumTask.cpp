/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "WeightedSumTask.hpp"

using namespace data_analysis;

WeightedSumTask::WeightedSumTask(std::string const& name, TaskCore::TaskState initial_state)
    : WeightedSumTaskBase(name, initial_state){
}

WeightedSumTask::WeightedSumTask(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : WeightedSumTaskBase(name, engine, initial_state){
}

WeightedSumTask::~WeightedSumTask(){
}

bool WeightedSumTask::configureHook(){
    if (! WeightedSumTaskBase::configureHook())
        return false;

    weights = _weights.get();
    for(int i = 0; i < weights.size(); i++){
        RTT::InputPort<base::VectorXd>* port = new RTT::InputPort<base::VectorXd>("summand_" + std::to_string(i));
        ports()->addEventPort(port->getName(), *port);
        input_ports.push_back(port);
    }
    summands.resize(weights.size());

    return true;
}

bool WeightedSumTask::startHook(){
    if (! WeightedSumTaskBase::startHook())
        return false;
    return true;
}

void WeightedSumTask::updateHook(){
    WeightedSumTaskBase::updateHook();

    weighted_sum.setZero();
    for(int i = 0; i < weights.size(); i++){
        if(input_ports[i]->readNewest(summands[i]) == RTT::NoData)
            return;
        weighted_sum += weights(i)*summands[i];
    }
    _weighted_sum.write(weighted_sum);
}

void WeightedSumTask::errorHook(){
    WeightedSumTaskBase::errorHook();
}

void WeightedSumTask::stopHook(){
    WeightedSumTaskBase::stopHook();
}

void WeightedSumTask::cleanupHook(){
    WeightedSumTaskBase::cleanupHook();
    for(auto p : input_ports){
        ports()->removePort(p->getName());
        delete p;
    }
    input_ports.clear();
}
