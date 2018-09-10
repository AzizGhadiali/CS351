#include <stdio.h>
#include <stdlib.h>
#include "primitives.h"
#include "image.h"

/*
  Aziz Ghadiali
  Project 4
  3/2/18
  Creates and image of a plane
*/
int main(int argc, char *argv[]) {
	Image *src;
	Polygon p;
	Color Blue, Red, White, Green, Yellow;
	Point pt[20];
	

	color_set(&Blue, 0.2, 0.1, 0.95 );
	color_set(&Red, 0.95, 0.1, 0.2 );
	color_set(&White, 1.0, 1.0, 1.0 );
	color_set(&Green, .2, 1.0, .1 );
	color_set(&Yellow, 1.0, 1.0, 0 );

	src = image_create(700, 700);
// Draw plane base
	point_set2D(&(pt[0]), 100 , 100);
	point_set2D(&(pt[1]), 500 , 100);
	point_set2D(&(pt[2]), 650 , 200);
	point_set2D(&(pt[3]), 100, 200);
	polygon_set(&p, 4, &(pt[0]));
	polygon_drawFill(&p, src, Yellow);
	
// 	Draw right wing
	point_set2D(&(pt[0]), 200 , 150);
	point_set2D(&(pt[1]), 400 , 150);
	point_set2D(&(pt[2]), 50 , 300);
	polygon_set(&p, 3, &(pt[0]));
	polygon_drawFill(&p, src, Red);

//  Draw left wing
	point_set2D(&(pt[0]), 300 , 200);
	point_set2D(&(pt[1]), 400 , 200);
	point_set2D(&(pt[2]), 250 , 300);
	polygon_set(&p, 3, &(pt[0]));
	polygon_drawFill(&p, src, Red);
	
// 	Rear
	point_set2D(&(pt[0]), 100 , 100);
	point_set2D(&(pt[1]), 100, 200);
	point_set2D(&(pt[2]), 30 , 200);
	point_set2D(&(pt[3]), 30 , 100);
	
	polygon_set(&p, 4, &(pt[0]));
	polygon_drawFill(&p, src, Blue);
	
	point_set2D(&(pt[0]), 30 , 100);
	point_set2D(&(pt[1]), 10 , 100);
	point_set2D(&(pt[2]), 27 , 120);
	point_set2D(&(pt[3]), 10 , 140);
	point_set2D(&(pt[4]), 26 , 160);
	point_set2D(&(pt[5]), 5 , 180);
	point_set2D(&(pt[6]), 30 , 200);
	polygon_set(&p, 7, &(pt[0]));
	polygon_drawFill(&p, src, Red);
	
	
	
	
	
	


	printf("writing output\n");
	image_write(src, "project3plane.ppm");
  
}