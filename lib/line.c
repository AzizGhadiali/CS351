/*
  Aziz Ghadiali & Brit Biddle
  line.c
  February 22, 2018
  contains all functions for lines
  
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "ppmIO.h"
#include "color.h"
#include "point.h"
#include "line.h"

// Initialize a 2D line
void line_set2D(Line *l, double x0, double y0, double x1, double y1){
	Point start, end;
// 	Assign start and end coordinates
	start.val[0] = x0;
	start.val[1] = y0;
	start.val[2] = 0;
	start.val[3] = 1;
	end.val[0] = x1;
	end.val[1] = y1;
	end.val[2] = 0;
	end.val[3] = 1;
// 	Assign point values to the line
	l->a = start;
	l->b = end;
}

// initialize a line to ta and tb
void line_set(Line *l, Point ta, Point tb){
	l->a = ta;
	l->b = tb;
	l->zBuffer = 1;
}

// set the z-buffer flag to the given value
void line_zBuffer(Line *l, int flag){
	l-> zBuffer = flag;
}
	
// normalize the x and y values of the endpoints by their homogeneous coordinate.	
void line_normalize(Line *l){
	double h0 = l->a.val[3];
	double x0 = l->a.val[0];
	double y0 = l->a.val[1];
	
	double h1 = l->b.val[3];
	double x1 = l->b.val[0];
	double y1 = l->b.val[1];
	
	l->a.val[0] = x0/h0;
	l->a.val[1] = y0/h0;
	
	l->b.val[0] = x1/h1;
	l->b.val[1] = y1/h1;
}

// copy the line data structure
void line_copy(Line *to, Line *from){
	point_copy(&to->a, &from->a);
	point_copy(&to->b, &from->b);
	to->zBuffer = from->zBuffer;
}

double sign(double x){
	if(x>0){
		return 1;
	}
	else if(x<0){
		return -1;
	}
	else{
		return 0;
	}
}

// draw the line into src using color c and the z-buffer, if appropriate
void line_draw(Line *l, Image *src, Color c){

	int x,y,dy,swap,temp,s1,s2,e;
	double dz, dx, zInv, ztemp;
	float zBuf;

// 	get values from Line l
	double x0 = l->a.val[0];
	double y0 = l->a.val[1];
	double x1 = l->b.val[0];
	double y1 = l->b.val[1];
	double z0 = l->a.val[2];
	double z1 = l->b.val[2];
	
	zInv = 1/z0;
// 	printf("%f\n", z0);

	x = x0;
	y = y0;
	
// 	get absolute value of dx and dx and check the signs
	dx= abs(x1-x0);
	dy= abs(y1-y0);
	s1=sign(x1-x0);
	s2=sign(y1-y0);
	
	
// 	if the dy value is greater than the dx value, swap them
	if (dy>dx){
		temp = dx;
		dx = dy;
		dy = temp;
		swap = 1;
		
		ztemp = z0;
		z0 = z1;
		z1 = ztemp;
		
	}
	else{
		swap = 0;
		
	}
	
	dz = (1/z1)-(1/z0)/dx;
	
	
	
// set error value		
	e = 3*dy-2*dx;
	

// 	Draw line pixels based on octant
	image_setColor( src, y, x, c );
	
	if (l->zBuffer == 1){
		for(int i = 0; i<dx; i++){
			// 	set zBuffer value for current pixel
			if(x > 0 && x < src->cols && y > 0 && y < src->rows){
				zBuf = image_getz(src, y, x);
			
				if(zInv > zBuf){
					image_setz(src, y, x, zInv);
					image_setColor( src, y, x, c );
					
				}
			}
			if(e<0){
				if(swap == 1){
					y+=s2;
				}
				else{
					x+=s1;
				}
				e = e + (2*dy);
			}
			else{
				y += s2;
				x += s1;
				e = e + (2*dy-2*dx);
			}
			zInv += dz;

		}
				
	}
	
// 	if the zBuffer flag is 0
	else{
		for(int i = 0; i<dx; i++){
			image_setColor( src, y, x, c );
		
			if(e<0){
				if(swap == 1){
					y+=s2;
				}
				else{
					x+=s1;
				}
				e = e + (2*dy);
			}
			else{
				y += s2;
				x += s1;
				e = e + (2*dy-2*dx);
			}
			image_setColor( src, y1, x1, c );
			
		}
	}
	
}

// draw a dashed line
void line_drawDashed(Line *l, Image *src, Color c, int length){	

	double x,y,dx,dy,swap,temp,s1,s2,e;

// 	get values from Line l
	double x0 = l->a.val[0];
	double y0 = l->a.val[1];
	double x1 = l->b.val[0];
	double y1 = l->b.val[1];
	
	
	x = x0;
	y = y0;
	
// 	get absolute value of dx and dx and check the signs
	dx=fabs(x1-x0);
	dy=fabs(y1-y0);
	s1=sign(x1-x0);
	s2=sign(y1-y0);
	
	
// 	if the dy value is greater than the dx value, swap them
	if (dy>dx){
		temp = dx;
		dx = dy;
		dy = temp;
		swap = 1;
	}
	else{
		swap = 0;
	}
	
// set error value		
	e = 3*dy-2*dx;
	
// 	Draw line pixels based on octant
	image_setColor( src, y, x, c );
	int countC = 0;
	int countB = length;
	for(int i = 0; i<dx; i++){
		if(countC<5 && (countB == length) ){
			image_setColor( src, y, x, c );
			countC++;
		}
		
		if(countC == 5 && countB>0){
			countB--;
		}
		
		if (countC == 5 && countB == 0){
			countC = 0;
			countB = length;
		}
			
		
		if(e<0){
			if(swap == 1){
				y+=s2;
			}
			else{
				x+=s1;
			}
			e = e + (2*dy);
		}
		else{
			y += s2;
			x += s1;
			e = e + (2*dy-2*dx);
		}
		
		
		if(countC<5 && (countB == length) ){
			image_setColor( src, y1, x1, c );
			countC++;
		}
		
		if(countC == 5 && countB>0){
			countB--;
		}
		
		if (countC == 5 && countB == 0){
			countC = 0;
			countB = length;
		}
		
	}
}
	

	





