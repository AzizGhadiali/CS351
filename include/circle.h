// Aziz Ghadiali & Brit Biddle, Project 3, 2/18/18
// circle header file


#ifndef CIRCLE_H
#define CIRCLE_H

#include "image.h"
#include "color.h"
#include "point.h"


// define circle structure
typedef struct {

	double r;
	Point c;

} Circle;

// Prototypes

// initialize to center tc and radius tr
void circle_set(Circle *c, Point tc, double tr);

// draw the circle into src using color p
void circle_draw(Circle *c, Image *src, Color p);

// draw a filled circle into src using color p
void circle_drawFill(Circle *c, Image *src, Color p);

// void floodFill(Image *src, double x,double y, Color new);
void circle_drawLineFill(Circle *c, Image *src, Color val);

// Line fill
void lFill(Image *src, double cx, double cy, double e1, double e2, Color val);

// Flood fill
void floodFill(Image *src, Point o, Color new);

// Fill in a circle with a Horizontal gradient
void circle_drawFillGradientHor(Circle *c, Image *src, Color val1, Color val2);

// Fill in a circle with a Vertical gradient
void circle_drawFillGradientVert(Circle *c, Image *src, Color val1, Color val2);




#endif


