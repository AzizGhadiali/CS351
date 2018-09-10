/*
  Aziz Ghadiali

  Creating stacked cylinders in z space to show zBuffer works

  C Version
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
  BezierSurface bc;
  Module *md, *scene;
  Polygon p1;
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
  point_set3D(&(view.vrp), 5, 5, -7.0);
  vector_set(&(view.vpn), -5, -5, 7);
  vector_set(&(view.vup), 0.0, 1.0, 0.0);
  view.d = 1;
  view.du = 1.6;
  view.dv = .9;
  view.f = 0.0;
  view.b = 10;
  view.screenx = cols;
  view.screeny = rows;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  // make a simple md module
  md = module_create();
 
  module_translate(md, 0,-2,0);
  
  for(i = 0; i<10; i++){
	  module_color( md, &Red );
	  module_scale(md,1.5,1.5,1.5);
	  module_cylinder(md, &p1, 40);
	  module_translate(md, 0,1,0);
	  module_color( md, &Blue );
	  module_scale(md, .8,.8,.8);
	  module_cylinder(md, &p1, 40);
	  module_translate(md, 0,1,0);
	  module_scale(md, .5,.5,.5);
	  module_color( md, &Red );
	  module_cylinder(md, &p1, 40);
   }
 
 scene = module_create();
 module_module(scene, md);
 module_scale(md,.5,.5,.5);
 module_translate(scene, 0,0,4);
 module_module(scene, md);
 module_scale(md,.5,.5,.5);
 module_translate(scene, 4,0,0);
 module_module(scene, md);
 

  ds = drawstate_create();
  ds->shade = ShadeDepth;

 for(i=0;i<20;i++) {
    char buffer[256];
	view.b = 9+i;
	matrix_setView3D(&VTM, &view);
	
    image_reset( src );
    module_draw(scene, &VTM, &GTM, ds, NULL, src);

    // write out the image
    sprintf(buffer, "zBufferTestframe-%03d.ppm", i);
    image_write(src, buffer);
  }
  // free stuff here
  module_delete( md );
  image_free( src );
  

  return(0);
}
