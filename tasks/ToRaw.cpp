/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "ToRaw.hpp"

using namespace data_analysis;

ToRaw::ToRaw(std::string const& name)
    : ToRawBase(name)
{
}

ToRaw::ToRaw(std::string const& name, RTT::ExecutionEngine* engine)
    : ToRawBase(name, engine)
{
}

ToRaw::~ToRaw()
{
}

bool ToRaw::configureHook()
{
    if (! ToRawBase::configureHook())
        return false;

    for(auto p : _port_config.get()){
        RTT::OutputPort<base::VectorXd>* port = new RTT::OutputPort<base::VectorXd>("raw_" + p.portname);
        ports()->addPort(port->getName(), *port);
        output_ports.push_back(port);
    }

    data.resize(output_ports.size());

    return true;
}

bool ToRaw::startHook()
{
    if (! ToRawBase::startHook())
        return false;
    return true;
}

void ToRaw::updateHook()
{
    ToRawBase::updateHook();
}

void ToRaw::errorHook()
{
    ToRawBase::errorHook();
}

void ToRaw::stopHook()
{
    ToRawBase::stopHook();
}

void ToRaw::cleanupHook()
{
    ToRawBase::cleanupHook();

    for(auto p : output_ports){
        ports()->removePort(p->getName());
        delete p;
    }
    output_ports.clear();
}

void ToRaw::process(){
    for(size_t i = 0; i < output_ports.size(); i++){
        if(isFilled(i)){
            getVector(i, data[i]);
            output_ports[i]->write(data[i]);
        }
    }
}
