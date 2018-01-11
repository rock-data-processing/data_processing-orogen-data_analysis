/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Mean.hpp"

using namespace data_analysis;

Mean::Mean(std::string const& name, TaskCore::TaskState initial_state)
    : MeanBase(name, initial_state){
}

Mean::Mean(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MeanBase(name, engine, initial_state){
}

Mean::~Mean(){
}

bool Mean::configureHook(){
    if (! MeanBase::configureHook())
        return false;    

    if(std::isinf((double)_window_size.get()))
        window_size = std::numeric_limits<int>::max();
    else
        window_size = (int)_window_size.get();

    sum.setZero();
    n_data = 0;

    return true;
}

bool Mean::startHook(){
    if (! MeanBase::startHook())
        return false;
    return true;
}

void Mean::updateHook(){
    MeanBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData){

        if(window_size == std::numeric_limits<int>::max()){
            sum += input_data;
            n_data++;
        }
        else{
            if((int)queue.size() < window_size) // Fill the queue, if it is not filled yet
                queue.push_back(input_data);
            else{ // Shift queue up
                for(size_t i = 1; i < queue.size(); i++)
                    queue[i-1] = queue[i];
                queue[queue.size()-1] = input_data;
            }

            sum.setZero();
            for(size_t i = 0; i < queue.size(); i++)
                sum += queue[i];
            n_data = queue.size();
        }
        _mean.write(sum / (double)n_data);
    }
}

void Mean::errorHook(){
    MeanBase::errorHook();
}

void Mean::stopHook(){
    MeanBase::stopHook();
}

void Mean::cleanupHook(){
    MeanBase::cleanupHook();
}
