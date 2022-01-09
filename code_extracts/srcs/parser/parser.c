/* 
* parser.c
*/

#include "parser.h"
#include "config.h"

static void *parserAllocator(t_parser *pdata, size_t size)
{
    void *ptr = NULL;

    ptr = NULL;
    ptr = malloc(size);
    if (!ptr)
        parserExit(pdata, "Problem with memory allocation during file parsing");
    ft_bzero(ptr, size);
    return ptr;
}

[...]

static char readObjFile(char **file, int *fd)
{
    *file = ft_filetostr(*fd, READBUFFERSIZE);
    if (*file)
    {
        if (ft_strlen(*file) > MAXOBJSIZE)
            return 0;
        return 1;
    }
    return 0;
}

static char checkExtension(char *fileName)
{
    size_t  strLenght;
    int     startCharacter; 

    if ((strLenght = ft_strlen(fileName)) <= ft_strlen(FILEEXT))
        return 0;
    startCharacter = strLenght - EXTLENGHT;
    for (int i = 0; i < EXTLENGHT; i++)
    {
        if (fileName[startCharacter + i] != FILEEXT[i])
            return 0;
    }
    return 1;
}

[...]

static char openObjFile(int *fd, char *fileName)
{ 
    char filePath[ft_strlen(fileName) + PATHLENGHT];
    
    ft_strcpy(filePath, "./objFiles/");
    ft_strcat(filePath, fileName);
    *fd = open(filePath, O_RDONLY);
    if (*fd > -1)
        return 1;
    return 0;
}

static void readFile(t_parser *pdata, char* filename)
{
    if (checkName(filename) != 1)
        parserExit(pdata, "Usage: ./scop [file.obj]");
    if (openObjFile(&pdata->FD, filename) != 1)
        parserExit(pdata, "Invalid OBJ file or path [Put it in '/objFiles']");
    if (readObjFile(&pdata->file, &pdata->FD) != 1)
        parserExit(pdata, "Impossible to read the specified file");
}

void parseObjFile(char* filename, float **vertexBuffer, unsigned int *bufferSize, void *vConfig)
{
    t_parser pdata;

    t_config *config = (t_config*)vConfig;
    ft_bzero(&pdata, sizeof(t_parser));
    pdata.textures.mode = config->texutureMode;

    readFile(&pdata, filename);
    countData(&pdata);
    allocateAndInitData(&pdata);
    fillData(&pdata);
    semiCleanParserAlloc(&pdata);
    if (fileToVertexBuffer(vertexBuffer, bufferSize, &pdata.faces, &pdata.vertices) != 1)
        parserExit(&pdata, "Memory error");
    cleanParserAlloc(&pdata);

    config->modelBbox = pdata.vertices.BoundingBoxSize;
    close (pdata.FD);
}