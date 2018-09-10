// Aziz Ghadiali & Brit Biddle, Project 3, 2/18/18
// line header file

#ifndef LINE_H
#define LINE_H

#include "image.h"
#include "color.h"
#include "point.h"

// define line structure
typedef struct {

	int zBuffer;
	Point a;
	Point b;

} Line;

// Initialize a 2D line
void line_set2D(Line *l, double x0, double y0, double x1, double y1);

// initialize a line to ta and tb
void line_set(Line *l, Point ta, Point tb);

// set the z-buffer flag to the given value
void line_zBuffer(Line *l, int flag);

// normalize the x and y values of the endpoints by their homogeneous coordinate.	
void line_normalize(Line *l);

// copy the line data structure
void line_copy(Line *to, Line *from);

// draw the line into src using color c and the z-buffer, if appropriate
void line_draw(Line *l, Image *src, Color c);

// Check if x is negative or positive
double sign(double x);

// draw the dashed line into src using color c and the z-buffer, if appropriate
void line_drawDashed(Line *l, Image *src, Color c, int length);





#endif