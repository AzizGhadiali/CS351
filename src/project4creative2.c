/*
  Aziz Ghadiali
  Project 4
  3/2/18
  
  Creates concentric circles with different drawing/filling techniques
 */
#include "primitives.h"


int main(int argc, char *argv[]) {
	Image *src;
	Color Red, Green, White, Blue;
	Point p;
//   Create image objects and colors
	src = image_create( 2000, 2000 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );
	color_set( &White, 1, 1, 1 );
	color_set( &Blue, 0, 0, 1 );
	
// Create first set of circles
   	for(int i = 0; i<250; i++){
   		if (i%2 == 0){
   			Circle e;
  			point_set2D( &p, 1000, 1000 );
  			circle_set( &e, p, 500+i*1.5 );
  			circle_draw(&e, src, Red);
  		}
  		else{
  			Circle e;
  			point_set2D( &p, 1000, 1000 );
  			circle_set( &e, p, 500+i*1.5 );
  			circle_draw(&e, src, Green);
  		}
  	}
//   	Create gradient fill circle
   	Circle e;
  	point_set2D( &p, 1000, 1000 );
  	circle_set( &e, p, 600 );
  	circle_drawFillGradientHor(&e, src, Red, Green);

//  Create second set of circles
  	for(int i = 0; i<250; i++){
   		if (i%2 == 0){
   			Circle e;
  			point_set2D( &p, 1000, 1000 );
  			circle_set( &e, p, 100+i*1.5 );
  			circle_draw(&e, src, Blue);
  		}
  		else{
  			Circle e;
  			point_set2D( &p, 1000, 1000 );
  			circle_set( &e, p, 100+i*1.5 );
  			circle_draw(&e, src, White);
  		}
  	}
  	
//   	Another gradient filled circle
  	point_set2D( &p, 1000, 1000 );
  	circle_set( &e, p, 100 );
  	circle_drawFillGradientVert(&e, src, Blue, Red);
  	
  	
  	

// write images
  image_write( src, "Project4_creative2.ppm" );



  image_free( src );

  return(0);
}
