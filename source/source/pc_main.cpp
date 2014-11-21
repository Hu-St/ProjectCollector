//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdio>

#include "pc_file_lister.h"
#include "pc_include_lister.h"

using namespace pc;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

/**
*  @brief  Structure containing all programm arguments.
*/
struct Arguments
{
    const char* mainFile;   ///< File that contains main function
    const char* sourceDir;  ///< Directory that will be scan recursive for files
    const char* outDir;     ///< Output directory to that all files will be copied, that are required by mainFile.
};

/**
*  @brief  Reads in program arguments.
*  @param[out] arguments   Argument structure that will be filled
*  @param[in]  argc        Number of arguments
*  @param[in]  argv        String list of arguments
*  @return True if arguments are valid, else false.
*/
bool GetArguments(Arguments& arguments, int argc, char* argv[]);

//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

/**
*  @brief  Search recursive within a given directory for all files, that are required by main() function.
*          Only files that are included with #include "" will be observed.
*/
int main(int argc, char* argv[])
{
    // Flag to check if any problems occured previous to skip further processing steps.
    result_t success = RESULT_SUCCESS;

    // Get program arguments
    Arguments arguments;
    {
        // Check if any problem occurs.
        if (false == GetArguments(arguments, argc, argv))
        {
            // Set skip flag.
            success = RESULT_ERROR_INVALID_ARGUMENT;
        }
    } // Get program arguments

    // Get all files.
    std::vector<std::string> files;

    pc::FileLister fileLister;

    if (RESULT_SUCCESS == success)
    {
        success = fileLister.GetFilesFromRootDirectory(files, arguments.sourceDir);
    } // Get all files.

    // Get includes.
    pc::IncludeLister includeLister;
    std::vector<std::string> includes;

    if (RESULT_SUCCESS == success)
    {
        success = includeLister.GetIncludesFromFile(includes, arguments.mainFile);
    } // Get includes.

    return 1;
}

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Reads in program arguments.
bool GetArguments(Arguments& arguments, int argc, char* argv[])
{
    // Default return value is failed.
    bool success = false;

    // Check for valid arguments number.
    // Must be 3 - file containing main()
    //             source dir that is searched recursive
    //             output dir where all files shall be copied to
    if (4 == argc) // must be 4, because first argument is program name.
    {
        arguments.mainFile = argv[1];
        arguments.sourceDir = argv[2];
        arguments.outDir = argv[3];

        success = true;
    }
    // Invalid number of arguments
    else
    {
        // Help output
        printf("Invalid program call!\n");
        printf("%s MainFile SourceDir OutDir\n", argv[0]);
        printf("MainFile  - File that contains main() function\n");
        printf("SourceDir - Directory that will be scan recursive for required files\n");
        printf("OutDir    - Director to that all by main() required files will be copied\n\n");

        success = false;
    }

    return success;
}