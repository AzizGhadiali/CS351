// Aziz Ghadiali, Project 5, 2/18/18
// vector header file

#ifndef VECTOR_H
#define VECTOR_H

#include "primitives.h"

// define vector structure
typedef struct {
// 	values are x, y, z
	double val[4];

} Vector;

// Set the Vector to (x, y, z, 0.0)
void vector_set(Vector *v, double x, double y, double z);

// Print out the Vector to stream fp in a pretty form
void vector_print(Vector *v, FILE *fp);

//Copy the src Vector into the dest Vector
void vector_copy(Vector *dest, Vector *src);

// Returns the Euclidean length of the vector, assuming the homogeneous coordinate is 1.0.
double vector_length(Vector *v);

// Normalize the Vector to unit length. Do not modify the homogeneous coordinate.
void vector_normalize(Vector *v);

// Returns the scalar product of ~a and ~b.
double vector_dot(Vector *a, Vector *b);

// Calculates the the cross product (vector product) of ~a and ~b and puts the result in ~c.
void vector_cross(Vector *a, Vector *b, Vector *c);

#endif
