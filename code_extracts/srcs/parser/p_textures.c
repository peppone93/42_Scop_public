/* 
* p_textures.c
*/

#include "parser.h"

static t_vec2 newVec2(float x, float y)
{
    t_vec2 v;

    v.x = x;
    v.y = y;

    return v;
}

static void CubicMapping(t_parser *pdata, int *Idx, t_vec3 *v, t_vec3 *normal)
{
    t_vec2 referenceVtx[3];
    t_vec2 referenceMin;

    if (normal->x > normal->y && normal->x > normal->z)
    {
        for (int i = 0; i < VERTICES; i++)
            referenceVtx[i] = newVec2(v[i].z, v[i].y);
        referenceMin = newVec2(pdata->vertices.minCoordinates.z, pdata->vertices.minCoordinates.y);
    }
    else if (normal->y > normal->x && normal->y > normal->z)
    {   
[...]
}

static void correctMeshseams(t_parser *pdata, int *Idx)
{
    char minor, major = 0;

    for (int i = 0; i < VERTICES; i++)
    {
        if (pdata->faces.face[*Idx].t[i].x > (1.f - SPHERICSEEMCORRECTION))
[...]
}

static void SphericMapping(t_parser *pdata, int *Idx, t_vec3 *v)
{
[...]
}

void fillMissingTextures(t_parser *pdata, int Idx, int endIdx)
{
    t_vec3 normal;

    while (Idx < endIdx)
    {
        if (pdata->textures.mode == 0)
        {
            normal = vec3(0, 0, 0);
            for (int i = 0; i < VERTICES; i++)
                normal = vec3sum(normal, pdata->faces.face[Idx].n[i]);
            normal = vec3(fabs(normal.x), fabs(normal.y), fabs(normal.z));
            normal = vec3div(normal, (float)VERTICES);
            CubicMapping(pdata, &Idx, pdata->faces.face[Idx].v, &normal);
        }
        else
        {
            SphericMapping(pdata, &Idx, pdata->faces.face[Idx].v);
        }

        Idx++;
    }
}