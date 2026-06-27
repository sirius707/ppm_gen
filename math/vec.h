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
VEC3 VEC3_add(VEC3 *a, VEC3 *b);
VEC3 VEC3_scale(float t, VEC3* v3);
VEC3 VEC3_unit(VEC3* v);
VEC3 VEC3_lerp(const VEC3 *src, const VEC3 *dest, float t);

#endif
