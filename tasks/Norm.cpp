/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Norm.hpp"
#include "type_to_vector/TypeToVectorTypes.hpp"
#include <base/Float.hpp>

using namespace data_analysis;

Norm::Norm(std::string const& name)
    : NormBase(name){
}

Norm::Norm(std::string const& name, RTT::ExecutionEngine* engine)
    : NormBase(name, engine){
}

Norm::~Norm(){
}

bool Norm::configureHook(){
    if (! NormBase::configureHook())
        return false;

    p = _p.get();
    std::vector<type_to_vector::PortConfig> port_config = _port_config.get();

    for(auto p : port_config)
        norm_interfaces.push_back(std::make_shared<NormInterface>(p.portname, this));

    data_vectors.resize(port_config.size());
    return true;
}

bool Norm::startHook(){
    if (! NormBase::startHook())
        return false;
    return true;
}
void Norm::updateHook(){
    NormBase::updateHook();
}

void Norm::errorHook(){
    NormBase::errorHook();
}

void Norm::stopHook(){
    NormBase::stopHook();
}

void Norm::cleanupHook(){
    NormBase::cleanupHook();
    norm_interfaces.clear();
}

void Norm::process(){
    for(int i = 0; i < getDataVectorCount(); i++){
        if(isFilled(i)){
            getVector(i, data_vectors[i]);
            norm_interfaces[i]->computeAndWrite(data_vectors[i], p);
        }
    }
}
