/**
    \file       pc_types_results.hpp

    \brief      Definitions of error type and codes and implementation of helper functions.

    \author     Hubert Strautz  (h.strautz@intenta.de)
    \data       2014/11/17
*/

#ifndef PC_TYPES_RESULTS_HPP
#define PC_TYPES_RESULTS_HPP

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
namespace pc
{
/**
    \brief  Type definition for result and error codes.
 */
enum result_t
{
    // General
    RESULT_SUCCESS      =  0,   ///< No errors occurs duering processing.
    RESULT_ERROR_BASE   = -1,   ///< Error base to generate further error codes.

    // Error codes
    RESULT_ERROR_INVALID_ARGUMENT       = RESULT_ERROR_BASE | 1,
    RESULT_ERROR_COULD_NOT_OPEN_DIR     = RESULT_ERROR_BASE | 2,
    RESULT_ERROR_COULD_GET_DIR_CONTENT  = RESULT_ERROR_BASE | 3
}; // result_t

//-----------------------------------------------------------------------------
// Helper functions
//-----------------------------------------------------------------------------

/**
    \brief  Cheks if an result is successful.
    \param[in]  result  Input result code.
    \return Returns true if result is RESULT_SUCCESS, else true will be returned.
 */
static bool IsResultSuccessful(const result_t& result)
{
    return  (result == RESULT_SUCCESS) ? true : false;
}

/**
    \brief  Generates a desired error code if boolean expression is fulfilled.
    \param[in]  condition   Condition that shall be fulfilled.
    \param[in]  errorCode   Desired error code that shall be returned if condition is fulfilled.
    \return If condition is fulfilled errorCode will be returned, else RESULT_SUCCESS will be returned.
 */
static result_t GenerateErrorIf(const bool& condition, const result_t& errorCode)
{
    return (true == condition) ? errorCode : RESULT_SUCCESS;
}

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
} // pc

#endif // PC_TYPES_RESULTS_HPP