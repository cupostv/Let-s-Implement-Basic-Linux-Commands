#include "ls_utils.h"
#include <ctype.h>

static void strcpyIgnoreSpecial(char* dest, char* src)
{
    uint32_t i = 0;
    uint32_t len = strlen(src);
    char c;

    while( (c = src[i++]) != '\0' )
    {
        if( isalnum(c) )
        {
            *dest++ = c;
        }
    }
    *dest = '\0';
}

static int32_t dirComparator(void* a, void* b)
{
    struct dirent* aa = (struct dirent*)a;
    struct dirent* bb = (struct dirent*)b;
    int32_t result = 0;
    char* cmpA = malloc(strlen(aa->d_name) * sizeof(char) + 1);
    char* cmpB = malloc(strlen(bb->d_name) * sizeof(char) + 1);

    /* LS ignores characters different then alpha and numeric so skip it */
    if( strcmp(".", aa->d_name) == 0 ||
        strcmp("..", aa->d_name) == 0 )
    {
        strcpy(cmpA, aa->d_name);
    }
    else
    {
        strcpyIgnoreSpecial(cmpA, aa->d_name);
    }

    if( strcmp(".", bb->d_name) == 0 ||
        strcmp("..", bb->d_name) == 0 )
    {
        strcpy(cmpB, bb->d_name);
    }
    else
    {
        strcpyIgnoreSpecial(cmpB, bb->d_name);
    }

    result = strcasecmp(cmpA, cmpB);
    free(cmpA);
    free(cmpB);
    return result;
}

LSDir* ls_openDir(char* path, uint32_t showHiddenFiles)
{
    LSDir* res = NULL;
    DIR* lsDir = NULL;
    struct dirent* curFile = NULL;

    lsDir = opendir(path);
    if( NULL == lsDir )
    {
        printf("ls: cannot access '%s': No such file or directory\n", path);
    }

    res = malloc(sizeof(LSDir));

    res->dirList = LList_create();
    res->lsDir = lsDir;
    res->dirSize = 0U;

    if( 1U == showHiddenFiles )
    {
        while(( curFile = readdir(lsDir)) != NULL )
        {
            LList_insert((LList* const)res->dirList, (void*)curFile, sizeof(struct dirent));
            res->dirSize++;
        }
    }
    else
    {
        while(( curFile = readdir(lsDir)) != NULL )
        {
            if( curFile->d_name[0] != '.' )
            {
                LList_insert((LList* const)res->dirList, (void*)curFile, sizeof(struct dirent));
                res->dirSize++;
            }
        }
    }

    LList_bSort(res->dirList, dirComparator);

    return res;
}

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

void ls_output(LSDir* lsDir, uint32_t terminalWidth)
{
    uint32_t outRows = 0;
    uint32_t rowWidth = 0;
    uint32_t colNum = 0;
    uint8_t isFound = 0U;
    uint32_t col = 0U;
    uint32_t row = 0U;
    uint32_t size = lsDir->dirSize;
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
        idx = lsDir->dirList;
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

    idx = lsDir->dirList;
    for( row = 0; row < outRows; row++ )
    {
        for( col = 0; col < colNum; col++)
        {
            struct dirent* el = (struct dirent*)LList_get(lsDir->dirList, row + col * outRows);
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

void ls_freeDir(LSDir* dir)
{
    closedir(dir->lsDir);
    LList_free(&dir->dirList);
    free(dir);
}
