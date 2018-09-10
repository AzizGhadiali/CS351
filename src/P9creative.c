/*
  Bruce A. Maxwell
  Fall 2014

  Example code for drawing a single cube

  C Version
*/
#include <stdio.h>
#include <stdlib.h>
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
  Image *src, *bg;
  Matrix VTM;
  Matrix GTM;
  Module *cube;
  int rows = 360;
  int cols = 640;
  int frame;

  Color White;
  Color Grey;
  Color DkGrey;
  Color Green;

  DrawState *ds;
  View3D view;

  Lighting *light, *light2;
  Point l2 = {{5,5,5}};

  color_set( &White, 1.0, 1.0, 1.0 );
  color_set( &Grey, 0.6, 0.62, 0.64 );
  color_set( &DkGrey, 0.1, 0.1, 0.1 );
  color_set( &Green, 0.2, 0.7, 0.2 );
  Color c1 = {{0.9, 0.1, 0.1}};
      Color c2 = {{0.9, 0.1, 0.2}};
      Color c3 = {{0.9, 0.1, 0.3}};
      Color c4 =  {{0.9,.1, .4}};
      Color c5 = {{0.9, 0.1, 0.5 }};
      Color c6 = {{0.9, 0.1, 0.6}};
      Color c7 = {{0.9, 0.1, 0.7}};
      Color c8 = {{0.9, 0.1, 0.8}};
      Color c9 =  {{0.9, .1, .9}};
      Color c10 = {{0.9, 0.1, 1.0 }};

  // initialize the image
  src = image_create(rows, cols);
  

  // initialize matrices
  matrix_identity(&GTM);
  matrix_identity(&VTM);

  // set the View parameters
  point_set3D(&(view.vrp), 10, 10, 10.0);
  vector_set(&(view.vpn), -10, -10, -10);
  vector_set(&(view.vup), 0.0, 1.0, 0.0);
  view.d = 2.0;
  view.du = 1;
  view.dv = .9;
  view.f = 0.0;
  view.b = 5;
  view.screenx = cols;
  view.screeny = rows;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  // make a simple cube module
  cube = module_create();

  // this would color the cube in ShadeConstant mode
  module_color( cube, &Grey );
    // set body and surface color values
  module_bodyColor( cube, &White );
  module_surfaceColor( cube, &Grey );

  // the example cube is blue (Y/-Y), red (Z/-Z), yellow (X/-X)
  // these colors should be the body colors
    module_translate(cube, -6,-10,-6);
    module_bodyColor(cube, &c1);
    module_cube(cube, 1);

    module_bodyColor(cube, &c2);
    module_translate(cube, 1, -1, 0);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c3);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c4);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c5);
    module_cube(cube, 1);

    module_translate(cube, 0, 1, -1);
    module_bodyColor(cube, &c6);
    module_cube(cube, 1);

    module_translate(cube, 1, 0, -1);
    module_bodyColor(cube, &c7);
    module_cube(cube, 1);

    module_translate(cube, 0, 1, -1);
    module_bodyColor(cube, &c8);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c9);
    module_cube(cube, 1);

    module_translate(cube, 0, 1, -1);
    module_bodyColor(cube, &c10);
    module_cube(cube, 1);

    module_translate(cube, -5, -1, -1);
    // 2nd 
    module_bodyColor(cube, &c1);
    module_cube(cube, 1);

    module_bodyColor(cube, &c2);
    module_translate(cube, 1, -1, 0);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c3);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c4);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c5);
    module_cube(cube, 1);

    module_translate(cube, 0, 1, -1);
    module_bodyColor(cube, &c6);
    module_cube(cube, 1);

    module_translate(cube, 1, 0, -1);
    module_bodyColor(cube, &c7);
    module_cube(cube, 1);

    module_translate(cube, 0, 1, -1);
    module_bodyColor(cube, &c8);
    module_cube(cube, 1);

    module_translate(cube, -1, 0, 1);
    module_bodyColor(cube, &c9);
    module_cube(cube, 1);

    module_translate(cube, 0, 1, -1);
    module_bodyColor(cube, &c10);
    module_cube(cube, 1);

    //  module_translate(cube, -2, -2, -2);
    // // 3rd
    // module_bodyColor(cube, &c1);
    // module_cube(cube, 1);

    // module_bodyColor(cube, &c2);
    // module_translate(cube, 1, -1, 0);
    // module_cube(cube, 1);

    // module_translate(cube, -1, 0, 1);
    // module_bodyColor(cube, &c3);
    // module_cube(cube, 1);

    // module_translate(cube, -1, 0, 1);
    // module_bodyColor(cube, &c4);
    // module_cube(cube, 1);

    // module_translate(cube, -1, 0, 1);
    // module_bodyColor(cube, &c5);
    // module_cube(cube, 1);

    // module_translate(cube, 0, 1, -1);
    // module_bodyColor(cube, &c6);
    // module_cube(cube, 1);

    // module_translate(cube, 1, 0, -1);
    // module_bodyColor(cube, &c7);
    // module_cube(cube, 1);

    // module_translate(cube, 0, 1, -1);
    // module_bodyColor(cube, &c8);
    // module_cube(cube, 1);

    // module_translate(cube, -1, 0, 1);
    // module_bodyColor(cube, &c9);
    // module_cube(cube, 1);

    // module_translate(cube, 0, 1, -1);
    // module_bodyColor(cube, &c10);
    // module_cube(cube, 1);



  // manually add a light source to the Lighting structure
  // put it in the same place as the eye in world space
  light = lighting_create();
  light2 = lighting_create();
  lighting_add( light, LightPoint, &c1, NULL, &(view.vrp), 0, 0 );
  lighting_add( light2, LightAmbient, &c10, NULL, &l2, 0.0, 0.0 );


  // set the shading to Gouraud
  ds = drawstate_create();
  
  point_copy((ds->viewer), &(view.vrp));
  // ds->shade = ShadeConstant;
  ds->shade = ShadeGouraud;
   // ds->shade = ShadeFlat;

for(frame=0;frame<1;frame++) {
    char buffer[256];
    matrix_identity(&GTM);
    
    matrix_rotateX(&GTM, cos(M_PI/30.0), sin(M_PI/30.0) );
    module_draw( cube, &VTM, &GTM, ds, light, src );

    sprintf(buffer, "P9creative%03d.ppm", frame);
    image_write(src, buffer);
    image_reset(src);
  }



  // write out the image
  // image_write(src, "test9a.ppm");

  // free stuff here
  module_delete( cube );
  image_free( src );
  

  return(0);
}
