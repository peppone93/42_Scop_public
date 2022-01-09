/* 
* p_faces.c
*/

#include "parser.h"

static void handleNormalsSection(t_parser *pdata, char* longline, int *pos, int i)
{
    unsigned int normalIndex;

    afterSlash(pdata, longline, pos);
    normalIndex = ft_atoi(&longline[*pos]) - 1;
    if (normalIndex >= pdata->normals.size)
        return ;

    pdata->faces.face[pdata->faces.idx].n[i] = pdata->normals.normal[normalIndex];
}

static void handleTexturesSection(t_parser *pdata, char* longline, int *pos, int i)
{
    unsigned int textureIndex;

    textureIndex = ft_atoi(&longline[*pos]) - 1;
    if (textureIndex >= pdata->textures.size)
        return ;

    pdata->faces.face[pdata->faces.idx].t[i] = pdata->textures.texture[textureIndex];
}

static void createFace(t_parser *pdata, char* longline, int *pos)
{
    unsigned int VertexIndex;

    VertexIndex = ft_atoi(&longline[*pos]) - 1;
    if (VertexIndex >= pdata->vertices.size)
        parserExit(pdata, "Major error during obj parsing, please check the vertex list");

    pdata->faces.face[pdata->faces.idx].v[0] = pdata->faces.face[pdata->faces.idx - 1].v[0];
    pdata->faces.face[pdata->faces.idx].v[1] = pdata->faces.face[pdata->faces.idx - 1].v[2];
    pdata->faces.face[pdata->faces.idx].v[2] = pdata->vertices.vertex[ft_atoi(&longline[*pos]) - 1];

    afterSlash(pdata, longline, pos);
[...]
    checkNextSpace(longline, pos);
}

static void fillMissingNormals(t_parser *pdata, int Idx, int endIdx)
{
    t_vec3 u;
    t_vec3 v;

[...]
}

static void fillMissingData(t_parser *pdata, int startIdx, int endIdx)
{
    if (!pdata->normals.size)
        fillMissingNormals(pdata, startIdx, endIdx);
    if (!pdata->textures.size)
        fillMissingTextures(pdata, startIdx, endIdx);
}

static void handleFirstVertices(t_parser *pdata, char* longline, int *pos, int i)
{
    unsigned int VertexIndex;

    VertexIndex = ft_atoi(&longline[*pos]) - 1;
    if (VertexIndex >= pdata->vertices.size)
        return ;

    pdata->faces.face[pdata->faces.idx].v[i] = pdata->vertices.vertex[VertexIndex];
    afterSlash(pdata, longline, pos);
    if (pdata->textures.size > 0)
        handleTexturesSection(pdata, longline, pos, i);
    if (pdata->normals.size > 0)
        handleNormalsSection(pdata, longline, pos, i);
    checkNextSpace(longline, pos);
}

void fill_faces(t_parser *pdata, char* longline)
{
    int vertex = 0;
    int pos = 0;

    while (nextDigit(longline, &pos))
    {
        if (vertex < 3)
            handleFirstVertices(pdata, longline, &pos, vertex);
        else if (vertex <= 8)
        {
            pdata->faces.idx++;
            createFace(pdata, longline, &pos);
        }
        else
            parserExit(pdata, "Serious vertex parser error");
        vertex++;
    }
    pdata->faces.idx++;

    int faces = vertex -= 2;
    fillMissingData(pdata, pdata->faces.idx - faces, pdata->faces.idx); 
}