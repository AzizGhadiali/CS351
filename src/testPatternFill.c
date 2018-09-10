#include <stdio.h>
#include <stdlib.h>
#include "primitives.h"
#include "image.h"
/*
	Aziz Ghadiali
	Project 4
	3/2/18
	
	Test the pattern fill for polygons
*/

int main(int argc, char *argv[]) {
  Image *src;
  Image *psrc;
  Polygon p;
  Color Blue;
  Point pt[7];
// create color
  color_set(&Blue, 0.2, 0.1, 0.95 );
//   crate image
  src = image_create(700, 700);
//   read in pattern
  psrc = image_read("pattern2.ppm");

//   create polygon
  point_set2D(&(pt[0]), 532 , 205);
  point_set2D(&(pt[1]), 446 , 216);
  point_set2D(&(pt[2]), 400 , 290);
  point_set2D(&(pt[3]), 430 , 372);
  point_set2D(&(pt[4]), 512 , 399);
  point_set2D(&(pt[5]), 585 , 352);
  point_set2D(&(pt[6]), 594 , 266);
  polygon_set(&p, 7, &(pt[0]));
  
//   fill the polygon
  polygon_drawFill(&p, src, Blue);
  
//   replace the filled pixels with the pattern
  polygon_drawFillPattern(&p, src, psrc, Blue);
  
  printf("writing output\n");
  image_write(src, "testPatternFill.ppm");
  
}