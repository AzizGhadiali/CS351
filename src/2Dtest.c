/*
  Aziz Ghadiali
  03/19/18
  Project 5 
  View2D test 

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "view2D.h"
#include "color.h"
#include "circle.h"

int main(int argc, char *argv[]) {
  const int nFrames = 50;
  const int rows = 1000;
  const int cols = 1000;
  View2D view;
  Matrix vtm;
  Polygon p;
  Point pt[20];
  char filename[256];
  Image *src;
  Color Red, Green, White, Blue;
  
//   animate through frames 
   for(int i = 0; i<nFrames; i++){
   
//    Setup 2D viewing
  	point_set2D( &(view.vrp), 200+(i*10), 500);
  	view.dx = 400.0-(i*2);
  	vector_set( &(view.x), 1.0, 1.0, 0.0 );
  	vector_print(&(view.x), stdout);
  	view.screenx = cols;
  	view.screeny = rows;

  	matrix_setView2D( &vtm, &view );

//   Create image objects and colors
	src = image_create( 1000, 1000 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );
	color_set( &White, 1, 1, 1 );
	color_set( &Blue, 0, 0, 1 );
	
// 	Create a space ship with 4 rectangles for the wings and a diamond for the center 
	point_set2D(&(pt[0]), 525, 440);
	point_set2D(&(pt[1]), 525, 410);
	point_set2D(&(pt[2]), 700, 410);
	point_set2D(&(pt[3]), 700 , 440);
	polygon_set(&p, 4, &(pt[0]));
	matrix_xformPolygon(&vtm, &p);
  	polygon_normalize( &p );
  	polygon_drawFill(&p, src, Red);
  	
	point_set2D(&(pt[0]), 700, 210);
	point_set2D(&(pt[1]), 700 , 540);
	point_set2D(&(pt[2]), 750 , 540);
	point_set2D(&(pt[3]), 750, 210);
	polygon_set(&p, 4, &(pt[0]));
	matrix_xformPolygon(&vtm, &p);
  	polygon_normalize( &p );
  	polygon_drawFill(&p, src, Blue);

	
	point_set2D(&(pt[0]), 475, 440);
	point_set2D(&(pt[1]), 475, 410);
	point_set2D(&(pt[2]), 300, 410);
	point_set2D(&(pt[3]), 300 , 440);
	polygon_set(&p, 4, &(pt[0]));
	matrix_xformPolygon(&vtm, &p);
  	polygon_normalize( &p );
  	polygon_drawFill(&p, src, Red);
  	
  	point_set2D(&(pt[0]), 300, 210);
	point_set2D(&(pt[1]), 300 , 540);
	point_set2D(&(pt[2]), 250 , 540);
	point_set2D(&(pt[3]), 250, 210);
	polygon_set(&p, 4, &(pt[0]));
	matrix_xformPolygon(&vtm, &p);
  	polygon_normalize( &p );
  	polygon_drawFill(&p, src, Blue);


	point_set2D(&(pt[0]), 500, 480);
	point_set2D(&(pt[1]), 550, 425);
	point_set2D(&(pt[2]), 500, 350);
	point_set2D(&(pt[3]), 450 , 425);
	polygon_set(&p, 4, &(pt[0]));
	matrix_xformPolygon(&vtm, &p);
  	polygon_normalize( &p );
  	polygon_drawFill(&p, src, Green);

// write file to ppm
  	printf("writing file\n");
    sprintf(filename, "view2D-%04d.ppm", i);
    image_write( src, filename );
  }


  
  
	image_write(src, "2Dtest.ppm");
  // cleanup
  image_free( src );

  return(0);
}
