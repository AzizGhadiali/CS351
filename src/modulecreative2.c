/*

Aziz Ghadiali 
4/12/18
test creative image 2

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
  Module *shape;
  Point c, c2, lp1, lp2;
  Polygon p1,p2;
  DrawState *ds;
  Image *src;
  Vector a,b,a2,b2;
  Point *v1,*v2; 
  Line l1;
  int x;
  double x0,y0,z0,x1,y1,z1;
  double start = 0;

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

  matrix_setView3D( &vtm, &view );
  
  

  ds = drawstate_create();
  src = image_create(view.screeny, view.screenx);

  // setup gtm
  matrix_identity( &gtm );

  // view3D_set( &view, &vrp, du, d, dv, f, b, &vpn, &vup, screenx, screeny );
  matrix_setView3D( &vtm, &view );

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
  module_polygon(shape, &p2);
  
  for (x = 0; x < 200; x ++){ 
    x0 = c.val[0] + (1)*cos(start)*a.val[0] + (1)*sin(start)*b.val[0];
    y0 = c.val[1] + (1)*cos(start)*a.val[1] + (1)*sin(start)*b.val[1];
    z0 = c.val[2] + (1)*cos(start)*a.val[2] + (1)*sin(start)*b.val[2];
    lp1 = (Point) {{x0, y0, z0, 1}}; 

    x1 = c2.val[0] + (2)*cos(start)*a2.val[0] + (2)*sin(start)*b2.val[0];
    y1 = c2.val[1] + (2)*cos(start)*a2.val[1] + (2)*sin(start)*b2.val[1];
    z1 = c2.val[2] + (2)*cos(start)*a2.val[2] + (2)*sin(start)*b2.val[2];
    lp2 = (Point) {{x1, y1, z1, 1}}; 

    start += (2*3.14159)/200; 
    line_set(&l1, lp1, lp2);

    module_line(shape, &l1);

  }

  point_set3D( &c, 1.0, 1.0, 1.0 );
  vector_set( &a, 0, 0, 1);
  vector_set( &b, 1, 1, 0 );
  polygon_create_circle_3D(&p1, &c, 1, 200, &a, &b, v1);

  point_set3D( &c2, 1.0, 1.0, 1.0 );
  vector_set( &a2, 0, 0, 1);
  vector_set( &b2, 0, 1, 0 );
  polygon_create_circle_3D(&p2, &c2, 3, 200, &a2, &b2, v2);

  for (x = 0; x < 200; x ++){ 
    x0 = c.val[0] + (1)*cos(start)*a.val[0] + (1)*sin(start)*b.val[0];
    y0 = c.val[1] + (1)*cos(start)*a.val[1] + (1)*sin(start)*b.val[1];
    z0 = c.val[2] + (1)*cos(start)*a.val[2] + (1)*sin(start)*b.val[2];
    lp1 = (Point) {{x0, y0, z0, 1}}; 

    x1 = c2.val[0] + (3)*cos(start)*a2.val[0] + (3)*sin(start)*b2.val[0];
    y1 = c2.val[1] + (3)*cos(start)*a2.val[1] + (3)*sin(start)*b2.val[1];
    z1 = c2.val[2] + (3)*cos(start)*a2.val[2] + (3)*sin(start)*b2.val[2];
    lp2 = (Point) {{x1, y1, z1, 1}}; 

    start += (2*3.14159)/200; 
    line_set(&l1, lp1, lp2);

    module_line(shape, &l1);

  }

  point_set3D( &c, 1.0, 1.0, 1.0 );
  vector_set( &a, 0, 0, 1);
  vector_set( &b, 1, 1, 0 );
  polygon_create_circle_3D(&p1, &c, 1, 200, &a, &b, v1);

  point_set3D( &c2, 1.0, 1.0, 1.0 );
  vector_set( &a2, 0, 0, 1);
  vector_set( &b2, 0, 1, 0 );
  polygon_create_circle_3D(&p2, &c2, 1, 200, &a2, &b2, v2);

  for (x = 0; x < 200; x ++){ 
    x0 = c.val[0] + (1)*cos(start)*a.val[0] + (1)*sin(start)*b.val[0];
    y0 = c.val[1] + (1)*cos(start)*a.val[1] + (1)*sin(start)*b.val[1];
    z0 = c.val[2] + (1)*cos(start)*a.val[2] + (1)*sin(start)*b.val[2];
    lp1 = (Point) {{x0, y0, z0, 1}}; 

    x1 = c2.val[0] + (3)*cos(start)*a2.val[0] + (3)*sin(start)*b2.val[0];
    y1 = c2.val[1] + (3)*cos(start)*a2.val[1] + (3)*sin(start)*b2.val[1];
    z1 = c2.val[2] + (3)*cos(start)*a2.val[2] + (3)*sin(start)*b2.val[2];
    lp2 = (Point) {{x1, y1, z1, 1}}; 

    start += (2*3.14159)/200; 
    line_set(&l1, lp1, lp2);

    module_line(shape, &l1);

  }
  
  module_draw(shape, &vtm, &gtm, ds, NULL, src);

  // module_delete(scene);
  image_write(src, "test3Dstructure9.ppm"); 
  
  module_delete(shape);
  // free drawstate
  free( ds );
  free(v1);
  free(v2);

  // free image
  image_free( src );
  

  return(0);
}

