/*
  Aziz Ghadiali & Brit Biddle
  color.c
  February 22, 2018
  contains all functions for colors
  
*/
//include
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "ppmIO.h"
#include "color.h"

//  copies the Color data
void color_copy(Color *to, Color *from){
	to->c[0] = from->c[0];
	to->c[1] = from->c[1];
	to->c[2] = from->c[2];
}
	
// sets the Color data
void color_set(Color *to, float r, float g, float b){
	to->c[0] = r;
	to->c[1] = g;
	to->c[2] = b;
}

// copies the Color data to the proper pixel
void image_setColor( Image *img, int r, int c, Color val ){
	int cols = img->cols;
	if (r>= 0 && c>= 0 && r<img->rows && c<img->cols){
		img->src[r*cols+c].rgb[0] = val.c[0];
		img->src[r*cols+c].rgb[1] = val.c[1];
		img->src[r*cols+c].rgb[2] = val.c[2];
	}
}

// copies the Color data to the proper pixel with shading
void image_setColorShade( Image *img, int r, int c, Color val, double curZ ){
	int cols = img->cols;
	if (r>= 0 && c>= 0 && r<img->rows && c<img->cols){
		img->src[r*cols+c].rgb[0] = val.c[0] * (1-(1/curZ));
		img->src[r*cols+c].rgb[1] = val.c[1] * (1-(1/curZ));
		img->src[r*cols+c].rgb[2] = val.c[2] * (1-(1/curZ));
	}
}

void image_setColorSave( Image *img, int r, int c, Color val, int i){
	int cols = img->cols;
	img->src[r*cols+c].rgb[0] = val.c[0];
	img->src[r*cols+c].rgb[1] = val.c[1];
	img->src[r*cols+c].rgb[2] = val.c[2];
	
	char filename[30];
	sprintf(filename, "image%d.ppm", i);
	image_write(img, filename);
	
}

// returns a Color structure built from the pixel values
Color image_getColor( Image *img, int r, int c ){
	Color values;
	int cols = img->cols;
	values.c[0] = img->src[r*cols+c].rgb[0];
	values.c[1] = img->src[r*cols+c].rgb[1];
	values.c[2] = img->src[r*cols+c].rgb[2];
	return(values);
}