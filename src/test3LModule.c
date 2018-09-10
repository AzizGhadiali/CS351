/*

Aziz Ghadiali 
4/12/18
test 3 layer scene

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "primitives.h"
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
	Module *building;
	Module *block;
	Module *city;
	Point p[8];
	DrawState *ds;
	Image *src, *src2, *src3;
	int i;

	Color Red =  { { 1.0, 0.2, 0.1 } };
	Color Green =  { { .2, 1, 0.1 } };
	Color Blue =  { { .2, 0.2, 1 } };



	point_set3D( &(view.vrp), 0, 0, 0 );
	vector_set( &(view.vpn), 1, 0, 0);
	// point_set3D( &(view.vrp), 10, 20, 15 );
	// vector_set( &(view.vpn), 1, 1, 1);
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
	src2 = image_create(view.screeny, view.screenx);
	src3 = image_create(view.screeny, view.screenx);


	// setup gtm
	matrix_identity( &gtm );

	// view3D_set( &view, &vrp, du, d, dv, f, b, &vpn, &vup, screenx, screeny );
	matrix_setView3D( &vtm, &view );

	building = module_create();
	module_scale( building, .5, 2, 1 );
	module_cube(building, 1);
	module_translate(building, 5, 0, 2);
	module_scale( building, .1, .2, .2 );
	module_cube(building, 1);
	module_translate(building, 0, -1, 0);
	module_cube(building, 1);
	module_translate(building, 0, 2, 0);
	module_cube(building, 1);
	module_translate(building, 0, 0, -.8);
	module_cube(building, 1);
	module_translate(building, 0, -1, 0);
	module_cube(building, 1);
	module_translate(building, 0, -1, 0);
	module_cube(building, 1);


	block = module_create();
	module_module( block, building );
	module_translate(block, 0, 0, -5);
	module_module( block, building );
	module_translate(block, -5, 0, 0);
	module_module( block, building );
	module_translate(block, 0, 0, 5);
	module_module( block, building );

	city = module_create();
	module_color( city, &Blue );	
	module_module( city, block );
	for(i=0;i<5;i++){
		module_translate(city, 0, 0, -10);
		module_module( city, block );
	}

	for(i=0;i<5;i++){
		module_color( city, &Green );
		module_translate(city, -10, 0, 0);
		module_module( city, block );
	}
	
	for(i=0;i<5;i++){
		module_color( city, &Red );
		module_translate(city, 0, 0, 10);
		module_module( city, block );
	}
	
	
	

	
	module_draw(building, &vtm, &gtm, ds, NULL, src);
	module_draw(block, &vtm, &gtm, ds, NULL, src2);
	module_draw(city, &vtm, &gtm, ds, NULL, src3);

	// module_delete(scene);
	image_write(src, "testbuilding.ppm");	
	// module_delete(scene);
	image_write(src2, "testblock.ppm");
	// module_delete(scene);
	// image_write(src3, "testcity.ppm");
	module_delete(building);
	module_delete(block);
	module_delete(city);
	// free drawstate
	free( ds );

	// free image
	image_free( src );
	// free image
	image_free( src2 );
	// free image
	image_free( src3 );

	return(0);
}













