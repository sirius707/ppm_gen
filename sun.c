#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define PINT(x) printf("%u\t", x)
#define NL puts("")

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

	w = 1055;
	h = 1055;
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
}
