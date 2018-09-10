/*
  Aziz Ghadiali
  03/19/18
  Project 5 
  Complex Scene 4

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

  const int nFrames = 100;
  const int rows = 500;
  const int cols = 500;
  View3D view;
  Matrix vtm;
  Polygon side[6];
  Image *src, *src2, *src3;
  Point v[7];
  Point tv[7];
  int i;
  char filename[256];
  char filename2[256];
  char filename3[256];
  Color Red, Green, White, Blue;


// Method to draw a rectangle at specified location with specified lengths
static void drawRect(double x, double dx, double y, double dy, double z, double dz){
		// initialize polygons
  		for(i=0;i<6;i++) {
    		polygon_init( &side[i] );
  		}
		
		point_set3D( &v[0], x-dx, y-dy, z-dz );
  		point_set3D( &v[1], x+dx, y-dy, z-dz);
  		point_set3D( &v[2],  x+dx,  y+dy, z-dz );
  		point_set3D( &v[3], x-dx,  y+dy, z-dz );
  		point_set3D( &v[4], x-dx, y-dy,  z+dz);
  		point_set3D( &v[5],  x+dx, y-dy,  z+dz);
  		point_set3D( &v[6],  x+dx,  y+dy,  z+dz);
  		point_set3D( &v[7], x-dx,  y+dy,  z+dz);
  		
// 		front
		polygon_set(&side[0], 4, &(v[0]));
		matrix_xformPolygon(&vtm, &side[0]);
		polygon_normalize( &side[0] );
		polygon_draw(&side[0], src, Blue);
		
// 		back
		polygon_set(&side[1], 4, &(v[4]));
		matrix_xformPolygon(&vtm, &side[1]);
		polygon_normalize( &side[1] );
		polygon_draw(&side[1], src, Red);
		
		point_copy( &tv[0], &v[2] );
  		point_copy( &tv[1], &v[3] );
  		point_copy( &tv[2], &v[7] );
  		point_copy( &tv[3], &v[6] );
  		
//   	top
  		polygon_set(&side[2], 4, &(tv[0]));
		matrix_xformPolygon(&vtm, &side[2]);
		polygon_normalize( &side[2] );
		polygon_draw(&side[2], src, Green);
		
		// bottom side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[1] );
		point_copy( &tv[2], &v[5] );
		point_copy( &tv[3], &v[4] );

		polygon_set( &side[3], 4, tv );
		
		polygon_set(&side[3], 4, &(tv[0]));
		matrix_xformPolygon(&vtm, &side[3]);
		polygon_normalize( &side[3] );
		polygon_draw(&side[3], src, Green);

//      left side
		point_copy( &tv[0], &v[0] );
		point_copy( &tv[1], &v[3] );
		point_copy( &tv[2], &v[7] );
		point_copy( &tv[3], &v[4] );

		polygon_set( &side[4], 4, tv );
		polygon_set(&side[4], 4, &(tv[0]));
		matrix_xformPolygon(&vtm, &side[4]);
		polygon_normalize( &side[4] );
		polygon_draw(&side[4], src, Green);
		
//      right side
		point_copy( &tv[0], &v[1] );
		point_copy( &tv[1], &v[2] );
		point_copy( &tv[2], &v[6] );
		point_copy( &tv[3], &v[5] );

		polygon_set( &side[5], 4, tv );
		polygon_set(&side[5], 4, &(tv[0]));
		matrix_xformPolygon(&vtm, &side[5]);
		polygon_normalize( &side[5] );
		polygon_draw(&side[5], src, Green);
		
		
}
 

int main(int argc, char *argv[]) {
//	 Create image objects and colors	
	src = image_create( 500, 500 );
	src2 = image_create( 500, 500 );
	src3 = image_create( 500, 500 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );
	color_set( &White, 1, 1, 1 );
	color_set( &Blue, 0, 0, 1 );

// Loop through animation frames
   for(int i = 0; i<nFrames; i++){
   		image_fillrgb(src, 0.0, 0.0, 0.0);
   		point_set3D( &(view.vrp), 7-(i/(double)nFrames*6.2), 7+(i/(double)nFrames*6.5), 7-(i/(double)nFrames*6.8));
   		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2]);
		vector_set( &(view.vup), 0, 1, 0);
		view.d = 1;	 // focal length
		view.du = 1;
		view.dv = view.du * (float)rows / cols;
		view.f = 0; // front clip plane
		view.b = 4; // back clip plane
		view.screenx = cols;
		view.screeny = rows;
		matrix_setView3D( &vtm, &view );
// 		Create the building
		for(int i = 0; i<10; i++){
			drawRect(1+i*.5, .2, 0, .2, 1, 1);
			drawRect(1+i*.5, 1, 0, .5, 1, 1);
			drawRect(1+i*.5, 1, 0, 1, 2, 1);
			drawRect(1+i*.5, 3, 0, .5, 3, 1);
			drawRect(1+i*.5, 4, 0, .5, 4, 1);
		}
		
		
// 		Write animation frame to ppm
		printf("writing file\n");
		sprintf(filename, "complexS4_1_-%04d.ppm", i);
		image_write(src, filename);
		
  }


  
  
	
  // cleanup
  image_free( src );
 
  return(0);
}