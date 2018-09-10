// Aziz Ghadiali & Brit Biddle, Project 3, 2/18/18
// ellipse header file

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "image.h"
#include "color.h"
#include "point.h"


// define ellipse structure
typedef struct {

	double ra;
	double rb;
	Point c;
	

} Ellipse;

#endif

//initialize an ellipse to location tc and radii ta and tb.
void ellipse_set(Ellipse *e, Point tc, double ta, double tb);

//draw into src using color p
void ellipse_draw(Ellipse *e, Image *src, Color p);

// fills ellipse
void ellipse_drawFill(Ellipse *e, Image *src, Color val);
