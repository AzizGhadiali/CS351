/*
  Aziz Ghadiali
  03/19/18
  Project 5 
  Complex Scene 1

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
  Polygon side[3];
  Image *src;
  Point verts[5];
  int i;
  char filename[256];
  Color Red, Green, White, Blue;

// Function to draw a rectangular pyramid
static void drawPyramid(double x, double y, double z){
		
		point_set3D( &verts[0], x, y, z );
  		point_set3D( &verts[1],  x+1, y, z );
  		point_set3D( &verts[2],  x+1,  y+1, z );
  		polygon_set( &side[0], 3, &(verts[0]) );
  		matrix_xformPolygon(&vtm, &side[0]);
		polygon_normalize( &side[0] );
		polygon_draw( &side[0], src, Red );

  
  		point_set3D( &verts[0], x+1, y+1, z );
  		point_set3D( &verts[1],  x+1,  y, z );
  		point_set3D( &verts[2],  x+.5, y, z+1 );
  		polygon_set( &side[1], 3, &(verts[0]) );
  		polygon_draw( &side[1], src, Red );
  		matrix_xformPolygon(&vtm, &side[1]);
		polygon_normalize( &side[1] );
		polygon_draw( &side[1], src, Blue );
		
		point_set3D( &verts[0], x+1, y+1, z );
		point_set3D( &verts[1],  x+.5, y, z+1 );
  		point_set3D( &verts[2],  x,  y, z );
  		polygon_set( &side[2], 3, &(verts[0]) );
  		polygon_draw( &side[2], src, Red );
  		matrix_xformPolygon(&vtm, &side[2]);
		polygon_normalize( &side[2] );
		polygon_draw( &side[2], src, Green );
}

int main(int argc, char *argv[]) {
  
//	 Create image objects and colors	
	src = image_create( 500, 500 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );
	color_set( &White, 1, 1, 1 );
	color_set( &Blue, 0, 0, 1 );

// initialize polygons
  for(i=0;i<3;i++) {
    polygon_init( &side[i] );
  }
  
//   Loop through frames and animate
   for(int i = 0; i<nFrames; i++){
   		image_fillrgb(src, 0.0, 0.0, 0.0);
   		point_set3D( &(view.vrp), 10, i+1, i+1 );
   		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2]);
		vector_set( &(view.vup), 1, .5, .5);
		view.d = 1;	 // focal length
		view.du = 2;
		view.dv = view.du * (float)rows / cols;
		view.f = 0; // front clip plane
		view.b = 4; // back clip plane
		view.screenx = cols;
		view.screeny = rows;
		matrix_setView3D( &vtm, &view );
		
// 		Create objects in 3D space
		for (int x = 0; x<50; x++){
			
			drawPyramid(x, x, x);
			drawPyramid(x, x, x+5);
			drawPyramid(x, x+5, x);		
		}
		
// 		Write frames to image
		printf("writing file\n");
		sprintf(filename, "complexS1-%04d.ppm", i);
		image_write( src, filename );
  }


  
  
	image_write(src, "complexScene1.ppm");
  // cleanup
  image_free( src );

  return(0);
}