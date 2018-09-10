/*
  Aziz Ghadiali
  view2D.c
  February 22, 2018
  contains all functions for 2D viewing
  
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "view2D.h"

// Set 2D view
void view2D_set( View2D *view, Point *vrp, float dx, Vector *xaxis, float screenx, float screeny ){
	
	point_copy(&(view->vrp), vrp);
	view->dx = dx;
	vector_copy(&(view->x), xaxis);
	view->screenx = screenx;
	view->screeny = screeny;
}
	

// Sets vtm to be the view transformation defined by the 2DView structure.
void matrix_setView2D(Matrix *vtm, View2D *view){
// 	screen rows and cols
	matrix_identity(vtm);
	
	int c = view->screenx;
	int r = view->screeny;
	
	
// 	center of view
	double vx = view->vrp.val[0];
	double vy = view->vrp.val[1];
	
	
// 	orient vector
	Vector x = view->x;
	vector_normalize(&x);
	double nx = x.val[0];
	double ny = x.val[1];
	
	
	double du = view->dx;
	double dv = (du*r)/c;
	
	
// 	translate to origin
	matrix_translate2D(vtm, -vx, -vy);

	
// 	rotate
	matrix_rotateZ(vtm, nx, -ny);
	
	
// 	scale
	matrix_scale2D(vtm, c/du, -r/dv);
	

// 	translate to image coords
	matrix_translate2D(vtm, c/2.0, r/2.0);
	
	
}
	
	
	







