/*
  Aziz Ghadiali
  lighting.h
  February 22, 2018
  contains all functions for lighting
  
*/

#ifndef LIGHTING_H
#define LIGHTING_H

typedef enum {

	LightNone,
	LightAmbient,
	LightDirect,
	LightPoint,
	LightSpot,

} LightType;

typedef struct {

	LightType type;
	Color color;
	Vector direction;
	Point position;
	float cutoff; // stores the cosine of the cutoff angle of a spotlight
	float sharpness; // coefficient of the falloff function (power for cosine)

} Light;

typedef struct{
  
  int nLights;
  Light light[64];
  
} Lighting;

// –initialize the light to default values
void light_init( Light *light );

// –copy the light information
void light_copy( Light *to, Light *from );

// – allocate and return a new lighting structure set to default values.
Lighting *lighting_create( void );

// – initialize the lighting structure to default values.
void lighting_init( Lighting *l );

// add a new light to the Lighting structure given the parameters, some of which may be NULL,
// depending upon the type. Make sure you don’t add more lights than MAX LIGHTS.
void lighting_add( Lighting *l, LightType type, Color *c, Vector *dir, Point *pos, float cutoff, float sharpness );

// calculate the proper color given the normal N, view vector V
void lighting_shading( Lighting *l, Vector *N, Vector *V, Point *p, Color *Cb, Color *Cs, float s, int oneSided, Color *c );

	

#endif








