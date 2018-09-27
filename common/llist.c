#include "llist.h"

static LList* getLastFreeElement(const LList* const list)
{
    LList* res = (LList*)list;

    while( res->next != NULL )
    {
        res = res->next;
    }

    return res;
}

LList* LList_create(void)
{
    LList* list = malloc(sizeof(LList));
    list->data = NULL;
    list->next = NULL;

    return list;
}

int32_t LList_insert(LList* const list, void* data, size_t size)
{
    int32_t status = 0;
    LList* p = getLastFreeElement(list);

    p->data = malloc(size);

    if( NULL == p->data )
    {
        status == -1;
    }

    if( status == 0 )
    {
        memcpy(p->data, data, size);
        p->next = LList_create();
    }

    if( NULL == p->next )
    {
        status = -1;
    }

    return status;
}

uint32_t LList_getSize(const LList* const list)
{
    LList* res = (LList*)list;
    uint32_t size = 0;

    while( res->next != NULL )
    {
        res = res->next;
        size++;
    }

    return size;
}

void LList_free(LList** list)
{
    LList* cur = *list;
    LList* next = cur->next;

    if( NULL != cur->data )
    {
        free(cur->data);
    }
    free(cur);

    while( NULL != next )
    {
        cur = next;
        next = next->next;
        if( NULL != cur->data )
        {
            free(cur->data);
        }
        free(cur);
    }

    *list = NULL;
}
