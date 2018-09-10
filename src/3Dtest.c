/*
  Aziz Ghadiali
  03/19/18
  Project 5 
  View3D test 

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "view3D.h"
#include "color.h"
#include "circle.h"

int main(int argc, char *argv[]) {
  const int nFrames = 100;
  const int rows = 1000;
  const int cols = 1000;
  View3D view;
  Matrix vtm;
  Polygon p;
  Image *src;
  Point pt[20];
  int i;
  char filename[256];
  Color Red, Green, White, Blue;
  
//	 Create image objects and colors
	src = image_create( 1000, 1000 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );
	color_set( &White, 1, 1, 1 );
	color_set( &Blue, 0, 0, 1 );

//   Loop through animation frames
   for(int i = 0; i<nFrames; i++){
   
//    Setup viewing 
   		image_fillrgb(src, 0.0, 0.0, 0.0);
   		vector_set( &(view.vpn), 1.8+(i/(double)nFrames*2), .2+(i/(double)nFrames*2), .5+(i/(double)nFrames*2));
		vector_set( &(view.vup), 100-i, 100-i, 100-i );
		view.d = 10000-(2*i);	 // focal length
		view.du = 1000-(2*i);
		view.dv = view.du * (float)rows / cols;
		view.f = 0; // front clip plane
		view.b = 4; // back clip plane
		view.screenx = cols;
		view.screeny = rows;
		matrix_setView3D( &vtm, &view );

// Create spaceship in 3D coordinates (4 rectangles for the wings and a diamond for the center)
		point_set3D(&(pt[0]), 525, 440, 100);
		point_set3D(&(pt[1]), 525, 410, 100);
		point_set3D(&(pt[2]), 700, 410, 100);
		point_set3D(&(pt[3]), 700 , 440, 100);
		polygon_set(&p, 4, &(pt[0]));
		matrix_xformPolygon(&vtm, &p);
		polygon_normalize( &p );
		polygon_drawFill(&p, src, Red);

		point_set3D(&(pt[0]), 700, 210, 100);
		point_set3D(&(pt[1]), 700 , 540, 100);
		point_set3D(&(pt[2]), 750 , 540, 100);
		point_set3D(&(pt[3]), 750, 210, 100);
		polygon_set(&p, 4, &(pt[0]));
		matrix_xformPolygon(&vtm, &p);
		polygon_normalize( &p );
		polygon_drawFill(&p, src, Blue);
		
		
		point_set3D(&(pt[0]), 475, 440, 100);
		point_set3D(&(pt[1]), 475, 410, 100);
		point_set3D(&(pt[2]), 300, 410, 100);
		point_set3D(&(pt[3]), 300 , 440, 100);
		polygon_set(&p, 4, &(pt[0]));
		matrix_xformPolygon(&vtm, &p);
		polygon_normalize( &p );
		polygon_drawFill(&p, src, Red);
			
			point_set3D(&(pt[0]), 300, 210, 100);
		point_set3D(&(pt[1]), 300 , 540, 100);
		point_set3D(&(pt[2]), 250 , 540, 100);
		point_set3D(&(pt[3]), 250, 210, 100);
		polygon_set(&p, 4, &(pt[0]));
		matrix_xformPolygon(&vtm, &p);
		polygon_normalize( &p );
		polygon_drawFill(&p, src, Blue);
		
		
		point_set3D(&(pt[0]), 500, 480, 100);
		point_set3D(&(pt[1]), 550, 425, 100);
		point_set3D(&(pt[2]), 500, 350, 100);
		point_set3D(&(pt[3]), 450 , 425, 100);
		polygon_set(&p, 4, &(pt[0]));
		matrix_xformPolygon(&vtm, &p);
		polygon_normalize( &p );
		polygon_drawFill(&p, src, Green);

// Write frame to image
		printf("writing file\n");
		sprintf(filename, "view3D-%04d.ppm", i);
		image_write( src, filename );
  }


  
  
	image_write(src, "3Dtest.ppm");
  // cleanup
  image_free( src );

  return(0);
}
