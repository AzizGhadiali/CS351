/*
  Aziz Ghadiali
  03/19/18
  Project 5 
  Complex Scene 2
  
  Creates a house floating in space

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
  Polygon side[4];
  Polygon recside[7];
  Polygon p;
  Image *src, *psrc;
  Point verts[5];
  Point recverts[5];
  Point pt[4];
  int i;
  char filename[256];
  Color Red, Green, White, Blue;



int main(int argc, char *argv[]) {
  	psrc = image_read("space.ppm");
//	 Create image objects and colors	
	src = image_create( 500, 500 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );
	color_set( &White, 1, 1, 1 );
	color_set( &Blue, 0, 0, 1 );

// initialize polygons
  for(i=0;i<4;i++) {
    polygon_init( &side[i] );
  }

// Loop through frames and animate
   for(int i = 0; i<nFrames; i++){
   		image_fillrgb(src, 0.0, 0.0, 0.0);
   		point_set3D( &(view.vrp), 10-(2.4*(i+1)/nFrames), 1, 5);
   		vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2]);
		vector_set( &(view.vup), 1, 0, 0);
		view.d = 1+(i/50.0);	 // focal length
		view.du = 1;
		view.dv = view.du * (float)rows / cols;
		view.f = 0; // front clip plane
		view.b = 4; // back clip plane
		view.screenx = cols;
		view.screeny = rows;
		matrix_setView3D( &vtm, &view );
		
		// draw space backgroun
		point_set3D(&(pt[0]), 0 , 499, 100);
		point_set3D(&(pt[1]), 499 , 499, 100);
		point_set3D(&(pt[2]), 499 , 0, 100);
		point_set3D(&(pt[3]), 0, 0, 100);
		polygon_set(&p, 4, &(pt[0]));
		polygon_drawFill(&p, src, Blue);
		polygon_drawFillPattern(&p, src, psrc, Blue);
		
// 		Draws a roof and a house (created this before I made my rectangle function)
		point_set3D( &verts[0], 1, 0, .5 );
  		point_set3D( &verts[1],  0, 1, 0 );
  		point_set3D( &verts[2],  2,  1, 0 );
  		polygon_set( &side[0], 3, &(verts[0]) );
  		matrix_xformPolygon(&vtm, &side[0]);
		polygon_normalize( &side[0] );
		polygon_draw( &side[0], src, White );
		
		point_set3D( &verts[0], 1, 0, .5 );
  		point_set3D( &verts[1],  0, 1, 1 );
  		point_set3D( &verts[2],  0,  1, 0 );
  		polygon_set( &side[1], 3, &(verts[0]) );
  		matrix_xformPolygon(&vtm, &side[1]);
		polygon_normalize( &side[1] );
		polygon_draw( &side[1], src, White );
		
		point_set3D( &verts[0], 1, 0, .5 );
  		point_set3D( &verts[1],  2, 1, 1 );
  		point_set3D( &verts[2],  2,  1, 0);
  		polygon_set( &side[2], 3, &(verts[0]) );
  		matrix_xformPolygon(&vtm, &side[2]);
		polygon_normalize( &side[2] );
		polygon_draw( &side[2], src, White );
		
		point_set3D( &verts[0], 1, 0, .5 );
  		point_set3D( &verts[1],  0, 1, 1 );
  		point_set3D( &verts[2],  2,  1, 1);
  		polygon_set( &side[3], 3, &(verts[0]) );
  		matrix_xformPolygon(&vtm, &side[3]);
		polygon_normalize( &side[3] );
		polygon_draw( &side[3], src, White );
		
		point_set3D( &recverts[0],  0,  2, 0);
		point_set3D( &recverts[1], 0, 1, 0 );
  		point_set3D( &recverts[2],  2, 1, 0 );
  		point_set3D( &recverts[3],  2,  2, 0);
  		
  		polygon_set( &recside[0], 4, &(recverts[0]) );
  		matrix_xformPolygon(&vtm, &recside[0]);
		polygon_normalize( &recside[0] );
		polygon_draw( &recside[0], src, Red );
		
		point_set3D( &recverts[0],  2,  2, 0);
  		point_set3D( &recverts[1],  2,  2, 1);
  		point_set3D( &recverts[2],  2,  1, 1);
  		point_set3D( &recverts[3],  2,  1, 0);
  		
  		polygon_set( &recside[1], 4, &(recverts[0]) );
  		matrix_xformPolygon(&vtm, &recside[1]);
		polygon_normalize( &recside[1] );
		polygon_draw( &recside[1], src, Red );
		
		point_set3D( &recverts[0],  2,  1, 1);
		point_set3D( &recverts[1],  2,  2, 1);
		point_set3D( &recverts[2],  0,  2, 1);
		point_set3D( &recverts[3],  0,  1, 1);
	
		polygon_set( &recside[2], 4, &(recverts[0]) );
  		matrix_xformPolygon(&vtm, &recside[2]);
		polygon_normalize( &recside[2] );
		polygon_draw( &recside[2], src, Red );
		
		point_set3D( &recverts[0],  0,  1, 0);
		point_set3D( &recverts[1],  0,  2, 0);
		point_set3D( &recverts[2],  0,  2, 1);
		point_set3D( &recverts[3],  0,  1, 1);
	
		polygon_set( &recside[3], 4, &(recverts[0]) );
  		matrix_xformPolygon(&vtm, &recside[3]);
		polygon_normalize( &recside[3] );
		polygon_draw( &recside[3], src, Red );

// 		Write frame to file
		printf("writing file\n");
		sprintf(filename, "complexS2nfill-%04d.ppm", i);
		image_write( src, filename );
  }


  
  
	image_write(src, "complexScene2.ppm");
  // cleanup
  image_free( src );

  return(0);
}