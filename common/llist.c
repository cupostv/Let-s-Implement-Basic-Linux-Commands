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

static void LList_swap(LList* a, LList* b)
{
    void* temp = a->data;
    a->data = b->data;
    b->data = temp;
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

void LList_bSort(LList* list, int32_t (*comp)(void*, void*))
{
    int32_t size = 0;
    int32_t i = 0;
    int32_t j = 0;
    LList* temp = NULL;
    if (list == NULL)
    {
        return;
    }
    size = (int32_t)LList_getSize(list);

    for (i = 0; i < size - 1; i++)
    {
        temp = list;
        for (j = 0; j < size - i - 1; j++, temp = temp->next)
        {
            LList* a = temp;
            LList* b = temp->next;
            if( comp(a->data, b->data) >= 0 )
            {
                LList_swap(a, b);
            }
        }
    }
}

void* LList_get(const LList* const list , uint32_t index)
{
    LList* temp = (LList*)list;

    while( index > 0 && temp->data != NULL )
    {
        temp = temp->next;
        index--;
    }

    return temp->data;
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
