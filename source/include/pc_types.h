/**
    \file       pc_types.h

    \brief      Common type definitions.

    \author     Hubert Strautz  (h.strautz@intenta.de)
    \data       2014/11/15
 */

#ifndef PC_TYPES_H
#define PC_TYPES_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "pc_types_floating.hpp"
#include "pc_types_results.hpp"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
namespace pc
{

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------

// Character types.
typedef char                char8_t;    ///< Signed 8 bit character type.
typedef unsigned char       uchar8_t;   ///< Unsigned 8 bit character type.

// Unsigned integers.
typedef unsigned char       uint8_t;    ///< 8  bit unsigned type.
typedef unsigned short      uint16_t;   ///< 16 bit unsigned type.
typedef unsigned long       uint32_t;   ///< 32 bit unsigned type.
typedef unsigned long long  uint64_t;   ///< 64 bit unsigned type.

// Signed integers.
typedef signed char         int8_t;     ///< 8  bit signed type.
typedef signed short        int16_t;    ///< 16 bit signed type.
typedef signed long         int32_t;    ///< 32 bit signed type.
typedef signed long long    int64_t;    ///< 64 bit signed type.

// Floating point types are included py pc_types_floating.hpp.

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
} // pc

#endif // PC_TYPES_H