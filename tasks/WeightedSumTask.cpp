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
        RTT::InputPort<base::VectorXd>* port_vect = new RTT::InputPort<base::VectorXd>("vect_summand_" + std::to_string(i));
        ports()->addEventPort(port_vect->getName(), *port_vect);
        input_ports_vect.push_back(port_vect);

        RTT::InputPort<double>* port_double = new RTT::InputPort<double>("summand_" + std::to_string(i));
        ports()->addEventPort(port_double->getName(), *port_double);
        input_ports_double.push_back(port_double);
    }

    return true;
}

bool WeightedSumTask::startHook(){
    if (! WeightedSumTaskBase::startHook())
        return false;
    return true;
}

void WeightedSumTask::updateHook(){
    WeightedSumTaskBase::updateHook();

    // handle vectors
    base::VectorXd weighted_sum_vect;
    weighted_sum_vect.setZero();
    bool has_all_summands = true;
    for(int i = 0; i < weights.size(); i++){
        base::VectorXd summand;
        if(input_ports_vect[i]->readNewest(summand) == RTT::NoData)
            has_all_summands = false;
        weighted_sum_vect += weights(i)*summand;
    }
    if(has_all_summands)
        _weighted_sum_vect.write(weighted_sum_vect);

    // handle doubles
    double weighted_sum = 0;
    has_all_summands = true;
    for(int i = 0; i < weights.size(); i++){
        double summand;
        if(input_ports_double[i]->readNewest(summand) == RTT::NoData)
            has_all_summands = false;
        weighted_sum += weights(i)*summand;
    }
    if(has_all_summands)
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
    for(auto p : input_ports_vect){
        ports()->removePort(p->getName());
        delete p;
    }
    input_ports_double.clear();
    for(auto p : input_ports_double){
        ports()->removePort(p->getName());
        delete p;
    }
    input_ports_double.clear();
}
