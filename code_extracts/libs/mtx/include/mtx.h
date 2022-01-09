/* 
* mtx.h
*/

#ifndef MTX_H
#define MTX_H

#include "math.h"
#include "libft.h"
#include "vec.h"

#define EPSILON 0.0001f
#define DEG2RAD 0.017452f

typedef struct		s_mtx3
{
    float m[3][3];
}					t_mtx3;

typedef struct		s_mtx4
{
    float m[4][4];
}					t_mtx4;

void	mtx4(t_mtx4 *mtx);
void	mtx4scale(t_mtx4 *mtx, t_vec3 scale);
void    mtx4translation(t_mtx4 *mtx, t_vec3 dir);
void    mtx4puretranslation(t_mtx4 *mtx, t_vec3 dir);
void    mtx4displace(t_mtx4 *mtx, t_vec3 dir);
void    mtx4xrotation(t_mtx4 *mtx, float angle, char pure);
void    mtx4yrotation(t_mtx4 *mtx, float angle, char pure);
void    mtx4zrotation(t_mtx4 *mtx, float angle, char pure);
void    mtx4axerotation(t_mtx4 *mtx, float angle, t_vec3 axe, char pure);
void    mtx4dot(t_mtx4 *mtx, t_mtx4 *a, t_mtx4 *b);
t_vec3  mtx4vectormlt(t_mtx4 *mtx, t_vec3 a);
void    mtx4perspective(t_mtx4 *mtx, float fov, float ratio, float near, float far);
void    mtx4transpose(t_mtx4 *mtx);
void    mtx4negate(t_mtx4 *mtx);
void    mtx4lookat(t_mtx4 *mtx, t_vec3 from, t_vec3 to);
void    mtx4copy(t_mtx4 *mtx, t_mtx4 *src);

void	mtx3(t_mtx3 *mtx);
void	mtx3normal(t_mtx3 *mtx, t_mtx4 *src);

#endif