/*
  Aziz Ghadiali
  sphere zBuffer test
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "module.h"
#include "drawState.h"
#include "lighting.h"
#include "bezier.h"
#include "view3D.h"

int main(int argc, char *argv[]) {
  Image *src;
  Matrix VTM;
  Matrix GTM;
  Module *shape;
  Vector a,b,a2,b2;
  Point c, c2;
  Polygon p1, p2;
  Point *v1, *v2;
  Point p[16];
  int rows = 360;
  int cols = 640;
  int i;

  Color Grey = {{0.6, 0.62, 0.64}};
  Color Red = {{1.0, 0.2, 0.14}};
  Color Blue = {{0.2, 0.1, 1}};
  

  DrawState *ds;
  View3D view;

  // initialize the image
  src = image_create(rows, cols);

  // initialize matrices
  matrix_identity(&GTM);
  matrix_identity(&VTM);

  // set the View parameters
 point_set3D( &(view.vrp), 3, 3, 3 );
  vector_set( &(view.vpn), -3, -3, -3);
  vector_set( &(view.vup), 0, 1, 0 );
  view.d = 1;
  view.du = 2;
  view.dv = 1;
  view.f = 0;
  view.b = 0;
  view.screenx = 640;
  view.screeny = 360;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  // make a simple md module
  shape = module_create();
 
	v1 = malloc(sizeof(Point)*200);
	v2 = malloc(sizeof(Point)*200);

  point_set3D( &c, 1.0, 1.0, 1.0 );
  vector_set( &a, 0, 0, 1);
  vector_set( &b, 1, 1, 0 );
  polygon_create_circle_3D(&p1, &c, 1, 200, &a, &b, v1);

  point_set3D( &c2, 1.0, 1.0, 1.0 );
  vector_set( &a2, 0, 0, 1);
  vector_set( &b2, 0, 1, 0 );
  polygon_create_circle_3D(&p2, &c2, 2, 200, &a2, &b2, v2);

  shape = module_create();
  module_polygon(shape, &p1);
 

  ds = drawstate_create();
  ds->shade = ShadeDepth;

 for(i=0;i<20;i++) {
    char buffer[256];
	
	matrix_setView3D(&VTM, &view);
	matrix_identity( &GTM );
	
    image_reset( src );
    module_draw(shape, &VTM, &GTM, ds, NULL, src);

    // write out the image
    sprintf(buffer, "zBufferSphere-%03d.ppm", i);
    image_write(src, buffer);
  }
  // free stuff here
  module_delete( shape );
  image_free( src );
  

  return(0);
}
