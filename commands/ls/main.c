#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "common.h"

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
        /* Creating copy of the directory so I can manipulate with it */
        LList_insert((LList* const)dirList, (void*)curFile, sizeof(struct dirent));
    }

    temp = dirList;

    while( NULL != temp && NULL != temp->data )
    {
        struct dirent* el = (struct dirent*)temp->data;
        if( strcmp(".", el->d_name) != 0 &&
            strcmp("..", el->d_name) != 0 &&
            el->d_name[0] != '.' )
        {
            switch( el->d_type )
            {
                case DT_DIR:
                    printf(BOLDBLUE "%s\t" RESET, el->d_name);
                    break;
                default:
                    printf("%s\t", el->d_name);
                    break;
            }
        }
        temp = temp->next;
    }

    closedir(lsDir);
    LList_free(&dirList);

    printf("\n");
    return EXIT_SUCCESS;
}
