#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H


#include <stdint.h>

typedef union{
    int64_t d[2];
    struct{
        int32_t x;
        int32_t y;
        int32_t z;
        int32_t a;
    };
}VEC3;


void VEC3_print(VEC3 *v3);
float VEC3_length(const VEC3 *v3);
float VEC3_length_sq(const VEC3 *v3);
VEC3 VEC3_add(VEC3 *a, VEC3 *b);
VEC3 VEC3_scale(float t, VEC3* v3);

#endif
