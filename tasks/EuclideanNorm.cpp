/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "EuclideanNorm.hpp"

using namespace data_analysis;

EuclideanNorm::EuclideanNorm(std::string const& name, TaskCore::TaskState initial_state)
    : EuclideanNormBase(name, initial_state)
{
}

EuclideanNorm::EuclideanNorm(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : EuclideanNormBase(name, engine, initial_state)
{
}

EuclideanNorm::~EuclideanNorm()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See EuclideanNorm.hpp for more detailed
// documentation about them.

bool EuclideanNorm::configureHook()
{
    if (! EuclideanNormBase::configureHook())
        return false;
    return true;
}
bool EuclideanNorm::startHook()
{
    if (! EuclideanNormBase::startHook())
        return false;
    return true;
}
void EuclideanNorm::updateHook()
{
    EuclideanNormBase::updateHook();
}
void EuclideanNorm::errorHook()
{
    EuclideanNormBase::errorHook();
}
void EuclideanNorm::stopHook()
{
    EuclideanNormBase::stopHook();
}
void EuclideanNorm::cleanupHook()
{
    EuclideanNormBase::cleanupHook();
}
