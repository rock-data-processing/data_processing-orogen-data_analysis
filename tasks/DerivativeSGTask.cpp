/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "DerivativeSGTask.hpp"
#include <data_analysis/sg_smooth.hpp>

using namespace data_analysis;

DerivativeSGTask::DerivativeSGTask(std::string const& name)
    : DerivativeSGTaskBase(name){
}

DerivativeSGTask::DerivativeSGTask(std::string const& name, RTT::ExecutionEngine* engine)
    : DerivativeSGTaskBase(name, engine){
}

DerivativeSGTask::~DerivativeSGTask(){
}

bool DerivativeSGTask::configureHook(){
    if (! DerivativeSGTaskBase::configureHook())
        return false;

    return true;
}

bool DerivativeSGTask::startHook(){
    if (! DerivativeSGTaskBase::startHook())
        return false;
    return true;
}

void DerivativeSGTask::updateHook(){
    DerivativeSGTaskBase::updateHook();
}

void DerivativeSGTask::errorHook(){
    DerivativeSGTaskBase::errorHook();
}

void DerivativeSGTask::stopHook(){
    DerivativeSGTaskBase::stopHook();
}

void DerivativeSGTask::cleanupHook(){
    DerivativeSGTaskBase::cleanupHook();
    filter_array.clear();
}

void DerivativeSGTask::process(){
    if(isFilled(0)){

        if(stamp.isNull()){
            stamp = base::Time::now();
            return;
        }
        base::Time start = base::Time::now();
        double diff = (start-stamp).toSeconds();
        stamp = start;

        getVector(0,input_data);

        if(filter_array.empty()){
            for(int i = 0; i < input_data.size(); i++)
                filter_array.push_back(std::make_shared<SGDerivative>(_window_size.get(), _poly_degree.get()));
            derivative.resize(filter_array.size());
        }

        if(input_data.size() != (int)filter_array.size())
            throw std::runtime_error("Size of input data should be " + std::to_string(filter_array.size()) + "(size of poly_degree vector), but is " + std::to_string(input_data.size()));

        for(size_t i = 0; i < filter_array.size(); i++){
            filter_array[i]->Process(input_data(i), derivative(i));
            // We have to scale the derivative the cycle time here
            derivative(i) /= diff;
        }
        _derivative.write(derivative);
        _computation_time.write((base::Time::now() - start).toSeconds());
        _cycle_time.write(diff);

    }
}
