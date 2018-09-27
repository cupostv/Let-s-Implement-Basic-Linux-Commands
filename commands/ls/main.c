#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "ls_utils.h"

static int32_t dirComparator(void* a, void* b)
{
    struct dirent* aa = (struct dirent*)a;
    struct dirent* bb = (struct dirent*)b;

    return strcasecmp(aa->d_name, bb->d_name);
}

int main(int argc, char** argv)
{
    char* dir = NULL;
    DIR* lsDir = NULL;
    struct dirent* curFile;
    uint32_t terminalWidth = 0;
    LList* dirList = NULL;
    LList* temp = NULL;

    if( 1 == argc )
    {
        dir = ".";
    }
    else
    {
        /* ToDo: Implement argument parser */
        dir = argv[1];
    }

    lsDir = opendir(dir);
    if( NULL == lsDir )
    {
        printf("ls: cannot access '%s': No such file or directory\n", dir);
        return EXIT_FAILURE;
    }

    dirList = LList_create();
    terminalWidth = getTerminalWidth();
    if( 0U == terminalWidth )
    {
        printf("ls: error occured\n");
        return EXIT_FAILURE;
    }

    while(( curFile = readdir(lsDir)) != NULL )
    {
        if( strcmp(".", curFile->d_name) != 0 &&
            strcmp("..", curFile->d_name) != 0 &&
            curFile->d_name[0] != '.' )
        {
            /* Creating copy of the directory so I can manipulate with it */
            LList_insert((LList* const)dirList, (void*)curFile, sizeof(struct dirent));
        }
    }

    LList_bSort(dirList, dirComparator);
    ls_output(dirList, terminalWidth);

    closedir(lsDir);
    LList_free(&dirList);

    return EXIT_SUCCESS;
}
