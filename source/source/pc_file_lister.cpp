/**
    \file       pc_file_lister.h

    \brief      Implementation of \ref FileLister class.

    \author     Hubert Strautz  (h.strautz@intenta.de)
    \data       2014/11/18
*/

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <algorithm>

#include "pc_file_lister.h"
#include "dirent.h"

//-----------------------------------------------------------------------------
// Namespace
//-----------------------------------------------------------------------------
using namespace pc;
using std::vector;
using std::string;

//-----------------------------------------------------------------------------
// FileLister
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Scans a given root directoy recursive for all files.
result_t FileLister::GetFilesFromRootDirectory(
    vector<string>& files,
    const char8_t* directory)
{
    // Default result value.
    result_t result = (0 == directory) ? RESULT_ERROR_INVALID_ARGUMENT : RESULT_SUCCESS;

    // Get all files from directory and recursive directories.
    vector<string> directories;               // Stack of all directories that shall be scanned.
    directories.push_back(string(directory)); // Add root directory to stack.

    // As long as no problems occurs and there are still directories in stack process.
    while ((RESULT_SUCCESS == result) && (0 < directories.size()))
    {
        result = FileLister::GetFilesFromDirectory(files, directories);
    }

    return result;
}

//-----------------------------------------------------------------------------
// Scans a given directory for all files or other directories.
result_t FileLister::GetFilesFromDirectory(
    vector<string>& files,
    vector<string>& directories)
{
    // Default return value, that is use to skip processing after any problems occured, too.
    result_t result = RESULT_SUCCESS;

    // Check if there are any directories remaining in stack.
    if (0 < directories.size())
    {
        // Get last directory name from stack.
        string directory_name = directories.at(directories.size() - 1);

        // Remove last directory from stack.
        directories.pop_back();

        // Open directory structure.
        DIR *directory = 0;
        {
            // Try to open directory.
            directory = opendir(directory_name.c_str());

            // Check if it wasn't possible to open directory.
            if (0 == directory)
            {
                result = RESULT_ERROR_COULD_NOT_OPEN_DIR;
            }
        } // Open directory structure.

        // Get directory content.
        if (RESULT_SUCCESS == result)
        {
            struct dirent *content = 0; 

            // As long as no problems occures and there are remaining content in directory process.
            while ( (RESULT_SUCCESS == result) &&
                    (content = readdir(directory)) )
            {
                // Check if any problem occurs due getting next directory entry.
                if (0 == content)
                {
                    result = RESULT_ERROR_COULD_GET_DIR_CONTENT;
                }

                // Check type of entry.
                // Entry is a directory.
                if (DT_DIR == content->d_type)
                {
                    // Check if entry is another directory.
                    if (true == IsValidDirectory(content->d_name, content->d_namlen))
                    {
                        // Add directory to end of stack.
                        string s = directory_name + "\\" + content->d_name;
                        directories.push_back(s);
                    }
                }
                // Entry is a file.
                else if (DT_REG == content->d_type)
                {
                    // Check if files relates to c or cpp.
                    if (true == IsRelevantFile(content->d_name, content->d_namlen, FileLister::GetRelevateCppFiles()))
                    {
                        // Add to files list.
                        string s = directory_name + "\\" + content->d_name;
                        files.push_back(s);
                    }
                }
                else
                {
                    // Nothing to do.
                }
            } // As long as no problems occures and there are remaining content in directory process.

            // Close directory.
            closedir(directory);
        } // Read in directory content.
    } // Check if there are any directories remaining in stack.

    return result;
}

//-----------------------------------------------------------------------------
// Checks if an entry (string) is a directory.
bool FileLister::IsValidDirectory(
    const char8_t* directory,
    int32_t length)
{
    // Default return value if directory is valid.
    bool isValid = (0 == directory) ? false : true;

    // Only continue if there aren't previous problems.
    if (true == isValid)
    {
        // Directory name of length 1
        if (1 == length)
        {
            // Check for invalid case .
            if ('.' == directory[0])
            {
                isValid = false;
            }
        }
        // Directory name of length 2
        else if (2 == length)
        {
            // Check for incalid case ..
            if (('.' == directory[0]) && ('.' == directory[1]))
            {
                isValid = false;
            }
        }
        // Other directory name lengths are valid.
        else
        {
            isValid = true;
        }
    } // Only continue if there aren't previous problems.

    return isValid;
}

//-----------------------------------------------------------------------------
// Checks if current file is relevant. This is done with a list of relevant file endings.
bool FileLister::IsRelevantFile(
    const char8_t* file,
    int32_t length,
    const std::vector<std::string>& relevateEndings)
{
    // Default return value if directory is valid.
    bool isValid = (0 == file) ? false : true;

    // Only continue if there aren't previous problems.
    if (true == isValid)
    {
        // Create string of filename.
        string fileName(file);

        // Find last . of file name to determine file extension.
        size_t startEnding = fileName.find_last_of(".");

        // Get ending of file.
        string fileEnding = fileName.substr(startEnding + 1);

        // Convert to lower case.
        transform(fileEnding.begin(), fileEnding.end(), fileEnding.begin(), tolower);

        // Clear isValid flag.
        isValid = false;

        // As long as valid file ending isn't detected process.
        uint32_t it = 0;
        while ( (false == isValid) &&
                (it < relevateEndings.size()))
        {
            // Compare file ending with next relevate ending from list.
            if (fileEnding == relevateEndings.at(it))
            {
                // Set flag that relevate ending is detected.
                isValid = true;
            }

            // Increment iterator.
            ++it ;
        } // As long as valid file ending isn't detected process.
    } // Only continue if there aren't previous problems.

    return isValid;
}

//-----------------------------------------------------------------------------
// Generates a list of a default set of cpp relevate file endings.
const vector<string>& FileLister::GetRelevateCppFiles()
{
    // Static vector of cpp relevate file endings.
    static vector<string> fileEndings;

    // Check if endings weren't generated before.
    if (0 == fileEndings.size())
    {
        // Add default cpp relevate endings to list.
        fileEndings.push_back("h");
        fileEndings.push_back("hpp");
        fileEndings.push_back("c");
        fileEndings.push_back("cpp");
        fileEndings.push_back("inc");
        fileEndings.push_back("impl");
    } // Check if endings weren't generated before.

    return fileEndings;
}