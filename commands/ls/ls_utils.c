#include "ls_utils.h"
#include <ctype.h>

static const char* const imgExt[] = \
{
    ".jpg",
    ".png",
    ".bmp",
    ".gif"
};

#define IMGEXT_SIZE (sizeof(imgExt) / sizeof(char*))

static void strcpyIgnoreSpecial(char* dest, const char* const src)
{
    uint32_t i = 0;
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

LSDir* ls_openDir(char* path, bool showHiddenFiles)
{
    LSDir* res = NULL;
    struct dirent* curFile = NULL;

    DIR* lsDir = opendir(path);

    if( NULL == lsDir )
    {
        return NULL;
    }

    res = malloc(sizeof(LSDir));

    res->dirList = LList_create();
    res->lsDir = lsDir;
    res->dirSize = 0U;
    res->dirPath = path;

    if( showHiddenFiles == true )
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

void ls_print(char* name, DirType type)
{
    switch( type )
    {
        case TYPE_DIRECTORY:
            printf(BOLDBLUE "%s" RESET, name);
            break;
        case TYPE_EXECUTABLE:
            printf(BOLDGREEN "%s" RESET, name);
            break;
        case TYPE_IMAGE:
            printf(BOLDMAGENTA "%s" RESET, name);
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
    uint32_t col = 0U;
    uint32_t row = 0U;
    const uint32_t size = lsDir->dirSize;
    uint32_t* maxLookup = malloc(size * sizeof(uint32_t));
    LList* idx = NULL;

    bool isFound = false;

    if( 0U == size )
    {
        return;
    }

    while( isFound == false )
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
            for( row = 0U; row < outRows && idx->data != NULL; row++, idx = idx->next )
            {
                struct dirent* el = (struct dirent*)idx->data;
                uint32_t len = 0;
                len = strlen(el->d_name);
                max = len > max ? len : max;
            }
            rowWidth += max + 1U + (col < colNum - 1);
            maxLookup[col] = max;
        }
        isFound = rowWidth <= terminalWidth || outRows == size;
    }

    idx = lsDir->dirList;
    for( row = 0; row < outRows; row++ )
    {
        for( col = 0; col < colNum; col++)
        {
            struct dirent* el = (struct dirent*)LList_get(lsDir->dirList, row + col * outRows);
            struct stat s;
            if( el == NULL)
            {
                break;
            }
            getDirStat(&s, lsDir->dirPath, el->d_name);
            ls_print(el->d_name, ls_getDirType(&s, el->d_name));
            if (maxLookup[col] < terminalWidth)
            {
                PRINT_SPACES(maxLookup[col] - (uint32_t)strlen(el->d_name) + (col == colNum - 1 ? 0U : 2U));
            }
        }
        printf("\n");
    }

    free(maxLookup);
}

static bool isImage(const char* str)
{
    char* ext = strchr(str, '.');
    uint32_t i = 0;

    if( NULL == ext )
    {
        return false;
    }

    for( i = 0; i < IMGEXT_SIZE; i++ )
    {
        if( strcmp(ext, imgExt[i]) == 0 )
        {
            return true;
        }
    }

    return false;
}

DirType ls_getDirType(const struct stat* const s, const char* name)
{
    if( S_ISDIR(s->st_mode) )
    {
        return TYPE_DIRECTORY;
    }
    else if( s->st_mode & S_IXUSR )
    {
        return TYPE_EXECUTABLE;
    }
    else if( isImage(name) == true )
    {
        return TYPE_IMAGE;
    }
    else
    {
        return TYPE_OTHER;
    }
}

void ls_freeDir(LSDir* dir)
{
    closedir(dir->lsDir);
    LList_free(&dir->dirList);
    free(dir);
}
