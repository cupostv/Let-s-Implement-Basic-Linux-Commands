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

void getDirStat(struct stat* s, const char* const path, const char* const filename)
{
    char* fullPath = (char*)malloc((strlen(path) + strlen(filename) + 2) * sizeof(char));

    strcpy(fullPath, path);
    strcat(fullPath, "/");
    strcat(fullPath, filename);

    stat(fullPath, s);
    free(fullPath);
}
