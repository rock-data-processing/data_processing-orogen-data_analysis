/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef DATA_ANALYSIS_MEANTASK_TASK_HPP
#define DATA_ANALYSIS_MEANTASK_TASK_HPP

#include "data_analysis/MeanTaskBase.hpp"
#include <data_analysis/mean.hpp>

namespace data_analysis{

    class MeanCmpInterface{
    protected:
        std::shared_ptr<Mean> mean_cmp;
        std::shared_ptr< RTT::OutputPort<base::VectorXd> > mean_port;
        std::shared_ptr< RTT::OutputPort<base::VectorXd> > std_dev_port;
        std::shared_ptr< RTT::OutputPort<double> > mean_element_port;
        base::VectorXd mean, std_dev;
        RTT::TaskContext *task_context;

    public:
        MeanCmpInterface(const std::string name, const int window_size, RTT::TaskContext* _task_context){
            mean_cmp          = std::make_shared<Mean>(window_size);

            mean_port         = std::make_shared< RTT::OutputPort<base::VectorXd> >("mean_" + name);
            std_dev_port      = std::make_shared< RTT::OutputPort<base::VectorXd> >("std_dev_" + name);
            mean_element_port = std::make_shared< RTT::OutputPort<double> >("mean_element_" + name);

            task_context = _task_context;
            task_context->ports()->addPort(mean_port->getName(), *mean_port);
            task_context->ports()->addPort(std_dev_port->getName(), *std_dev_port);
            task_context->ports()->addPort(mean_element_port->getName(), *mean_element_port);
        }
        ~MeanCmpInterface(){
            task_context->ports()->removePort(mean_port->getName());
            task_context->ports()->removePort(std_dev_port->getName());
            task_context->ports()->removePort(mean_element_port->getName());
        }

        void update(const base::VectorXd &input_data){
            mean_cmp->update(input_data, mean, std_dev);
            mean_port->write(mean);
            std_dev_port->write(std_dev);
            mean_element_port->write(input_data.mean());
        }

        void reset(const int window_size){
            mean_cmp.reset();
            mean_cmp = std::make_shared<Mean>(window_size);
        }
    };

    /*! \class MeanTask
     * \brief The task context provides and requires services. It uses an ExecutionEngine to perform its functions.
     * Essential interfaces are operations, data flow ports and properties. These interfaces have been defined using the oroGen specification.
     * In order to modify the interfaces you should (re)use oroGen and rely on the associated workflow.
     * Compute mean and std. dev. of the input data stream
     * \details
     * The name of a TaskContext is primarily defined via:
     \verbatim
     deployment 'deployment_name'
         task('custom_task_name','data_analysis::MeanTask')
     end
     \endverbatim
     *  It can be dynamically adapted when the deployment is called with a prefix argument.
     */
    class MeanTask : public MeanTaskBase
    {
	friend class MeanTaskBase;
    protected:
        base::VectorXd input_data;
        std::vector< std::shared_ptr<MeanCmpInterface> > cmp_interfaces;
        int window_size;

        /** Process new data samples*/
        virtual void process();
        /** Empty the data queue*/
        virtual void reset();

    public:
        /** TaskContext constructor for MeanTask
         * \param name Name of the task. This name needs to be unique to make it identifiable via nameservices.
         * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
         */
        MeanTask(std::string const& name = "data_analysis::MeanTask");

        /** TaskContext constructor for MeanTask
         * \param name Name of the task. This name needs to be unique to make it identifiable for nameservices.
         * \param engine The RTT Execution engine to be used for this task, which serialises the execution of all commands, programs, state machines and incoming events for a task.
         * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
         */
        MeanTask(std::string const& name, RTT::ExecutionEngine* engine);

        /** Default deconstructor of MeanTask
         */
        ~MeanTask();

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

