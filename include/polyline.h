// Aziz Ghadiali & Brit Biddle, Project 3, 2/18/18
// include color file

#ifndef POLYLINE_H
#define POLYLINE_H

#include "image.h"
#include "color.h"
#include "point.h"


// define polyline structure
typedef struct e {

	int zBuffer;
	int numVertex;
	Point *vertex;
	

} Polyline;



//returns an allocated Polyline pointer initialized so that numVertex is 0 and vertex is NULL.
Polyline *polyline_create(void);

//Polyline *polyline createp(int numV, Point *vlist)
Polyline *polyline_createp(int numV, Point *vlist);

//void polyline free(Polyline *p)
void polyline_free(Polyline *p);

//initializes the pre-existing Polyline to an empty Polyline.
void polyline_init(Polyline *p);

//initializes the vertex list to the points in vlist. De-allocates/allocates the vertex list for p, as necessary.
void polyline_set(Polyline *p, int numV, Point *vlist);

//frees the internal data for a Polyline, if necessary, and sets numVertex to 0 and vertex to NULL
void polyline_clear(Polyline *p);

// sets the z-buffer flag to the given value.
void polyline_zBuffer(Polyline *p, int flag);

//De-allocates/allocates space as necessary in the destination Polyline data structure and copies the
//vertex data from the source polyline (from) to the destination (to)
void polyline_copy(Polyline *to, Polyline *from);

//prints Polyline data to the stream designated by the FILE pointer
void polyline_print(Polyline *p, FILE *fp);

//normalize the x and y values of each vertex by the homogeneous coordinate.
void polyline_normalize( Polyline *p );

//draw the polyline using color c and the z-buffer, if appropriate
void polyline_draw(Polyline *p, Image *src, Color c);

#endif