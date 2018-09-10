/*
  Aziz Ghadiali
  particles.c
  May 13, 2018
  contains all functions for particles
  
*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "primitives.h"
#include "particles.h"
#include "matrix.h"


// sets the location, velocity, acceleration, state, color, and temperature of the particle
void particle_set(Particle *p, Point location, Vector velocity, Vector acceleration, int state, Color c, int temp){
	point_copy(&p->location, &location);
	vector_copy(&p->velocity, &velocity);
	vector_copy(&p->acceleration, &acceleration);
	p->state = state;
	color_copy(&p->color, &c);
	p->temp = temp;
}

// draws the particle into the image src as either a point (0) or a circle (1) based on the value of dc
void particle_draw(Particle *p, Image *src, Matrix *VTM, int ds){
	if (ds == 0){
		Point tmp;
		matrix_xformPoint(VTM, &p->location, &tmp);
		point_draw(&p->location, src, p->color);
	}
	else{
		Circle circ;
		circle_set(&circ, p->location, 1);
		circle_drawFill(&circ, src, p->color);
	}
	

}

// copies the particle information to a new particle
void particle_copy(Particle *to, Particle *from){
	point_copy(&to->location, &from->location);
	vector_copy(&to->velocity, &from->velocity);
	vector_copy(&to->acceleration, &from->acceleration);
	to->state = from->state;
	color_copy(&to->color, &from->color);
	to->temp = from->temp;
	
}

// Creates an emitter
Emitter *emitter_create(){
	Emitter *e = malloc(sizeof(Emitter));
	e->total = 0;
	e->rate = 0;
	e->time = 0;
	e->particles = NULL;
	return e;
}

// initialize an emitter to default values
void emitter_init(Emitter *e){
	if(e != NULL){
		e->total = 0;
		e->rate = 0;
		e->time = 0;
		if(e->particles != NULL){
			free(e->particles);
			e->particles = NULL;
		}
	}
}

// set the emitter rate and point
void emitter_set(Emitter *e, int rate, Point c){
	e->rate = rate;
	point_copy(&e->p, &c);
	
	
}

// free the emitter
void emitter_free(Emitter *e){
	if(e != NULL){
		if(e->particles != NULL){
			free(e->particles);
		}
		free(e);
	}
}

/* updates the state of the particles in the emitter. Takes in an emitter, 
final time step, base color, temperature (life of the particle) and values between 0 and 1 
in order to manipluate the x, y, and z of the acceleration and velocity of the particles*/

void updateState(Emitter *e, int timestep, Color color, int temp, double vx, double vy, double vz, double ax, double ay, double az ){
	srand(time(NULL));
	
	if(e == NULL){
		return;
	}
	// if time step is 0 create the amount of particles specified by the spawn rate
	int i;
	if(timestep == 0){
		e->particles = malloc(sizeof(Particle)*e->rate);
		for(i=0; i < e->rate; i++){
			
			Particle part;
			// sets the velocity of the particle
			Vector v;
			vector_set(&v, ((rand()%200)/100.0)-vx, ((rand()%200)/100.0)-vy, ((rand()%200)/100.0)-vz);
			// sets the acceleration of the particle
			Vector a;
			vector_set(&a, ((rand()%200)/1000.0)-ax, ((rand()%200)/1000.0)-ay, ((rand()%200)/1000.0)-az);
			
			
			particle_set(&part, e->p, v, a, 1, color, temp);
			
			e->particles[i] = part;
			
		}
		e->total = e->rate;
		// fade out the particles and add in newly spawned particles
	}else if(timestep < 10){
		int count = 0;
		for(i=0; i<e->total; i++){
			if(e->particles[i].temp > 0){
				count ++;
			}else{
				e->particles[i].state = 0;
			}
		}
		count += e->rate;
		
		
		Particle *tmpList = malloc(sizeof(Particle)*e->total);
		for(i=0; i<e->total; i++){
			particle_copy( &tmpList[i], &e->particles[i]);
		}
		free(e->particles);
		e->particles = malloc(sizeof(Particle)*count);

		int idx = 0;
		for(i=0; i<e->total; i++){
			if(tmpList[i].state == 1){
				particle_copy(&e->particles[idx], &tmpList[i]);
			
				//update location
				e->particles[idx].location.val[0] += e->particles[idx].velocity.val[0];
				e->particles[idx].location.val[1] += e->particles[idx].velocity.val[1];
				e->particles[idx].location.val[2] += e->particles[idx].velocity.val[2];
			
// 				point_print(&e->particles[i].location, stdout);
				vector_print(&e->particles[i].velocity, stdout);
			
				//update velocity
				e->particles[idx].velocity.val[0] += e->particles[idx].acceleration.val[0];
				e->particles[idx].velocity.val[1] += e->particles[idx].acceleration.val[1];
				e->particles[idx].velocity.val[2] += e->particles[idx].acceleration.val[2];
			

				e->particles[i].color.c[0] += e->particles[i].temp%10;
				e->particles[i].color.c[1] += e->particles[i].temp%10;
				e->particles[i].color.c[2] -= e->particles[i].temp%10;
			
				e->particles[idx].temp -= 1;
				
				idx ++;
			}
		}
		
		for(i=idx; i < count; i++){
			
			Particle part;
			
			Vector v;
			vector_set(&v, ((rand()%200)/100.0)-vx, ((rand()%200)/100.0)-vy, ((rand()%200)/100.0)-vz);
			
			Vector a;
			vector_set(&a, ((rand()%200)/1000.0)-ax, ((rand()%200)/1000.0)-ay, ((rand()%200)/1000.0)-az);
						
			particle_set(&part, e->p, v, a, 1, color, temp);
			
			
			e->particles[i] = part;
			

		}
		e->total = count;
		free(tmpList);
	}else{
		// update particles velocity and position
		int count = 0;
		for(i=0; i<e->total; i++){
			if(e->particles[i].temp > 0){
				count ++;
			}else{
				e->particles[i].state = 0;
			}
		}
		
		Particle *tmpList = malloc(sizeof(Particle)*e->total);
		for(i=0; i<e->total; i++){
			particle_copy( &tmpList[i], &e->particles[i]);
		}
		free(e->particles);
		e->particles = malloc(sizeof(Particle)*count);

		int idx = 0;
		for(i=0; i<e->total; i++){
			if(tmpList[i].state == 1){
				particle_copy(&e->particles[idx], &tmpList[i]);
			
				//update location
				e->particles[idx].location.val[0] += e->particles[idx].velocity.val[0];
				e->particles[idx].location.val[1] += e->particles[idx].velocity.val[1];
				e->particles[idx].location.val[2] += e->particles[idx].velocity.val[2];
			
// 				point_print(&e->particles[i].location, stdout);
				vector_print(&e->particles[i].velocity, stdout);
			
				//update velocity
				e->particles[idx].velocity.val[0] += e->particles[idx].acceleration.val[0];
				e->particles[idx].velocity.val[1] += e->particles[idx].acceleration.val[1];
				e->particles[idx].velocity.val[2] += e->particles[idx].acceleration.val[2];
			

				e->particles[i].color.c[0] += e->particles[i].temp%10;
				e->particles[i].color.c[1] += e->particles[i].temp%10;
				e->particles[i].color.c[2] -= e->particles[i].temp%10;
			
				e->particles[idx].temp -= 1;
				
				idx ++;
			}
		}
		e->total = count;
		free(tmpList);
	}
}


 










