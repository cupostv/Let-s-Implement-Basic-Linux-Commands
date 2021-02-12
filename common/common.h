#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "ccodes.h"
#include "llist.h"

#define PRINT_SPACES(ammount) printf("%*s", ammount, "")

/**
 * \brief Get current width of terminal.
 *        This function returns width of the terminal. Width represents
 *        number of columns in the terminal.
 *
 * \ret   uint32_t - If error, the function returns 0, otherwise number
 *                   of columns.
 */
uint32_t getTerminalWidth(void);

/**
 * \brief Get stat of a directory/file.
 *        This function returns stat structure (passed as argument) for the
 *        path/filename.
 *
 * \param s - Output argument. It will be filled by the function.
 * \param path - Absolute or relative path
 * \param filename - Name of the file/folder
 *
 * \ret   void
 */
void getDirStat(struct stat* s, const char* const path, const char* const filename);

#endif
