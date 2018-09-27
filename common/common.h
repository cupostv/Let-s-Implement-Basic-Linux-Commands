#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>
#include "ccodes.h"
#include "llist.h"

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
 * \brief Print ammount of spaces.
 *        This function prints \a ammount of spaces to a terminal.
 *
 * \param ammount - Ammount of spaces about to be printed.
 *
 * \ret   void
 */
void printSpaces(uint32_t ammount);

#endif
