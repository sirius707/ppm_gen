#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H


#include <stdint.h>

typedef union{
    float d[4];
    struct{
        float x;
        float y;
        float z;
        float a;
    };
}VEC3;


void VEC3_print(VEC3 *v3);
float VEC3_length(const VEC3 *v3);
float VEC3_length_sq(const VEC3 *v3);
float VEC3_dot(VEC3 const *a, VEC3 const *b);
VEC3 VEC3_add( VEC3 const *a, VEC3 const *b);
VEC3 VEC3_sub( VEC3 const *a, VEC3 const *b);
VEC3 VEC3_cross(const VEC3 *a, const VEC3 *b);
VEC3 VEC3_scale(float t, const VEC3* v3);
VEC3 VEC3_unit(VEC3 const *v);
VEC3 VEC3_lerp(const VEC3 *src, const VEC3 *dest, float t);
VEC3 VEC3_ray_at(const VEC3 *orign, const VEC3 *dir, const float t);
VEC3 VEC3_random_point_in_unit();

#define VEC3_CON(X, Y, Z) ((VEC3){.x = X, .y = Y, .z = Z})
#endif
