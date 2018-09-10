


/*
  Bruce A. Maxwell
  Fall 2014

  Example code for drawing a single car

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

void cylinder( Module *mod, int sides );
void cylinder( Module *mod, int sides ) {
  Polygon p;
  Point xtop, xbot;
  double x1, x2, z1, z2;
  int i;

  polygon_init( &p );
  point_set3D( &xtop, 0, 1.0, 0.0 );
  point_set3D( &xbot, 0, 0.0, 0.0 );

  // make a fan for the top and bottom sides
  // and quadrilaterals for the sides
  for(i=0;i<sides;i++) {
    Point pt[4];
    Vector n[4];
    int j;

    x1 = cos( i * M_PI * 2.0 / sides );
    z1 = sin( i * M_PI * 2.0 / sides );
    x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
    z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

    point_copy( &pt[0], &xtop );
    point_set3D( &pt[1], x1, 1.0, z1 );
    point_set3D( &pt[2], x2, 1.0, z2 );

    polygon_set( &p, 3, pt );
    for(j=0;j<3;j++)
      vector_set( &(n[j]), 0, 1, 0 );
    polygon_setNormals( &p, 3, n );
    module_polygon( mod, &p );

    point_copy( &pt[0], &xbot );
    point_set3D( &pt[1], x1, 0.0, z1 );
    point_set3D( &pt[2], x2, 0.0, z2 );

    polygon_set( &p, 3, pt );
    for(j=0;j<3;j++)
      vector_set( &(n[j]), 0, -1, 0 );
    polygon_setNormals( &p, 3, n );
    module_polygon( mod, &p );

    point_set3D( &pt[0], x1, 0.0, z1 );
    point_set3D( &pt[1], x2, 0.0, z2 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    point_set3D( &pt[3], x1, 1.0, z1 );

    vector_set( &n[0], x1, 0.0, z1 );
    vector_set( &n[1], x2, 0.0, z2 );
    vector_set( &n[2], x2, 0.0, z2 );
    vector_set( &n[3], x1, 0.0, z1 );
    
    polygon_set( &p, 4, pt );
    polygon_setNormals( &p, 4, n );
    module_polygon( mod, &p );
  }

  polygon_clear( &p );
}

int main(int argc, char *argv[]) {
  Image *src, *bg;
  Matrix VTM;
  Matrix GTM;
  Module *block, *group;
  int rows = 330;
  int cols = 640;

  Color White;
  Color Grey;
  Color DkGrey;

  DrawState *ds;
  View3D view;

  Lighting *light, *light2;

  color_set( &White, 1.0, 1.0, 1.0 );
  color_set( &Grey, 0.6, 0.62, 0.64 );
  color_set( &DkGrey, 0.1, 0.1, 0.1 );
  Color c1 = {{1.0, 0.1, 0.1}};
  Color c2 = {{0.1, 1.0, 0.1}};
  Color c3 = {{0.1, 0.1, 1.0}};
  Color c4 =  {{0.9,.1, .9}};
  Color c5 = {{0.4, 0.9, 0.5 }};
  Color c6 = {{0.3, 0.8, 0.6}};
  Color c7 = {{0.9, 0.1, 0.7}};
  Color c8 = {{0.4, 0.6, 0.8}};
  Color c9 =  {{0.6, 7, .9}};
  Color c10 = {{0.0, 0.0, .2 }};
  

  // initialize the image
  src = image_create(rows, cols);
  // bg = image_read("hpbg.ppm");
  // for(int x = 0; x < src->rows;x++ ){
  //   for(int j = 0; j<src->cols; j++){
  //     image_setColor(src, x, j, DkGrey);
  //   }
  // }

  // initialize matrices
  matrix_identity(&GTM);
  matrix_identity(&VTM);

  // set the View parameters
  point_set3D(&(view.vrp), 9, 10, 10.0);
  vector_set(&(view.vpn), -9, -10, -10);
  vector_set(&(view.vup), 0.0, 1.0, 0.0);
  view.d = 2;
  view.du = 1.6;
  view.dv = .9;
  view.f = 0.0;
  view.b = 5;
  view.screenx = cols;
  view.screeny = rows;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  // make a simple car module
  block = module_create();
  group = module_create();

  

  // this would color the car in ShadeConstant mode
    // set body and surface color values
  module_bodyColor( block, &White );
   module_surfaceColor( block, &c3 );

  // the example car is blue (Y/-Y), red (Z/-Z), yellow (X/-X)
  // these colors should be the body colors
  



  // manually add a light source to the Lighting structure
  // put it in the same place as the eye in world space
  light = lighting_create();
  light2 = lighting_create();
  lighting_add( light, LightPoint, &c10, NULL, &(view.vrp), 0, 0 );
  lighting_add( light2, LightAmbient, &White, NULL, &(view.vrp), 0.0, 0.0 );
  
  
    // module_cube(block, 1);

    // module_translate(block, 1.1, -1.1, 0);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c2 );

    // module_translate(block, -1.1, 0, 1.1);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c3 );

    // module_translate(block, 1.1, 0, 0);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c4 );

    // module_translate(block, 0, 1.1, 0);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c5 );

    // module_translate(block, 0, 0, -1.1);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c6 );

    // module_translate(block, -1.1, 0, 1.1);
   
    // module_cube(block, 1);

    module_cube(block, 1);

    module_translate(block, 0, 1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c3 );

    module_translate(block, 0, -2.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c3 );

    module_translate(block, 0, -1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c1 );

    module_translate(block, 0, 0, 1.1);
    module_cube(block, 1);
    module_surfaceColor( block, &c4 );

    module_translate(block, 0, 0, -2.1);
    module_cube(block, 1);
    module_surfaceColor( block, &c4 );

    module_translate(block, 0, 1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c4 );

    module_translate(block, 0, 1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c4 );

    module_translate(block, 0, 1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c5 );

    module_translate(block, 0, 0, -1.1);
    module_cube(block, 1);
    module_surfaceColor( block, &c5 );

    module_translate(block, 0, -1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c5 );

    module_translate(block, 0, -1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c5 );

    module_translate(block, 0, -1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c1);

    module_translate(block, 0, 1.1, 3.2);
    module_cube(block, 1);
    module_surfaceColor( block, &c1 );

    module_translate(block, 0, 1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c1 );

    module_translate(block, 0, 1.1, 0);
    module_cube(block, 1);
    module_surfaceColor( block, &c1 );


    // module_translate(block, -1.1, 0, 1.1);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c3 );

    // module_translate(block, 1.1, 0, 0);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c4 );

    // module_translate(block, 0, 1.1, 0);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c5 );

    // module_translate(block, 0, 0, -1.1);
    // module_cube(block, 1);
    // module_surfaceColor( block, &c6 );

    // module_translate(block, -1.1, 0, 1.1);
   


    module_module(group, block);
    module_translate(group, -1.1, 0, 0);
    module_module(group, block);
    module_translate(group, -1.1, 0, 0);
    module_module(group, block);
    module_translate(group, -1.1, 0, 0);
    module_module(group, block);
    // module_translate(group, 0, 2.1, 0);
    // module_module(group, block);
    // module_translate(group, 2.1, 0, 0);
    // module_module(group, block);
    // module_translate(group, 0, 0, 2.1);
    // module_module(group, block);
    // module_translate(group, -2.1, 0, 0);
    // module_module(group, block);
 
 


  





  // set the shading to Gouraud
  ds = drawstate_create();
  
  point_copy((ds->viewer), &(view.vrp));
  ds->shade = ShadeGouraud;
  //  ds->shade = ShadeFlat;
  for(int i = 0; i < 1; i++){
    char buffer[256];
    matrix_identity(&GTM);
    module_draw(group, &VTM, &GTM, ds, light, src);
    // write out the image
    sprintf(buffer, "creative9_4_%03d.ppm", i);
    image_write(src, buffer);
    image_reset(src);
  }

  // free stuff here
  module_delete( block );
  image_free( src );
  

  return(0);
}

// /*
//   Bruce A. Maxwell
//   Fall 2014

//   Example code for drawing a single car

//   C Version
// */
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <string.h>
// #include "primitives.h"
// #include "matrix.h"
// #include "vector.h"
// #include "module.h"
// #include "drawState.h"
// #include "lighting.h"
// #include "bezier.h"
// #include "view3D.h"

// void cylinder( Module *mod, int sides );
// void cylinder( Module *mod, int sides ) {
//   Polygon p;
//   Point xtop, xbot;
//   double x1, x2, z1, z2;
//   int i;

//   polygon_init( &p );
//   point_set3D( &xtop, 0, 1.0, 0.0 );
//   point_set3D( &xbot, 0, 0.0, 0.0 );

//   // make a fan for the top and bottom sides
//   // and quadrilaterals for the sides
//   for(i=0;i<sides;i++) {
//     Point pt[4];
//     Vector n[4];
//     int j;

//     x1 = cos( i * M_PI * 2.0 / sides );
//     z1 = sin( i * M_PI * 2.0 / sides );
//     x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
//     z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

//     point_copy( &pt[0], &xtop );
//     point_set3D( &pt[1], x1, 1.0, z1 );
//     point_set3D( &pt[2], x2, 1.0, z2 );

//     polygon_set( &p, 3, pt );
//     for(j=0;j<3;j++)
//       vector_set( &(n[j]), 0, 1, 0 );
//     polygon_setNormals( &p, 3, n );
//     module_polygon( mod, &p );

//     point_copy( &pt[0], &xbot );
//     point_set3D( &pt[1], x1, 0.0, z1 );
//     point_set3D( &pt[2], x2, 0.0, z2 );

//     polygon_set( &p, 3, pt );
//     for(j=0;j<3;j++)
//       vector_set( &(n[j]), 0, -1, 0 );
//     polygon_setNormals( &p, 3, n );
//     module_polygon( mod, &p );

//     point_set3D( &pt[0], x1, 0.0, z1 );
//     point_set3D( &pt[1], x2, 0.0, z2 );
//     point_set3D( &pt[2], x2, 1.0, z2 );
//     point_set3D( &pt[3], x1, 1.0, z1 );

//     vector_set( &n[0], x1, 0.0, z1 );
//     vector_set( &n[1], x2, 0.0, z2 );
//     vector_set( &n[2], x2, 0.0, z2 );
//     vector_set( &n[3], x1, 0.0, z1 );
    
//     polygon_set( &p, 4, pt );
//     polygon_setNormals( &p, 4, n );
//     module_polygon( mod, &p );
//   }

//   polygon_clear( &p );
// }

// int main(int argc, char *argv[]) {
//   Image *src, *bg;
//   Matrix VTM;
//   Matrix GTM;
//   Module *car, *bunch;
//   int rows = 330;
//   int cols = 640;

//   Color White;
//   Color Grey;
// 	Color DkGrey;

//   DrawState *ds;
//   View3D view;

//   Lighting *light, *light2;

// 	color_set( &White, 1.0, 1.0, 1.0 );
// 	color_set( &Grey, 0.6, 0.62, 0.64 );
// 	color_set( &DkGrey, 0.1, 0.1, 0.1 );
//   Color c1 = {{0.9, 0.1, 0.1}};
//       Color c2 = {{0.9, 0.9, 0.2}};
//       Color c3 = {{0.6, 0.4, 0.8}};
//       Color c4 =  {{0.9,.1, .4}};
//       Color c5 = {{0.9, 0.1, 0.5 }};
//       Color c6 = {{0.9, 0.1, 0.6}};
//       Color c7 = {{0.9, 0.1, 0.7}};
//       Color c8 = {{0.9, 0.1, 0.8}};
//       Color c9 =  {{0.9, .1, .9}};
//       Color c10 = {{0.9, 0.1, 1.0 }};
  

//   // initialize the image
//   src = image_create(rows, cols);
//   bg = image_read("hpbg.ppm");
//   for(int x = 0; x < src->rows;x++ ){
//     for(int j = 0; j<src->cols; j++){
//       Color c = image_getColor( bg, x, j);
//       image_setColor(src, x, j, c);
//     }
//   }

//   // initialize matrices
//   matrix_identity(&GTM);
//   matrix_identity(&VTM);

//   // set the View parameters
//   point_set3D(&(view.vrp), 9, 10, 10.0);
//   vector_set(&(view.vpn), -9, -10, -10);
//   vector_set(&(view.vup), 0.0, 1.0, 0.0);
//   view.d = .4;
//   view.du = 1.6;
//   view.dv = .9;
//   view.f = 0.0;
//   view.b = 5;
//   view.screenx = cols;
//   view.screeny = rows;
//   matrix_setView3D(&VTM, &view);

//   // print out VTM
//   printf("Final VTM: \n");
//   matrix_print(&VTM, stdout);

//   // make a simple car module
//   car = module_create();
//   bunch = module_create();

  

//   // this would color the car in ShadeConstant mode
//     // set body and surface color values
//   module_bodyColor( car, &White );

//   // the example car is blue (Y/-Y), red (Z/-Z), yellow (X/-X)
//   // these colors should be the body colors
  



//   // manually add a light source to the Lighting structure
//   // put it in the same place as the eye in world space
//   light = lighting_create();
//   light2 = lighting_create();
//   lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
//   lighting_add( light2, LightAmbient, &Grey, NULL, &(view.vrp), 0.0, 0.0 );
  
  
//   module_scale(car, 6,3,15);
//   module_translate(car, -3,5.5,-3);
//   module_surfaceColor(car, &c10);
//   module_cube(car, 1);
//   module_surfaceColor( car, &DkGrey );

//   module_scale(car, .26,.43,.17);
//   // module_translate(car, -3,0,0);
//   module_rotateX(car, cos(M_PI/2), sin(M_PI/2));
//   module_rotateY(car, cos(M_PI/2), sin(M_PI/2));
//   module_translate(car, -4,1,.5);
//   module_bodyColor(car, &c1);
//   cylinder( car, 30);
  
//   module_translate(car, 0,0,-10);
//   cylinder( car, 30);
//   module_translate(car, -5,0,0);
//   cylinder( car, 30);
//   module_translate(car, 0,0,10);
//   cylinder( car, 30);

//   module_module(bunch, car);

//   module_translate(bunch, 10, 0, 0);
//   module_module(bunch, car);
//   module_translate(bunch, -25, 0, 0);
//   module_module(bunch, car);
 
 


  





//   // set the shading to Gouraud
//   ds = drawstate_create();
	
//   point_copy((ds->viewer), &(view.vrp));
// 	ds->shade = ShadeGouraud;
// 	//	ds->shade = ShadeFlat;
//   for(int i = 0; i < 1; i++){
//     char buffer[256];
//     matrix_identity(&GTM);
//     module_draw(bunch, &VTM, &GTM, ds, light, src);
//     module_rotateX(bunch, cos(M_PI/3), sin(M_PI/3));
//     // write out the image
//     sprintf(buffer, "creative9_2_%03d.ppm", i);
//     image_write(src, buffer);
//     image_reset(src);
//   }

//   // free stuff here
//   module_delete( car );
//   image_free( src );
  

//   return(0);
// }
