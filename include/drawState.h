/*
  Aziz Ghadiali
  drawState.h
  April 4, 2018
  contains all functions for models
  
*/

#ifndef DRAWSTATE_H
#define DRAWSTATE_H

typedef enum { 
	
	ShadeFrame,
	ShadeConstant, 
	ShadeDepth,
	ShadeFlat,
	ShadeGouraud
	
} ShadeMethod;

// DrawState structure
typedef struct {
	
	Color *color; 
	Color *flatColor;
	Color *body;
	Color *surface;
	float surfaceCoeff;
	int zBufferFlag;
	ShadeMethod shade;
	Point *viewer;
	
} DrawState;

// – create a new DrawState structure and initialize the fields.
DrawState *drawstate_create( void );

// – set the color field to c.
void drawstate_setColor( DrawState *s, Color c );

void drawstate_setBody( DrawState *s, Color c );

void drawstate_setSurface( DrawState *s, Color c );

void drawstate_setSurfaceCoeff( DrawState *s, float f );

// – copy the DrawState data.
void drawstate_copy( DrawState *to, DrawState *from );


#endif








