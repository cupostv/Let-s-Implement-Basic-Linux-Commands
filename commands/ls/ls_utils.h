#ifndef _LS_UTILS_H_
#define _LS_UTILS_H_

#include "common.h"

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
void ls_print(char* name, uint32_t type);

/**
 * \brief Output directory as a table.
 *        This function prints directories stored in the list in nice
 *        looking table view.
 *
 * \param dirList - List which represents directory
 * \param terminalWidth - Current width of the terminal
 *
 * \ret   void
 */
void ls_output(LList* dirList, uint32_t terminalWidth);

#endif
