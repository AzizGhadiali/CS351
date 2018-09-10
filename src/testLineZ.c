/*
  * Maan Qraitem
  * CS351 - Proj08
  * Test zbuffer for lines.
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "module.h"
#include "drawState.h"
#include "lighting.h"
#include "bezier.h"
#include "view3D.h"


int main(int argc, char* argv[]){

  Color blue, green, purple, red, white;
  Matrix VTM, GTM;
  DrawState *ds;
  Module *scene;
  View3D view;
  int rows = 768, cols = 1024;
  int frame;
  Image *src = image_create(rows, cols);

	color_set(&white, 1.0, 1.0, 1.0 );
	color_set(&blue, .1, .2, .8);
	color_set(&green, .2, 0.7, 0.3 );
	color_set(&purple, 0.6, 0.1, 0.7 );
	color_set(&red, 0.75, 0.3, 0.3 );

  scene = module_create();

  module_color(scene, &red);
  module_cube(scene, 0);
  
  module_translate(scene, 0.1, 0, 0.5);
  
  module_color(scene, &blue);
  module_cube(scene, 0);

//   set up the drawstate
	ds = drawstate_create();
	

	// set up the view
	point_set3D(&(view.vrp),  3.0, 3.0, 3.0);
	vector_set( &(view.vpn),  -1.0, -1.0, -1.0 );
	vector_set( &(view.vup), 0.0, 1.0, 0.0 );
	view.d = 1.0;
	view.du = 1.0;
	view.dv = 1.0*rows/cols;
	view.screeny = rows;
	view.screenx = cols;
	view.f = 0.0;
	view.b = 1.0;

	matrix_setView3D( &VTM, &view );
	matrix_identity( &GTM );

	// Create the animation by adjusting the GTM
	for(frame=0;frame<1;frame++) {
		char buffer[256];

		matrix_rotateY(&GTM, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( scene, &VTM, &GTM, ds, NULL, src );

		sprintf(buffer, "zbuffer_test-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

  // clean up
	image_free( src );
	module_delete( scene );
	return(0);

}