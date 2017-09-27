/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Sigmoid.hpp"
#include <fstream>
#include <iomanip>

using namespace data_analysis;

Sigmoid::Sigmoid(std::string const& name, TaskCore::TaskState initial_state)
    : SigmoidBase(name, initial_state){
}

Sigmoid::Sigmoid(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : SigmoidBase(name, engine, initial_state){
}

Sigmoid::~Sigmoid(){
}

void Sigmoid::writeToFile(const std::string &filename, double range_min, double range_max, double step_size){
    std::ofstream file;
    file.open(filename.c_str());
    for(double x = range_min; x <= range_max; x += step_size)
        file << x << " " << compute(x) << std::setprecision(16) << std::endl;
    file.close();
}

double Sigmoid::compute(double data_in){
    return lower_asymptote + (upper_asymptote - lower_asymptote)/(1 + initial_value*exp(-growth_rate*(data_in - hor_shift)));
}

bool Sigmoid::configureHook(){
    if (! SigmoidBase::configureHook())
        return false;

    lower_asymptote = _lower_asymptote.get();
    upper_asymptote = _upper_asymptote.get();
    growth_rate = _growth_rate.get();
    hor_shift = _hor_shift.get();
    initial_value = _initial_value.get();

    return true;
}

bool Sigmoid::startHook(){
    if (! SigmoidBase::startHook())
        return false;
    return true;
}

void Sigmoid::updateHook(){
    SigmoidBase::updateHook();

    double data_in;
    while(_input_data.read(data_in) == RTT::NewData)
        _sigmoid.write(compute(data_in));
}

void Sigmoid::errorHook(){
    SigmoidBase::errorHook();
}

void Sigmoid::stopHook(){
    SigmoidBase::stopHook();
}

void Sigmoid::cleanupHook(){
    SigmoidBase::cleanupHook();
}
