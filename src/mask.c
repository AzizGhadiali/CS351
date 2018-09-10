/*
  Aziz Ghadiali, 2/13/18
  Reads in an image with green background and creates a mask making all green values white
  and all other values black. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image;
  int rows, cols, colors;
  char input[10];
  long imagesize;
  long i;

  if(argc < 3) {
    printf("Usage: mask <input file> <output file>\n");
    exit(-1);
  }

  printf("Is the background black or green? \n");
  scanf("%s", input);	
  /* read in the image */
  image = readPPM(&rows, &cols, &colors, argv[1]);
  if(!image) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }
  

  /* calculate the image size */
  imagesize = (long)rows * (long)cols;

  /* make mask  */
  for(i=0;i<imagesize;i++) {
  	
  	unsigned char r = image[i].r;
  	unsigned char g = image[i].g;
  	unsigned char b = image[i].b;
  	
  	if (strcmp(input,"green")==0){
		//if the value is green, change the r,g,b values to 255
  		if (g>b && 2*g>3*r && g>30){
  			image[i].r = image[i].b = image[i].g = 255;
  		}
  		//else set the r,g,b values to 0
  		else{
  			image[i].r = image[i].b = image[i].g = 0;
  		}
  	}
  	else{
		if (g<10 && r<10 && b<10){
  			image[i].r = image[i].b = image[i].g = 255;
  		}
  		else{
  			image[i].r = image[i].b = image[i].g = 0;
  		}
  	}
  	
  }

  /* write out the resulting image */
  writePPM(image, rows, cols, colors /* s/b 255 */, argv[2]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image);
#endif

  return(0);
}
