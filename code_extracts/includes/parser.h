/* 
* parser.h
*/

#ifndef PARSER_H
#define PARSER_H

#include <fcntl.h> //open
#include "libft.h"
#include "vec.h"

#define IGNORETEXTURE 0

#define VERTICES 3
#define EXTLENGHT 4
#define PATHLENGHT 12
#define VERTEXBUFFERUNIT 9
#define READBUFFERSIZE 2097134
#define MAXOBJSIZE 64000000
#define MYMAXFLOAT 99999999.f
#define COLORGRADIENT 0.125f
#define SPHERICSEEMCORRECTION 0.05f
#define FILEEXT ".obj"

#define PI 3.141592f
#define CONTINUE 1

typedef enum    eLineType
{
    None,
    Vertex,
    Normal,
    Texture,
    Face
}               LineType;

typedef struct  s_vec2
{
    float       x;
    float       y;
}				t_vec2;

typedef struct  s_face
{
    t_vec3        v[3];
    t_vec3        n[3];
    t_vec2        t[3];
}				t_face;

typedef struct      s_vertices
{
    unsigned int    size;
    unsigned int    idx;
    t_vec3          maxCoordinates;
    t_vec3          minCoordinates;
    float           BoundingBoxSize;
    t_vec3          *vertex;
}			        t_vertices;

typedef struct      s_normals
{
    unsigned int    size;
    unsigned int    idx;
    t_vec3            *normal;
}			        t_normals;

typedef struct      s_textures
{
    unsigned int    size;
    unsigned int    idx;
    unsigned char   mode;
    t_vec2            *texture;

}			        t_textures;

typedef struct      s_faces
{
    unsigned int    size;
    unsigned int    idx;
    t_face          *face;
}			        t_faces;

typedef struct      s_parser
{
    int             FD;
    char*           file;

    t_vertices      vertices;
    t_normals       normals;
    t_textures      textures;
    t_faces         faces;
}					t_parser;

typedef void (*lineHandler)(t_parser *p, LineType, char *c);


void    parseObjFile(char* filename, float **vertexBuffer, unsigned int *bufferSize, void *config);
void    countData(t_parser *pdata);
void    fillData(t_parser *pdata);

void    cycleLines(t_parser *pdata, lineHandler lineHandlerType);
char    isLineEnd(char *c);
char    nextFacesBlock(char *longline, int *linePos);
char    nextDigit(char *longline, int *linePos);
void    checkNextSpace(char *longline, int *linePos);
void    afterSlash(t_parser *pdata, char* longline, int *pos);
char    fileToVertexBuffer(float **vertexBuffer, unsigned int *bufferSize, t_faces *faces, t_vertices *vertices); 

void    fill_faces(t_parser *pdata, char* longline);
void    fillMissingTextures(t_parser *pdata, int Idx, int endIdx); 

void    cleanParserAlloc(t_parser *pdata);
void    semiCleanParserAlloc(t_parser *pdata);
void    parserExit(t_parser *pData, char *str);

#endif