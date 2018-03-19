/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "DerivativeSGTask.hpp"
#include <data_analysis/sg_derivative.hpp>
#include <math.h>

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

    if(_port_config.get().size() != 1){
        LOG_ERROR("Size of port_config property has to be 1 for this task!");
        return false;
    }

    expected_cycle_time = _expected_cycle_time.get();
    window_size = _window_size.get();
    poly_degree = _poly_degree.get();

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
    if(isUpdated(0)){
        resetIsUpdated(0);

        if(stamp.isNull()){
            stamp = base::Time::now();
            return;
        }
        base::Time start = base::Time::now();
        double cycle_time = (start-stamp).toSeconds();
        stamp = start;

        x_minus_2 = x_minus_1;
        x_minus_1 = x;
        getVector(0,x);

        if(filter_array.empty()){
            for(int i = 0; i < x.size(); i++)
                filter_array.push_back(std::make_shared<SGDerivative>(window_size, poly_degree));
            derivative_sg.resize(filter_array.size());
            derivative.resize(filter_array.size());
        }

        if(x.size() != (int)filter_array.size())
            throw std::runtime_error("Size of input data should be " + std::to_string(filter_array.size()) + "(size of poly_degree vector), but is " + std::to_string(x.size()));

        double delta_t = cycle_time;
        if(!std::isnan(expected_cycle_time))
            delta_t = expected_cycle_time;

        for(size_t i = 0; i < filter_array.size(); i++){
            filter_array[i]->Process(x(i), derivative_sg(i));
            // We have to scale the derivative the cycle time here
            derivative_sg(i) /= delta_t;
        }

        if(!x_minus_2.size() == 0){
            for(size_t i = 0; i < filter_array.size(); i++)
                derivative(i) = (x(i) - x_minus_2(i))/(2*delta_t);
            _derivative.write(derivative);
        }

        _derivative_sg.write(derivative_sg);
        _computation_time.write((base::Time::now() - start).toSeconds());
        _cycle_time.write(cycle_time);

    }
}
