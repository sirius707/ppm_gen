
#include "vec.h"

int ____main()
{
    VEC3 v;
    VEC3 v2;

    v.x = 2;
    v.y = 3;

    v2 = VEC3_scale(3, &v);
    VEC3_print(&v2);

    v = VEC3_add(&v,&v2);
    VEC3_print(&v);
}
