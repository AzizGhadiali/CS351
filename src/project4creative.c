 #include <stdio.h>
#include <stdlib.h>
#include "primitives.h"
#include "image.h"

/*
  Aziz Ghadiali
  Project 4
  3/2/18
  
  Creates a scene with a house, sun, and background using abstract textures
*/
int main(int argc, char *argv[]) {
	Image *src;
	Image *psrc, *psrc2, *psrc3, *psrc4, *psrc5, *psrc6, *psrc7;
	Polygon p, p1, p2, p3, p4, p5;
	Color Blue, Red, White, Green, Yellow;
	Point pt[20];
	Point pt1;
	Line frame1, frame2;
	Circle circ;
// create colors
	color_set(&Blue, 0.2, 0.1, 0.95 );
	color_set(&Red, 0.95, 0.1, 0.2 );
	color_set(&White, 1.0, 1.0, 1.0 );
	color_set(&Green, .2, 1.0, .1 );
	color_set(&Yellow, 1.0, 1.0, 0 );

	src = image_create(700, 700);
// read in textures
	psrc = image_read("fishpattern.ppm");
	psrc2 = image_read("bricks.ppm");
	psrc3 = image_read("wall.ppm");
	psrc4 = image_read("mosaic.ppm");
	psrc5 = image_read("geometric.ppm");
	psrc6 = image_read("grass.ppm");
	psrc7 = image_read("sky.ppm");

	
// draw sky
	point_set2D(&(pt[0]), 10 , 650);
	point_set2D(&(pt[1]), 650 , 650);
	point_set2D(&(pt[2]), 650 , 10);
	point_set2D(&(pt[3]), 10, 10);
	polygon_set(&p5, 4, &(pt[0]));
	polygon_drawFill(&p5, src, Green);
	polygon_drawFillPattern(&p5, src, psrc7, Green);
	
	point_set2D( &pt1, 100, 100 );
  	circle_set( &circ, pt1, 60 );
  	circle_drawFillGradientVert(&circ, src, Red, Yellow);
// draw grass
	point_set2D(&(pt[0]), 0 , 500);
	point_set2D(&(pt[1]), 0 , 700);
	point_set2D(&(pt[2]), 700 , 700);
	point_set2D(&(pt[3]), 700, 500);
	polygon_set(&p5, 4, &(pt[0]));
	polygon_drawFill(&p5, src, Green);
	polygon_drawFillPattern(&p5, src, psrc6, Green);
	
// draw roof top	
	point_set2D(&(pt[0]), 400 , 200);
	point_set2D(&(pt[1]), 490, 300);
	point_set2D(&(pt[2]), 320 , 300);

	polygon_set(&p1, 3, &(pt[0]));
	polygon_drawFill(&p1, src, White);
	polygon_drawFillPattern(&p1, src, psrc4, White);
	
	point_set2D(&(pt[0]), 100 , 200);
	point_set2D(&(pt[1]), 400, 200);
	point_set2D(&(pt[2]), 320 , 300);
	point_set2D(&(pt[3]), 20 , 300);

	polygon_set(&p, 4, &(pt[0]));
	polygon_drawFill(&p, src, Blue);
	polygon_drawFillPattern(&p, src, psrc3, Blue);

	

//   Draw long side wall
	point_set2D(&(pt[0]), 20 , 300);
	point_set2D(&(pt[1]), 20 , 500);
	point_set2D(&(pt[2]), 320 , 500);
	point_set2D(&(pt[3]), 320 , 300);
	polygon_set(&p2, 4, &(pt[0]));
	polygon_drawFill(&p2, src, Red);
	polygon_drawFillPattern(&p2, src, psrc2, Red);
  
// Draw front wall
	point_set2D(&(pt[0]), 320 , 500);
	point_set2D(&(pt[1]), 320 , 300);
	point_set2D(&(pt[2]), 490, 300);
	point_set2D(&(pt[3]), 490 , 500);
	polygon_set(&p3, 4, &(pt[0]));
	polygon_drawFill(&p3, src, Blue);
	polygon_drawFillPattern(&p3, src, psrc5, Blue);

// Draw window on long wall
	point_set2D(&(pt[0]), 50 , 350);
	point_set2D(&(pt[1]), 50 , 400);
	point_set2D(&(pt[2]), 200 , 400);
	point_set2D(&(pt[3]), 200 , 350);
	polygon_set(&p4, 4, &(pt[0]));
	polygon_drawFill(&p4, src, Blue);
	polygon_drawFillPattern(&p4, src, psrc, Blue);
	
	line_set2D( &frame1, 50, 375, 200, 375);
	line_draw( &frame1, src, Blue );
	line_set2D( &frame2, 125, 350, 125, 400);
	line_draw( &frame2, src, Blue );

	polygon_drawFillPattern(&p4, src, psrc, Blue);
  
	printf("writing output\n");
	image_write(src, "project3creative2.ppm");
  
}