/*
  Aziz Ghadiali
  module.c
  May 8, 2018
  contains all functions for lighting
  
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "primitives.h"
#include "matrix.h"
#include "vector.h"
#include "module.h"
#include "drawState.h"
#include "lighting.h"
#include "bezier.h"

// –initialize the light to default values
void light_init( Light *light ){
	Color c = {{0,0,0}};
	Vector d = {{0,0,0}};
	Point p = {{0,0,0}};

	light->type = LightNone;
	light->color = c;
	light->direction = d;
	light->position = p;
	light->cutoff = 0;
	light->sharpness = 0;
	
}

// –copy the light information
void light_copy( Light *to, Light *from ){
	to->type = from->type;
	color_copy(&to->color,&from->color);
	vector_copy(&to->direction,&from->direction);
	point_copy(&to->position, &from->position);
	to->cutoff = from->cutoff;
	to->sharpness = from->sharpness;
}

// – allocate and return a new lighting structure set to default values.
Lighting *lighting_create( void ){
	Lighting *l = malloc(sizeof(Lighting));
	l->nLights = 0;
	return l;
}

// – initialize the lighting structure to default values.
void lighting_init( Lighting *l ){
	l->nLights = 0;
}

// add a new light to the Lighting structure given the parameters, some of which may be NULL,
// depending upon the type. Make sure you don’t add more lights than MAX LIGHTS.
void lighting_add( Lighting *l, LightType type, Color *c, Vector *dir, Point *pos, float cutoff, float sharpness ){
	if(l == NULL){
		return;
	}

	if(l->nLights > 64){
		return;
	}


	switch(type){
		case LightNone:
			break;
		case LightAmbient:
		{
			printf("%s\n", "hi");
			Light light;
			light.type = LightAmbient;
			color_copy(&light.color, c);
			light.cutoff = cutoff;
			light.sharpness = sharpness;
			l->light[l->nLights] = light;
			l->nLights++;
			break;
		}
		case LightDirect:
		{
			Light light;
			light.type = LightDirect;
			
			color_copy(&light.color, c);
			vector_copy(&light.direction, dir);
			light.cutoff = cutoff;
			light.sharpness = sharpness;
			l->light[l->nLights] = light;
			l->nLights++;
			break;
		}
		case LightPoint:
		{
			Light light;
			light.type = LightPoint;
			color_copy(&light.color, c);
			// printf("light r = %f\n", light.color.c[0] );
			// printf("light g = %f\n", light.color.c[1] );
			// printf("light b = %f\n", light.color.c[2] );
			point_copy(&light.position, pos);
			light.cutoff = cutoff;
			light.sharpness = sharpness;
			l->light[l->nLights] = light;
			l->nLights++;
			break;
		}
		case LightSpot:
		{
			Light light;
			light.type = LightSpot;
			color_copy(&light.color, c);
			point_copy(&light.position, pos);
			vector_copy(&light.direction, dir);
			light.cutoff = cutoff;
			light.sharpness = sharpness;
			l->light[l->nLights] = light;
			l->nLights++;
			break;
		}
	}


}

// calculate the proper color given the normal N, view vector V
void lighting_shading( Lighting *l, Vector *N, Vector *V, Point *p, Color *Cb, Color *Cs, float s, int oneSided, Color *c ){
	// printf("enters lightingShading\n");
	Color sum; 

	sum.c[0] = sum.c[1] = sum.c[2] = 0;
	int i;


	for(i = 0; i<l->nLights; i++){

		switch(l->light[i].type){
			case LightNone:
				break;	
			
			case LightAmbient:
			{
				sum.c[0] += l->light[i].color.c[0] * Cb->c[0];
				sum.c[1] += l->light[i].color.c[1] * Cb->c[1];
				sum.c[2] += l->light[i].color.c[2] * Cb->c[2];


				break;
			}
			case LightDirect:
			{
				
				break;
			}
			case LightPoint:
			{

				// printf("enters lightPoint\n");
				vector_normalize(N);
				vector_normalize(V);

				Vector L = {{l->light[i].position.val[0] - p->val[0], l->light[i].position.val[1] - p->val[1], l->light[i].position.val[2] - p->val[2], p->val[3]}};
				vector_normalize(&L);
				
				// vector_print(&L, stdout);
				// vector_print(N, stdout);
				double L_N = vector_dot(&L,N);
				// printf("L_N = %f\n", L_N);
				
				if (oneSided == 1 && L_N < 0){
					continue;
				}


				double sigma = vector_dot(V,N);
				// printf("%f\n", sigma );
				if ((L_N < 0 && sigma > 0) || (L_N > 0 && sigma < 0)){
					continue;
				}

				Vector H = {{(L.val[0] + V->val[0])/2, (L.val[1] + V->val[1])/2, (L.val[2] + V->val[2])/2}};
				vector_normalize(&H);
				double H_N = pow(vector_dot(&H,N), s);


				if(L_N < 0){
					L_N = -1 *L_N;
					H_N = -1 *H_N;
				}

				// printf("%f\n", l->light[i].color.c[0]);
				// printf("%f\n", Cb->c[0]);
				// printf("%f\n", Cs->c[0]);


				sum.c[0] += l->light[i].color.c[0] * Cb->c[0] * L_N + l->light[i].color.c[0] * Cs->c[0] * H_N;
				sum.c[1] += l->light[i].color.c[1] * Cb->c[1] * L_N + l->light[i].color.c[1] * Cs->c[1] * H_N;
				sum.c[2] += l->light[i].color.c[2] * Cb->c[2] * L_N + l->light[i].color.c[2] * Cs->c[2] * H_N;

				// sum.c[0] += l->light[i].color.c[0] * Cs->c[0] * H_N;
				// sum.c[1] += l->light[i].color.c[1] * Cs->c[1] * H_N;
				// sum.c[2] += l->light[i].color.c[2] * Cs->c[2] * H_N;

				// printf("Red %f\n", l->light[i].color.c[0]);
				// printf("Green %f\n", l->light[i].color.c[1]);
				// printf("Blue %f\n", l->light[i].color.c[2]);

				// printf("Red %f\n", sum.c[0]);
				// printf("Green %f\n", sum.c[1]);
				// printf("Blue %f\n", sum.c[2]);


				break;
			}
			case LightSpot:
			{

				// printf("enters lightPoint\n");
				vector_normalize(N);
				vector_normalize(V);

				Vector L = {{l->light[i].position.val[0] - p->val[0], l->light[i].position.val[1] - p->val[1], l->light[i].position.val[2] - p->val[2], p->val[3]}};
				vector_normalize(&L);
				
				// vector_print(&L, stdout);
				// vector_print(N, stdout);
				double L_N = vector_dot(&L,N);


				if (oneSided == 1 && L_N < 0){
					continue;
				}

				double sigma = vector_dot(V,N);
				if ((L_N < 0 && sigma > 0) || (L_N > 0 && sigma < 0)){
					continue;
				}

				Vector H = {{(L.val[0] + V->val[0])/2, (L.val[1] + V->val[1])/2, (L.val[2] + V->val[2])/2}};
				vector_normalize(&H);
				double H_N = pow(vector_dot(&H,N), s);

				if(L_N < 0){
					L_N = -1 *L_N;
					H_N = -1 *H_N;
				}

				double t = vector_dot(&L,&l->light[i].direction);	
		
				if (t < l->light[i].cutoff){
					sum.c[0] += (l->light[i].color.c[0] * Cb->c[0] * L_N + l->light[i].color.c[0] * Cs->c[0] * H_N) * pow(t, l->light[i].sharpness);
					sum.c[1] += (l->light[i].color.c[1] * Cb->c[1] * L_N + l->light[i].color.c[1] * Cs->c[1] * H_N) * pow(t, l->light[i].sharpness);
					sum.c[2] += (l->light[i].color.c[2] * Cb->c[2] * L_N + l->light[i].color.c[2] * Cs->c[2] * H_N) * pow(t, l->light[i].sharpness);

						// sum.c[0] *= pow(t, l->light[i].sharpness); 
						// sum.c[1] *= pow(t, l->light[i].sharpness); 
						// sum.c[2] *= pow(t, l->light[i].sharpness); 
				}
			
				break;
			}
		}
	}

	if(sum.c[0] > 1){
		sum.c[0] = 1;
	}
	if(sum.c[1] > 1){
		sum.c[1] = 1;
	}
	if(sum.c[2] > 1){
		sum.c[2] = 1;
	}
	if(sum.c[0] < 0){
		sum.c[0] = 0;
	}
	if(sum.c[1] < 0){
		sum.c[1] = 0;
	}
	if(sum.c[2] < 0){
		sum.c[2] = 0;
	}
	color_copy(c,&sum);

}