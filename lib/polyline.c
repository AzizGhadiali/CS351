/*
  Aziz Ghadiali & Brit Biddle
  polyline.c
  March 1st, 2018
  contains all functions to create a polyline shape
  
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
#include "polyline.h"


// 	int zBuffer;
// 	int numVertex;
// 	Point *vertex;

//returns an allocated Polyline pointer initialized so that numVertex is 0 and vertex is NULL.
Polyline *polyline_create(){
	Polyline *pyl = malloc(sizeof(Polyline));
	pyl->zBuffer = 1;
	pyl->numVertex = 0;
	pyl->vertex = NULL;
	return(pyl);

}

//returns an allocated Polyline pointer with the vertex list initialized to the points in vlist
Polyline *polyline_createp(int numV, Point *vlist){
	//allocate space
	Polyline *pyl = malloc(sizeof(Polyline));
	//initialize values
	pyl->zBuffer = 1;
	pyl->numVertex = numV;
	// allocate numV Points using malloc, assign to pyl->vertex
	pyl->vertex = malloc(sizeof(Point)*numV);
	int i;
	// for loop numV, copy vlist[i] to pyl->vertex[i]
	for(i=0; i<numV;i++){
		pyl->vertex[i] = vlist[i];
	}
	//pyl->vertex = vlist;
	return(pyl);

}

//frees the internal data and the Polyline pointer.
void polyline_free(Polyline *p){
	//check if p is not already null
	if(p != NULL){
		if(p->vertex !=NULL){
			free(p->vertex);
		}
		//free polyline space
		free(p);
	}
}

//initializes the pre-existing Polyline to an empty Polyline.
void polyline_init(Polyline *p){
	if(p != NULL){
		p->zBuffer = 0;
		p->numVertex = 0;
		p->vertex = NULL;
	}
}

//initializes the vertex list to the points in vlist. De-allocates/allocates the vertex list for p, as necessary.
void polyline_set(Polyline *p, int numV, Point *vlist){
	p->numVertex = numV;
	if (p->vertex != NULL){
		free(p->vertex);
	}
	// allocate numV Points using malloc, assign to pyl->vertex
	p->vertex = malloc(sizeof(Point)*numV);
	int i;
 	//for every item in vlist allocate enough memory
	for(i=0; i<numV;i++){
		p->vertex[i] = vlist[i];
	}

}

//frees the internal data for a Polyline, if necessary, and sets numVertex to 0 and vertex to NULL
void polyline_clear(Polyline *p){
	//check if p is not already null
	if(p != NULL){
		if(p->vertex !=NULL){
			free(p->vertex);
		}
		//free polyline space
		//free(p);// don't do this here
	}
	p->numVertex = 0;
	p->vertex = NULL;
}

// sets the z-buffer flag to the given value.
void polyline_zBuffer(Polyline *p, int flag){
	p->zBuffer = flag;
}

//De-allocates/allocates space as necessary in the destination Polyline data structure and copies the
//vertex data from the source polyline (from) to the destination (to)
void polyline_copy(Polyline *to, Polyline *from){
	// if either is NULL, just return (can't do anything)
	if(from == NULL || to==NULL){
		return;
	}
	// check if to->vertex is not NULL, if so, free to->vertex
	if(to->vertex != NULL){
		free(to->vertex);
	}
	// allocate to->vertex to be the same size as from->vertex
	to->vertex = malloc(sizeof(from->vertex));
	
	//copy over vertex data
	int i;
	//copy vertex data from (from) to (to)
	for(i=0; i<from->numVertex;i++){
			to->vertex[i] = from->vertex[i];
	}
}

//prints Polyline data to the stream designated by the FILE pointer
void polyline_print(Polyline *p, FILE *fp){
	fprintf(fp, p);

}

//normalize the x and y values of each vertex by the homogeneous coordinate. x = x/h, y = y/h
void polyline_normalize( Polyline *p ){
	int i;
	//go through every point in vertex list
	for(i=0; i<p->numVertex;i++){
		//grab x,y, and homogenous coordinate
		double h = p->vertex[i].val[3];
		double x = p->vertex[i].val[0];
		double y = p->vertex[i].val[1];
		//normalize and reassign
		p->vertex[i].val[0] = x/h;
		p->vertex[i].val[1] = y/h;	
	}
}

//draw the polyline using color c and the z-buffer, if appropriate
void polyline_draw(Polyline *p, Image *src, Color c){
	Line line;
	int i,x0,x1,y0,y1;
	//go through every point in vertex list
	for(i=0; i<p->numVertex-1;i++){
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
}





