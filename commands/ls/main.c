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

    if( argc == 1 )
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

    while(( curFile = readdir(lsDir)) != NULL )
    {
        if( strcmp(".", curFile->d_name) != 0 &&
            strcmp("..", curFile->d_name) != 0 &&
            curFile->d_name[0] != '.' )
        {
            switch( curFile->d_type )
            {
                case DT_DIR:
                    printf(BOLDBLUE "%s\t" RESET, curFile->d_name);
                    break;
                case DT_REG:
                    printf("%s\t", curFile->d_name);
                    break;
                default:
                    break;
            }

        }
    }

    closedir(lsDir);

    printf("\n");
    return EXIT_SUCCESS;
}