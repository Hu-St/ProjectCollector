/**
\file       pc_include_lister.cpp

\brief      Implementation of \ref IncludeLister class.

\author     Hubert Strautz  (h.strautz@intenta.de)
\data       2014/11/20
*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <fstream>
#include <string>
#include <algorithm>

#include "pc_include_lister.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
using namespace pc;
using namespace std;

//-----------------------------------------------------------------------------
// IncludeLister
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Scans a given file for all include files.
result_t IncludeLister::GetIncludesFromFile(
    vector<string>& includes,
    const string& file)
{
    // Default result value.
    result_t result = (0 == file.size()) ? RESULT_ERROR_INVALID_ARGUMENT : RESULT_SUCCESS;

    // Try to open source file.
    ifstream inputFile;
    if (RESULT_SUCCESS == result)
    {
        // Try to open file.
        inputFile.open(file.c_str(), ios::in);

        // Check if file wasn't opened successful.
        if (false == inputFile.is_open())
        {
            result = RESULT_ERROR_COULD_NOT_OPEN_FILE;
        }
    } // Try to open source file.

    // Read in file.
    if (RESULT_SUCCESS == result)
    {
        // Loop over file.
        while (false == inputFile.eof())
        {
            // Get current line.
            string line;
            getline(inputFile, line);

            // Try to find include file in current line.
            result_t result_last = GetIncludeFromLine(includes, line);

            // Set last error if there occured one.
            if (RESULT_SUCCESS != result_last)
            {
                result = result_last;
            };
        } // Loop over file.

        // Close file.
        inputFile.close();
    } // Read in file.

    return result;
}

//-----------------------------------------------------------------------------
// Scans a given line for a include file.
result_t IncludeLister::GetIncludeFromLine(
    std::vector<std::string>& includes,
    std::string& line)
{
    result_t result = (0 == line.size()) ? RESULT_ERROR_INVALID_ARGUMENT : RESULT_SUCCESS;
    
    // Remove whitespaces and tabs from line.
    line.erase(remove(line.begin(), line.end(), ' '));
    line.erase(remove(line.begin(), line.end(), '\t'));

    // Find include syntax.
    uint32_t position = static_cast<uint32_t>(line.find("#include"));
    if ( (RESULT_SUCCESS == result) &&
         (string::npos != position) )
    {
        // Set string position after include syntax.
        position += 8;

        // Only interessting in non system or libraries includes.
        // These includes shall be identified by #include "file"
        if ('"' == line.at(position))
        {
            // Set start position of file name.
            uint32_t start = ++position;
            uint32_t end = start;

            // Search end position of file name.
            bool isFound = false;
            while ((position < line.size()) &&
                (false == isFound))
            {
                // Check if current char is closing ".
                if ('"' == line.at(position))
                {
                    // Save end position and set flag that end is found.
                    end = position;
                    isFound = true;
                } // Check if current char is closing ".

                ++position;
            } // Search end position of file name.

            // Check for valid include syntax.
            if (true == isFound)
            {
                includes.push_back(line.substr(start, end - start));
            }
            else
            {
                // Return error code.
                result = RESULT_ERROR_NO_END_OF_INCLUDE;
            }
        } // Only interessting in non system or libraries includes.
    } // Find include syntax.

    return result;
}