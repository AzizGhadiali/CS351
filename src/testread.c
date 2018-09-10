/*
	Aziz Ghadiali
	Project 6
	Tests the polygon read function
*/

#include <stdio.h>
#include <stdlib.h>
#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "module.h"
#include "drawState.h"
#include "lighting.h"
#include "view3D.h"

int main(int argc, char *argv[]) {
  View3D view;
  Matrix vtm;
  Matrix gtm;
  Module *scene;
  Point vlist[8];
  DrawState *ds;
  Image *src;
  Polygon *p;
  FILE *fp;
  char filename[100] = "Polygon.txt";;


  point_set3D( &(view.vrp), 3, 2, 2 );
  vector_set( &(view.vpn), -3, -2, -2);
  vector_set( &(view.vup), 0, 1, 0 );
  view.d = 1;
  view.du = 2;
  view.dv = 1;
  view.f = 0;
  view.b = 0;
  view.screenx = 640;
  view.screeny = 360;

  ds = drawstate_create();
  src = image_create(view.screeny, view.screenx);


 	// setup gtm
 	matrix_identity( &gtm );
  
	// view3D_set( &view, &vrp, du, d, dv, f, b, &vpn, &vup, screenx, screeny );
 	matrix_setView3D( &vtm, &view );
 	scene = module_create();

  printf("%s\n", filename );

  p = polygon_read(fp, filename, vlist);
  module_translate(scene, 1, 1, 1);
  module_polygon(scene, p);
  module_scale(scene, .7, .7, .7);
  module_translate(scene, .1, .1, .1);
  module_polygon(scene, p);
  module_scale(scene, .3, .3, .3);
  module_translate(scene, .5, .5, .5);
  module_polygon(scene, p);
 	module_draw(scene, &vtm, &gtm, ds, NULL, src);



 	// module_delete(scene);
  image_write(src, "testread.ppm");

  module_delete(scene);
	// free drawstate
 	free( ds );

	// free image
 	image_free( src );

  return(0);
}
