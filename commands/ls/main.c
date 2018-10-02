#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "ls_utils.h"

int main(int argc, char** argv)
{
    char* dir = NULL;
    LSDir* lsDir = NULL;
    uint32_t terminalWidth = 0;

    if( 1 == argc )
    {
        dir = ".";
    }
    else
    {
        /* ToDo: Implement argument parser */
        dir = argv[1];
    }

    lsDir = ls_openDir(dir, 0U);
    if( NULL == lsDir )
    {
        printf("ls: cannot access '%s': No such file or directory\n", dir);
        return EXIT_FAILURE;
    }

    terminalWidth = getTerminalWidth();
    if( 0U == terminalWidth )
    {
        printf("ls: error occured\n");
        return EXIT_FAILURE;
    }

    ls_output(lsDir, terminalWidth);

    ls_freeDir(lsDir);

    return EXIT_SUCCESS;
}
