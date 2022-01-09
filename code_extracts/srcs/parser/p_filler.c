/* 
* p_filler.c
*/

#include "parser.h"

static void nextNumberBlock(t_parser *pdata, char* longline, int *pos)
{
    while (longline[*pos] != '\n' && !ft_isnumber(longline[*pos]))
        (*pos)++;
    if (longline[*pos] == '\n')
        parserExit(pdata, "Invalid vertex detected");
}

static void nextSpace(t_parser *pdata, char* longline, int *pos)
{
    while (longline[*pos] != '\n' && longline[*pos] != ' ')
        (*pos)++;
    if (longline[*pos] == '\n')
        parserExit(pdata, "Invalid vertex detected");
}

[...]

void fill_textures(t_parser *pdata, char* longline)
{
    int i = 0;

    nextNumberBlock(pdata, longline, &i);
    pdata->textures.texture[pdata->textures.idx].x = ft_atof(&longline[i]);
    nextSpace(pdata, longline, &i);
    nextNumberBlock(pdata, longline, &i);
    pdata->textures.texture[pdata->textures.idx].y = ft_atof(&longline[i]);
    pdata->textures.idx++;
}

void fill_normals(t_parser *pdata, char* longline)
{
    int i = 0;

    nextNumberBlock(pdata, longline, &i);
    pdata->normals.normal[pdata->normals.idx].x = ft_atof(&longline[i]);
    nextSpace(pdata, longline, &i);
    nextNumberBlock(pdata, longline, &i);
    pdata->normals.normal[pdata->normals.idx].y = ft_atof(&longline[i]);
    nextSpace(pdata, longline, &i);
    nextNumberBlock(pdata, longline, &i);
    pdata->normals.normal[pdata->normals.idx].z = ft_atof(&longline[i]);
    pdata->normals.idx++;
}

void fill_vertices(t_parser *pdata, char* longline)
{
    int i = 0;

    nextNumberBlock(pdata, longline, &i);
    pdata->vertices.vertex[pdata->vertices.idx].x = ft_atof(&longline[i]);
    nextSpace(pdata, longline, &i);
    nextNumberBlock(pdata, longline, &i);
    pdata->vertices.vertex[pdata->vertices.idx].y = ft_atof(&longline[i]);
    nextSpace(pdata, longline, &i);
    nextNumberBlock(pdata, longline, &i);
    pdata->vertices.vertex[pdata->vertices.idx].z = ft_atof(&longline[i]);

    updateVerticesRange(pdata, &pdata->vertices.vertex[pdata->vertices.idx]);
    pdata->vertices.idx++;
}

[...]

void fillData(t_parser *pdata)
{
    lineHandler lineHandlerType = &fill;
    cycleLines(pdata, lineHandlerType);
}