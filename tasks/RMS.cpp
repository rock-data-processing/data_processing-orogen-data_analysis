/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "RMS.hpp"
#include <base/Float.hpp>

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

    if(std::isinf((double)_window_size.get()))
        window_size = std::numeric_limits<int>::max();
    else
        window_size = (int)_window_size.get();

    sum = 0;
    n_data = 0;

    return true;
}

bool RMS::startHook(){
    if (! RMSBase::startHook())
        return false;
    return true;
}

void RMS::updateHook(){
    RMSBase::updateHook();

    if(_input_data.readNewest(input_data) == RTT::NewData){

        if(window_size == std::numeric_limits<int>::max()){
            sum += input_data.squaredNorm();
            n_data++;
        }
        else{
            if(queue.size() < window_size) // Fill the queue, if it is not filled yet
                queue.conservativeResize(queue.rows()+1);
            else // Shift queue up
                queue.block(0, 0, queue.rows() - 1, 1) = queue.block(1, 0, queue.rows(), 1);

            queue(queue.rows()-1) = input_data.squaredNorm();
            sum = 0;
            for(int i = 0; i < queue.size(); i++)
                sum += queue(i)*queue(i);
            n_data = queue.size();
        }
        _rms.write(sqrt(sum / (double)n_data));
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
