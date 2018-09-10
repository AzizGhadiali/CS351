/*

Aziz Ghadiali 
4/12/18
test creative image 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primitives.h"
#include "polygon.h"
#include "matrix.h"
#include "vector.h"
#include "drawState.h"
#include "lighting.h"
#include "module.h"
#include "view3D.h"

int main(int argc, char *argv[]) {
  View3D view;
  Matrix vtm;
  Matrix gtm;
  Module *oct;
  Module *block;
  Point pt[8];
  Polygon p;
  DrawState *ds;
  Image *src;
  int i,x;

  Color Red =  { { 1.0, 0.2, 0.1 } };
  Color Green =  { { .2, 1, 0.1 } };
  Color Blue =  { { .2, 0.2, 1 } };

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

  matrix_setView3D( &vtm, &view );
  matrix_identity( &gtm );

  ds = drawstate_create();
  src = image_create(view.screeny, view.screenx);



  // setup gtm
  matrix_identity( &gtm );

  // view3D_set( &view, &vrp, du, d, dv, f, b, &vpn, &vup, screenx, screeny );
  matrix_setView3D( &vtm, &view );

  oct = module_create();
  polygon_init( &p );
  point_set3D( &pt[0], 1.0, 0.0, 1.0 );
  point_set3D( &pt[1], sqrt(2)/2, sqrt(2)/2, 1.0 );
  point_set3D( &pt[2], 0, 1.0, 1 );
  point_set3D( &pt[3], -sqrt(2)/2, sqrt(2)/2, 1.0 );
  point_set3D( &pt[4], -1.0, 0, 1 );
  point_set3D( &pt[5], -sqrt(2)/2, -sqrt(2)/2, 1.0 );
  point_set3D( &pt[6], 0, -1.0, 1 );
  point_set3D( &pt[7], sqrt(2)/2, -sqrt(2)/2, 1.0 );
  polygon_set( &p, 8, pt );
  module_polygon( oct, &p );


  block = module_create();
  for (i=0;i<20;i++){ 
    module_translate(block, 0, 0, -3);
    module_module( block,oct );
    module_scale(block,.7,.7,.7);
    for (x=0;x<20;x++){
      module_translate(block, -1, 0, 0);
      module_module( block,oct );
    }
    for (x=0;x<20;x++){
      module_translate(block, 0, -1, 0);
      module_module( block,oct );
    }
    for (x=0;x<20;x++){
      module_translate(block, 0, 0, -1);
      module_module( block,oct );
    }
    
    
    
  }
  
  // for (i=0;i<20;i++){ 
  //   module_translate(block, -3, 0, 0);
  //   module_module( block,oct );
  //   module_translate(block, 0, 0, 3);
  //   module_module( block,oct );
  // }
    
  // for (i=0;i<20;i++){ 
  //   module_translate(block, 0, 0, 3);
  //   module_module( block,oct );
  // }
  
  
  module_draw(block, &vtm, &gtm, ds, NULL, src);

  // module_delete(scene);
  image_write(src, "tesoct.ppm"); 
  
  module_delete(oct);
  module_delete(block);
  
  // free drawstate
  free( ds );

  // free image
  image_free( src );
  

  return(0);
}













