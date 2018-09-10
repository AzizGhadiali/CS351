/*
  Aziz Ghadiali
  drawState.c
  February 22, 2018
  contains all functions for drawstate
  
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "drawState.h"
#include "module.h"
#include "lighting.h"



// – create a new DrawState structure and initialize the fields.
DrawState *drawstate_create( ){
	DrawState *ds = malloc(sizeof(DrawState));
	ds -> color = malloc(sizeof(Color));
	ds -> flatColor = malloc(sizeof(Color));
	ds -> body = malloc(sizeof(Color));
	ds -> surface = malloc(sizeof(Color));
	ds -> surfaceCoeff = 0;
	ds ->zBufferFlag = 1;
	color_set(ds -> color, 1.0, 1.0, 1.0);
	color_set(ds -> body, 1.0, 1.0, 1.0);
	color_set(ds -> surface, 1.0, 1.0, 1.0);
	color_set(ds -> flatColor, 1.0, 1.0, 1.0);
	ds -> viewer = malloc(sizeof(Point));
	return ds;
}
	

// – set the color field to c.
void drawstate_setColor( DrawState *s, Color c ){
	if (s->color != NULL){
		free(s->color);
	}
	// allocate color
	s->color = malloc(sizeof(Color));
	color_copy(s->color,&c);
}

void drawstate_setBody( DrawState *s, Color c ){
	if (s->body != NULL){
		free(s->body);
	}
	// allocate color 
	s->body = malloc(sizeof(Color));
	color_copy(s->body,&c);	
}

void drawstate_setSurface( DrawState *s, Color c ){
	if (s->surface != NULL){
		free(s->surface);
	}
	// allocate color 
	s->surface = malloc(sizeof(Color));
	color_copy(s->surface,&c);
}

void drawstate_setSurfaceCoeff( DrawState *s, float f ){
	s->surfaceCoeff = f;
}


// – copy the DrawState data.
void drawstate_copy( DrawState *to, DrawState *from ){
	if (to == NULL || from == NULL){
		return;
	}
	
	to->shade = from->shade;
	
	if (from-> color != NULL){
		if (to->color != NULL){
			free(to->color);
		}
		
		to->color = malloc(sizeof(Color));
		color_copy(to->color, from->color);
	}

	if (from-> body != NULL){
		if (to->body != NULL){
			free(to->body);
		}
		
		to->body = malloc(sizeof(Color));
		color_copy(to->body, from->body);
	}

	if (from-> surface != NULL){
		if (to->surface != NULL){
			free(to->surface);
		}
		
		to->surface = malloc(sizeof(Color));
		color_copy(to->surface, from->surface);
	}
	
	if (from-> viewer != NULL){
		if (to-> viewer != NULL){
			free(to->viewer);
		}
		
		to->viewer = malloc(sizeof(Point));
		point_copy(to->viewer, from->viewer);
	}
	to->surfaceCoeff = from->surfaceCoeff;
		
}