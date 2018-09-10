/*
  Aziz Ghadiali & Brit Biddle
  ellipse.c
  February 22, 2018
  contains all functions for ellipses
  
*/

//include
#include <stdio.h>
#include <stdlib.h>

//headers
#include "image.h"
#include "ppmIO.h"
#include "color.h"
#include "circle.h"
#include "line.h"
#include "ellipse.h"

//Implement the midpoint circle and ellipse algorithms (only standard orientation is required for ellipses) 
//as the basis for the draw functions for these types.

//initialize an ellipse to location tc and radii ta and tb.
void ellipse_set(Ellipse *e, Point tc, double ta, double tb){
	e->c = tc;
	e->ra = ta;
	e->rb = tb;
}

//draw into src using color p
void ellipse_draw(Ellipse *e, Image *src, Color val){
	double x,y,px,py,p;
	double rx = e->ra;
	double ry = e->rb;
	//x and y values
	double cx = e->c.val[0];
	double cy = e->c.val[1];
	
	//initialize values
	x = 0;
	//- y-axis radius
	y = -ry;
	//initial values of px and py
	px = 2 * ry * ry;
	py = 2 * rx * rx * -y;
	
	//plot the first set of points
	image_setColor( src, cy + x , cx + y, val );
	image_setColor( src, cy - x , cx + y, val );
	image_setColor( src, cy + x , cx - y, val );
	image_setColor( src, cy - x , cx - y, val );
	
	/* Region 1 */
	p = ry * ry - rx * rx * ry + rx*rx/4 + ry*ry + px;
	while(px < py){
		x--;
		px = px + 2 * ry * ry;
		if(p < 0){
			p = p + ry*ry + px;
		}
		else{
			y++;
			py = py - 2 * rx * rx;
			p = p + ry * ry + px - py;
		}
		//Plot(x + cx, y + cy) and its four reflections
		image_setColor( src, cy + x , cx + y, val );
		image_setColor( src, cy - x , cx + y, val );
		image_setColor( src, cy + x , cx - y, val );
		image_setColor( src, cy - x , cx - y, val );
	}
	//end region 1
	
	//region 2
	p = ry*ry * (x*x + x) + rx*rx * (y*y - 2*y + 1) -rx*rx * ry*ry+ rx*rx - py;
	while(y < 0){
		y++;
		py = py - 2 * rx * rx;
		if(p > 0){
			p = p + rx * rx - py;
		}
		else{
			x--;
			px = px + 2 * ry * ry;
			p = p + rx * rx - py + px;
		}
		//Plot (x + cx, y + cy) and its four reflections
		image_setColor( src, cy + x , cx + y, val );
		image_setColor( src, cy - x , cx + y, val );
		image_setColor( src, cy + x , cx - y, val );
		image_setColor( src, cy - x , cx - y, val );
	}
	//end region 2
}

// draw a filled ellipse into src using color p.
void ellipse_drawFill(Ellipse *e, Image *src, Color val){
	double x,y,px,py,p,tmp;
	double rx = e->ra;
	double ry = e->rb;
	//x and y values
	double cx = e->c.val[0];
	double cy = e->c.val[1];
	
	//initialize values
	x = -1;
	//- y-axis radius
	y = -ry;
	//initial values of px and py
	px = 2 * ry * ry;
	py = 2 * rx * rx * -y;
	
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
	
	//while loop code
	while(y < 0){
		y++;
		py = py - 2 * rx * rx;
		if(p > 0){
			p = p + rx * rx - py;
		}
		else{
			x--;
			px = px + 2 * ry * ry;
			p = p + rx * rx - py + px;
		}
		
		
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

