/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "MinValue.hpp"

using namespace data_analysis;

MinValue::MinValue(std::string const& name, TaskCore::TaskState initial_state)
    : MinValueBase(name, initial_state)
{
}

MinValue::MinValue(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : MinValueBase(name, engine, initial_state)
{
}

MinValue::~MinValue()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See MinValue.hpp for more detailed
// documentation about them.

bool MinValue::configureHook()
{
    if (! MinValueBase::configureHook())
        return false;
    return true;
}
bool MinValue::startHook()
{
    if (! MinValueBase::startHook())
        return false;
    return true;
}
void MinValue::updateHook()
{
    MinValueBase::updateHook();
}
void MinValue::errorHook()
{
    MinValueBase::errorHook();
}
void MinValue::stopHook()
{
    MinValueBase::stopHook();
}
void MinValue::cleanupHook()
{
    MinValueBase::cleanupHook();
}
