#include "mtx.h"

void    mtx4negate(t_mtx4 *mtx)
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            mtx->m[j][i] =  mtx->m[j][i] * -1.f;
        }
    }
}