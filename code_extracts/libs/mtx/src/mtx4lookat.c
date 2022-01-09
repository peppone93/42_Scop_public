#include "mtx.h"

static void forwardupright(t_vec3 *from, t_vec3 *to, t_vec3 *forward, t_vec3 *up, t_vec3 *right)
{
    t_vec3 temp;

    *forward = vec3diff(*from, *to);
    vec3normalize(forward);
    temp = vec3(0, 1.f, 0);
    if (forward->y > 0.95f || forward->y < -0.95f)
    {
        if(forward->y > 0)
            temp = vec3(0, 0, -1);
        else
            temp = vec3(0, 0, 1);
    }
    *right = vec3cross(*forward, temp); 
    *up = vec3cross(*right, *forward); 
}

void    mtx4lookat(t_mtx4 *mtx, t_vec3 from, t_vec3 to)
{
    t_vec3 forward, right, up;
    t_mtx4 translation, rotation;

    forwardupright(&from, &to, &forward, &up, &right);

    mtx4(&rotation);
    rotation.m[0][0] = right.x;
    rotation.m[0][1] = right.y;
    rotation.m[0][2] = right.z;
    rotation.m[1][0] = up.x;
    rotation.m[1][1] = up.y;
    rotation.m[1][2] = up.z;
    rotation.m[2][0] = forward.x;
    rotation.m[2][1] = forward.y;
    rotation.m[2][2] = forward.z;

    mtx4(&translation);
    translation.m[3][0] = -from.x;
    translation.m[3][1] = -from.y;
    translation.m[3][2] = -from.z;

    mtx4dot(mtx, &rotation, &translation);
}