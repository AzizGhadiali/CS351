/*
  Aziz Ghadiali
  particles.h
  February 22, 2018
  contains all functions for particle systems
  
*/

#include "matrix.h"

#ifndef PARTICLES_H
#define PARTICLES_H

typedef struct{
	Point location;
	Vector velocity;
	Vector acceleration;
	int state; //0-dead, 1-alive
	Color color;
	int temp;
}Particle;

typedef struct{
	int total; //total particles 
	int rate; //rate to create particles 
	int time;
	Particle *particles; //particles 
	Point p;
}Emitter;

void particle_set(Particle *p, Point loc, Vector vel, Vector acc, int state, Color c, int temp);

void particle_draw(Particle *p, Image *src, Matrix *VTM, int ds);

void particle_copy(Particle *to, Particle *from);

Emitter *emitter_create(void);

void emitter_init(Emitter *e);

void emitter_set(Emitter *e, int rate, Point c);

void emitter_free(Emitter *e);

void updateState(Emitter *e, int timestep, Color color, int temp, double vx, double vy, double vz, double ax, double ay, double az);



#endif








