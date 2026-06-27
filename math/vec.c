#include "vec.h"
#include <stdio.h>
#include <math.h>

inline void VEC3_print(VEC3 *v3)
{
    printf("<%d,%d,%d,%d>", v3->x, v3->y, v3->z, v3->a);
}

inline float VEC3_length(const VEC3 *v3)
{
     return sqrt(v3->x * v3->x
                +v3->y * v3->y
                +v3->z * v3->z
                );
}



inline float VEC3_length_sq(const VEC3 *v3)
{
     return (v3->x * v3->x + v3->y * v3->y + v3->z * v3->z);
}

inline VEC3 VEC3_add(VEC3 *a, VEC3 *b)
{
    VEC3 res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    res.z = a->z + b->z;

    return res;
}

inline VEC3 VEC3_scale(float t, VEC3* v3)
{
    VEC3 res;
    res.x = v3->x * t;
    res.y = v3->y * t;
    res.z = v3->z * t;

    return res;
}
