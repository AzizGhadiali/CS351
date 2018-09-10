/*
  Aziz Ghadiali
  bezier.c
  April 16, 2018
  contains all functions for bezier curves and surfaces
  
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "module.h"
#include "drawState.h"
#include "lighting.h"
#include "bezier.h"

// – sets the zbuffer flag to 1 and the curve points to the X-axis between 0 and 1.
void bezierCurve_init(BezierCurve *b){
	int i;

	if(b == NULL){ return;}

	point_set3D(&b->ctrl[0],.1,0,0);
	point_set3D(&b->ctrl[1],.33,0,0);
	point_set3D(&b->ctrl[2],.66,0,0);
	point_set3D(&b->ctrl[3],1,0,0);


	b->zBuffer = 1;


}

// – sets the zbuffer flag to 1 and the surface to the X-Z plane between (0, 0) and (1, 1).
void bezierSurface_init(BezierSurface *b){
	int i;

	if(b == NULL){ return;}

	for(i = 0; i < 16; i++){
		point_set3D(&b->ctrl[i],i/15,0,i/16);
	}
	

	b->zBuffer = 1;
}

// – sets the control points of the BezierCurve to the four points in the vlist array.
void bezierCurve_set(BezierCurve *b, Point *vlist){
	int i;

	if(b == NULL){ return;}

	// allocate 4 Points using malloc, assign to b->ctrl
	for(i=0; i<4;i++){
		point_copy(&b->ctrl[i], &vlist[i]);
	}
}

// – sets the control points of the BezierSurface to the 16 points in the vlist array.
void bezierSurface_set(BezierSurface *b, Point *vlist){
	int i;

	if(b == NULL){ return;}

	// allocate 4 Points using malloc, assign to b->ctrl
	for(i=0; i<16;i++){
		point_copy(&b->ctrl[i], &vlist[i]);
	}

}

// – sets the z-buffer flag to the given value.
void bezierCurve_zBuffer(BezierCurve *p, int flag){
	p->zBuffer = flag;
}

// – sets the z-buffer flag to the given value.
void bezierSurface_zBuffer(BezierCurve *p, int flag){
	p->zBuffer = flag;
}

/*– draws the Bezier curve, given in screen coordinates, into the image using the given color. The
function should be adaptive so that it uses an appropriate number of line segments to draw the curve.
For example, if the bounding box of the control points is less than 10 pixels in the largest dimension,
then it is reasonable to draw the lines between the control points as an approximation to the curve.*/
void bezierCurve_draw(BezierCurve *b, Image *src, Color c){

	int xDiff = b->ctrl[3].val[0] - b->ctrl[0].val[0];
	int yDiff = b->ctrl[3].val[1] - b->ctrl[0].val[1];
	printf("%d\n",xDiff );
	printf("%d\n",yDiff );


	if(xDiff < 10 && yDiff < 10){
		Line l[3];

		line_set(&l[0], b->ctrl[0], b->ctrl[1]);
		line_set(&l[1], b->ctrl[1], b->ctrl[2]);
		line_set(&l[2], b->ctrl[2], b->ctrl[3]);

		line_draw(&l[0], src, c);
		line_draw(&l[1], src, c);
		line_draw(&l[2], src, c);
		return;
		
	}
	

	Point p1[4];
	Point p2[4];

	BezierCurve q;
	BezierCurve r;

	// q0
	point_copy(&p1[0], &b->ctrl[0]);

	// q1
	point_set3D(&p1[1], .5*(b->ctrl[0].val[0]+b->ctrl[1].val[0]), .5*(b->ctrl[0].val[1]+b->ctrl[1].val[1]), .5*(b->ctrl[0].val[2]+b->ctrl[1].val[2]));


	// q2
	point_set3D(&p1[2], .5 * (p1[1].val[0]) + .25*(b->ctrl[1].val[0] + b->ctrl[2].val[0]), .5*(p1[1].val[1]) + .25*(b->ctrl[1].val[1] + b->ctrl[2].val[1]), .5*(p1[1].val[2]) + .25*(b->ctrl[1].val[2] + b->ctrl[2].val[2])  );

	// r3
	point_copy(&p2[3], &b->ctrl[3]);

	// r2
	point_set3D(&p2[2], .5*(b->ctrl[2].val[0]+b->ctrl[3].val[0]), .5*(b->ctrl[2].val[1]+b->ctrl[3].val[1]), .5*(b->ctrl[2].val[2]+b->ctrl[3].val[2]));

	// r1
	point_set3D(&p2[1], .5*(p2[2].val[0]) +  .25*(b->ctrl[1].val[0] + b->ctrl[2].val[0]), .5*(p2[2].val[1]) +  .25*(b->ctrl[1].val[1] + b->ctrl[2].val[1]), .5*(p2[2].val[2]) +  .25*(b->ctrl[1].val[2] + b->ctrl[2].val[2])  );

	// q3
	point_set3D(&p1[3], .5*(p1[2].val[0] + p2[1].val[0]), .5*(p1[2].val[1] + p2[1].val[1]), .5*(p1[2].val[2] + p2[1].val[2]));

	 // r0
	point_copy(&p2[0], &p1[3]);

	bezierCurve_set(&q, &p1[0]);
	bezierCurve_set(&r, &p2[0]);

	bezierCurve_draw(&q, src, c);
	bezierCurve_draw(&r, src, c);
}





