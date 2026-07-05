#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "math/vec.h"
#include <float.h>
#include <stdbool.h>

#define PINT(x) printf("%u\t", x)
#define NL puts("")

typedef struct{
    VEC3; //dimensions + radius
}SPHERE;

typedef struct{
    float t;
    VEC3 point;
    VEC3 normal;
}HIT_INFO;

bool trace_circle(VEC3 const *org, VEC3 const *end, VEC3 const *sphere, float t_min, float t_max, HIT_INFO *record)
{

    float a, b, c;
    VEC3 oc;
    oc = VEC3_sub(org, sphere);

    //a = end->x * end->x + end->y * end->y + end->z * end->z;
    a = VEC3_dot(end, end);


    //b = -2 * ((end->x - org->x) * (sphere->x - org->x) +(end->y - org->y) * (sphere->y - org->y) +(sphere->z - org->z) * (end->z - org->z));
    b = (VEC3_dot(&oc, end));

    //c = (sphere->x - org->x) * (sphere->x - org->x) + (sphere->y - org->y) * (sphere->y - org->y) + (sphere->z - org->z) * (sphere->z - org->z) - sphere->a * sphere->a;
    c = VEC3_dot(&oc, &oc) - sphere->a * sphere->a;

    float discriminant = 0;
    float temp;
    discriminant = b*b -  a * c;


    if(discriminant > 0){
        temp = (-b - sqrt(discriminant))/(a);
        if(temp > t_min && temp < t_max){
            record->t = temp;
            record->point = VEC3_ray_at(org, end, temp);
            record->normal = VEC3_sub(&(record->point), &sphere);
            record->normal = VEC3_scale(1/sphere->a, &(record->normal));


            return true;
        }


        temp = (-b + sqrt(discriminant))/(a);
        if(temp > t_min && temp < t_max){
            record->t = temp;
            record->point = VEC3_ray_at(org, end, temp);
            record->normal = VEC3_sub(&(record->point), &sphere);
            record->normal = VEC3_scale(1.0/(sphere->a), &(record->normal));


            return true;
        }

    }

    return false;

}

void print_sky()
{
	puts("255 255");
	puts("255");

	for(int j = 255; j >= 0; j--){
		for(int i = 0; i < 255; i++){
			printf("%d\t%d\t%d\t\n",0, 0, j);
		}
	}
}

// draw a sun
int main()
{

	int   w, h;
	float  r, g, b;
	int  depth;
	float radius;

	w = 400;
	h = 200;
	depth = 255;

	r = 0;
	g = 0;
	b = 0;

	float x = w/2;
	float y = h/2;


	srand(time(0));
	radius = h/2;

	puts("P3");
	//print_sky();

	printf("%d\t%d\n%d\n", w, h, depth);

	/*
	for(int j = 0; j < h; j++){
		for(int i = 0; i < w; i++){

			float distance = sqrt((i - x) * (i - x) + (j - y) * (j - y));

			float ratio = fabs((radius - (distance*1.2)) / (radius));
			if(distance > radius){
				ratio = 0;
			}

			//r = (double)  distance/radius;
			//g = (double)  distance/radius;
			//b = (double)  distance/radius;

			//fprintf(stderr, "%f\n", r);
			PINT((int)(25.0f * ratio));PINT((int)( 215.0f * ratio));PINT((int) (22.0f * ratio));NL;

		}
	}
	*/

	//print skybox
	VEC3 lower_left ={.x = -2.0, .y = -1.0, .z = -1.0};
	VEC3 horizontal ={.x =  4.0, .y = 0.0 , .z =  0.0};
	VEC3 vertical  ={.x = 0.0, .y = 2.0 , .z =  0.0};
	VEC3 origin ={.x = 0, .y = 0, .z = 0};

    VEC3 white = {.x = 1.0, .y = 1.0, .z = 1.0};
    VEC3 blue = {.x = 0.5, .y = 0.7, .z = 1.0};

    VEC3 tmp_h;
    VEC3 tmp_v;
    VEC3 dir = {.x = 0.0, .y = 0.0, .z = 0.0};

    #define N_SPHERES 8
    VEC3 sphere[N_SPHERES];

    sphere[0].x = 0;
    sphere[0].y = 0;
    sphere[0].z = -1;
    sphere[0].a = 0.5;


    sphere[7].x = -0.9;
    sphere[7].y = -0.3;
    sphere[7].z = -1;
    sphere[7].a = 0.2;


    sphere[2].x = -0.9;
    sphere[2].y = 0.3;
    sphere[2].z = -1;
    sphere[2].a = 0.2;


    sphere[3].x = -1.5;
    sphere[6].x = 1.5;
    sphere[6].y = 0;
    sphere[6].z = -1;
    sphere[6].a = 0.2;

    sphere[3].y = 0;
    sphere[3].z = -1;
    sphere[3].a = 0.2;

    sphere[4].x = 0.9;
    sphere[4].y = -0.3;
    sphere[4].z = -1;
    sphere[4].a = 0.2;


    sphere[5].x = 0.9;
    sphere[5].y = 0.3;
    sphere[5].z = -1;
    sphere[5].a = 0.2;


    sphere[6].x = 1.5;
    sphere[6].y = 0;
    sphere[6].z = -1;
    sphere[6].a = 0.2;


    sphere[1].x = 0;
    sphere[1].y = -100.5;
    sphere[1].z = -1;
    sphere[1].a = 100;

    for(int j = h-1; j > 0; j--){
		for(int i = 0; i < w; i++){

            float u = (float)i/(w);
            float v = (float)j/(h);
            VEC3 unit_dir;
            VEC3 color;

            tmp_h = VEC3_scale(u, &horizontal);
            tmp_v = VEC3_scale(v, &vertical);

            dir = VEC3_add(&lower_left, &tmp_h);
            dir = VEC3_add(&dir, &tmp_v);



            unit_dir = VEC3_unit(&dir);

            float t = 0.5 * (unit_dir.y + 1.0f);
            color = VEC3_lerp(&white, &blue, t);

            int ir =  (int)(color.x * 255.99);
            int ig =  (int)(color.y * 255.99);
            int ib =  (int)(color.z * 255.99);

            for(int k = 2-1; k >= 0; k--){

                HIT_INFO record;
                bool bDraw_sphere = trace_circle(&origin, &dir, &sphere[k], 0.01, 10000000000000.0, &record);

                if(bDraw_sphere){

                    VEC3 normal;
                    VEC3 at_t;

                    VEC3 other = VEC3_CON(0, 0, -1);
                    at_t = record.point;

                    normal = record.normal;

                    normal.x += 1.0;
                    normal.y += 1.0;
                    normal.z += 1.0;

                    normal = VEC3_scale(0.5, &normal);

                    VEC3_print(&normal);

                    // PINT(ir);PINT(ig);PINT(ib);NL;
                    ir =  (int)(normal.x * 255.99);
                    ig =  (int)(normal.y * 255.99);
                    ib =  (int)(normal.z * 255.99);


                }
            }


            PINT(ir);PINT(ig);PINT(ib);NL;



		}
	}
}
