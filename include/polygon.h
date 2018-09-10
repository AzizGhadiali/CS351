// Aziz Ghadiali & Brit Biddle, Project 4, 2/18/18
// polygon header file

#ifndef POLYGON_H
#define POLYGON_H

#include "image.h"
#include "color.h"
#include "point.h"
#include "vector.h"
#include "lighting.h"
#include "drawState.h"

// define line structure
typedef struct {

// 	whether to consider the polygon one-sided (1) or two-sided (0) for shading
	int oneSided;
	
// 	Number of vertices
	int nVertex;

// 	vertex information
	Point *vertex;

// 	color information for each vertex.
	Color *color;

// surface normal information for each vertex.
	Vector *normal;

// whether to use the z-buffer; should default to true (1)
	int zBuffer; 

} Polygon;

// returns an allocated Polygon pointer initialized so that numVertex is 0 and vertex is NULL.
Polygon *polygon_create(void);

// returns an allocated Polygon pointer with the vertex list initialized to a copy of the points in vlist.
Polygon *polygon_createp(int numV, Point *vlist);

// frees the internal data for a Polygon and the Polygon pointer.
void polygon_free(Polygon *p);

// initializes the existing Polygon to an empty Polygon.
void polygon_init(Polygon *p);

// initializes the vertex array to the points in vlist.
void polygon_set(Polygon *p, int numV, Point *vlist);

// frees the internal data and resets the fields.
void polygon_clear(Polygon *p);

// sets the oneSided field to the value.
void polygon_setSided(Polygon *p, int oneSided);

// initializes the color array to the colors in clist.
void polygon_setColors(Polygon *p, int numV, Color *clist);

// initializes the normal array to the vectors in nlist.
void polygon_setNormals(Polygon *p, int numV, Vector *nlist);

// initializes the vertex list to the points in vlist, the colors to the colors in clist, the normals to the
// vectors in nlist, and the zBuffer and oneSided flags to their respectively values.
// void polygon_setAll(Polygon *p, int numV, Point *vlist, Color *clist, Vector *nlist, int zBuffer, int oneSided);

// sets the z-buffer flag to the given value.
void polygon_zBuffer(Polygon *p, int flag);

// De-allocates/allocates space and copies the vertex and color data from one polygon to the other.
void polygon_copy(Polygon *to, Polygon *from);

// prints polygon data to the stream designated by the FILE pointer.
void polygon_print(Polygon *p, FILE *fp);

// normalize the x and y values of each vertex by the homogeneous coord.
void polygon_normalize( Polygon *p );

// draw the outline of the polygon using color c.
void polygon_draw(Polygon *p, Image *src, Color c);

void polygon_drawShade(Polygon *p, Image *src, DrawState *ds, Lighting *lights);

// draw the filled polygon using color c with the scanline z-buffer rendering algorithm.
void polygon_drawFill(Polygon *p, Image *src, Color c, DrawState *dstate);

// draw the filled polygon using color c with the Barycentric coordinates algorithm.
void polygon_drawFillB(Polygon *p, Image *src, Color c);

//uses barycentric coordinates to determine which pixels to gradient fill given a polygon with only 3 points.
void polygon_drawFillBGradient(Polygon *p, Image *src, Color c1, Color c2);

// fills a polygon using a pattern
void polygon_drawFillPattern(Polygon *p, Image *src, Image *psrc, Color val);

void polygon_shade(Polygon *p, Lighting *lighting, DrawState *ds);


// creates a 3D circle 
Polygon *polygon_create_circle_3D(Polygon *poly, Point *center, double radius, int numV, Vector *a, Vector *b, Point *c);

// Creates a 2D circle
Polygon *polygon_create_circle_2D(Polygon *poly, Point *center, double radius, int numV, Point *c);

// Reads in a polygon text file
Polygon *polygon_read(FILE *fp, char *filename, Point *vlist);
// draw the filled polygon using the given DrawState. The shade field of the DrawState determines
// how the polygon should be rendered. The Lighting parameter should be NULL unless you are doing
// Phong shading.


/*
– For the ShadeFlat
and ShadeGouraud cases of the shade field of DrawState, calculate colors at each vertex and create
and fill out the color array of the Polygon data structure. For ShadeFlat, use the average surface
normal and average polygon location to calculate one color and set the color at each vertex to the
calculated value. For ShadeGouraud use the surface normals and locations of each vertex.*/








#endif