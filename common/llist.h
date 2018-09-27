#ifndef _LLIST_H_
#define _LLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct _LList
{
    void* data;
    struct _LList* next;
} LList;

/**
 * \brief Create empty LList object.
 *        This function returns a new empty LList object.
 *
 * \ret   LList - Pointer to a created list.
 */
LList* LList_create(void);

/**
 * \brief Insert data into the list.
 *        This function allocates size ammount of memory and copies data into
 *        the allocated memory.
 *
 * \param list - List where data will be inserted
 * \param data - Data to be inserted
 * \param size - Size of the data
 *
 * \ret   int32_t - If error, the function returns -1, otherwise 0.
 */
int32_t LList_insert(LList* const list, void* data, size_t size);

/**
 * \brief Get size of the list.
 *        This function returns number of elements in the list.
 *
 * \param list - List which size will be calculated
 *
 * \ret   uint32_t - Number of elements in the list.
 */
uint32_t LList_getSize(const LList* const list);

/**
 * \brief Sort the list.
 *        This function sorts the list in order passid with comparator function.
 *
 * \param list - List which will be sorted
 * \param comp - Comparator function which will be used for sorting
 *
 * \ret   void
 */
void LList_bSort(LList* list, int32_t (*comp)(void*, void*));

/**
 * \brief Free list.
 *
 * \param list - List which should be freed
 *
 * \ret   void
 */
void LList_free(LList** list);

#endif
