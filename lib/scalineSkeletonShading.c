/*
  Bruce A. Maxwell
  Fall 2014
  
  Modified by Aziz Ghadiali 
  Spring 2018

	Skeleton scanline fill algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "polygon.h"
#include "list.h"
#include "drawState.h"

// global variable for counting gif images
/********************
Scanline Fill Algorithm
********************/

// define the struct here, because it is local to only this file
typedef struct tEdge {
	float x0, y0, z0;                   /* start point for the edge */
	float x1, y1, z1;                   /* end point for the edge */
	int yStart, yEnd;
	Color color, cIntersect, dcPerScan;
	               /* start row and end row */
  	float xIntersect, dxPerScan, zIntersect, dzPerScan;   /* where the edge intersects the current scanline and how it changes */
	/* we'll add more here later */
  struct tEdge *next;
} Edge;


/*
	This is a comparison function that returns a value < 0 if a < b, a
	value > 0 if a > b, and 0 if a = b.  It uses the yStart field of the
	Edge structure.  It is used to sort the overall edge list.
 */
static int compYStart( const void *a, const void *b ) {
	Edge *ea = (Edge *)a;
	Edge *eb = (Edge *)b;

	return(ea->yStart - eb->yStart);
}


/*
	This is a comparison function that returns a value < 0 if a < b, a
	value > 0 if a > b, and 0 if a = b.  It uses the xIntersect field of the
	Edge structure.  It is used to sort the active edge list.
 */
static int compXIntersect( const void *a, const void *b ) {
	Edge *ea = (Edge *)a;
	Edge *eb = (Edge *)b;

	if( ea->xIntersect < eb->xIntersect )
		return(-1);
	else if(ea->xIntersect > eb->xIntersect )
		return(1);

	return(0);
}

/*
	Allocates, creates, fills out, and returns an Edge structure given
	the inputs.

	Current inputs are just the start and end location in image space.
	Eventually, the points will be 3D and we'll add color and texture
	coordinates.
 */
static Edge *makeEdgeRec( Point start, Point end, Color c1, Color c2, Image *src)
{
	
	Edge *edge;
	float dscan = end.val[1] - start.val[1];
	float slope;
	

	/******
				 Your code starts here
	******/
	edge = malloc(sizeof(Edge));
	// Check if the starting row is below the image or the end row is
	// above the image and skip the edge if either is true
	if(start.val[1]>=src->rows || end.val[1]<0){
// 		modified after project 4 feedback from Bruce
		edge->xIntersect += edge->dxPerScan * (-edge->yStart);
		edge->yStart = 0;
	}
	// printf("printing start and end points in make edge rec\n\n");
// 	point_print(&start, stdout);
// 	point_print(&end, stdout);
	
	
	// allocate an edge structure and set the x0, y0, x1, y1 values
	edge->x0 = start.val[0];
	edge->y0 = start.val[1];
	edge->z0 = start.val[2];
	edge->x1 = end.val[0];
	edge->y1 = end.val[1];
	edge->z1 = end.val[2];
	color_copy(&edge->color, &c2);
	
	
	// turn on an edge only if the edge starts in the top half of it or
	// the lower half of the pixel above it.  In other words, round the
	// start y value to the nearest integer and assign it to
	// edge->yStart.
	edge->yStart = (int)round(edge->y0);

	// Turn off the edge if it starts in the lower half or the top half
	// of the next pixel.  In other words, round the end y value to the
	// nearest integer and subtract 1, assigning the result to
	// edge->yEnd.
	edge->yEnd = (int)round(edge->y1) - 1;

	// Clip yEnd to the number of rows-1. ASK
 	if(edge->yEnd > src->rows){
 		edge->yEnd = src->rows-1;
 	}

	// Calculate the slope, dxPerScan
	slope = (edge->y1-edge->y0)/(edge->x1-edge->x0);
	edge->dxPerScan = 1/slope;

	// Calculate xIntersect, adjusting for the fraction of the point in the pixel.
	// Scanlines go through the middle of pixels
	// Move the edge to the first scanline it crosses
	edge->xIntersect = edge->x0;
	if(edge->y0 - floor(edge->y0) <= .5){
		edge->xIntersect += (.5 - (floor(edge->y0) - edge->y0)) * (edge->dxPerScan);
		edge->zIntersect += (.5 - (floor(edge->y0) - edge->y0)) * (edge->dzPerScan);
	}
	else if(edge->y0 - floor(edge->y0) > .5){
		edge->xIntersect += ((1.0 - (floor(edge->y0) - edge->y0)) + .5) * (edge->dxPerScan);
		edge->zIntersect += ((1.0 - (floor(edge->y0) - edge->y0)) + .5) * (edge->dzPerScan);

		// edge->cIntersect.c[0] += ((1.0 - (floor(edge->cIntersect.c[0]) - edge->cIntersect.c[0])) + .5) * (edge->dcPerScan);
		// edge->cIntersect.c[1] += ((1.0 - (floor(edge->cIntersect.c[1]) - edge->cIntersect.c[1])) + .5) * (edge->dcPerScan);
		// edge->cIntersect.c[2] += ((1.0 - (floor(edge->cIntersect.c[2]) - edge->cIntersect.c[2])) + .5) * (edge->dcPerScan);
	}
	
	edge->zIntersect = 1/start.val[2];
	edge->dzPerScan = ((1/end.val[2])-(1/start.val[2]))/(edge->y1-edge->y0);
	
	// Calculate color values 
	edge->dcPerScan.c[0] = ( c2.c[0]/end.val[2] - c1.c[0]/start.val[2] ) / dscan;
	edge->dcPerScan.c[1] = ( c2.c[1]/end.val[2] - c1.c[1]/start.val[2] ) / dscan;
	edge->dcPerScan.c[2] = ( c2.c[2]/end.val[2] - c1.c[2]/start.val[2] ) / dscan;

	// Ask
	edge->cIntersect.c[0] = c1.c[0]/edge->z0; 
	edge->cIntersect.c[1] = c1.c[1]/edge->z0; 
	edge->cIntersect.c[2] = c1.c[2]/edge->z0; 
	// printf(" %f, %f\n", edge->zIntersect, edge->dzPerScan);
	printf("makeEdgeRec: %.3f %.3f %.3f\n", edge->cIntersect.c[0], edge->cIntersect.c[1], edge->cIntersect.c[2]);
	printf("makeEdgeRec: %.3f %.3f %.3f\n", c1.c[0], c1.c[1], c1.c[2]);

	// adjust if the edge starts above the image
	// move the intersections down to scanline zero
	// if edge->y0 < 0
	//   update xIntersect
	//   update y0
  //   update x0
	//   update yStart
	if(edge->y0 < 0){
		edge->xIntersect = (int)round(edge->x0)+.5;
		edge->y0 = edge->y0 + (-1*edge->y0);
		edge->x0 = (edge->y1 - edge->y0)/(edge-> dxPerScan + edge->x0);
		edge->zIntersect += edge->dzPerScan*(-edge->yStart);

		edge->cIntersect.c[0] += edge->dcPerScan.c[0] * (-edge->yStart);
		edge->cIntersect.c[1] += edge->dcPerScan.c[1] * (-edge->yStart);
		edge->cIntersect.c[2] += edge->dcPerScan.c[2] * (-edge->yStart);
		edge-> yStart = edge->y0;
		
	}

	// check for really bad cases with steep slopes where xIntersect has gone beyond the end of the edge
	if(edge-> xIntersect > edge -> x1 && slope >0){
		edge -> xIntersect = edge -> x1;
		edge -> zIntersect = 1/edge -> z1;

		edge->cIntersect.c[0] = c2.c[0]/edge->z1;
		edge->cIntersect.c[1] = c2.c[1]/edge->z1;
		edge->cIntersect.c[2] = c2.c[2]/edge->z1;
	}
	if(edge-> xIntersect < edge -> x1 && slope < 0){
		edge -> xIntersect = edge -> x0;
		edge -> zIntersect = 1/edge -> z1;

		edge->cIntersect.c[0] = c2.c[0]/edge->z1;
		edge->cIntersect.c[1] = c2.c[1]/edge->z1;
		edge->cIntersect.c[2] = c2.c[2]/edge->z1;
	}
	// return the newly created edge data structure
	return( edge );
}


/*
	Returns a list of all the edges in the polygon in sorted order by
	smallest row.
*/
static LinkedList *setupEdgeList( Polygon *p, Image *src) {
	LinkedList *edges = NULL;
	Point v1, v2;
	Color c1, c2;
	int i;
	
	// printf("printing v1 and v2 in setup edge list\n");
// 	point_print(&v1, stdout);
// 	point_print(&v2, stdout);
	
	// create a linked list
	edges = ll_new();

	// walk around the polygon, starting with the last point
	v1 = p->vertex[p->nVertex-1];
	c1 = p->color[p->nVertex-1];

	for(i=0;i<p->nVertex;i++) {
		
		// the current point (i) is the end of the segment
		v2 = p->vertex[i];
		c2 = p->color[i];

		// if it is not a horizontal line
		if( (int)(v1.val[1]+0.5) != (int)(v2.val[1]+0.5) ) {
			Edge *edge;

			// if the first coordinate is smaller (top edge)
			if( v1.val[1] < v2.val[1] )
				edge = makeEdgeRec( v1, v2, c1, c2, src );
			else
				edge = makeEdgeRec( v2, v1, c2, c1, src );

			// insert the edge into the list of edges if it's not null
			if( edge )
				ll_insert( edges, edge, compYStart );
		}
		v1 = v2;
		c1 = c2;
	}

	// check for empty edges (like nothing in the viewport)
	if( ll_empty( edges ) ) {
		ll_delete( edges, NULL );
		edges = NULL;
	}

	return(edges);
}

/*
	Draw one scanline of a polygon given the scanline, the active edges,
	a DrawState, the image, and some Lights (for Phong shading only).
 */
static void fillScan( int scan, LinkedList *active, Image *src, Color c, DrawState *dstate ) {
  Edge *p1, *p2;
  int i, f;
  double curZ, dzPerCol;
  Color currC, dcPerCol;

	// loop over the list
  p1 = ll_head( active );
  while(p1) {
		// the edges have to come in pairs, draw from one to the next
	  p2 = ll_next( active );
	  if( !p2 ) {
		  printf("bad bad bad (your edges are not coming in pairs)\n\n");
		  break;
	  }

		// if the xIntersect values are the same, don't draw anything.
		// Just go to the next pair.
	  if( p2->xIntersect == p1->xIntersect ) {
		  p1 = ll_next( active );
		  continue;
	  }
		
		/**** Your code goes here ****/
	  // identify the starting column
	  // clip to the left side of the image
	  // identify the ending column
	  // clip to the right side of the image
		// loop from start to end and color in the pixels
		int start = round(p1->xIntersect);
		
		curZ = p1->zIntersect;

		currC.c[0] = p1->cIntersect.c[0];
		currC.c[1] = p1->cIntersect.c[1];
		currC.c[2] = p1->cIntersect.c[2];

		if(0 && currC.c[1]/curZ > currC.c[0]/curZ+0.1 && currC.c[1]/curZ > currC.c[2]/curZ+0.1) {
			printf("%d starting green %.3f %.3f %.3f\n", scan, currC.c[0], currC.c[1], currC.c[2]);
		}
		
		dzPerCol = ((p2->zIntersect)-(p1->zIntersect))/ ((p2->xIntersect)-(p1->xIntersect));
		dcPerCol.c[0] = ((p2->cIntersect.c[0])-(p1->cIntersect.c[0]))/ ((p2->xIntersect)-(p1->xIntersect));
		dcPerCol.c[1] = ((p2->cIntersect.c[1])-(p1->cIntersect.c[1]))/ ((p2->xIntersect)-(p1->xIntersect));
		dcPerCol.c[2] = ((p2->cIntersect.c[2])-(p1->cIntersect.c[2]))/ ((p2->xIntersect)-(p1->xIntersect));


		
		if(start < 0){
			// update curZ and curC by -p1->xIntersect * dPerScan
			start = 0;
		}
		
		int end = round(p2->xIntersect);

	
		if (end > src->cols){
			end = src->cols;
		}

		double avgZ = (p1->zIntersect+p2->zIntersect)/2;
	

		// if(p2->xIntersect > f-1){
			for(i = start; i < end; i++){
					Color c;
					c.c[0] = currC.c[0]/curZ;
					c.c[1] = currC.c[1]/curZ;
					c.c[2] = currC.c[2]/curZ;
				if (curZ > image_getz(src, scan, i)){
					// if(avgZ > image_getz(src, scan, i)){
					if( 0 && c.c[1] > c.c[0]+0.01 && c.c[1] > c.c[2]+0.01 ) {
						printf("drawing green %.3f %.3f %.3f curZ %.3f\n", currC.c[0]/curZ, currC.c[1]/curZ, currC.c[2]/curZ, curZ);
						printf("green: %d %d\n", scan, i);
					}
						image_setColor(src, scan, i, c);
						image_setz(src, scan, i, curZ);
					// }
				}
				curZ += dzPerCol;
				currC.c[0] += dcPerCol.c[0];
				currC.c[1] += dcPerCol.c[1];
				currC.c[2] += dcPerCol.c[2];

				
			}
		// }
		

		// move ahead to the next pair of edges
	  p1 = ll_next( active );
  }

	return;
}

/* 
	 Process the edge list, assumes the edges list has at least one entry
*/
static int processEdgeList( LinkedList *edges, Image *src, Color c, DrawState *dstate ) {
	LinkedList *active = NULL;
	LinkedList *tmplist = NULL;
	LinkedList *transfer = NULL;
	Edge *current;
	Edge *tedge;
	int scan = 0;

	active = ll_new( );
	tmplist = ll_new( );

	// get a pointer to the first item on the list and reset the current pointer
	current = ll_head( edges );

	// start at the first scanline and go until the active list is empty
	for(scan = current->yStart;scan < src->rows;scan++ ) {

		// grab all edges starting on this row
		while( current != NULL && current->yStart == scan ) {
			ll_insert( active, current, compXIntersect );
			current = ll_next( edges );
		}
		// current is either null, or the first edge to be handled on some future scanline

		if( ll_empty(active) ) {
			break;
		}

		// if there are active edges
		// fill out the scanline
		fillScan( scan, active, src, c, dstate);

		// remove any ending edges and update the rest
		for( tedge = ll_pop( active ); tedge != NULL; tedge = ll_pop( active ) ) {

			// keep anything that's not ending
			if( tedge->yEnd > scan ) {
				float a = 1.0;

				// update the edge information with the dPerScan values
				tedge->xIntersect += tedge->dxPerScan;
				tedge->zIntersect += tedge->dzPerScan;
				tedge->cIntersect.c[0] += tedge->dcPerScan.c[0];
				tedge->cIntersect.c[1] += tedge->dcPerScan.c[1];
				tedge->cIntersect.c[2] += tedge->dcPerScan.c[2];
				

				// adjust in the case of partial overlap
				if( tedge->dxPerScan < 0.0 && tedge->xIntersect < tedge->x1 ) {
					a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
					tedge->zIntersect = 1/tedge->z1;


					tedge->cIntersect.c[0] = tedge->color.c[0]/tedge->z1;
					tedge->cIntersect.c[1] = tedge->color.c[1]/tedge->z1;
					tedge->cIntersect.c[2] = tedge->color.c[2]/tedge->z1;
				}
				else if( tedge->dxPerScan > 0.0 && tedge->xIntersect > tedge->x1 ) {
					a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
					tedge->zIntersect = 1/tedge->z1;

					tedge->cIntersect.c[0] = tedge->color.c[0]/tedge->z1;
					tedge->cIntersect.c[1] = tedge->color.c[1]/tedge->z1;
					tedge->cIntersect.c[2] = tedge->color.c[2]/tedge->z1;
				}

				ll_insert( tmplist, tedge, compXIntersect );
			}
		}

		transfer = active;
		active = tmplist;
		tmplist = transfer;

	}

	// get rid of the lists, but not the edge records
	ll_delete(active, NULL);
	ll_delete(tmplist, NULL);

	return(0);
}

/*
	Draws a filled polygon of the specified color into the image src.
 */
void polygon_drawShade(Polygon *p, Image *src, DrawState *ds, Lighting *lights) {
	LinkedList *edges = NULL;
	
	// set up the edge list
	edges = setupEdgeList( p, src );
	// printf("printing polygons in polygon drawfill\n");
// 	polygon_print(p, stdout);
	if(lights != NULL){
		return;
	}
	
	if( !edges )
		return;
	
	// process the edge list (should be able to take an arbitrary edge list)
	processEdgeList( edges, src, *ds->color, ds);

	// clean up
	ll_delete( edges, (void (*)(const void *))free );

	return;
}

/****************************************
End Scanline Fill
*****************************************/
