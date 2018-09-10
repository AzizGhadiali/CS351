#include <stdio.h>
#include <stdlib.h>
#include "primitives.h"
#include "image.h"

/*
  Program to test polygon functionality
*/
int main(int argc, char *argv[]) {
	Image *src;
	Polygon p;
	Color Blue, Red, White, Green, Yellow;
	Point pt[20];
	Point pt1;
	Circle circ;

	color_set(&Blue, 0.2, 0.1, 0.95 );
	color_set(&Red, 0.95, 0.1, 0.2 );
	color_set(&White, 1.0, 1.0, 1.0 );
	color_set(&Green, .2, 1.0, .1 );
	color_set(&Yellow, 1.0, 1.0, 0 );

	src = image_create(700, 500);

	
// draw sky
	point_set2D(&(pt[0]), 250 , 10);
	point_set2D(&(pt[1]), 300 , 58);
	point_set2D(&(pt[2]), 350 , 106);
	point_set2D(&(pt[3]), 400 , 154);
	point_set2D(&(pt[4]), 450 , 202);
	point_set2D(&(pt[5]), 500 , 58);
	point_set2D(&(pt[6]), 450 , 202);
	point_set2D(&(pt[7]), 400 , 154);
	point_set2D(&(pt[8]), 490 , 250);
	
	
	point_set2D(&(pt[9]), 250 , 490);
	point_set2D(&(pt[10]), 10, 250);
	polygon_set(&p, 11, &(pt[0]));
	polygon_drawFill(&p, src, Green);
	
// 	point_set2D( &pt1, 100, 100 );
//   	circle_set( &circ, pt1, 60 );
//   	circle_drawFillGradientHor(&circ, src, Red, Yellow);


  
	printf("writing output\n");
	image_write(src, "project4creative3.ppm");
  
}