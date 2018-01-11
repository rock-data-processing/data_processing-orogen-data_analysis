/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "MinMax.hpp"

using namespace data_analysis;

MinMax::MinMax(std::string const& name, TaskCore::TaskState initial_state)
    : MinMaxBase(name, initial_state)
{
}

MinMax::MinMax(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MinMaxBase(name, engine, initial_state)
{
}

MinMax::~MinMax()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See MinMax.hpp for more detailed
// documentation about them.

bool MinMax::configureHook()
{
    if (! MinMaxBase::configureHook())
        return false;
    return true;
}
bool MinMax::startHook()
{
    if (! MinMaxBase::startHook())
        return false;
    return true;
}
void MinMax::updateHook()
{
    MinMaxBase::updateHook();
}
void MinMax::errorHook()
{
    MinMaxBase::errorHook();
}
void MinMax::stopHook()
{
    MinMaxBase::stopHook();
}
void MinMax::cleanupHook()
{
    MinMaxBase::cleanupHook();
}
