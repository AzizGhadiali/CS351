/*
  Aziz Ghadiali, 2/13/18
  Merges two images using a mask as an alpha mask
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
		
  Pixel *image1;
  Pixel *image1copy;
  Pixel *image2;
  Pixel *mask;
  int rows1, cols1, rows2, cols2, rowsMask, colsMask, colors1, colors2, colorsMask; 
  int alpha, dx, dy, rows1copy, cols1copy, colors1copy;
  long imagesize, masksize, image2size;
  long i, j;
  char style[10];
  char upDown[5];
  char fbg[10];
  
  
  if(argc < 5) {
    printf("Usage: mask <input file 1> <input file 2> <mask file> <output file>\n");
    exit(-1);
  }

  /* read in the images */
  image1 = readPPM(&rows1, &cols1, &colors1, argv[1]);
  if(!image1) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }
  
  image1copy = readPPM(&rows1copy, &cols1copy, &colors1copy, argv[1]);
  if(!image1copy) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }
  
  image2 = readPPM(&rows2, &cols2, &colors2, argv[2]);
  if(!image2) {
    fprintf(stderr, "Unable to read %s\n", argv[2]);
    exit(-1);
  }
  
  mask = readPPM(&rowsMask, &colsMask, &colorsMask, argv[3]);
  if(!mask) {
    fprintf(stderr, "Unable to read %s\n", argv[3]);
    exit(-1);
  }

  /* calculate the image sizes */
  imagesize = (long)rows1 * (long)cols1;
  image2size = (long)rows2 * (long)cols2;
  masksize = (long)rowsMask * (long)colsMask;
  
  /* Take in the dx and dy input from the user*/
  printf("Type in a dx \n");
		scanf("%d", &dx);
  printf("Type in a dy \n");
		scanf("%d", &dy);
  /* Take in the style input from the user*/		
  printf("Enter 'normal', 'dark', or 'futuristic' for your overlay choice\n");
		scanf("%s", style);
  /* Take in the fg orientation from the user*/			
  printf("Enter 'flip' to flip the masked image with respect to the orientation of the background image, otherwise 'none'\n");
		scanf("%s", upDown);
  /* Take in the image orientation from the user*/			
  printf("Enter 'flipbg' to flip the entire image, otherwise 'none'\n");
		scanf("%s", fbg);
			
  /* Creates the start and end positions of the mask image*/
  int endx = dx + colsMask;
  int endy = dy + rowsMask;
  
  /* If the ending row or column of the image does not exist within the bounds of the 
  background, the end row or column is set to the final row or columns in the bg image*/
  if (endx > cols1){
  	endx = cols1;
  }
  if (endy > rows1){
  	endy = rows1;
  }

  /* Makes alpha masked image based on the user selected options */  
  for(i=dy;i<endy;i++) {
  	for(j=dx;j<endx;j++) {
  		int bgPos = i*cols1+j;
  		int fgPos = (i-dy) * cols2 + (j-dx);
  		
  		if (strcmp(upDown, "flip")==0){
  			fgPos = (endy-i)*cols2 + (endx-j);
  		}	
  		
		alpha = mask[fgPos].r/255;
		
		if (strcmp(style,"normal")==0 ){
		image1copy[bgPos].r = image1[bgPos].r = alpha*image1[bgPos].r + (1 - alpha)*image2[fgPos].r;
		image1copy[bgPos].g = image1[bgPos].g = alpha*image1[bgPos].g + (1 - alpha)*image2[fgPos].g;
		image1copy[bgPos].b = image1[bgPos].b = alpha*image1[bgPos].b + (1 - alpha)*image2[fgPos].b;
		
		}
		
		else if(strcmp(style,"futuristic")==0){
		image1copy[bgPos].r = image1[bgPos].r = image1[bgPos].r + (1 - alpha)*image2[fgPos].r*20;
		image1copy[bgPos].g = image1[bgPos].g = image1[bgPos].g + (1 - alpha)*image2[fgPos].g*20;
		image1copy[bgPos].b = image1[bgPos].b = image1[bgPos].b + (1 - alpha)*image2[fgPos].b*20;
		}
		
		else if(strcmp(style,"dark")==0){
		image1copy[bgPos].r = image1[bgPos].r = alpha*image1[bgPos].r + (1 - alpha)*image2[fgPos].r/5;
		image1copy[bgPos].g = image1[bgPos].g = alpha*image1[bgPos].g + (1 - alpha)*image2[fgPos].g/5;
		image1copy[bgPos].b = image1[bgPos].b = alpha*image1[bgPos].b + (1 - alpha)*image2[fgPos].b/5;
		}
		

		
	}	
  }
  
  //flip entire image based on user selection
  if (strcmp(fbg, "flipbg")==0){
  	int index = 0; 
  	for (i=imagesize; i>-1; i--){
  		image1[index].r = image1copy[i].r; 
    	image1[index].g = image1copy[i].g;
    	image1[index].b = image1copy[i].b; 
    	index++;
  	}
  }	  
    
  	
  

  		

  
  /* write out the resulting image */
  writePPM(image1, rows1, cols1, colors1 /* s/b 255 */, argv[4]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image1);
  free(image2);
  free(mask);
#endif

  return(0);
}
