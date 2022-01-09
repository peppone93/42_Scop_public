#include "vec.h"

short   vec3cmp(t_vec3 v1, t_vec3 v2)
{
    if ( fabs(v1.x - v2.x) > EPSILON)
        return 0;
    if ( fabs(v1.y - v2.y) > EPSILON)
        return 0; 
    if ( fabs(v1.z - v2.z) > EPSILON)
        return 0; 
    return 1;   
}