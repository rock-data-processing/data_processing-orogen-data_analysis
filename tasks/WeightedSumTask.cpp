/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "WeightedSumTask.hpp"
#include <base-logging/Logging.hpp>

using namespace data_analysis;

WeightedSumTask::WeightedSumTask(std::string const& name)
    : WeightedSumTaskBase(name){
}

WeightedSumTask::WeightedSumTask(std::string const& name, RTT::ExecutionEngine* engine)
    : WeightedSumTaskBase(name, engine){
}

WeightedSumTask::~WeightedSumTask(){
}

bool WeightedSumTask::configureHook(){
    if (! WeightedSumTaskBase::configureHook())
        return false;

    weights = _weights.get();
    if((int)_port_config.get().size() != weights.size()){
        LOG_ERROR("Size of port_config property has to be same as size of weight vector!");
        return false;
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
}

void WeightedSumTask::errorHook(){
    WeightedSumTaskBase::errorHook();
}

void WeightedSumTask::stopHook(){
    WeightedSumTaskBase::stopHook();
}

void WeightedSumTask::cleanupHook(){
    WeightedSumTaskBase::cleanupHook();
}

void WeightedSumTask::process(){
    // handle vectors
    weighted_sum.setZero();
    bool has_all_summands = true;
    for(int i = 0; i < weights.size(); i++){
        if(!isFilled(i))
            has_all_summands = false;
        base::VectorXd summand;
        getVector(i,summand);

        if(weighted_sum.size() == 0){
            weighted_sum.resize(summand.size());
            weighted_sum.setZero();
        }

        if(weighted_sum.size() != summand.size())
            throw std::runtime_error("Summand " + std::to_string(i) + " has size " + std::to_string(summand.size()) + " but should have size " + std::to_string(weighted_sum.size()));

        weighted_sum += weights(i)*summand;
    }
    if(has_all_summands)
        _weighted_sum.write(weighted_sum);
}
