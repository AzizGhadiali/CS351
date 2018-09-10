/*
  Aziz Ghadiali
  Project 3
  3/2/18
  
  Creates an image of a truck
 */
#include "primitives.h"

int main(int argc, char *argv[]) {
  Image *src;
  Color Red, Green;
  Point tire1, tire2;
  Circle t1, t2;
  Line carBase, carBack, carBack2, carTop1, carTop2, carTop3, carTop4, carFront1, carFront2, carFront3, carFront4, carFront5, carFront6, carFront7, carFront8;
  
// Set colors
  color_set( &Green, 0, 1.0, .2 );
  color_set( &Red, 0.9, 0.05, 0.05 );

// Create Image
  src = image_create( 1000, 1000 );

// Draw car base  
  line_set2D( &carBase, 100, 500, 700, 500);
  line_draw( &carBase, src, Green );
  
//  Draw car back 
  line_set2D( &carBack, 100, 500, 100, 300);
  line_draw( &carBack, src, Green );
  
  line_set2D( &carBack2, 100, 500, 0, 400);
  line_draw( &carBack2, src, Green );
  
// Draw car top  
  line_set2D( &carTop1, 100, 300, 700, 300);
  line_draw( &carTop1, src, Green );
  
  line_set2D( &carTop2, 100, 300, 0, 200);
  line_draw( &carTop2, src, Green );
  
  line_set2D( &carTop3, 0, 200, 600, 200);
  line_draw( &carTop3, src, Green );
  

// Draw car front
  
  line_set2D( &carFront1, 700, 300, 700, 500);
  line_draw( &carFront1, src, Green );
  
  line_set2D( &carFront2, 700, 300, 700, 100);
  line_draw( &carFront2, src, Green );
  
  line_set2D( &carFront3, 600, 200, 600, 50);
  line_draw( &carFront3, src, Green );
  
  line_set2D( &carTop4, 600, 200, 700, 300);
  line_draw( &carTop4, src, Green );
  
  line_set2D( &carFront4, 600, 50, 700, 100);
  line_draw( &carFront4, src, Green );
  
  line_set2D( &carFront5, 700, 100, 800, 300);
  line_draw( &carFront5, src, Green );
  
  line_set2D( &carFront6, 700, 100, 800, 300);
  line_draw( &carFront6, src, Green );
  
  line_set2D( &carFront6, 800, 300, 600, 300);
  line_draw( &carFront6, src, Green );
  
  line_set2D( &carFront7, 800, 300, 800, 500);
  line_draw( &carFront7, src, Green );
  
  line_set2D( &carFront8, 800, 500, 700, 500);
  line_draw( &carFront8, src, Green );
  
  

//   Draw Wheels
  point_set2D( &tire1, 600, 500 );
  circle_set( &t1, tire1, 60 );
  circle_draw( &t1, src, Red );
  
  floodFill(src, tire1, Red);
  
  point_set2D( &tire2, 200, 500 );
  circle_set( &t2, tire2, 60 );
  circle_draw( &t2, src, Red );
  
  floodFill(src, tire2, Red);

//   Write image
  image_write( src, "test_aziz_creative.ppm" );

// Free memory
  image_free( src );

  return(0);
}
