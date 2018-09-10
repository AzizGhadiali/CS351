/*
  Aziz Ghadiali
  view3D.c
  February 22, 2018
  3-D viewing pipeline
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "view3D.h"

// Set 2D view
void view3D_set( View3D *view, Point *vrp, float dx, double d, double dv, double f, double b, Vector *vpn, Vector *vup, float screenx, float screeny ){
	
	point_copy(&(view->vrp), vrp);
	view->du = dx;
	view->d = d;
	view->dv = dv;
	view->f = f;
	view->b = b;
	vector_copy(&(view->vpn), vpn);
	vector_copy(&(view->vup), vup);
	view->screenx = screenx;
	view->screeny = screeny;
}

/* When the function returns, the vtm should contain the complete view matrix. Inside the function, begin by
initializing VTM to the identity. Do not modify any of the values in the PerspectiveView structure inside the
function (no side-effects).*/
void matrix_setView3D(Matrix *vtm, View3D *view){
// 	Initialize variables 
	Vector u;
	Point vrp;
	Vector vpn;
	Vector vup;
	double d = view->d;
	double du = view->du;
	double dv = view->dv;
	double f = view->f;
	double b = view->b;
	int screenx = view->screenx;
	int screeny = view->screeny;
	
// 	Make copy of point and vectors
	point_copy(&vrp, &view->vrp);
	vector_copy(&vpn, &view->vpn);
	vector_copy(&vup, &view->vup);

// 	Setup matrix and viewing vectors
	matrix_identity(vtm);
	vector_cross(&vup, &vpn, &u);
	vector_cross(&vpn, &u, &vup);
	
// 	Translate VRP to origin
	matrix_translate(vtm, -vrp.val[0], -vrp.val[1], -vrp.val[2]);
	printf("After VRP translation\n");
	matrix_print(vtm, stdout);
	
// 	Normalize vectors
	vector_normalize(&u);
	vector_normalize(&vup);
	vector_normalize(&vpn);
	
	printf("View ref axes\n");
	vector_print(&u, stdout);
	vector_print(&vup, stdout);
	vector_print(&vpn, stdout);
	
// 	Align the axes
	matrix_rotateXYZ(vtm, &u, &vup, &vpn);
	printf("After Rxyz\n");
	matrix_print(vtm, stdout);
	
// 	Translate COP to the origin
	matrix_translate(vtm, 0, 0, d);
	printf("After translating COP to origin\n");
	matrix_print(vtm, stdout);
	
// 	Scale to the canonical view volume
	double Bp = d+b;
	double sx = (2*d)/(Bp*du);
	double sy = (2*d)/(Bp*dv);
	double sz = 1/Bp;
	
	matrix_scale(vtm, sx, sy, sz);
	printf("After scaling to CVV\n");
	matrix_print(vtm, stdout);
	
//  Apply perspective	
	double dp = d/Bp;
	matrix_perspective(vtm, dp);
	printf("After perspective\n"); 
	matrix_print(vtm, stdout);
	
// 	Scale to image coordinates
	double sx2 = -screenx/(2*dp);
	double sy2 = -screeny/(2*dp);
	matrix_scale2D(vtm, sx2, sy2);
	
	printf("dp, screenx, screeny\n");
	printf("%f, %d, %d\n", dp, screenx, screeny);
	
	printf("After scale to image coords\n");
	matrix_print(vtm, stdout);
	
// 	Translate to image coordinates
	matrix_translate2D(vtm, screenx/2, screeny/2);
	printf("After final translation to image coords\n");
	matrix_print(vtm, stdout);
	
}
	
	
	
	







