#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "math/vec.h"
#include <float.h>
#include <stdbool.h>
#include <string.h>

#define PINT(x) printf("%u\t", x)
#define NL puts("")
#define N_SPHERES 8

typedef struct{
    VEC3 lower_left;
	VEC3 horizontal;
	VEC3 vertical;
	VEC3 origin;

}CAM;


VEC3 VEC3_ray_dir_for_cam(CAM *cam, float u, float v);



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
            record->normal = VEC3_sub(&(record->point), sphere);
            record->normal = VEC3_scale(1/sphere->a, &(record->normal));


            return true;
        }


        temp = (-b + sqrt(discriminant))/(a);
        if(temp > t_min && temp < t_max){
            record->t = temp;
            record->point = VEC3_ray_at(org, end, temp);
            record->normal = VEC3_sub(&(record->point), sphere);
            record->normal = VEC3_scale(1.0/(sphere->a), &(record->normal));


            return true;
        }

    }

    return false;

}


bool draw_spheres(VEC3 const *org, VEC3 const *end, VEC3 const spheres[], float t_min, float t_max, HIT_INFO *record)
{
    HIT_INFO temp_record;
    float closest_t = t_max;
    bool bHit = false;

    for(int k = N_SPHERES-1; k >= 0; k--){
        if(trace_circle(org, end, &spheres[k], t_min, closest_t, &temp_record)){
            bHit = true;
            closest_t = temp_record.t;
            *record = temp_record;
        }
    }

    return bHit;
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


    VEC3 light_src = {.x = 0.0, .y = 0.7, .z = -1.0};

    VEC3 white = {.x = 1.0, .y = 1.0, .z = 1.0};
    VEC3 blue = {.x = 0.5, .y = 0.7, .z = 1.0};

    VEC3 tmp_h;
    VEC3 tmp_v;
    VEC3 dir = {.x = 0.0, .y = 0.0, .z = 0.0};

    CAM cam;

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
    sphere[2].z = 0.4;
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
    sphere[6].z = 0.1;
    sphere[6].a = 0.2;


    sphere[1].x = 0;
    sphere[1].y = -100.5;
    sphere[1].z = -1;
    sphere[1].a = 100;

    memset(&cam, 0, sizeof(cam));
    cam.lower_left =(VEC3){.x = -2.0, .y = -1.0, .z = -1.0};
	cam.horizontal =(VEC3){.x =  4.0, .y = 0.0 , .z =  0.0};
	cam.vertical   = (VEC3){.x = 0.0, .y = 2.0 , .z =  0.0};
	cam.origin = (VEC3){.x = 0, .y = 0, .z = 0};

    VEC3 origin = {.x = 0, .y = 0, .z = 0};
    VEC3 prev_color =  {.x = 0, .y = 0, .z = 0};

    bool bAA = true; // anti aliasing
    int ns = 100;

    for(int j = h-1; j > 0; j--){
		for(int i = 0; i < w; i++){


            VEC3 unit_dir;
            VEC3 color = {.x = 0, .y = 0, .z = 0};


            int ir;
            int ig;
            int ib;

            for(int s=0; s < ns; s++){

                float u = ((float)i + ((float)(rand()%1000))/1000.0)/(w);
                float v = ((float)j + ((float)(rand()%1000))/1000.0)/(h);


                VEC3 dir  = VEC3_ray_dir_for_cam(&cam, u, v);
                unit_dir = VEC3_unit(&dir);



                HIT_INFO record;
                bool bDraw_sphere = draw_spheres(&cam.origin, &dir, sphere, 0.01, FLT_MAX, &record);

                if(bDraw_sphere){

                        VEC3 normal;
                        normal = record.normal;

                        normal.x += 1.0;
                        normal.y += 1.0;
                        normal.z += 1.0;

                        normal = VEC3_scale(0.5, &normal);


                        float distance;
                        VEC3 diff = VEC3_sub(&record.point, &light_src);
                        distance = VEC3_length(&diff) + 0.0001;


                        //color.x = normal.x;
                        //color.y = normal.y;
                        //color.z = normal.z;
                        color = VEC3_add(&color, &normal);
                        //apply light source
                        //ir *= 1.0/distance ;
                        //ig *= 1.0/distance ;
                        //ib *= 1.0/distance ;



                }else{
                    float t = 0.5 * (unit_dir.y + 1.0f);
                    VEC3 tmp = VEC3_lerp(&white, &blue, t);
                    color = VEC3_add(&tmp, &color);

                }
            }

                color = VEC3_scale(1.0/ns, &color);

            //this is blur lol
            //color = VEC3_add(&color, &prev_color);
            //color = VEC3_scale(0.2, &color);

            ir =  (int)(color.x * 255.99);
            ig =  (int)(color.y * 255.99);
            ib =  (int)(color.z * 255.99);

            PINT(ir);PINT(ig);PINT(ib);NL;
            //prev_color = color;


		}
	}
}


inline VEC3 VEC3_ray_dir_for_cam(CAM *cam, float u, float v)
{

            VEC3 tmp_h;
            VEC3 tmp_v;
            VEC3 dir = {.x = 0.0, .y = 0.0, .z = 0.0};
            VEC3 unit_dir;

            tmp_h = VEC3_scale(u, &cam->horizontal);
            tmp_v = VEC3_scale(v, &cam->vertical);

            dir = VEC3_add(&cam->lower_left, &tmp_h);
            dir = VEC3_add(&dir, &tmp_v);



            return dir;
}
