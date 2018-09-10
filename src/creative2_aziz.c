/*
  Aziz Ghadiali
  Project 3
  3/2/18
  
  Experimenting with random 3d object creation
 */
#include "primitives.h"

int main(int argc, char *argv[]) {
	Image *src;
	Color Red, Green;
	Point p;
//   Create image
	src = image_create( 2000, 2000 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );

//   	Creates a cylindrical objects
	for(int i = 0; i<100; i++){
  		Ellipse e;
  	
  		point_set2D( &p, 260+i*1.5, 160+i );
  	
  		ellipse_set(&e, p, 150, 100);
 		ellipse_draw(&e, src, Red);
 	 
  	}
  
	for(int i = 0; i<100; i++){
   		Circle c;
  		point_set2D( &p, 200+i*1.2, 500+i*1.5 );
  		circle_set( &c, p, 100 );
  		circle_draw( &c, src, Green );
  	}
  	
//  Creates concentric circles 	
  	for(int i = 0; i<200; i++){
   		Circle c;
  		point_set2D( &p, 1000, 700 );
  		circle_set( &c, p, 10+i*1.5 );
  		circle_draw( &c, src, Green );
  		
  	}
  	
//   	Creates a triangle
  	for(int i = 0; i<1000; i++){
   		Line l;
  		line_set2D( &l, 1000, 900, 600+i, 1500);
  		line_draw( &l, src, Red );
  		
  	}

//   Wite image
  image_write( src, "test_aziz_creative2.ppm" );
  
// Free memory
  image_free( src );

  return(0);
}
