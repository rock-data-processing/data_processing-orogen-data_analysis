/* Generated from orogen/lib/orogen/templates/tasks/Task.hpp */

#ifndef DATA_ANALYSIS_NORM_TASK_HPP
#define DATA_ANALYSIS_NORM_TASK_HPP

#include "data_analysis/NormBase.hpp"

namespace data_analysis{

    /*! \class Norm
     * \brief The task context provides and requires services. It uses an ExecutionEngine to perform its functions.
     * Essential interfaces are operations, data flow ports and properties. These interfaces have been defined using the oroGen specification.
     * In order to modify the interfaces you should (re)use oroGen and rely on the associated workflow.
     * Compute the lp norm of the input data stream
     * \details
     * The name of a TaskContext is primarily defined via:
     \verbatim
     deployment 'deployment_name'
         task('custom_task_name','data_analysis::Norm')
     end
     \endverbatim
     *  It can be dynamically adapted when the deployment is called with a prefix argument.
     */
    class Norm : public NormBase
    {
	friend class NormBase;
    protected:

        struct NormInterface{
            NormInterface(const std::string& name,
                          RTT::TaskContext *task) :
                task_context(task){
                port = new RTT::OutputPort<double>("norm_" + name);
                task_context->ports()->addPort(port->getName(), *port);
            }
            ~NormInterface(){
                task_context->ports()->removePort(port->getName());
                delete port;
            }
            void computeAndWrite(const base::VectorXd &data, const double p){
                double norm;
                if(p == 1)
                    norm = data.lpNorm<1>();
                else if(p == 2)
                    norm = data.lpNorm<2>();
                else if(p == std::numeric_limits<double>::infinity())
                    norm = data.lpNorm<Eigen::Infinity>();
                else
                    throw std::runtime_error("Invalid norm. Allowed values are p = 1,2,inf");

                port->write(norm);
            }
            RTT::OutputPort<double> *port;
            RTT::TaskContext *task_context;
        };
        typedef std::shared_ptr<NormInterface> NormInterfacePtr;

        /** Implementation from base class*/
        virtual void process();

        std::vector<NormInterfacePtr> norm_interfaces;
        std::vector<base::VectorXd> data_vectors;
        double p;

    public:
        /** TaskContext constructor for Norm
         * \param name Name of the task. This name needs to be unique to make it identifiable via nameservices.
         * \param initial_state The initial TaskState of the TaskContext. Default is Stopped state.
         */
        Norm(std::string const& name = "data_analysis::Norm");

        /** TaskContext constructor for Norm
         * \param name Name of the task. This name needs to be unique to make it identifiable for nameservices.
         * \param engine The RTT Execution engine to be used for this task, which serialises the execution of all commands, programs, state machines and incoming events for a task.
         * 
         */
        Norm(std::string const& name, RTT::ExecutionEngine* engine);

        /** Default deconstructor of Norm
         */
	~Norm();

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

