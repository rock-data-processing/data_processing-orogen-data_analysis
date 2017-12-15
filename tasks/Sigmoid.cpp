/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Sigmoid.hpp"
#include <fstream>
#include <iomanip>

using namespace data_analysis;

Sigmoid::Sigmoid(std::string const& name)
    : SigmoidBase(name){
}

Sigmoid::Sigmoid(std::string const& name, RTT::ExecutionEngine* engine)
    : SigmoidBase(name, engine){
}

Sigmoid::~Sigmoid(){
}

bool Sigmoid::configureHook(){
    if (! SigmoidBase::configureHook())
        return false;

    if(_port_config.get().size() != 1){
        LOG_ERROR("Port config size has to be 1!");
        return false;
    }
    sigmoid_params = _sigmoid_params.get();
    sigmoid.resize(sigmoid_params.size());

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
    if(isFilled(0)){
        getVector(0, data);

        if(data.size() != sigmoid_params.size())
            throw std::runtime_error("Size mismatch. Data vector has size " + std::to_string(data.size()) + " but sigmoid params vector has size " + std::to_string(sigmoid_params.size()));

        for(uint i = 0; i < data.size(); i++)
            sigmoid(i) = compute(data(i), sigmoid_params[i]);

        _sigmoid.write(sigmoid);
    }
}

double Sigmoid::compute(const double data_in, const SigmoidParams params){
    return params.lower_asymptote + (params.upper_asymptote - params.lower_asymptote)/(1 + params.initial_value*exp(-params.growth_rate*(data_in - params.hor_shift)));
}

void Sigmoid::writeToFile(::std::string const & filename, double range_min, double range_max, double step_size){
    std::ofstream file;
    file.open(filename.c_str());
    for(double x = range_min; x <= range_max; x += step_size)
        for(int i = 0; i < sigmoid_params.size(); i++)
            file << x << " " << compute(x, sigmoid_params[i]) << std::setprecision(16) << std::endl;
    file.close();
}
