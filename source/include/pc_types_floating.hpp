/**
    @file       pc_types_floating.hpp

    @brief      Definitions of floating point types.

    @author     Hubert Strautz  (h.strautz@intenta.de)
    @data       2014/11/15
    @version    0.1
 */

#ifndef PC_TYPES_FLOATING_HPP
#define PC_TYPES_FLOATING_HPP

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cfloat>

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
namespace pc
{

    //-----------------------------------------------------------------------------
    // float32_t
    //-----------------------------------------------------------------------------

    typedef float   float32_t;  ///< 32 bit floating point type.

    /**
        @brief  Epsilon value for the use with 32 bit floating point type (float32_t).
     */
    static const float32_t Float32Eps()
    {
        return static_cast<float32_t>(FLT_MIN);
    }

    /**
        @brief  Compares two 32 bit floating point values (float32_t).
                Two floating point values will be equal,
                if first one is within an epsilon range of the second value - look at float32Eps().

        @param[in]  lhs First 32 bit floating point value.
        @param[in]  rhs Second 32 bit floating point value.
        @return Returns true if both values are equal, else false will be returned.
    */
    bool AreFloat32Equal(const float32_t& lhs, const float32_t& rhs)
    {
        float32_t lower = lhs - Float32Eps();
        float32_t upper = lhs + Float32Eps();

        return ((rhs > lower) && (rhs < upper)) ? true : false;
    }

    //-----------------------------------------------------------------------------
    // float64_t
    //-----------------------------------------------------------------------------

    typedef double  float64_t;  ///< 64 bit floating point type.

    /**
        @brief  Epsilon value for the use with 64 bit floating point type (float64_t).
    */
    static const float64_t Float64Eps()
    {
        return static_cast<float64_t>(DBL_MIN);
    }

    /**
        @brief  Compares two 64 bit floating point values (float64_t).
                Two floating point values will be equal,
                if first one is within an epsilon range of the second value - look at float64Eps().
           
        @param[in]  lhs First 64 bit floating point value.
        @param[in]  rhs Second 64 bit floating point value.
        @return Returns true if both values are equal, else false will be returned.
     */
    bool AreFloat64Equal(const float64_t&lhs, const float64_t& rhs)
    {
        float64_t lower = lhs - Float64Eps();
        float64_t upper = lhs + Float64Eps();

        return ((rhs > lower) && (rhs < upper)) ? true : false;
    }

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
} // pc

#endif // PC_TYPES_FLOATING_HPP