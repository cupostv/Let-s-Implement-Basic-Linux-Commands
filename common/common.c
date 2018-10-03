#include "common.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

uint32_t getTerminalWidth(void)
{
    struct winsize term;
    int32_t status = ioctl(STDOUT_FILENO, TIOCGWINSZ, &term);

    return status == -1 ? 0 : term.ws_col;
}

void printSpaces(int32_t ammount)
{
    while( ammount > 0 )
    {
        printf(" ");
        ammount--;
    }
}

void getDirStat(struct stat* s, char* path, char* filename)
{
    char* fullPath = (char*)malloc((strlen(path) + strlen(filename) + 2) * sizeof(char));

    strcpy(fullPath, path);
    strcat(fullPath, "/");
    strcat(fullPath, filename);

    stat(fullPath, s);
    free(fullPath);
}
