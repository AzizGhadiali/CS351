/*
  Bruce Maxwell
  Fall 2014

  Test function for 3D matrix viewing
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "view3D.h"



int main(int argc, char *argv[]) {
  const int rows = 180;
  const int cols = 320;
  View3D view;
  Matrix vtm;
  Polygon side[6];
  Polygon tpoly;
  Point  tv[4];
  Point  v[8];
  Color  color[6];
  Image *src;
  int i;
  char filename[256];

  // set some colors
  color_set( &color[0], 0, 0, 1 );
  color_set( &color[1], 0, 1, 0 );
  color_set( &color[2], 1, 0, 0 );
  color_set( &color[3], 1, 0, 1 );
  color_set( &color[4], 0, 1, 1 );
  color_set( &color[5], 1, 1, 0 );

  // initialize polygons
  for(i=0;i<6;i++) {
    polygon_init( &side[i] );
  }

  // corners of a cube, centered at (0, 0, 0)
  point_set3D( &v[0], -1, -1, -1 );
  point_set3D( &v[1],  1, -1, -1 );
  point_set3D( &v[2],  1,  1, -1 );
  point_set3D( &v[3], -1,  1, -1 );
  point_set3D( &v[4], -1, -1,  1 );
  point_set3D( &v[5],  1, -1,  1 );
  point_set3D( &v[6],  1,  1,  1 );
  point_set3D( &v[7], -1,  1,  1 );

  // front side
  polygon_set( &side[0], 4, &(v[0]) );

  // back side
  polygon_set( &side[1], 4, &(v[4]) );

  // top side
  point_copy( &tv[0], &v[2] );
  point_copy( &tv[1], &v[3] );
  point_copy( &tv[2], &v[7] );
  point_copy( &tv[3], &v[6] );

  polygon_set( &side[2], 4, tv );

  // bottom side
  point_copy( &tv[0], &v[0] );
  point_copy( &tv[1], &v[1] );
  point_copy( &tv[2], &v[5] );
  point_copy( &tv[3], &v[4] );

  polygon_set( &side[3], 4, tv );

  // left side
  point_copy( &tv[0], &v[0] );
  point_copy( &tv[1], &v[3] );
  point_copy( &tv[2], &v[7] );
  point_copy( &tv[3], &v[4] );

  polygon_set( &side[4], 4, tv );

  // right side
  point_copy( &tv[0], &v[1] );
  point_copy( &tv[1], &v[2] );
  point_copy( &tv[2], &v[6] );
  point_copy( &tv[3], &v[5] );

  polygon_set( &side[5], 4, tv );

  // grab command line argument to determine viewpoint
  // and set up the view structure
  if( argc > 1 ) {
    float alpha = atof( argv[1] );
    if( alpha < 0.0 || alpha > 1.0 )
      alpha = 0.0;

    point_set3D( &(view.vrp), 3*alpha, 2*alpha, -2*alpha - (1.0-alpha)*3 );
  }
  else {
    point_set3D( &(view.vrp), 3, 2, -2 );
  }
  vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );

  vector_set( &(view.vup), 0, 1, 0 );
  view.d = 1;  // focal length
  view.du = 2;
  view.dv = view.du * (float)rows / cols;
  view.f = 0; // front clip plane
  view.b = 4; // back clip plane
  view.screenx = cols;
  view.screeny = rows;

  matrix_setView3D( &vtm, &view );

  // create image
  src = image_create( rows, cols );

  // use a temprary polygon to transform stuff
  polygon_init( &tpoly );

  printf("Drawing Polygons\n");
  printf("hi\n");
  for(i=0;i<6;i++) {
  	printf("hi\n");
    polygon_copy( &tpoly, &side[i] );
    printf("hi1\n");
    matrix_xformPolygon( &vtm, &tpoly );
	printf("hi2\n");
    // normalize by homogeneous coordinate before drawing
    polygon_normalize( &tpoly );
	printf("hi3\n");
    polygon_draw( &tpoly, src, color[i] );
    printf("hi4\n");
    polygon_print( &tpoly, stdout );
    
   
  }

  printf("Writing image\n");
  image_write( src, "cube.ppm" );


  return(0);
}
