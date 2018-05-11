/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "AbsTask.hpp"

using namespace data_analysis;

AbsTask::AbsTask(std::string const& name)
    : AbsTaskBase(name){
}

AbsTask::AbsTask(std::string const& name, RTT::ExecutionEngine* engine)
    : AbsTaskBase(name, engine){
}

AbsTask::~AbsTask(){
}

bool AbsTask::configureHook(){
    if (! AbsTaskBase::configureHook())
        return false;

    for(auto c : _port_config.get())
        cmp_interfaces.push_back(std::make_shared<AbsCmpInterface>(c.portname, this));

    return true;
}

bool AbsTask::startHook(){
    if (! AbsTaskBase::startHook())
        return false;
    return true;
}

void AbsTask::updateHook(){
    AbsTaskBase::updateHook();

    for(size_t i = 0; i < _port_config.get().size(); i++){
        base::VectorXd input_data;
        if(isUpdated(i)){
            resetIsUpdated(i);
            getVector(i, input_data);
            cmp_interfaces[i]->update(input_data);
        }
    }
}

void AbsTask::errorHook(){
    AbsTaskBase::errorHook();
}

void AbsTask::stopHook(){
    AbsTaskBase::stopHook();
}

void AbsTask::cleanupHook(){
    AbsTaskBase::cleanupHook();
    cmp_interfaces.clear();
}

void AbsTask::process(){
    /* process() is only triggered if ALL input ports have data. Here, we want to trigger the computation, whenever ANY
     input port has data. Thus, this computation is done in the updateHook() */
}
