#include "vec.h"
#include <stdio.h>
#include <math.h>

static float drand(int resolution)
{
    return ((float)(rand()%resolution))/resolution;
}

inline void VEC3_print(VEC3 *v3)
{
    fprintf(stderr, "<%f,%f,%f,%f>\n", v3->x, v3->y, v3->z, v3->a);
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

inline VEC3 VEC3_add(VEC3 const *a, VEC3 const *b)
{
    VEC3 res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    res.z = a->z + b->z;

    return res;
}


inline VEC3 VEC3_sub( VEC3 const *a, VEC3 const *b)
{
    VEC3 res;
    res.x = a->x - b->x;
    res.y = a->y - b->y;
    res.z = a->z - b->z;

    return res;
}

inline VEC3 VEC3_scale(float t, const VEC3* v3)
{
    VEC3 res;
    res.x = v3->x * t;
    res.y = v3->y * t;
    res.z = v3->z * t;

    return res;
}

inline float VEC3_dot(VEC3 const *a, VEC3 const *b)
{
    float res;
    res = a->x * b->x +
          a->y * b->y +
          a->z * b->z;

    return res;
}

// i forgot to initialize res here
// i was returning res/= vec_length
// this is undefined behaviour and it cause
// seemingly unrelated bug in main
// calling trace_sphere even tho it modified nothing
// changed the final ppm
inline VEC3 VEC3_unit(VEC3 const * v)
{
    VEC3 res;
    res.x = v->x / VEC3_length(v);
    res.y = v->y / VEC3_length(v);
    res.z = v->z / VEC3_length(v);
    res.a = 0;

    return res;
}

inline VEC3 VEC3_lerp(const VEC3 *src, const VEC3 *dest, float t)
{

            VEC3 tmp_a  = VEC3_scale(1.0f - t, src);
            VEC3 tmp_b  = VEC3_scale(t, dest);
            VEC3 result = VEC3_add(&tmp_a, &tmp_b);

            return result;
}


inline VEC3 VEC3_cross(const VEC3 *a, const VEC3 *b)
{

            VEC3 res;

            res.x = a->y * b->z - a->z * b->y;
            res.y = a->x * b->z - a->z * b->x;
            res.z = a->x * b->y - a->y * b->x;

            return res;
}

inline VEC3 VEC3_ray_at(const VEC3 *origin, const VEC3 *dir, const float t)
{
                VEC3 scaled_dir;
                VEC3 at_result;

                scaled_dir = VEC3_scale(t, dir);
                at_result = VEC3_add(origin, &scaled_dir);

                return at_result;
}


VEC3 VEC3_random_point_in_unit()
{
    VEC3 p;
    VEC3 one = {1,1,1,1};
    do{

        p = (VEC3){.x = drand(1000), .y = drand(1000), .z = drand(1000)};
        p = VEC3_scale(2.0, &p);
        p = VEC3_sub(&p, &one);

    }while(VEC3_length_sq(&p) > 1);

    return p;
}
