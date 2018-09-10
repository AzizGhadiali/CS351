/*
  Aziz Ghadiali

  Particle Test Code

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
#include "particles.h"

int main(int argc, char *argv[]) {
  Image *src;
  Matrix VTM;
  Matrix GTM;
  Vector velocity, acceleration;
  int rows = 360;
  int cols = 640;
  int i, x;

  Color Red = {{1.0, 0.1, 0.1}};
  Color Blue = {{0.2, 0.1, 1.0}};
  Color Green = {{0.2, 1.0, .1}};
  Color White = {{1.0, 1.0, 1.0 }};
  View3D view;

  // initialize the image
  src = image_create(rows, cols);

  // initialize matrices
  matrix_identity(&GTM);
  matrix_identity(&VTM);

  // set the View parameters
  point_set3D(&(view.vrp), 1, 1, 1);
  vector_set(&(view.vpn), -1, -1, -1);
  vector_set(&(view.vup), 0.0, 1.0, 0.0);
  vector_set(&(velocity), 0.0, 1.0, 0.0);
  vector_set(&(acceleration), 0.0, 1.0, 0.0);
  view.d = 2.0;
  view.du = 1;
  view.dv = 1;
  view.f = 0;
  view.b = 5;
  view.screenx = cols;
  view.screeny = rows;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  Emitter e, e1, e2, e3;
  Point p, p1, p2, p3;
  Vector v, a;
  
  point_set3D(&p, 250, 250, 1);
  point_set3D(&p1, 100, 100, 1);
  point_set3D(&p2, 300, 150, 1);
  point_set3D(&p3, 400, 200, 1);

  emitter_set(&e, 100, p);
  emitter_set(&e1, 100, p1);
  emitter_set(&e2, 100, p2);
   emitter_set(&e3, 100, p3);

  for(i = 0; i < 120; i++){
    updateState(&e, i, Blue, 100, 1, 1, 1, -.05 + i%10, -.05 + i%10, -.05 + i%10);
    // updateState(&e1, i, Red, 100, 1, 1, 1, -.05, -.05, .05);
    // updateState(&e2, i, Green, 100, 1, 1, 1, -.05, .05, -.05);
    // updateState(&e3, i, White, 100, 1, 1, 1, .05, -.1, -.05);

    for(x = 0; x < e.total; x++){
      particle_draw(&e.particles[x], src, &VTM, 1 );
      // particle_draw(&e1.particles[x], src, &VTM, 1);
      // particle_draw(&e2.particles[x], src, &VTM, 1 );
      // particle_draw(&e3.particles[x], src, &VTM, 1);
    }

    
    
    char buffer[256];
    sprintf(buffer, "particles%03d.ppm", i);
    image_write(src, buffer);
    image_reset(src);

  }
  

  // free stuff here
  image_free( src );
  

  return(0);
}
