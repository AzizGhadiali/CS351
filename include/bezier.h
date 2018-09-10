/*
  Aziz Ghadiali
  bezier.h
  April 16, 2018
  contains all functions for bezier curves and surfaces
  
*/

#ifndef BEZIER_H
#define BEZIER_H



// Element structure
typedef struct {
	
	Point ctrl[4];
	int zBuffer;
	
} BezierCurve;

typedef struct {

	Point ctrl[16];
	int zBuffer;
	
} BezierSurface;

// – sets the zbuffer flag to 1 and the curve points to the X-axis between 0 and 1.
void bezierCurve_init(BezierCurve *b);

// – sets the zbuffer flag to 1 and the surface to the X-Z plane between (0, 0) and (1, 1).
void bezierSurface_init(BezierSurface *b);

// – sets the control points of the BezierCurve to the four points in the vlist array.
void bezierCurve_set(BezierCurve *b, Point *vlist);

// – sets the control points of the BezierSurface to the 16 points in the vlist array.
void bezierSurface_set(BezierSurface *b, Point *vlist);

// – sets the z-buffer flag to the given value.
void bezierCurve_zBuffer(BezierCurve *p, int flag);

// – sets the z-buffer flag to the given value.
void bezierSurface_zBuffer(BezierCurve *p, int flag);

/*– draws the Bezier curve, given in screen coordinates, into the image using the given color. The
function should be adaptive so that it uses an appropriate number of line segments to draw the curve.
For example, if the bounding box of the control points is less than 10 pixels in the largest dimension,
then it is reasonable to draw the lines between the control points as an approximation to the curve.*/
void bezierCurve_draw(BezierCurve *b, Image *src, Color c);



#endif








