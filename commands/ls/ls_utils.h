#ifndef _LS_UTILS_H_
#define _LS_UTILS_H_

#include "common.h"
#include <dirent.h>
#include <sys/stat.h>

typedef enum
{
    TYPE_DIRECTORY,
    TYPE_EXECUTABLE,
    TYPE_IMAGE,
    TYPE_OTHER
} DirType;

typedef struct
{
    LList* dirList;
    char* dirPath;
    uint32_t dirSize;
    DIR* lsDir;
} LSDir;

/**
 * \brief Open directory.
 *        This function opens and reads a directory.
 *
 * \param path - Path to the directory/file
 * \param showHiddenFiles - Indicator which shows if hidden files should be shown
 *
 * \ret   LSDir* - Pointer to created LSDir structure.
 */
LSDir* ls_openDir(char* path, uint32_t showHiddenFiles);

/**
 * \brief Print directory/file name.
 *        This function prints directory name according to its type. If it's a
 *        directory it color output will be BLUEBOLD, if it's executable it will
 *        be GREENBOLD, otherwise, default value.
 *
 * \param name - Name of the directory/file
 * \param type - Type of the directory/file
 *
 * \ret   void
 */
void ls_print(char* name, DirType type);

/**
 * \brief Output directory as a table.
 *        This function prints directories stored in the list in nice
 *        looking table view.
 *
 * \param lsDir - Struct which represents directory
 * \param terminalWidth - Current width of the terminal
 *
 * \ret   void
 */
void ls_output(LSDir* lsDir, uint32_t terminalWidth);

/**
 * \brief Get type of a directory.
 *        This type returns type of a directory.
 *
 * \param s - Struct which is created with getDirStat function.
 * \param name - Name of the file/dir.
 *
 * \ret   DirType - Type of a file/directory.
 */
DirType ls_getDirType(struct stat* s, char* name);

/**
 * \brief Free a directory.
 *        Call this function at the end of the program.
 *
 * \param dir - Struct which represents directory and should be freed.
 *
 * \ret   void
 */
void ls_freeDir(LSDir* dir);

#endif
