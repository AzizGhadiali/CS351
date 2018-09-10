/*
  Aziz Ghadiali & Brit Biddle
  polygon.c
  February 22, 2018
  contains all functions for polygons
  
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"


// returns an allocated Polygon pointer initialized so that numVertex is 0 and vertex is NULL.
Polygon *polygon_create(){
	Polygon *p = malloc(sizeof(Polygon));
	p->nVertex = 0;
	p->vertex = NULL;
	p->normal = NULL;
	p->zBuffer = 1;
	return(p);
}
	
// returns an allocated Polygon pointer with the vertex list initialized to a copy of the points in vlist.
Polygon *polygon_createp(int numV, Point *vlist){
	Polygon *p = malloc(sizeof(Polygon));
	p->nVertex = numV;
	
// allocate numV Points using malloc, assign to p->vertex
	p->vertex = malloc(sizeof(Point)*numV);
	// for loop numV, copy vlist[i] to p->vertex[i]
	for(int i=0; i<numV;i++){
		p->vertex[i] = vlist[i];
	}
	return(p);
}
	

// frees the internal data for a Polygon and the Polygon pointer.
void polygon_free(Polygon *p){
	//check if p is not already null
	if(p != NULL){
		if(p->vertex !=NULL){
			free(p->vertex);
		}
		//free polygon space
		free(p);
	}
}

// initializes the existing Polygon to an empty Polygon.
void polygon_init(Polygon *p){
	if(p != NULL){
		p->zBuffer = 1;
		p->nVertex = 0;
		p->vertex = NULL;
		p->normal = NULL;
		p->color = NULL;
		p->oneSided = 1;
	}
}

// initializes the vertex array to the points in vlist.
void polygon_set(Polygon *p, int numV, Point *vlist){
	if (p->vertex != NULL){
		free(p->vertex);
	}
	p->nVertex = numV;
	
	// allocate numV Points using malloc, assign to p->vertex
	p->vertex = malloc(sizeof(Point)*numV);
 	//for every item in vlist allocate enough memory
	for(int i=0; i<numV;i++){
		p->vertex[i] = vlist[i];
	}

}

// frees the internal data and resets the fields.
void polygon_clear(Polygon *p){
	//check if p is not already null
	if(p != NULL){
		if(p->vertex != NULL){
			free(p->vertex);
		}
		if(p->color != NULL){
			free(p->color);
		}
		p->zBuffer = 1;
		p->nVertex = 0;
		p->vertex = NULL;
		p->color = NULL;
		p->oneSided = 1;
	}
	
}

// sets the oneSided field to the value.
void polygon_setSided(Polygon *p, int oneSided){
	p->oneSided = oneSided;
}

// initializes the color array to the colors in clist.
void polygon_setColors(Polygon *p, int numV, Color *clist){
	if (p->color != NULL){
		free(p->color);
	}
	// allocate color with numV using malloc
	p->color = malloc(sizeof(Color)*numV);
 	//for every item in clist allocate enough memory
	for(int i=0; i<numV;i++){
		color_copy(&p->color[i], &clist[i]);
		printf("setColors: %.3f %.3f %.3f\n", p->color[i].c[0], p->color[i].c[1], p->color[i].c[2]);
		// printf("Red %f\n", clist[i].c[0]);
		// printf("Green %f\n", clist[i].c[1]);
		// printf("Blue %f\n", clist[i].c[2]);
	}

}

// sets the z-buffer flag to the given value.
void polygon_zBuffer(Polygon *p, int flag){
	p->zBuffer = flag;
}

// De-allocates/allocates space and copies the vertex and color data from one polygon to the other.
void polygon_copy(Polygon *to, Polygon *from){
	int i;
	
	// if either is NULL, just return (can't do anything)
	if(from == NULL || to==NULL){
		return;
	}
	
	// check if to->vertex is not NULL, if so, free to->vertex
	if(to->vertex != NULL){
		free(to->vertex);
	}

	if(to->normal != NULL){
		free(to->normal);
	}
	
	to->zBuffer = from->zBuffer;
	to->oneSided = from->oneSided;
	// allocate to->vertex to be the same size as from->vertex
	to->vertex = malloc(sizeof(Point)*from->nVertex);

	
	to->nVertex = from->nVertex;
	//copy vertex data from (from) to (to)
	for(i=0; i<from->nVertex;i++){	
		point_copy(&to->vertex[i], &from->vertex[i]);
	}
	// 	check if to->color is not NULL, if so, free to->color
	if(to->color != NULL){
		free(to->color);
	}
	

	// allocate to->color to be the same size as from->color
	to->color = malloc(sizeof(Color)*from->nVertex);

	if(from->color != NULL){
		for(i=0; i<from->nVertex;i++){
			color_copy(&to->color[i], &from->color[i]);
		
		}
	}

	to->normal = malloc(sizeof(Vector)*from->nVertex);
	

	for(i=0; i<from->nVertex;i++){
		vector_copy(&to->normal[i], &from->normal[i]);
	}

	
	
}

// prints polygon data to the stream designated by the FILE pointer.
void polygon_print(Polygon *p, FILE *fp){
	printf("Polygon: %d vertices\n",p->nVertex );
	for (int i = 0; i<p->nVertex; i++){
		point_print(&p->vertex[i], fp);

	}
}

// normalize the x and y values of each vertex by the homogeneous coord.
void polygon_normalize( Polygon *p ){
	//go through every point in vertex list
	for(int i=0; i<p->nVertex;i++){
		//grab x,y, and homogenous coordinate
		double h = p->vertex[i].val[3];
		double x = p->vertex[i].val[0];
		double y = p->vertex[i].val[1];
		//normalize and reassign
		p->vertex[i].val[0] = x/h;
		p->vertex[i].val[1] = y/h;	
		p->vertex[i].val[3] = 1.0;
	}
}

// draw the outline of the polygon using color c.
void polygon_draw(Polygon *p, Image *src, Color c){
	Line line;
	int x0,x1,y0,y1;
	//go through every point in vertex list
	for(int i=0; i<p->nVertex-1;i++){
		//get x and y values
		x0 = p->vertex[i].val[0];
		y0 = p->vertex[i].val[1];
		x1 = p->vertex[i+1].val[0];
		y1 = p->vertex[i+1].val[1];
		//set line
		line_set2D(&line, x0,y0,x1,y1);
		//draw line 
		line_draw(&line, src, c);
	}
	x0 = p->vertex[0].val[0];
	y0 = p->vertex[0].val[1];
	line_set2D(&line, x0,y0,x1,y1);
	line_draw(&line, src, c);	
}

// Create a pattern fill for polygons using flood fill
void polygon_drawFillPattern(Polygon *p, Image *src, Image *psrc, Color val){
        int xpat, ypat;
        Color color;
        int xorg = p->vertex[0].val[0];
        int yorg = p->vertex[0].val[1];

        Point *stack = malloc(sizeof(Point)*src->rows * src->cols);
        stack[0] = p->vertex[0];
        int top = 1;
// While the stack is not empty
        while(top > 0){

                top--;
                Point current = stack[top];

                int x = current.val[0];
                int y = current.val[1];
/* Check all 8 neighbors of the pixel, and if the pixel is the color val, color it 
using the texture map*/

                if(image_getColor(src, y, x+1).c[0] == val.c[0] && image_getColor(src, y, x+1).c[1] == val.c[1] &&
                image_getColor(src, y, x+1).c[2] == val.c[2]){
                        xpat = abs(x+1 - xorg) % psrc->cols;
                        ypat = abs(y - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y, x+1, color);
                        Point p1;
                        point_set2D(&p1, x+1, y);
                        stack[top] = p1;
                        top++;
                }
                if(image_getColor(src, y, x-1).c[0] == val.c[0] && image_getColor(src, y, x-1).c[1] == val.c[1] &&
                image_getColor(src, y, x-1).c[2] == val.c[2]){
                        xpat = abs(x-1 - xorg) % psrc->cols;
                        ypat = abs(y - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y, x-1, color);
                        Point p1;
                        point_set2D(&p1, x-1, y);
                        stack[top] = p1;
                        top++;
                }
                if(image_getColor(src, y-1, x).c[0] == val.c[0] && image_getColor(src, y-1, x).c[1] == val.c[1] &&
                image_getColor(src, y-1, x).c[2] == val.c[2]){
                        xpat = abs(x - xorg) % psrc->cols;
                        ypat = abs(y-1 - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y-1, x, color);
                        Point p1;
                        point_set2D(&p1, x, y-1);
                        stack[top] = p1;
                        top++;
                }
                if(image_getColor(src, y+1, x).c[0] == val.c[0] && image_getColor(src, y+1, x).c[1] == val.c[1] &&
                image_getColor(src, y+1, x).c[2] == val.c[2]){
                        xpat = abs(x - xorg) % psrc->cols;
                        ypat = abs(y+1 - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y+1, x, color);
                        Point p1;
                        point_set2D(&p1, x, y+1);
                        stack[top] = p1;
                        top++;
                }
                 if(image_getColor(src, y+1, x+1).c[0] == val.c[0] && image_getColor(src, y+1, x+1).c[1] == val.c[1] &&
                image_getColor(src, y+1, x+1).c[2] == val.c[2]){
                        xpat = abs(x+1 - xorg) % psrc->cols;
                        ypat = abs(y+1 - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y+1, x+1, color);
                        Point p1;
                        point_set2D(&p1, x+1, y+1);
                        stack[top] = p1;
                        top++;
                }
                if(image_getColor(src, y-1, x-1).c[0] == val.c[0] && image_getColor(src, y-1, x-1).c[1] == val.c[1] &&
                image_getColor(src, y-1, x-1).c[2] == val.c[2]){
                        xpat = abs(x-1 - xorg) % psrc->cols;
                        ypat = abs(y-1 - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y-1, x-1, color);
                        Point p1;
                        point_set2D(&p1, x-1, y-1);
                        stack[top] = p1;
                        top++;
                }
                if(image_getColor(src, y-1, x+1).c[0] == val.c[0] && image_getColor(src, y-1, x+1).c[1] == val.c[1] &&
                image_getColor(src, y-1, x+1).c[2] == val.c[2]){
                        xpat = abs(x+1 - xorg) % psrc->cols;
                        ypat = abs(y-1 - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y-1, x+1, color);
                        Point p1;
                        point_set2D(&p1, x+1, y-1);
                        stack[top] = p1;
                        top++;
                }
                if(image_getColor(src, y+1, x-1).c[0] == val.c[0] && image_getColor(src, y+1, x-1).c[1] == val.c[1] &&
                image_getColor(src, y+1, x-1).c[2] == val.c[2]){
                        xpat = abs(x-1 - xorg) % psrc->cols;
                        ypat = abs(y+1 - yorg) % psrc->rows;
                        color = image_getColor(psrc, xpat, ypat);

                        image_setColor(src, y+1, x-1, color);
                        Point p1;
                        point_set2D(&p1, x-1, y+1);
                        stack[top] = p1;
                        top++;
                }
        }
        free(stack);
}

//uses barycentric coordinates to determine which pixels to fill given a polygon with only 3 points.
void polygon_drawFillB(Polygon *p, Image *src, Color c){
	//– draw the filled polygon using color c with the Barycentric coordinates algorithm.
	
	//. Scan over the bounding box of the triangle, filling any pixel whose barycentric coordinates are all in the range [0, 1].
	//barycentric coordinates (u+v+w=1)
	float alpha,beta,gamma;
	
	//get x and y values- vertices of a triangle
	
	//A vertex
	float xa = p->vertex[0].val[0];
	float ya = p->vertex[0].val[1];
	
	//B vertex
	float xb = p->vertex[1].val[0];
	float yb = p->vertex[1].val[1];
	
	//C vertex
	float xc = p->vertex[2].val[0];
	float yc = p->vertex[2].val[1];
	
	//get min and max values of of x and y
	//get first min and max x values
	float val1min = ((((xa)<(xb))?(xa):(xb)));
	float val1max = (((xa)>(xb))?(xa):(xb));
	float val2min = ((((ya)<(yb))?(ya):(yb)));
	float val2max = (((ya)>(yb))?(ya):(yb));
	
	//get final min and max x and y values
	float minx = ((((val1min)<(xc))?(val1min):(xc)));
	float maxx = (((val1max)>(xc))?(val1max):(xc));
	float miny = (((val2min)<(yc))?(val2min):(xc));
	float maxy = (((val2max)>(yc))?(val2max):(xc));
	
	
	//loop through min and max value range
	for(int x=minx; x<maxx;x++){
		for(int y=miny; y<maxy;y++){
			//calculate beta
			beta = (((yc - ya)*(float)x) + (xa -xc)*(float)y + (xc*ya) - (xa*yc)) / ( ((yc-ya)*xb) + ((xa-xc) *yb) +(xc*ya) - (xa*yc));
			//calculate gamma
			gamma = (((ya - yb)*(float)x) + (xb -xa)*(float)y + (xa*yb) - (xb*ya)) / ( ((ya-yb)*xc) + ((xb-xa) *yc) +(xa*yb) - (xb*ya));
			//calculate alpha
			alpha = 1 - beta - gamma;
			//check values and fill pixel
			if( beta>= -0.0001 && gamma>-0.0001 && alpha>-0.0001){
				image_setColor( src, y , x, c);
			
			}
		}
	}
}

//uses barycentric coordinates to determine which pixels to gradient fill given a polygon with only 3 points.
void polygon_drawFillBGradient(Polygon *p, Image *src, Color c1, Color c2){
	
	//. Scan over the bounding box of the triangle, filling any pixel whose barycentric coordinates are all in the range [0, 1].
	//barycentric coordinates (u+v+w=1)
	float alpha,beta,gamma;
	float cr,cg,cb;
	//get x and y values- vertices of a triangle
	
	//A vertex
	float xa = p->vertex[0].val[0];
	float ya = p->vertex[0].val[1];
	
	//B vertex
	float xb = p->vertex[1].val[0];
	float yb = p->vertex[1].val[1];
	
	//C vertex
	float xc = p->vertex[2].val[0];
	float yc = p->vertex[2].val[1];
	
	//get min and max values of of x and y
	//get first min and max x values
	float val1min = ((((xa)<(xb))?(xa):(xb)));
	float val1max = (((xa)>(xb))?(xa):(xb));
	float val2min = ((((ya)<(yb))?(ya):(yb)));
	float val2max = (((ya)>(yb))?(ya):(yb));
	
	//get final min and max x and y values
	float minx = ((((val1min)<(xc))?(val1min):(xc)));
	float maxx = (((val1max)>(xc))?(val1max):(xc));
	float miny = (((val2min)<(yc))?(val2min):(xc));
	float maxy = (((val2max)>(yc))?(val2max):(xc));
	
	
	//loop through min and max value range
	for(int x=minx; x<maxx;x++){
		for(int y=miny; y<maxy;y++){
			//calculate beta
			beta = (((yc - ya)*(float)x) + (xa -xc)*(float)y + (xc*ya) - (xa*yc)) / ( ((yc-ya)*xb) + ((xa-xc) *yb) +(xc*ya) - (xa*yc));
			//calculate gamma
			gamma = (((ya - yb)*(float)x) + (xb -xa)*(float)y + (xa*yb) - (xb*ya)) / ( ((ya-yb)*xc) + ((xb-xa) *yc) +(xa*yb) - (xb*ya));
			//calculate alpha
			alpha = 1 - beta - gamma;
			//check values and fill pixel
			if( beta>= -0.0001 && gamma>-0.0001 && alpha>-0.0001){
				Color newColor;
				cr = alpha*c1.c[0] + (1-alpha)*c2.c[0];
				cb = beta*c1.c[1] + (1-beta)*c2.c[1];
				cg = gamma*c1.c[2] + (1-gamma)*c2.c[2];
				color_set(&newColor, cr,cg,cb);
				image_setColor( src, y , x, newColor);
			
			}
		}
	}
}


Polygon *polygon_create_circle_2D(Polygon *poly, Point *center, double radius, int numV, Point *c){ 

	if (poly == NULL) return NULL; 

	poly->nVertex = numV; 
	poly->vertex = c;
	
	double steps = (2*3.15159)/numV; 
	double start = 0; 
	double x, y; 
	int i; 
	
	for (i = 0; i < numV; i ++){ 
		x = center->val[0] + (radius)*cos(start);
		y = center->val[1] + (radius)*sin(start);
		start += steps; 
		poly->vertex[i] = (Point) {{x, y, 0, 1}}; 
	}

	poly->color = NULL;

	return poly;

}

Polygon *polygon_create_circle_3D(Polygon *poly, Point *center, double radius, int numV, Vector *a, Vector *b, Point *c){ 

	if (poly == NULL ) return NULL; 

	poly->nVertex = numV; 
	poly->vertex = c;
	
	double steps = (2*3.14159)/numV; 
	double start = 0; 
	double x, y, z; 
	int i; 
	
	for (i = 0; i < numV; i ++){ 
		x = center->val[0] + (radius)*cos(start)*a->val[0] + (radius)*sin(start)*b->val[0];
		y = center->val[1] + (radius)*cos(start)*a->val[1] + (radius)*sin(start)*b->val[1];
		z = center->val[2] + (radius)*cos(start)*a->val[2] + (radius)*sin(start)*b->val[2];
		start += steps; 
		poly->vertex[i] = (Point) {{x, y, z, 1}}; 
	}

	poly->color = NULL;

	return poly;

}

// Read in a polygon from a text file
Polygon *polygon_read(FILE *fp, char *filename, Point *vlist){
	int numV = 0;
	char line[100];
	float val1, val2, val3;
	Point *tmp = malloc(sizeof(Point));

	
	fp = fopen(filename,"r");

	if (fp!=NULL){
		
	    while (fgets(line, sizeof(line), fp)){
	    	printf("reading %s\n", line);
	    	val1 = atof(&line[7]);
	    	val2 = atof(&line[9]);
	    	val3 = atof(&line[11]);
	    	point_set3D(&tmp[numV], val1, val2, val3);
	    	numV++;
	    }
	    
	    numV--;
	    for(int i = 0; i<numV; i++){
	    	val1 = tmp[i].val[0];
	    	val2 = tmp[i].val[1];
	    	val3 = tmp[i].val[2];
	    	point_set3D(&vlist[i], val1, val2, val3);
	    	point_print(&vlist[i], stdout);
	    }
    	
    	Polygon *p = polygon_createp(numV, vlist);
   	
   		fclose(fp);
   		free(tmp);
    	return p;
    }
    else{
    	printf("File is Null\n");
    	return NULL;
	}
}

void polygon_setNormals(Polygon *p, int numV, Vector *nlist){
	int i;

	if(!p || !nlist){
		return;
	}

	if(p->normal != NULL){
		free(p->normal);
	}

	p->normal = malloc(sizeof(Vector)*numV);

	for(i = 0; i<numV; i++){
		vector_copy(&p->normal[i], &nlist[i]);

	}
}

void polygon_shade(Polygon *p, Lighting *lighting, DrawState *ds){
	Vector view;
	 printf("r body %f \n", ds->body->c[0]);
	 		printf("g %f \n", ds->body->c[1]);
	 		printf("b %f \n", ds->body->c[2]);

		printf("r surface in polygon_shade %f \n", ds->surface->c[0]);
			printf("g %f \n", ds->surface->c[1]);
			printf("b %f \n", ds->surface->c[2]);

	// 		printf("r color %f \n", ds->color->c[0]);
	// 		printf("g %f \n", ds->color->c[1]);
	// 		printf("b %f \n", ds->color->c[2]);
		
	
	if(ds->shade == ShadeFlat){
		Point pCenter;
		Vector avgN;
		Color c;

		pCenter.val[0] = (p->vertex[0].val[0]+ p->vertex[1].val[0]+ p->vertex[2].val[0])/3;
		pCenter.val[1] = (p->vertex[0].val[1]+ p->vertex[1].val[1]+ p->vertex[2].val[1])/3;
		pCenter.val[2] = (p->vertex[0].val[2]+ p->vertex[1].val[2]+ p->vertex[2].val[2])/3;
		pCenter.val[3] = (p->vertex[0].val[3]+ p->vertex[1].val[3]+ p->vertex[2].val[3])/3;

		avgN.val[0] = (p->normal[0].val[0] + p->normal[1].val[0] + p->normal[2].val[0])/3;
		avgN.val[1] = (p->normal[0].val[1] + p->normal[1].val[1] + p->normal[2].val[1])/3;
		avgN.val[2] = (p->normal[0].val[2] + p->normal[1].val[2] + p->normal[2].val[2])/3;

		view.val[0] = ds->viewer->val[0] - pCenter.val[0];
		view.val[1] = ds->viewer->val[1] - pCenter.val[1];
		view.val[2] = ds->viewer->val[2] - pCenter.val[2];

		lighting_shading( lighting, &avgN, &view, &pCenter, ds->body, ds->surface, ds->surfaceCoeff, p->oneSided, &c);
		// polygon_setColors(p, p->nVertex, &c);
		// color_set(ds->body, 1.0, .1, .1);
		// 	color_set(ds->surface, .1, 1.0, .1);

		for(int x = 0; x < p->nVertex; x++){
			color_copy(&p->color[x], &c);
			// printf("%f \n", c.c[0]);
		}

	}


	if (ds->shade == ShadeGouraud){
		int i;
		Color *c = malloc(sizeof(Color)*(p->nVertex));

		for(i = 0; i < p->nVertex; i++){
			view.val[0] = ds->viewer->val[0] - p->vertex[i].val[0];
			view.val[1] = ds->viewer->val[1] - p->vertex[i].val[1];
			view.val[2] = ds->viewer->val[2] - p->vertex[i].val[2];
			// color_set(ds->body, 1.0, .1, .1);
			// color_set(ds->surface, .1, 1.0, .1);
			
			lighting_shading( lighting, &p->normal[i], &view, &p->vertex[i], ds->body, ds->surface, ds->surfaceCoeff, p->oneSided, &c[i]);
		}
		


		polygon_setColors(p, p->nVertex, c);
		// for(int x = 0; x < p->nVertex; x++){
			
		// }

		free(c);


	}
	
}





 










