/*
  Aziz Ghadiali
  module.c
  February 22, 2018
  contains all functions for modules
  
*/

//include
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


// – Allocate and return an initialized but empty Element.
Element *element_create(){
	Element *element = malloc(sizeof(Element));
	return element;
}

// – Allocate an Element and store a duplicate of the data pointed to by obj in the Element. Modules do
// not get duplicated. The function needs to handle each type of object separately in a case statement.
Element *element_init(ObjectType type, void *obj){
	if (obj == NULL){
		return NULL;
	}
	
	Element *element = malloc(sizeof(Element));
	element -> type = type; 
	  
	switch(type){
	
      case ObjNone :
         break;
      case ObjLine :
      	element->obj = (void*) malloc(sizeof(Line));
      	line_copy((Line *) element->obj, (Line *) obj);
      	break;
      case ObjPoint :
      	element->obj = (void*) malloc(sizeof(Point));
        point_copy((Point *) element->obj, (Point *) obj);
		break;
      case ObjPolygon :
      	 element->obj = (void*)malloc(sizeof(Polygon));
      	 polygon_init((Polygon*) element->obj);
         polygon_copy((Polygon *) element->obj, (Polygon *) obj);
         break;
      case ObjPolyline :
      	 element->obj = (void*) malloc(sizeof(Polyline));
      	 polyline_init((Polyline*) element->obj);
         polyline_copy((Polyline *) element->obj, (Polyline *) obj);
         break;
      case ObjIdentity :
      	 element->obj = (void*) malloc(sizeof(Matrix));
         matrix_copy((Matrix *) element->obj, (Matrix *) obj);
         break;
       case ObjMatrix :
       	 element->obj = (void*) malloc(sizeof(Matrix));
         matrix_copy((Matrix *) element->obj, (Matrix *) obj);
         break;
      case ObjColor :
      	 element->obj = (void*) malloc(sizeof(Color));
      	 color_copy((Color *) element->obj, (Color *) obj);
      	 break;
      case ObjBodyColor :
      	 element->obj = (void*) malloc(sizeof(Color));
      	 color_copy((Color *) element->obj, (Color *) obj);
         break;
      case ObjSurfaceColor :
      	 element->obj = (void*) malloc(sizeof(Color));
      	 color_copy((Color *) element->obj, (Color *) obj);

         break;
      case ObjSurfaceCoeff :
      	 element->obj = (void*) malloc(sizeof(float));
      	 element->obj = obj;
         break;
      case ObjLight :
      	 element->obj = (void*) malloc(sizeof(Light));
      	 light_copy((Light *) element->obj, (Light *) obj);
         break;
      case ObjModule :
         element->obj = obj;
         break; 
    }
    
    return element;
}
         	
         
// – free the element and the object it contains, as appropriate.
void element_delete(Element *e){
	if (e == NULL){return;}
	 
	ObjectType type = e -> type;
	
	switch(type){
	
      case ObjNone :
         break;
      case ObjLine :
			if(e->obj != NULL){
				free((Line*)e->obj);
			}
			free(e);
      		break;
      case ObjPoint :
			if(e->obj != NULL){
				free((Point*)e->obj);
			}
			free(e);
      		break;
      case ObjPolygon :
			if(e->obj != NULL){
				polygon_free((Polygon*)e->obj);
			}
			free(e);
      		break;
      case ObjPolyline :
			if(e->obj != NULL){
				polyline_free((Polyline*)e->obj);
			}
			free(e);
      		break;
      case ObjIdentity :
			if(e->obj != NULL){
				free((Matrix*)e->obj);
			}
			free(e);
      		break;
       case ObjMatrix :
			if(e->obj != NULL){
				free((Matrix*)e->obj);
			}
			free(e);
      		break;
      case ObjColor :
			if(e->obj != NULL){
				free((Color*)e->obj);
			}
			free(e);
      		break;
      case ObjBodyColor :
      	if(e->obj != NULL){
				free((Color*)e->obj);
			}
			free(e);
      		break;
         
      case ObjSurfaceColor :
      	if(e->obj != NULL){
				free((Color*)e->obj);
			}
			free(e);
      		break;
         
      case ObjSurfaceCoeff :
      	if(e->obj != NULL){
				free((float*)e->obj);
			}
			free(e);
         
      case ObjLight :
      	if(e->obj != NULL){
				free((Light*)e->obj);
			}
			free(e);

         	break;
      case ObjModule :
      	if(e->obj != NULL){
      		free((Module*)e->obj);
      	}
      	free(e);
      	break; 
	}
}

// – Allocate an empty module.
Module *module_create(){ 
	Module *md = malloc(sizeof(Module)); 
	md->head = NULL;
	md->tail = NULL;
	return md;
}

// – clear the module’s list of Elements, freeing memory as appropriate.
void module_clear(Module *md){
	if(md == NULL){
		return;
	}

	Element *temp;
	Element *n = md->head;

	while(n != NULL){
		temp = n->next;
		element_delete(n);
		n = temp;
	}
	md->head = NULL;
	md->tail = NULL;
}

// – Free all of the memory associated with a module, including the memory pointed to by md.
void module_delete(Module *md){
	 module_clear(md);
	 free(md);
}
	
// – Generic insert of an element into the module at the tail of the list.
void module_insert(Module *md, Element *e){
	if(md == NULL){
		return;
	}
	
	if (e == NULL){
		return;
	}
	if(md->tail == NULL){
		md->head = e;
		md->tail = e;
		md->tail->next = NULL;
		return;
	}
				
	md->tail->next = e;
	md->tail = e;
	md->tail->next = NULL;
}

// – Adds a pointer to the Module sub to the tail of the module’s list.
void module_module(Module *md, Module *sub){
	if(md == NULL || sub == NULL){
		return;
	}
	
	Element *e = element_init(ObjModule, (void*)sub);
	module_insert(md,e);
}

// – Adds p to the tail of the module’s list.
void module_point(Module *md, Point *p){
	if(md == NULL){
		return;
	}
	
	if(p == NULL){
		return;
	}
	
	Element *e = element_init(ObjPoint, (void*)p);
	module_insert(md,e);
}

// – Adds p to the tail of the module’s list.
void module_line(Module *md, Line *p){
	if(md == NULL){
		return;
	}
	
	if(p == NULL){
		return;
	}
	Element *e = element_init(ObjLine, (void*)p);
	module_insert(md,e);
}

// – Adds p to the tail of the module’s list.
void module_polyline(Module *md, Polyline *p){
	if(md == NULL){
		return;
	}
	
	if(p == NULL){
		return;
	}
	
	Element *e = element_init(ObjPolyline, (void*)p);
	module_insert(md,e);
}

// – Adds p to the tail of the module’s list.
void module_polygon(Module *md, Polygon *p){
	if(md == NULL){
		return;
	}
	
	if(p == NULL){
		return;
	}
	
	Element *e = element_init(ObjPolygon, (void*)p);
	module_insert(md,e);
}

void module_identity(Module *md){

	if (md == NULL) return; 
	Matrix m; 
	matrix_identity(&m);
	Element *ele = element_init(ObjIdentity, (void *) &m);
	module_insert(md, ele); 
}


void module_translate2D(Module *md, double tx, double ty){

	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_translate2D(&m, tx, ty);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele); 
}


void module_scale2D(Module *md, double sx, double sy){

	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_scale2D(&m, sx, sy);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele); 
}


void module_rotateZ(Module *md, double cth, double sth){

	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_rotateZ(&m, cth, sth);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele); 
}


void module_shear2D(Module *md, double shx, double shy){

	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_shear2D(&m, shx, shy);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele); 
}
// – Draw the module into the image using the given view transformation matrix [VTM], Lighting and
// DrawState by traversing the list of Elements. (For now, Lighting can be an empty structure.)
void module_draw(Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Lighting *lighting, Image *src){

	Matrix LTM; 
	matrix_identity(&LTM);
	
	Element *ele = md->head;

	while(ele){
		switch(ele->type){

			case ObjNone:
				break; 

			case ObjLine:
				{

					Line tmp; 
					line_copy(&tmp, (Line *) ele->obj);
					matrix_xformLine(&LTM, &tmp);
// 					point_print(&tmp.b, stdout);
					matrix_xformLine(GTM, &tmp);
// 					point_print(&tmp.b, stdout);
					matrix_xformLine(VTM, &tmp);
// 					point_print(&tmp.b, stdout);
					line_normalize(&tmp); 
					// point_print(&tmp.b, stdout);
// 					point_print(&tmp.a, stdout);
					line_draw(&tmp, src, *ds->color);
					break; 
				}

			case ObjPoint:
				{
					Point tmp; 
					Point tmp2;
					point_copy(&tmp, (Point *) ele->obj);
					matrix_xformPoint(&LTM, (Point *) ele->obj, &tmp);
					matrix_xformPoint(GTM, &tmp, &tmp2);
					matrix_xformPoint(VTM, &tmp2, &tmp);
					point_normalize(&tmp); 
					point_print(&tmp, stdout);
					point_draw(&tmp, src, *ds->color);
					break; 
				}

			case ObjPolyline:
				{
					Polyline tmp; 
					polyline_init(&tmp);
					polyline_copy(&tmp, (Polyline *) ele->obj);
					matrix_xformPolyline(&LTM, &tmp);
					matrix_xformPolyline(GTM, &tmp);
					matrix_xformPolyline(VTM, &tmp);
					polyline_normalize(&tmp); 
					polyline_draw(&tmp, src, *ds->color);
					polyline_print(&tmp, stdout);
					polyline_clear(&tmp);
					break; 
				}

			case ObjPolygon:
				{
										
					Polygon tmp; 
					polygon_init(&tmp);
					polygon_copy(&tmp, (Polygon *) ele->obj);
					matrix_xformPolygon(&LTM, &tmp);
					matrix_xformPolygon(GTM, &tmp);
					if(ds->shade == ShadeGouraud || ds->shade == ShadeFlat){
						polygon_shade(&tmp, lighting, ds);

					}

					matrix_xformPolygon(VTM, &tmp);
					polygon_normalize(&tmp); 

					if(ds->shade == ShadeFrame){
						polygon_draw(&tmp, src, *ds->color);
					}
					else if(ds->shade == ShadeConstant){
						polygon_drawFill(&tmp, src, *ds->color, ds);
						
					}
					else{
						polygon_drawShade(&tmp, src, ds, NULL);
					}
						
			

					polygon_clear(&tmp);
					
					break; 
				}

			case ObjIdentity:
				matrix_identity(&LTM);
				break;

			case ObjMatrix:
				matrix_multiply((Matrix *) ele->obj, &LTM, &LTM);
				break;

			case ObjColor:
				color_copy(ds->color, (Color *) ele->obj);				 
				break;

			case ObjBodyColor:
				color_copy(ds->body, (Color *) ele->obj);
				break; 

			case ObjSurfaceColor:
				color_copy(ds->surface, (Color *) ele->obj);
			printf("r surface in module draw %f \n", ds->surface->c[0]);
			printf("g %f \n", ds->surface->c[1]);
			printf("b %f \n", ds->surface->c[2]);
				break; 

			case ObjSurfaceCoeff:
				ds->surfaceCoeff = *(float*) ele->obj;
				break; 

			case ObjLight:
				break; 

			case ObjModule:
				{
					Matrix TM; 
					DrawState *tempDs = drawstate_create(); 
					matrix_multiply(GTM, &LTM, &TM); 
					drawstate_copy( tempDs, ds);
					module_draw( (Module *) ele->obj, VTM, &TM, tempDs, lighting, src );
					free(tempDs);
					break;
				}
		}
		ele = ele->next; 

	} 

}

// – Matrix operand to add a 3D translation to the Module.
void module_translate(Module *md, double tx, double ty, double tz)
{
	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_translate(&m, tx, ty, tz);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele);
}

// – Matrix operand to add a 3D scale to the Module.
void module_scale(Module *md, double sx, double sy, double sz){
	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_scale(&m, sx, sy, sz);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele);
}

// – Matrix operand to add a rotation about the X-axis to the Module.
void module_rotateX(Module *md, double cth, double sth){
	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_rotateX(&m, cth, sth);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele);
}

// – Matrix operand to add a rotation about the Y-axis to the Module.
void module_rotateY(Module *md, double cth, double sth){
	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_rotateY(&m, cth, sth);
	Element *ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele);
}

// – Matrix operand to add a rotation that orients to the orthonormal axes ~u, ~v, w~.
void module_rotateXYZ(Module *md, Vector *u, Vector *v, Vector *w){
	if (md == NULL) return; 
	Matrix m;
	matrix_identity(&m);  
	matrix_rotateXYZ(&m, u, v, w);
	Element *ele;
	ele = element_init(ObjMatrix, (void *) &m);
	module_insert(md, ele);
}

//– Adds a unit cube, axis-aligned and centered on zero to the Module. If solid is zero, add only lines. If solid is non-zero, use polygons. Make sure each polygon has surface normals defined for it.
void module_cube(Module *md, int solid){
	Polygon side[6];
	Polygon p;
	Point pt[4];
  	Point v[8];
  	Point tv[4];
  	Line lines[12];
  	Vector n[4];
  	int i;

  	
  	for(i=0;i<6;i++) {
    	polygon_init( &side[i] );
  	}

  	 // corners of a cube, centered at (0, 0, 0)
		 point_set3D( &v[0], -.5, -.5, -.5 );
		 point_set3D( &v[1],  .5, -.5, -.5 );
		 point_set3D( &v[2],  .5,  .5, -.5 );
		 point_set3D( &v[3], -.5,  .5, -.5 );
		 point_set3D( &v[4], -.5, -.5,  .5 );
		 point_set3D( &v[5],  .5, -.5,  .5 );
		 point_set3D( &v[6],  .5,  .5,  .5 );
		 point_set3D( &v[7], -.5,  .5,  .5 );
  	
  	if(solid == 1){
		polygon_init( &p );
		point_set3D( &pt[0], -.5, -.5, -.5 );
		point_set3D( &pt[1], -.5, -.5,  .5 );
		point_set3D( &pt[2], -.5,  .5,  .5 );
		point_set3D( &pt[3], -.5,  .5, -.5 );
		polygon_set( &p, 4, pt );
		for(i=0;i<4;i++)
		  vector_set( &(n[i]), -1, 0, 0 );
		polygon_setNormals( &p, 4, n );
		module_polygon( md, &p );

		point_set3D( &pt[0], .5, -.5, -.5 );
		point_set3D( &pt[1], .5, -.5,  .5 );
		point_set3D( &pt[2], .5,  .5,  .5 );
		point_set3D( &pt[3], .5,  .5, -.5 );
		polygon_set( &p, 4, pt );
		for(i=0;i<4;i++)
		  vector_set( &(n[i]), 1, 0, 0 );
		polygon_setNormals( &p, 4, n );
		module_polygon( md, &p );

		point_set3D( &pt[0], -.5, -.5, -.5 );
		point_set3D( &pt[1], -.5, -.5,  .5 );
		point_set3D( &pt[2],  .5, -.5,  .5 );
		point_set3D( &pt[3],  .5, -.5, -.5 );
		polygon_set( &p, 4, pt );
		for(i=0;i<4;i++)
		  vector_set( &(n[i]), 0, -1, 0 );
		polygon_setNormals( &p, 4, n );
		module_polygon( md, &p );

		point_set3D( &pt[0], -.5, .5, -.5 );
		point_set3D( &pt[1], -.5, .5,  .5 );
		point_set3D( &pt[2],  .5, .5,  .5 );
		point_set3D( &pt[3],  .5, .5, -.5 );
		polygon_set( &p, 4, pt );
		for(i=0;i<4;i++)
		  vector_set( &(n[i]), 0, 1, 0 );
		polygon_setNormals( &p, 4, n );
		module_polygon( md, &p );

		point_set3D( &pt[0], -.5, -.5, -.5 );
		point_set3D( &pt[1], -.5,  .5, -.5 );
		point_set3D( &pt[2],  .5,  .5, -.5 );
		point_set3D( &pt[3],  .5, -.5, -.5 );
		polygon_set( &p, 4, pt );
		for(i=0;i<4;i++)
		  vector_set( &(n[i]), 0, 0, -1 );
		polygon_setNormals( &p, 4, n );
		module_polygon( md, &p );

		point_set3D( &pt[0], -.5, -.5, .5 );
		point_set3D( &pt[1], -.5,  .5, .5 );
		point_set3D( &pt[2],  .5,  .5, .5 );
		point_set3D( &pt[3],  .5, -.5, .5 );
		polygon_set( &p, 4, pt );
		for(i=0;i<4;i++)
		  vector_set( &(n[i]), 0, 0, 1 );
		polygon_setNormals( &p, 4, n );
		module_polygon( md, &p );




		  // // front side
		  // polygon_set( &side[0], 4, &(v[0]) );
		  
		  // for(i=0;i<4;i++){
		  // 	vector_set( &(n[i]), -1, 0, 0 );
		  // }

		  // polygon_setNormals( &side[0], 4, n );

		  // // back side
		  // polygon_set( &side[1], 4, &(v[4]) );



		  // // top side
		  // point_copy( &tv[0], &v[2] );
		  // point_copy( &tv[1], &v[3] );
		  // point_copy( &tv[2], &v[7] );
		  // point_copy( &tv[3], &v[6] );

		  // polygon_set( &side[2], 4, tv );

		  // // bottom side
		  // point_copy( &tv[0], &v[0] );
		  // point_copy( &tv[1], &v[1] );
		  // point_copy( &tv[2], &v[5] );
		  // point_copy( &tv[3], &v[4] );

		  // polygon_set( &side[3], 4, tv );

		  // // left side
		  // point_copy( &tv[0], &v[0] );
		  // point_copy( &tv[1], &v[3] );
		  // point_copy( &tv[2], &v[7] );
		  // point_copy( &tv[3], &v[4] );

		  // polygon_set( &side[4], 4, tv );

		  // // right side
		  // point_copy( &tv[0], &v[1] );
		  // point_copy( &tv[1], &v[2] );
		  // point_copy( &tv[2], &v[6] );
		  // point_copy( &tv[3], &v[5] );

		  // polygon_set( &side[5], 4, tv );
		  
		  // for(int i=0;i<6;i++) {
    // 		module_polygon(md, &side[i] );
  		//   }
	  }
	  else{
	  	
	  	line_set(&(lines[0]), v[0], v[1]);
	  	line_set(&(lines[1]), v[1], v[2]);
	  	line_set(&(lines[2]), v[2], v[3]);
	  	line_set(&(lines[3]), v[3], v[0]);
	  	line_set(&(lines[4]), v[3], v[7]);
	  	line_set(&(lines[5]), v[6], v[2]);
	  	line_set(&(lines[6]), v[4], v[7]);
	  	line_set(&(lines[7]), v[7], v[6]);
	  	line_set(&(lines[8]), v[6], v[5]);
	  	line_set(&(lines[9]), v[0], v[4]);
	  	line_set(&(lines[10]), v[4], v[5]);
	  	line_set(&(lines[11]), v[5], v[1]);
	  	
	  	module_line(md, &lines[0]);
	  	module_line(md, &lines[1]);
	  	module_line(md, &lines[2]);
	  	module_line(md, &lines[3]);
		module_line(md, &lines[4]);
		module_line(md, &lines[5]);
		module_line(md, &lines[6]);
		module_line(md, &lines[7]);
		module_line(md, &lines[8]);
		module_line(md, &lines[9]);
		module_line(md, &lines[10]);
		module_line(md, &lines[11]);
	}	
 
}

// – Adds the foreground color value to the tail of the module’s list.
void module_color(Module *md, Color *c){
	if (md == NULL || c == NULL){ return;} 
	Element *ele = element_init(ObjColor, (void *) c);
	module_insert(md, ele);
}

void module_bezierCurve(Module *m, BezierCurve *b, int divisions){

	if (divisions == 0){
		Line l[3];

		line_set(&l[0], b->ctrl[0], b->ctrl[1]);
		line_set(&l[1], b->ctrl[1], b->ctrl[2]);
		line_set(&l[2], b->ctrl[2], b->ctrl[3]);

		module_line(m, &l[0]);
		module_line(m, &l[1]);
		module_line(m, &l[2]);

		return;
	}

	Point p1[4];
	Point p2[4];

	BezierCurve q;
	BezierCurve r;

	// q0
	point_copy(&p1[0], &b->ctrl[0]);

	// q1
	point_set3D(&p1[1], .5*(b->ctrl[0].val[0]+b->ctrl[1].val[0]), .5*(b->ctrl[0].val[1]+b->ctrl[1].val[1]), .5*(b->ctrl[0].val[2]+b->ctrl[1].val[2]));


	// q2
	point_set3D(&p1[2], .5 * (p1[1].val[0]) + .25*(b->ctrl[1].val[0] + b->ctrl[2].val[0]), .5*(p1[1].val[1]) + .25*(b->ctrl[1].val[1] + b->ctrl[2].val[1]), .5*(p1[1].val[2]) + .25*(b->ctrl[1].val[2] + b->ctrl[2].val[2])  );

	// r3
	point_copy(&p2[3], &b->ctrl[3]);

	// r2
	point_set3D(&p2[2], .5*(b->ctrl[2].val[0]+b->ctrl[3].val[0]), .5*(b->ctrl[2].val[1]+b->ctrl[3].val[1]), .5*(b->ctrl[2].val[2]+b->ctrl[3].val[2]));

	// r1
	point_set3D(&p2[1], .5*(p2[2].val[0]) +  .25*(b->ctrl[1].val[0] + b->ctrl[2].val[0]), .5*(p2[2].val[1]) +  .25*(b->ctrl[1].val[1] + b->ctrl[2].val[1]), .5*(p2[2].val[2]) +  .25*(b->ctrl[1].val[2] + b->ctrl[2].val[2])  );

	// q3
	point_set3D(&p1[3], .5*(p1[2].val[0] + p2[1].val[0]), .5*(p1[2].val[1] + p2[1].val[1]), .5*(p1[2].val[2] + p2[1].val[2]));

	 // r0
	point_copy(&p2[0], &p1[3]);


	bezierCurve_set(&q, &p1[0]);
	bezierCurve_set(&r, &p2[0]);

	module_bezierCurve(m, &q, divisions-1);
	module_bezierCurve(m, &r, divisions-1);

}

void decastCurves(BezierCurve *b, Point p1[4], Point p2[4], int i){

	// q0
	point_copy(&p1[0], &b->ctrl[i+0]);

	// q1
	point_set3D(&p1[1], .5*(b->ctrl[i+0].val[0]+b->ctrl[i+1].val[0]), .5*(b->ctrl[i+0].val[1]+b->ctrl[i+1].val[1]), .5*(b->ctrl[i+0].val[2]+b->ctrl[i+1].val[2]));


	// q2
	point_set3D(&p1[2], .5 * (p1[1].val[0]) + .25*(b->ctrl[i+1].val[0] + b->ctrl[i+2].val[0]), .5*(p1[1].val[1]) + .25*(b->ctrl[i+1].val[1] + b->ctrl[i+2].val[1]),  .5*(p1[1].val[2]) + .25*(b->ctrl[i+1].val[2] + b->ctrl[i+2].val[2]));

	// r3
	point_copy(&p2[3], &b->ctrl[i+3]);

	// r2
	point_set3D(&p2[2], .5*(b->ctrl[i+2].val[0]+b->ctrl[i+3].val[0]), .5*(b->ctrl[i+2].val[1]+b->ctrl[i+3].val[1]), .5*(b->ctrl[i+2].val[2]+b->ctrl[i+3].val[2]));

	// r1
	point_set3D(&p2[1], .5*(p2[2].val[0]) +  .25*(b->ctrl[i+1].val[0] + b->ctrl[i+2].val[0]), .5*(p2[2].val[1]) +  .25*(b->ctrl[i+1].val[1] + b->ctrl[i+2].val[1]), .5*(p2[2].val[2]) +  .25*(b->ctrl[i+1].val[2] + b->ctrl[i+2].val[2]));

	// q3
	point_set3D(&p1[3], .5*(p1[2].val[0] + p2[1].val[0]), .5*(p1[2].val[1] + p2[1].val[1]), .5*(p1[2].val[2] + p2[1].val[2]));

	 // r0
	point_copy(&p2[0], &p1[3]);


}

void decastSurfaces(BezierSurface *b, Point p1[4], Point p2[4], int i){
	
	// q0
	point_copy(&p1[0], &b->ctrl[i+0]);

	// q1
	point_set3D(&p1[1], .5*(b->ctrl[i+0].val[0]+b->ctrl[i+1].val[0]), .5*(b->ctrl[i+0].val[1]+b->ctrl[i+1].val[1]), .5*(b->ctrl[i+0].val[2]+b->ctrl[i+1].val[2]));


	// q2
	point_set3D(&p1[2], .5 * (p1[1].val[0]) + .25*(b->ctrl[i+1].val[0] + b->ctrl[i+2].val[0]), .5*(p1[1].val[1]) + .25*(b->ctrl[i+1].val[1] + b->ctrl[i+2].val[1]),  .5*(p1[1].val[2]) + .25*(b->ctrl[i+1].val[2] + b->ctrl[i+2].val[2]));

	// r3
	point_copy(&p2[3], &b->ctrl[i+3]);

	// r2
	point_set3D(&p2[2], .5*(b->ctrl[i+2].val[0]+b->ctrl[i+3].val[0]), .5*(b->ctrl[i+2].val[1]+b->ctrl[i+3].val[1]), .5*(b->ctrl[i+2].val[2]+b->ctrl[i+3].val[2]));

	// r1
	point_set3D(&p2[1], .5*(p2[2].val[0]) +  .25*(b->ctrl[i+1].val[0] + b->ctrl[i+2].val[0]), .5*(p2[2].val[1]) +  .25*(b->ctrl[i+1].val[1] + b->ctrl[i+2].val[1]), .5*(p2[2].val[2]) +  .25*(b->ctrl[i+1].val[2] + b->ctrl[i+2].val[2]));

	// q3
	point_set3D(&p1[3], .5*(p1[2].val[0] + p2[1].val[0]), .5*(p1[2].val[1] + p2[1].val[1]), .5*(p1[2].val[2] + p2[1].val[2]));

	 // r0
	point_copy(&p2[0], &p1[3]);


}

void modSurfaceCreate(BezierSurface *b1, int start1, int end1, int start2, int end2, Point c[8][8]){
	int index = 0;
	Point surfPoints [16];
	int a,b;

	for(a = start1;a > end1;a--){
			for(b = start2;b < end2;b++){
				point_copy(&surfPoints[index], &c[a][b]);
				index++;		
			}
	}

	bezierSurface_set(b1, surfPoints);

}


void module_bezierSurface(Module *m, BezierSurface *b, int divisions, int solid){
	int i, j;

	if (divisions == 0){
		if (solid == 0){
			Line l;
			
			for (i=0;i<4;i++){
				for(j=0;j<3;j++){
					line_set(&l, b->ctrl[i*4 + j], b->ctrl[i*4 + j+1]);
					module_line(m, &l);
				}
			}
			
			for(i=0;i<3;i++){
				for(j=0;j<4;j++){
					line_set(&l, b->ctrl[i*4 + j], b->ctrl[i*4 + j + 4]);
					module_line(m, &l);
				}
			}
			return;
		}
		
	}
	

	BezierSurface b1;
	BezierCurve bCurve;

	Point p1[4];
	Point p2[4];
	Point p3[4];

	Point a1[4][8];
	Point c1[8][8];

// run deCasteljau on a set of 4 curves yielding 32 points 
	int count = 0;
	for(i=0;i<4;i++){

		decastSurfaces(b, p1, p2, i*4);

		for (j=0;j<4;j++){
			a1[i][j] = p1[j];
			a1[i][j+4] = p2[j];
		}
		
	}



// run deCasteljau on the 8 curves in the opposite direction yielding 64 points
	

	for(i=0;i<8;i++){

		point_copy(&p3[0], &a1[0][i]);
		point_copy(&p3[1], &a1[1][i]);
		point_copy(&p3[2], &a1[2][i]);
		point_copy(&p3[3], &a1[3][i]);
		
		bezierCurve_set(&bCurve, p3);
		decastCurves(&bCurve, p1, p2, 0);
		count++;

		for (j=0;j<4;j++){
			c1[i][j] = p1[j];
			c1[i][j+4] = p2[j];
			
		}
		
	}

// resursively divide the 4x4 surfaces

	modSurfaceCreate(&b1, 3, -1, 0, 4, c1);
	module_bezierSurface(m, &b1, divisions-1, solid);

	modSurfaceCreate(&b1, 7, 3, 0, 4, c1);
	module_bezierSurface(m, &b1, divisions-1, solid);

	modSurfaceCreate(&b1, 3, -1, 4, 8, c1);
	module_bezierSurface(m, &b1, divisions-1, solid);

	modSurfaceCreate(&b1, 7, 3, 4, 8, c1);
	module_bezierSurface(m, &b1, divisions-1, solid);

}

// Function to add a unit cylinder to the module
// Based test 6b code by Bruce Maxwell
void module_cylinder(Module *mod, Polygon *p, int sides){
	
	Point xtop, xbot;
	double x1, x2, z1, z2;
	int i;

	polygon_init( p );
	point_set3D( &xtop, 0, 1.0, 0.0 );
	point_set3D( &xbot, 0, 0.0, 0.0 );

	// make a fan for the top and bottom sides
	// and quadrilaterals for the sides

	for(i=0;i<sides;i++) {
		Point pt[4];

		x1 = cos( i * M_PI * 2.0 / sides );
		z1 = sin( i * M_PI * 2.0 / sides );
		x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
		z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

		point_copy( &pt[0], &xtop );
		point_set3D( &pt[1], x1, 1.0, z1 );
		point_set3D( &pt[2], x2, 1.0, z2 );

		polygon_set( p, 3, pt );
		module_polygon( mod, p );

		point_copy( &pt[0], &xbot );
		point_set3D( &pt[1], x1, 0.0, z1 );
		point_set3D( &pt[2], x2, 0.0, z2 );

		polygon_set( p, 3, pt );
		module_polygon( mod, p );

		point_set3D( &pt[0], x1, 0.0, z1 );
		point_set3D( &pt[1], x2, 0.0, z2 );
		point_set3D( &pt[2], x2, 1.0, z2 );
		point_set3D( &pt[3], x1, 1.0, z1 );

		polygon_set( p, 4, pt );
		module_polygon( mod, p );
  }
  polygon_clear(p);
	
}

void module_octahedron(Module *mod, Polygon *p, int x, int y, int z){

	Point pt[16];

	polygon_init(p);

	point_set3D(&pt[0], x+0, y+0, z+1);
	point_set3D(&pt[1], x+0, y+1, z+0);
	point_set3D(&pt[2], x+1, y+0, z+0);
	point_set3D(&pt[3], x+0, y+0, z+1);
	point_set3D(&pt[4], x+0, y-1, z+0);
	point_set3D(&pt[5], x+1, y+0, z+0);
	point_set3D(&pt[6], x+0, y+0, z-1);
	point_set3D(&pt[7], x+0, y-1, z+0);
	point_set3D(&pt[8], x-1, y+0, z+0);
	point_set3D(&pt[9], x+0, y+0, z-1);
	point_set3D(&pt[10], x+0, y+1, z+0);
	point_set3D(&pt[11], x-1, y+0, z+0);
	point_set3D(&pt[12], x+0, y+0, z+1);
	point_set3D(&pt[13], x+0, y+1, z+0);
	point_set3D(&pt[14], x+0, y+0, z+1);
	point_set3D(&pt[15], x+0, y-1, z+0);

	polygon_set( p, 16, pt );
	module_polygon( mod, p );

	polygon_clear(p);
}

void module_pyramid(Module *mod, Polygon *p, double x, double y, double z){
		
		Point verts[10];
		polygon_init(p);

		point_set3D( &verts[0], x+.5, y+1, z+.5 );
		point_set3D( &verts[1], x, y, z );
		point_set3D( &verts[2],  x+1, y, z );
		polygon_set( p, 3, &(verts[0]) );
  		module_polygon(mod, p);

  		point_set3D( &verts[0], x+.5, y+1, z+.5 );
  		point_set3D( &verts[1], x, y, z );
  		point_set3D( &verts[2],  x, y, z+1 );
  		polygon_set( p, 3, &(verts[0]) );
  		module_polygon(mod, p);

  		point_set3D( &verts[0], x+.5, y+1, z+.5 );
  		point_set3D( &verts[1],  x, y, z+1 );
		point_set3D( &verts[2],  x+1,  y, z+1 );
		polygon_set( p, 3, &(verts[0]) );
  		module_polygon(mod, p);
  		
  		point_set3D( &verts[0], x+.5, y+1, z+.5 );
		point_set3D( &verts[1],  x+1, y, z );
		point_set3D( &verts[2],  x+1,  y, z+1 );
		polygon_set( p, 3, &(verts[0]) );
  		module_polygon(mod, p);
  	
  		polygon_clear(p);
}

void module_bodyColor(Module *md, Color *c){
	if (md == NULL) return; 
	Element *ele = element_init(ObjBodyColor, (void*) c);
	module_insert(md, ele);
}

void module_surfaceColor(Module *md, Color *c){
	if (md == NULL) return; 
	Element *ele = element_init(ObjSurfaceColor, (void*) c);
	module_insert(md, ele);
}

void module_surfaceCoeff(Module *md, float coeff){
	if (md == NULL) return; 
	Element *ele = element_init(ObjSurfaceCoeff, (void*) &coeff);
	module_insert(md, ele);
}


