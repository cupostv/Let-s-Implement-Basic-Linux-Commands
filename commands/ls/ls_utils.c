#include "ls_utils.h"
#include <dirent.h>

void ls_print(char* name, uint32_t type)
{
    switch( type )
    {
        case DT_DIR:
            printf(BOLDBLUE "%s" RESET, name);
            break;
        default:
            printf("%s", name);
            break;
    }
}

void ls_output(LList* dirList, uint32_t terminalWidth)
{
    uint32_t outRows = 0;
    uint32_t rowWidth = 0;
    uint32_t colNum = 0;
    uint8_t isFound = 0U;
    uint32_t col = 0U;
    uint32_t row = 0U;
    uint32_t size = LList_getSize(dirList);
    uint32_t* maxLookup = malloc(size * sizeof(uint32_t));
    LList* idx = NULL;

    if( 0U == size )
    {
        return;
    }

    while( 0U == isFound )
    {
        do
        {
            outRows++;
            colNum = size / outRows;
            if( size % outRows != 0 )
            {
                colNum++;
            }
        }
        while( colNum * outRows - size > colNum - 1 );

        rowWidth = 0;
        idx = dirList;
        for( col = 0U; col < colNum; col++ )
        {
            uint32_t max = 0;
            for( row = 0U; row < outRows; row++, idx = idx->next )
            {
                struct dirent* el = (struct dirent*)idx->data;
                uint32_t len = 0;
                if( NULL == el )
                {
                    break;
                }
                len = strlen(el->d_name);
                max = len > max ? len : max;
            }
            rowWidth += max + 1U;
            if( col < colNum - 1 )
            {
                rowWidth += 1U;
            }
            maxLookup[col] = max;
        }
        if( rowWidth <= terminalWidth || outRows == size )
        {
            isFound = 1;
        }
    }

    idx = dirList;
    for( row = 0; row < outRows; row++ )
    {
        for( col = 0; col < colNum; col++)
        {
            struct dirent* el = (struct dirent*)LList_get(dirList, row + col * outRows);
            if( el == NULL)
            {
                break;
            }
            ls_print(el->d_name, el->d_type);
            if (maxLookup[col] < terminalWidth)
            {
                printSpaces(maxLookup[col] - strlen(el->d_name) + (col == colNum - 1 ? 0 : 2));
            }
        }
        printf("\n");
    }

    free(maxLookup);
}
