/*
  Aziz Ghadiali
  module.h
  February 22, 2018
  contains all functions for models
  
*/

#ifndef MODULE_H
#define MODULE_H

#include "drawState.h"
#include "lighting.h"
#include "bezier.h"

typedef enum { // example of an enumerated type
	
	ObjNone,
	ObjLine,
	ObjPoint,
	ObjPolyline,
	ObjPolygon,
	ObjIdentity,
	ObjMatrix,
	ObjColor,
	ObjBodyColor,
	ObjSurfaceColor,
	ObjSurfaceCoeff,
	ObjLight,
	ObjModule
	
} ObjectType;

// Element structure
typedef struct {
	
	ObjectType type; // Type of object stored in the obj pointer
	void *obj; // pointer to the object
	void *next; // next pointer
	
} Element;

typedef struct {

	Element *head; // pointer to the head of the linked list
	Element *tail; // keep around a pointer to the last object
	
} Module;

// – Allocate and return an initialized but empty Element.
Element *element_create(void);

// – Allocate an Element and store a duplicate of the data pointed to by obj in the Element. Modules do
// not get duplicated. The function needs to handle each type of object separately in a case statement.
Element *element_init(ObjectType type, void *obj);

// – free the element and the object it contains, as appropriate.
void element_delete(Element *e);

// – Allocate an empty module.
Module *module_create(void);

// – clear the module’s list of Elements, freeing memory as appropriate.
void module_clear(Module *md);

// – Free all of the memory associated with a module, including the memory pointed to by md.
void module_delete(Module *md);

// – Generic insert of an element into the module at the tail of the list.
void module_insert(Module *md, Element *e);

// – Adds a pointer to the Module sub to the tail of the module’s list.
void module_module(Module *md, Module *sub);

// – Adds p to the tail of the module’s list.
void module_point(Module *md, Point *p);

// – Adds p to the tail of the module’s list.
void module_line(Module *md, Line *p);

// – Adds p to the tail of the module’s list.
void module_polyline(Module *md, Polyline *p);

// – Adds p to the tail of the module’s list.
void module_polygon(Module *md, Polygon *p);

// – Object that sets the current transform to the identity, placed at the tail of the module’s list.
void module_identity(Module *md);

// – Matrix operand to add a translation matrix to the tail of the module’s list.
void module_translate2D(Module *md, double tx, double ty);

// – Matrix operand to add a scale matrix to the tail of the module’s list.
void module_scale2D(Module *md, double sx, double sy);

// – Matrix operand to add a rotation about the Z axis to the tail of the module’s list
void module_rotateZ(Module *md, double cth, double sth);

// – Matrix operand to add a 2D shear matrix to the tail of the module’s list.
void module_shear2D(Module *md, double shx, double shy);

// – Draw the module into the image using the given view transformation matrix [VTM], Lighting and
// DrawState by traversing the list of Elements. (For now, Lighting can be an empty structure.)
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Lighting *lighting, Image *src);

// – Matrix operand to add a 3D translation to the Module.
void module_translate(Module *md, double tx, double ty, double tz);

// – Matrix operand to add a 3D scale to the Module.
void module_scale(Module *md, double sx, double sy, double sz);

// – Matrix operand to add a rotation about the X-axis to the Module.
void module_rotateX(Module *md, double cth, double sth);

// – Matrix operand to add a rotation about the Y-axis to the Module.
void module_rotateY(Module *md, double cth, double sth);

// – Matrix operand to add a rotation that orients to the orthonormal axes ~u, ~v, w~.
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w);

//– Adds a unit cube, axis-aligned and centered on zero to the Module. If solid is zero, add only lines. If solid is non-zero, use polygons. Make sure each polygon has surface normals defined for it.
void module_cube(Module *md, int solid);

// – Adds the foreground color value to the tail of the module’s list.
void module_color(Module *md, Color *c);

void module_bezierSurface(Module *m, BezierSurface *b, int divisions, int solid);

void module_bezierCurve(Module *m, BezierCurve *b, int divisions);

void decastCurves(BezierCurve *b, Point p1[4], Point p2[4], int i);

void decastSurfaces(BezierSurface *b, Point p1[4], Point p2[4], int i);

void modSurfaceCreate(BezierSurface *b1, int start1, int end1, int start2, int end2, Point c[8][8]);

void module_cylinder(Module *mod, Polygon *p, int sides);

void module_octahedron(Module *mod, Polygon *p, int x, int y, int z);

void module_pyramid(Module *mod, Polygon *p, double x, double y, double z);

void module_color(Module *md, Color *c);

void module_bodyColor(Module *md, Color *c);

void module_surfaceColor(Module *md, Color *c);

void module_surfaceCoeff(Module *md, float coeff);


#endif








