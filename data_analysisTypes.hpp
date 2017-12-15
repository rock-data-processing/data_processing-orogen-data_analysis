#ifndef data_analysis_TYPES_HPP
#define data_analysis_TYPES_HPP

/* If you need to define types specific to your oroGen components, define them
 * here. Required headers must be included explicitly
 *
 * However, it is common that you will only import types from your library, in
 * which case you do not need this file
 */

#include <limits>
#include <Eigen/Core>
#include <base/Eigen.hpp>

namespace data_analysis {

/** Parameters defining a 1-dim. Sigmoid function*/
struct SigmoidParams{
    SigmoidParams() :
        lower_asymptote(0.0),
        upper_asymptote(1.0),
        growth_rate(1.0),
        hor_shift(0.0),
        initial_value(1.0){}

    /** The lower Asymptote of the Sigmoid function*/
    double lower_asymptote;
    /** The upper Asymptote of the Sigmoid function*/
    double upper_asymptote;
    /** The growth rate of the Sigmoid function*/
    double growth_rate;
    /** The Horizontal shift of the Sigmoid function*/
    double hor_shift;
    /** The initial value  of the Sigmoid function*/
    double initial_value;
};
}

#endif

