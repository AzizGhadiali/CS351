/*
  Aziz Ghadiali
  03/19/18
  Project 5 
  Complex Scene 3

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

  const int nFrames = 50;
  const int rows = 500;
  const int cols = 500;
  View3D view;
  Matrix vtm;
  Polygon side[3];
  Image *src, *src2, *src3;
  Point verts[5];
  int i;
  char filename[256];
  char filename2[256];
  char filename3[256];
  Color Red, Green, White, Blue;


// Function to draw a 3D triangle 
static void drawT(double x, double y, double z, Image *dest, Color c){
		
		point_set3D(&(verts[0]), x , y, z+1);
		point_set3D(&(verts[1]), x, y+1, z);
		point_set3D(&(verts[2]), x+1 , y, z);
		polygon_set(&side[0], 3, &(verts[0]));
		matrix_xformPolygon(&vtm, &side[0]);
		polygon_normalize( &side[0] );
		polygon_draw(&side[0], dest, c);
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

// initialize polygons
  for(i=0;i<3;i++) {
    polygon_init( &side[i] );
  }
	int count = 25;
   for(int i = 0; i<nFrames; i++){
//    	Setup View
   		image_fillrgb(src, 0.0, 0.0, 0.0);
   		point_set3D( &(view.vrp), 3, 3, count);
   		count --;
   		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2]);
		vector_set( &(view.vup), 0, 0, 1);
		view.d = 1;	 // focal length
		view.du = 1;
		view.dv = view.du * (float)rows / cols;
		view.f = 0; // front clip plane
		view.b = 4; // back clip plane
		view.screenx = cols;
		view.screeny = rows;
		matrix_setView3D( &vtm, &view );
		
// 		Draw triangles in 3D space
		for(int a = 10; a>-10; a--){
			drawT(a,0,0, src, Red);
		}
		
		for(int e = 10; e>-10; e--){
			drawT(e,e,e,src2, Blue  );
		}
		
		for(int e = 10; e>-10; e--){
			drawT(e,0,e,src3, Green  );
		}
// 		Write frames to files
		printf("writing file\n");
		sprintf(filename, "complexS3_1_-%04d.ppm", i);

		printf("writing file\n");
		sprintf(filename2, "complexS3_2_-%04d.ppm", i);
		
		printf("writing file\n");
		sprintf(filename3, "complexS3_3_-%04d.ppm", i);
		
		image_write(src, filename);
		image_write(src2, filename2);
		image_write(src3, filename3);
  }


  
  
	
  // cleanup
  image_free( src );
  image_free( src2 );
  image_free( src3 );

  return(0);
}