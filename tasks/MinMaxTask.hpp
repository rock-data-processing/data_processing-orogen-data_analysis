/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef DATA_ANALYSIS_MINMAXTASK_TASK_HPP
#define DATA_ANALYSIS_MINMAXTASK_TASK_HPP

#include "data_analysis/MinMaxTaskBase.hpp"
#include <data_analysis/min_max.hpp>

namespace data_analysis{

    class MinMaxCmpInterface{
    protected:
        std::shared_ptr<MinMax> min_max_cmp;
        std::shared_ptr< RTT::OutputPort<double> > min_port;
        std::shared_ptr< RTT::OutputPort<double> > max_port;
        std::shared_ptr< RTT::OutputPort<double> > min_coef_port;
        std::shared_ptr< RTT::OutputPort<double> > max_coef_port;
        RTT::TaskContext *task_context;

    public:
        MinMaxCmpInterface(const std::string name, const int window_size, RTT::TaskContext* _task_context){
            min_max_cmp = std::make_shared<MinMax>(window_size);

            min_port      = std::make_shared< RTT::OutputPort<double> >("min_" + name);
            max_port      = std::make_shared< RTT::OutputPort<double> >("max_" + name);
            min_coef_port = std::make_shared< RTT::OutputPort<double> >("min_coef_" + name);
            max_coef_port = std::make_shared< RTT::OutputPort<double> >("max_coef_" + name);

            task_context = _task_context;
            task_context->ports()->addPort(min_port->getName(), *min_port);
            task_context->ports()->addPort(max_port->getName(), *max_port);
            task_context->ports()->addPort(min_coef_port->getName(), *min_coef_port);
            task_context->ports()->addPort(max_coef_port->getName(), *max_coef_port);
        }
        ~MinMaxCmpInterface(){
            task_context->ports()->removePort(min_port->getName());
            task_context->ports()->removePort(max_port->getName());
            task_context->ports()->removePort(min_coef_port->getName());
            task_context->ports()->removePort(max_coef_port->getName());
        }

        void update(const base::VectorXd &input_data){
            double min, max;
            min_max_cmp->update(input_data, min, max);
            min_port->write(min);
            max_port->write(max);
            min_coef_port->write(input_data.minCoeff());
            max_coef_port->write(input_data.maxCoeff());
        }

        void reset(const int window_size){
            min_max_cmp.reset();
            min_max_cmp = std::make_shared<MinMax>(window_size);
        }
    };

    /*! \class MinMaxTask
     * \brief The task context provides and requires services. It uses an ExecutionEngine to perform its functions.
     * Essential interfaces are operations, data flow ports and properties. These interfaces have been defined using the oroGen specification.
     * In order to modify the interfaces you should (re)use oroGen and rely on the associated workflow.
     * The max value of each element of the input data stream.
     * \details
     * The name of a TaskContext is primarily defined via:
     \verbatim
     deployment 'deployment_name'
         task('custom_task_name','data_analysis::MinMaxTask')
     end
     \endverbatim
     *  It can be dynamically adapted when the deployment is called with a prefix argument.
     */
    class MinMaxTask : public MinMaxTaskBase
    {
	friend class MinMaxTaskBase;
    protected:

        base::VectorXd input_data;
        std::vector< std::shared_ptr<MinMaxCmpInterface> > cmp_interfaces;
        int window_size;

        /** Process new data samples*/
        virtual void process();
        /** Empty the data queue*/
        virtual void reset();

    public:
        /** TaskContext constructor for MinMaxTask
         * \param name Name of the task. This name needs to be unique to make it identifiable via nameservices.
         * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
         */
        MinMaxTask(std::string const& name = "data_analysis::MinMaxTask");

        /** TaskContext constructor for MinMaxTask
         * \param name Name of the task. This name needs to be unique to make it identifiable for nameservices.
         * \param engine The RTT Execution engine to be used for this task, which serialises the execution of all commands, programs, state machines and incoming events for a task.
         * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
         */
        MinMaxTask(std::string const& name, RTT::ExecutionEngine* engine);

        /** Default deconstructor of MinMaxTask
         */
        ~MinMaxTask();

        /** This hook is called by Orocos when the state machine transitions
         * from PreOperational to Stopped. If it returns false, then the
         * component will stay in PreOperational. Otherwise, it goes into
         * Stopped.
         *
         * It is meaningful only if the #needs_configuration has been specified
         * in the task context definition with (for example):
         \verbatim
         task_context "TaskName" do
           needs_configuration
           ...
         end
         \endverbatim
         */
        bool configureHook();

        /** This hook is called by Orocos when the state machine transitions
         * from Stopped to Running. If it returns false, then the component will
         * stay in Stopped. Otherwise, it goes into Running and updateHook()
         * will be called.
         */
        bool startHook();

        /** This hook is called by Orocos when the component is in the Running
         * state, at each activity step. Here, the activity gives the "ticks"
         * when the hook should be called.
         *
         * The error(), exception() and fatal() calls, when called in this hook,
         * allow to get into the associated RunTimeError, Exception and
         * FatalError states.
         *
         * In the first case, updateHook() is still called, and recover() allows
         * you to go back into the Running state.  In the second case, the
         * errorHook() will be called instead of updateHook(). In Exception, the
         * component is stopped and recover() needs to be called before starting
         * it again. Finally, FatalError cannot be recovered.
         */
        void updateHook();

        /** This hook is called by Orocos when the component is in the
         * RunTimeError state, at each activity step. See the discussion in
         * updateHook() about triggering options.
         *
         * Call recover() to go back in the Runtime state.
         */
        void errorHook();

        /** This hook is called by Orocos when the state machine transitions
         * from Running to Stopped after stop() has been called.
         */
        void stopHook();

        /** This hook is called by Orocos when the state machine transitions
         * from Stopped to PreOperational, requiring the call to configureHook()
         * before calling start() again.
         */
        void cleanupHook();
    };
}

#endif

