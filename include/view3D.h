// Aziz Ghadiali, Project 5, 2/18/18
// view3D header file

#ifndef VIEW3D_H
#define VIEW3D_H

#include "primitives.h"
#include "matrix.h"


// define vector structure
typedef struct {

	Point vrp;
	Vector vpn;
	Vector vup;
	double d;
	double du;
	double dv;
	double f;
	double b;
	int screenx;
	int screeny;
	
} View3D;

/* When the function returns, the vtm should contain the complete view matrix. Inside the function, begin by
initializing VTM to the identity. Do not modify any of the values in the PerspectiveView structure inside the
function (no side-effects).*/
void matrix_setView3D(Matrix *vtm, View3D *view);

void view3D_set( View3D *view, Point *vrp, float dx, double d, double dv, double f, double b, Vector *vpn, Vector *vup, float screenx, float screeny );

#endif
