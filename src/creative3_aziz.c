/*
  Aziz Ghadiali
  Project 3
  3/2/18
  
  Creates images of a record player and abstract art
 */
#include "primitives.h"

// Used from Bruce's test code
static int box( Image *src, Color color, int x, int y, int dx, int dy );
static int box( Image *src, Color color, int x, int y, int dx, int dy ) {
  Line l;
  
  line_set2D( &l, x, y, x, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x, y+dy, x + dx, y+dy );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y+dy, x+dx, y );
  line_draw( &l, src, color );

  line_set2D( &l, x+dx, y, x, y );
  line_draw( &l, src, color );

  return(0);
}

int main(int argc, char *argv[]) {
	Image *src, *src2;
	Color Red, Green, White, Blue;
	Point p;
	Line l1;
//   Create image objects and colors
	src = image_create( 2000, 2000 );
	src2 = image_create( 2000, 2000 );
	color_set( &Red, 0.9, 0.05, 0.05 );
	color_set( &Green, 0.6, 0.7, 0.09 );
	color_set( &White, 1, 1, 1 );
	color_set( &Blue, 0, 0, 1 );
	
// 	Creates a record player
// Creates the record
	for(int i = 0; i<200; i+=5){
   		Circle e;
  		point_set2D( &p, 600, 600 );
  		circle_set( &e, p, 100+i*1.5 );
  		circle_draw( &e, src, Green );
  		
  	}
// 	Create the nob 
	box( src, White, 800, 800, 50, 70);
	point_set2D( &p, 801, 801 );
 	floodFill(src, p, White);
 	
//  	Create the player
	int num = 0;
	while(num<100){
  		box( src, Red, 100+num, 100+num, 1000, 1000);
  		num++;
  	}
//   	Creates the line from center of record to nob
  	line_set2D( &l1, 600, 600, 800, 800 );
	line_draw( &l1, src, Red );
  	
//   	Abstract art
  	num = 0;
	while(num<100){
  		box( src2, Red, 500+num, 500+num, 1000+num, 1000+num);
  		box( src2, Blue, 500-num, 500-num, 1000+num, 1000+num);
  		box( src2, Green, 500+num, 500+num, 1000-num, 1000-num);
  		num++;
  	}
  
// write images
  image_write( src, "test_aziz_creative3.ppm" );
  image_write( src2, "test_aziz_creative4.ppm" );


  image_free( src );
  image_free( src2 );

  return(0);
}
