/**
    \file       pc_file_lister.h

    \brief      Implementation of \ref FileLister class.

    \author     Hubert Strautz  (h.strautz@intenta.de)
    \data       2014/11/18
*/

#ifndef PC_FILE_LISTER_H
#define PC_FILE_LISTER_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <vector>
#include <string>

#include "pc_types.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------

/**
    \brief  Namespace for project collector related types, functions, classes.
 */
namespace pc
{

//-----------------------------------------------------------------------------
// FileLister
//-----------------------------------------------------------------------------

/**
    \brief  Class that scans a directory recursive and lists all files that are found.
 */
class FileLister
{
// Public methods.
public:

    /**
        \brief  Scans a given root directoy recursive for all files.
        \param[out] files       Vector containing all files that were found.
                                Files will be add at and of vector.
        \param[in]  directory   Complete path of directory that shall be scanned.
        \return Result/error code - see also \ref result_t.
    */
    result_t GetFilesFromRootDirectory(std::vector<std::string>& files,
                                       const char8_t* directory);

    /**
        \brief  Generates a list of a default set of cpp relevate file endings.
        \return Vector that contains cpp relevate file endings.
     */
    static const std::vector<std::string>& GetRelevateCppFiles();

// Private methods.
private:

    /**
        \brief  Scans a given directory for all files or other directories.
        \param[in,out]  files       Vector containing all files that were found.
                                    Files will be add at and of vector.
        \param[in,out]  directories Stack with all remaining directories that shall be scanned.
        \return Result/error code - see also \ref result_t.
     */
    result_t GetFilesFromDirectory(std::vector<std::string>& files,
                                   std::vector<std::string>& directories);

    /**
        \brief  Checks if an entry (string) is a valid directory.
                Invalid directories are .\ and ..\
        \param[in]  directory   Name (string) of directory.
        \param[in]  length      Number of characters of name/string.
        \return Returns true if entry is a valid directory, else false will returned.
     */
    static bool IsValidDirectory(const char8_t* directory,
                                 int32_t length);

    /**
        \brief  Checks if current file is relevant. This is done with a list of relevant file endings.
        \param[in]  file            Name (string) of file.
        \param[in]  length          Number of characters of name/string.
        \param[in]  relevateEndings List of all relevant file endings.
        \return Returns true if it's a relevant file, else false will returned.
     */
    static bool IsRelevantFile(const char8_t* file,
                               int32_t length,
                               const std::vector<std::string>& relevateEndings);

// Private vars.
private:

}; // FileLister

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
} // pc

#endif // PC_FILE_LISTER_H