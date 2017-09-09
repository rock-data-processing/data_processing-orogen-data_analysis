/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Mean.hpp"

using namespace data_analysis;

Mean::Mean(std::string const& name, TaskCore::TaskState initial_state)
    : MeanBase(name, initial_state)
{
}

Mean::Mean(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MeanBase(name, engine, initial_state)
{
}

Mean::~Mean()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Mean.hpp for more detailed
// documentation about them.

bool Mean::configureHook()
{
    if (! MeanBase::configureHook())
        return false;
    return true;
}
bool Mean::startHook()
{
    if (! MeanBase::startHook())
        return false;
    return true;
}
void Mean::updateHook()
{
    MeanBase::updateHook();
}
void Mean::errorHook()
{
    MeanBase::errorHook();
}
void Mean::stopHook()
{
    MeanBase::stopHook();
}
void Mean::cleanupHook()
{
    MeanBase::cleanupHook();
}
