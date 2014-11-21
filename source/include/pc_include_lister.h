/**
    \file       pc_include_lister.h

    \brief      Implementation of \ref IncludeLister class.

    \author     Hubert Strautz  (h.strautz@intenta.de)
    \data       2014/11/20
*/

#ifndef INCLUDE_LISTER_H
#define INCLUDE_LISTER_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <vector>
#include <string>

#include "pc_types.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

namespace pc
{

//-----------------------------------------------------------------------------
// IncludeLister
//-----------------------------------------------------------------------------

/**
    \brief  Class that scans a given source file for all included files.
 */
class IncludeLister
{
// Public methods.
public:

    /**
        \brief  Scans a given file for all include files.
        \param[out] includes    List of all include files that were found.
        \param[in]  file        File that shall be scanned.
        \return Result/error code - see also \ref result_t.
     */
    result_t GetIncludesFromFile(std::vector<std::string>& includes,
                                 const std::string& file);

// Private methods.
private:

    /**
        \brief  Scans a given line for a include file.
        \param[out] includes    List of all include files that were found.
        \param[in]  line        Current line that shall be scanned.
        \return Result/error code - see also \ref result_t.
    */
    result_t GetIncludeFromLine(std::vector<std::string>& includes,
                                std::string& line);
}; // IncludeLister

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
} // pc

#endif // INCLUDE_LISTER_H