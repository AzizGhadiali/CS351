// Aziz Ghadiali, Project 5, 2/18/18
// view2D header file

#ifndef VIEW2D_H
#define VIEW2D_H

#include "primitives.h"

// define vector structure
typedef struct {
// 	center of view
	Point vrp;
	
// 	width of view
	double dx;
	
// 	number of cols
	int screenx;

//  number of rows
	int screeny;

// 	normalized vector
	Vector x;
	
} View2D;

// Sets vtm to be the view transformation defined by the 2DView structure.
void matrix_setView2D(Matrix *vtm, View2D *view);

// Set 2D view
void view2D_set( View2D *view, Point *vrp, float dx, Vector *xaxis, float screenx, float screeny );

#endif
