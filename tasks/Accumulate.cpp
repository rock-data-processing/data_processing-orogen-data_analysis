/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Accumulate.hpp"
#include <base/Float.hpp>

using namespace data_analysis;

Accumulate::Accumulate(std::string const& name, TaskCore::TaskState initial_state)
    : AccumulateBase(name, initial_state){
}

Accumulate::Accumulate(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : AccumulateBase(name, engine, initial_state){
}

Accumulate::~Accumulate(){
}

bool Accumulate::configureHook()
{
    if (! AccumulateBase::configureHook())
        return false;

    vect = base::VectorXd(_window_size.get());
    vect.setConstant(base::NaN<double>());
    queue_size = 0;

    return true;
}

bool Accumulate::startHook(){
    if (! AccumulateBase::startHook())
        return false;
    return true;
}

void Accumulate::updateHook(){
    AccumulateBase::updateHook();

    double data_in;
    while(_input_data.read(data_in) == RTT::NewData){

        if(queue_size >= vect.size()){
            for(int i = 1; i < vect.size(); i++)
                vect(i-1) = vect(i);
            vect(vect.size()-1) = data_in;
        }
        else{
            vect(queue_size) = data_in;
            queue_size++;
        }
        _output_data.write(vect);
    }
}

void Accumulate::errorHook(){
    AccumulateBase::errorHook();
}

void Accumulate::stopHook(){
    AccumulateBase::stopHook();
}

void Accumulate::cleanupHook(){
    AccumulateBase::cleanupHook();
}
