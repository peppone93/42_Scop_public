/* 
* vec.h
*/

#ifndef VEC_H
#define VEC_H

#include "math.h"

#define EPSILON 0.0001f

typedef struct		s_vec3
{
    float x;
    float y;
    float z;
}					t_vec3;

t_vec3  vec3u();
t_vec3	vec3(float x, float y, float z);
t_vec3	vec3sum(t_vec3 v1, t_vec3 v2);
t_vec3	vec3diff(t_vec3 v1, t_vec3 v2);
t_vec3	vec3mlt(t_vec3 v1, float scalar);
t_vec3	vec3div(t_vec3 v1, float scalar);
float	vec3dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3cross(t_vec3 v1, t_vec3 v2);
short   vec3cmp(t_vec3 v1, t_vec3 v2);
float   vec3dist(t_vec3 v1, t_vec3 v2);
double	vec3len(t_vec3 v1);
void	vec3inv(t_vec3 *vec);
void	vec3normalize(t_vec3 *vec);

#endif