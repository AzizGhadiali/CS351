/*
  Aziz Ghadiali (based on Bruce Maxwell's test code)

  Creates a Mandelbrot set at a selected location
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "fractals.h"



int main(int argc, char *argv[]) {
  Image *src;
//   create variables
  int rows;
  int cols;
  int noiseIter;
  float x;
  float y;
  float dx;
  char choice[10];
//  Ask user for values and what they want to create
  printf("Type in rows \n");
		scanf("%d", &rows);
		
  printf("Type in cols \n");
		scanf("%d", &cols);
				
  printf("Type in an x \n");
		scanf("%f", &x);
		
  printf("Type in a y \n");
		scanf("%f", &y);
		
  printf("Type in a dx \n");
		scanf("%f", &dx);
		
  printf("Type in a 'mandel', 'julia', or 'noise' \n");
		scanf("%s", choice);						
  
//   create an image
  src = image_create(rows, cols);

// create the desired fractal/noise
  if (strcmp(choice,"mandel")==0){			
  	mandelbrot( src, x, y, dx);
  }
  else if (strcmp(choice,"julia")==0){
  	julia( src, x, y, dx);
  }
  else{
  	printf("Type in a value between 1 and 10 to control the noise density \n");
	scanf("%d", &noiseIter);
  	fractalNoise(src, noiseIter);
  }
//   write image to file
  image_write( src, argv[1]);
// free src    
  image_free( src );
 
  return(0);
}

