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

#endif
