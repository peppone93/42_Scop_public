#include "mtx.h"

void    mtx4perspective(t_mtx4 *mtx, float fov, float ratio, float near, float far)
{
    mtx4(mtx);
    float tangent = tanf(fov * 0.5f * DEG2RAD) * near;
    float height = tangent;
    float width = tangent * ratio;

    mtx->m[0][0] = 2.f * near / (width - -width); 
    mtx->m[1][1] = 2.f * near / (height - -height); 
    mtx->m[2][0] = (width + -width) / (width - -width); 
    mtx->m[2][1] = (height + -height) / (height - -height); 
    mtx->m[2][2] = -(far + near) / (far - near); 
    mtx->m[2][3] = -1.f;
    mtx->m[3][2] = -2.f * far * near / (far - near); 
    mtx->m[3][3] = 0;
}