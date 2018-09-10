/*
  Aziz Ghadiali & Brit Biddle
  circle.c
  February 22, 2018
  contains all functions for circles
  
*/

//include
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "ppmIO.h"
#include "color.h"
#include "circle.h"
#include "line.h"

// initialize to center tc and radius tr
void circle_set(Circle *c, Point tc, double tr){
	c->r = tr;
	c->c = tc;
}

// draw the circle into src using color p
void circle_draw(Circle *c, Image *src, Color val){
	double x,y,p;
	double r = c->r;
	double cx = c->c.val[0];
	double cy = c->c.val[1];
	
	x = 0;
	y = -r;
	p = 1-r;
	
// 	Set initial circle octant points
	image_setColor( src, cy + y, cx + x, val );
	image_setColor( src, cy - y , cx + x, val );
	image_setColor( src, cy + y , cx - x, val );
	image_setColor( src, cy - y , cx - x, val );
	image_setColor( src, cy + x , cx + y, val );
	image_setColor( src, cy - x , cx + y, val );
	image_setColor( src, cy + x , cx - y, val );
	image_setColor( src, cy - x , cx - y, val );
	
	
	while(x>=y){
		x--;
		if(p<0){
			p = p+1-2*x;
		}
		else{
			y++;
			p = p+1 - 2*(x-y);
		}
// 		Create the rest of the circle
		image_setColor( src, cy + y, cx + x, val );
		image_setColor( src, cy - y , cx + x, val );
		image_setColor( src, cy + y , cx - x, val );
		image_setColor( src, cy - y , cx - x, val );
		image_setColor( src, cy + x , cx + y, val );
		image_setColor( src, cy - x , cx + y, val );
		image_setColor( src, cy + x , cx - y, val );
		image_setColor( src, cy - x , cx - y, val );
		
		
	}
}
// extension
// flood fill object
void floodFill(Image *src, Point o, Color new)
{
// Creates a stack of size 10000 and sets the initial pixel color
	Point stack[5000];
	stack[0] = o;
	int top = 1;
	image_setColor(src,o.val[1], o.val[0], new);

/* 	While the stack is not empty, pop the top value off the stack and check its neighbors.
If the neighbor is not colored, color it, and add it onto the stack*/
	while(top>0){
	top--;
	Point currP = stack[top];
	
	double x = currP.val[0];
	double y = currP.val[1];

// 	Check right
	if (image_getColor(src, y, x+1).c[0] != new.c[0] &&image_getColor(src, y, x+1).c[1] != new.c[1] &&image_getColor(src, y, x+1).c[2] != new.c[2]){
		image_setColor(src,y, x+1, new);
        Point p1;
        point_set2D(&p1, x+1, y);
        stack[top] = p1;
        top++;
 
		
    }
    
//     Check top
    if (image_getColor(src, y+1, x).c[0] != new.c[0] && image_getColor(src, y+1, x).c[1] != new.c[1] &&image_getColor(src, y+1, x).c[2] != new.c[2]){
    	image_setColor(src,y+1, x, new);
		Point p1;
        point_set2D(&p1, x, y+1);
        stack[top] = p1;
        top++;

    }
    
//     Check left
	if (image_getColor(src, y, x-1).c[0] != new.c[0] && image_getColor(src, y, x-1).c[1] != new.c[1] && image_getColor(src, y, x-1).c[2] != new.c[2]){
		image_setColor(src,y, x-1, new);

		Point p1;
        point_set2D(&p1, x-1, y);
        stack[top] = p1;
        top++;

    }
    
//     Check bottom
    if (image_getColor(src, y-1, x).c[0] != new.c[0] && image_getColor(src, y-1, x).c[1] != new.c[1] && image_getColor(src, y-1, x).c[2] != new.c[2]){
    	image_setColor(src, y-1, x, new);
		Point p1;
        point_set2D(&p1, x, y-1);
        stack[top] = p1;
        top++;

    }
    
    
    }


}

// Fill circle with vertical gradient
void circle_drawFillGradientVert(Circle *c, Image *src, Color val1, Color val2){
	double x,y,p, tmp;
	double r = c->r;
	double cx = c->c.val[0];
	double cy = c->c.val[1];
	
	Color val;
	
	x = 0;
	y = -r;
	p = 1-r;
	
	int i = 0;
	double alpha = 0;
	
	i = 0;
	alpha = 0;
	for (tmp = cx+y; tmp< cx-y; tmp++){
		alpha = i/((cx-y)-(cx+y));
		i++;
		val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
		val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
		val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
		image_setColor( src, tmp , cy + x, val );
		image_setColor( src, tmp , cy + x, val );
	}
	
	i = 0;
	alpha = 0;
	for (tmp = cx+y; tmp< cx-y; tmp++){
		alpha = i/((cx-y)-(cx+y));
		i++;
		val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
		val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
		val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
		image_setColor( src, tmp , cy - x, val );
		image_setColor( src, tmp , cy - x, val );
	}
	
	
	while(x>=y){
		x--;
		if(p<0){
			p = p+1-2*x;
		}
		else{
			y++;
			p = p+1 - 2*(x-y);
		}
		
// 	Colors each col for the given rows
		i = 0;
		alpha = 0;
		for (tmp = cx+x; tmp< cx-x; tmp++){
			alpha = i/((cx-x)-(cx+x));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
			image_setColor( src, tmp , cy + y, val );
			image_setColor( src, tmp , cy + y, val );
		}
	
		i = 0;
		alpha = 0;
		for (tmp = cx+x; tmp< cx-x; tmp++){
			alpha = i/((cx-x)-(cx+x));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
			image_setColor( src, tmp , cy - y, val );
			image_setColor( src, tmp , cy - y, val );
		}
	
		i = 0;
		alpha = 0;
		for (tmp = cx+y; tmp< cx-y; tmp++){
			alpha = i/((cx-y)-(cx+y));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
			image_setColor( src, tmp , cy + x, val );
			image_setColor( src, tmp , cy + x, val );
		}
	
		i = 0;
		alpha = 0;
		for (tmp = cx+y; tmp< cx-y; tmp++){
			alpha = i/((cx-y)-(cx+y));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
			image_setColor( src, tmp , cy - x, val );
			image_setColor( src, tmp , cy - x, val );
		}
	
	}
	
	
}

// Fill in a circle with a horizontal gradient
void circle_drawFillGradientHor(Circle *c, Image *src, Color val1, Color val2){
	double x,y,p, tmp;
	double r = c->r;
	double cx = c->c.val[0];
	double cy = c->c.val[1];
	
	Color val;
	
	x = 0;
	y = -r;
	p = 1-r;
	
	int i = 0;
	double alpha = 0;
	for (tmp = cx+y; tmp< cx-y; tmp++){
		alpha = i/((cx-y)-(cx+y));
		i++;
		val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
		val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
		val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
		image_setColor( src, cy - x , tmp, val );
		image_setColor( src, cy - x , tmp, val );
	}
	i = 0;
	alpha = 0;
	for (tmp = cx+y; tmp< cx-y; tmp++){
		alpha = i/((cx-y)-(cx+y));
		i++;
		val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
		val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
		val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];
		image_setColor( src, cy + x , tmp, val );
		image_setColor( src, cy + x , tmp, val );
	}
	
	
	while(x>=y){
		x--;
		if(p<0){
			p = p+1-2*x;
		}
		else{
			y++;
			p = p+1 - 2*(x-y);
		}
		
// 	Colors each col for the given rows
		i = 0;
		alpha = 0;	
		for ( tmp = cx+x; tmp< cx-x; tmp++){
			alpha = i/((cx-x)-(cx+x));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];

			image_setColor( src, cy + y, tmp, val );
			image_setColor( src, cy + y , tmp, val );
		}
		i = 0;
		alpha = 0;
		for (tmp = cx+x; tmp< cx-x; tmp++){
			alpha = i/((cx-x)-(cx+x));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];

			image_setColor( src, cy - y , tmp, val );
			image_setColor( src, cy - y , tmp, val );
		}
		i = 0;
		alpha = 0;
		for (tmp = cx+y; tmp< cx-y; tmp++){
			alpha = i/((cx-y)-(cx+y));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];

			image_setColor( src, cy - x , tmp, val );
			image_setColor( src, cy - x , tmp, val );
		}
		i = 0;
		alpha = 0;
		for (tmp = cx+y; tmp< cx-y; tmp++){
			alpha = i/((cx-y)-(cx+y));
			i++;
			val.c[0] = alpha*val1.c[0] + (1-alpha)*val2.c[0];
			val.c[1] = alpha*val1.c[1] + (1-alpha)*val2.c[1];
			val.c[2] = alpha*val1.c[2] + (1-alpha)*val2.c[2];

			image_setColor( src, cy + x , tmp, val );
			image_setColor( src, cy + x , tmp, val );
		}
	
	}
	
	
}

// draw a filled circle into src using color p
void circle_drawFill(Circle *c, Image *src, Color val){
	double x,y,p, tmp;
	double r = c->r;
	double cx = c->c.val[0];
	double cy = c->c.val[1];
	
	x = 0;
	y = -r;
	p = 1-r;
	
// 	Colors each col for the given initial row
	for ( tmp = cx+x; tmp< cx-x; tmp++){
		image_setColor( src, cy + y, tmp, val );
		image_setColor( src, cy + y , tmp, val );
	}
	
	for (tmp = cx+x; tmp< cx-x; tmp++){
		image_setColor( src, cy - y , tmp, val );
		image_setColor( src, cy - y , tmp, val );
	}
	
	for (tmp = cx+y; tmp< cx-y; tmp++){
		image_setColor( src, cy - x , tmp, val );
		image_setColor( src, cy - x , tmp, val );
	}
	
	for (tmp = cx+y; tmp< cx-y; tmp++){
		image_setColor( src, cy + x , tmp, val );
		image_setColor( src, cy + x , tmp, val );
	}
	
	
	while(x>=y){
		x--;
		if(p<0){
			p = p+1-2*x;
		}
		else{
			y++;
			p = p+1 - 2*(x-y);
		}
		
// 	Colors each col for the given rows	
	for ( tmp = cx+x; tmp< cx-x; tmp++){
		image_setColor( src, cy + y, tmp, val );
		image_setColor( src, cy + y , tmp, val );
	}
	
	for (tmp = cx+x; tmp< cx-x; tmp++){
		image_setColor( src, cy - y , tmp, val );
		image_setColor( src, cy - y , tmp, val );
	}
	
	for (tmp = cx+y; tmp< cx-y; tmp++){
		image_setColor( src, cy - x , tmp, val );
		image_setColor( src, cy - x , tmp, val );
	}
	
	for (tmp = cx+y; tmp< cx-y; tmp++){
		image_setColor( src, cy + x , tmp, val );
		image_setColor( src, cy + x , tmp, val );
	}
	
	}
	
	
}


// extension
// draw a filled circle using line fill into src using color p
void circle_drawLineFill(Circle *c, Image *src, Color val){
	double x,y,p;
	double r = c->r;
	double cx = c->c.val[0];
	double cy = c->c.val[1];
	
	x = 0;
	y = -r;
	p = 1-r;

// Fills initial pixels using line fill function
	lFill(src, cx, cy, cx + x, cy + y, val);
	lFill(src, cx, cy, cx + x, cy - y, val);
	lFill(src, cx, cy, cx - x, cy + y, val);
	lFill(src, cx, cy, cx - x, cy - y, val);
	lFill(src, cx, cy, cx + y, cy + x, val);
	lFill(src, cx, cy, cx + y, cy - x, val);
	lFill(src, cx, cy, cx - y, cy + x, val);
	lFill(src, cx, cy, cx - y, cy - x, val);

	while(x>=y){
		x--;
		if(p<0){
			p = p+1-2*x;
		}
		else{
			y++;
			p = p+1 - 2*(x-y);
		}
	
// Fills pixels using line fill function
	lFill(src, cx, cy, cx + x, cy + y, val);
	lFill(src, cx, cy, cx + x, cy - y, val);
	lFill(src, cx, cy, cx - x, cy + y, val);
	lFill(src, cx, cy, cx - x,  cy - y, val);
	lFill(src, cx, cy, cx + y, cy + x, val);
	lFill(src, cx, cy, cx + y, cy - x, val);
	lFill(src, cx, cy, cx - y, cy + x, val);
	lFill(src, cx, cy, cx - y, cy - x, val);
	

	}
}

// function to draw a line in a circle
void lFill(Image *src, double cx, double cy, double e1, double e2, Color val){
	Point start;
	Point end;

	Line l1;
	start.val[0] = cx;
	start.val[1] = cy;

	l1.a = start;
	end.val[0] = e1;
	end.val[1] = e2;
	l1.b = end;

	line_draw(&l1, src, val);
}
	

