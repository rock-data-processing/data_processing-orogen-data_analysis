/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Difference.hpp"

using namespace data_analysis;

Difference::Difference(std::string const& name, TaskCore::TaskState initial_state)
    : DifferenceBase(name, initial_state)
{
}

Difference::Difference(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : DifferenceBase(name, engine, initial_state)
{
}

Difference::~Difference()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Difference.hpp for more detailed
// documentation about them.

bool Difference::configureHook()
{
    if (! DifferenceBase::configureHook())
        return false;
    return true;
}
bool Difference::startHook()
{
    if (! DifferenceBase::startHook())
        return false;
    return true;
}
void Difference::updateHook()
{
    DifferenceBase::updateHook();
}
void Difference::errorHook()
{
    DifferenceBase::errorHook();
}
void Difference::stopHook()
{
    DifferenceBase::stopHook();
}
void Difference::cleanupHook()
{
    DifferenceBase::cleanupHook();
}
