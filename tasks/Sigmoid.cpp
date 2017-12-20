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

bool Sigmoid::configureHook(){
    if (! SigmoidBase::configureHook())
        return false;

    sigmoid_params = _sigmoid_params.get();

    return true;
}

bool Sigmoid::startHook(){
    if (! SigmoidBase::startHook())
        return false;
    return true;
}

void Sigmoid::updateHook(){
    SigmoidBase::updateHook();
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

void Sigmoid::process(){
    while(_input_data.read(data) == RTT::NewData)
        _sigmoid.write(compute(data, sigmoid_params));
}

double Sigmoid::compute(const double data_in, const SigmoidParams params){
    return params.lower_asymptote + (params.upper_asymptote - params.lower_asymptote)/(1 + params.initial_value*exp(-params.growth_rate*(data_in - params.hor_shift)));
}

void Sigmoid::writeToFile(::std::string const & filename, double range_min, double range_max, double step_size){
    std::ofstream file;
    file.open(filename.c_str());
    for(double x = range_min; x <= range_max; x += step_size)
        file << x << " " << compute(x, sigmoid_params) << std::setprecision(16) << std::endl;
    file.close();
}
