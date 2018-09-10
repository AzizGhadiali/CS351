/* Aziz Ghadiali, Project 2, 2/18/18*/

//include
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "ppmIO.h"


//Image create function
Image *image_create( int rows, int cols){
	int i;
	long imagesize = cols * rows;
	Image *img = malloc(sizeof(Image));
	img->rows = rows;
	img->cols = cols;
	img->src = malloc(sizeof(FPixel)*rows*cols);
	return(img);
}

// de-allocates image data and frees the Image structure.
void image_free(Image *src){ 
	if (src != NULL){
		if (src->src != NULL){
			free(src->src);
		}
		free(src);
	}
}

/* given an uninitialized Image structure, sets the rows and cols
fields to zero and the data field to NULL.*/
void image_init(Image *src){
	src->rows = 0;
	src->cols = 0;
	src->src = NULL;
}
/* allocates space for the image data given rows and columns and initializes the image 
data to appropriate values, such as 0.0 for RGB and 1.0 for A and Z. Returns 0 if the 
operation is successful. Returns a non-zero value if the operation fails. */
int image_alloc(Image *src, int rows, int cols){
	int i;
	long imagesize = cols * rows;
	
	src->rows = rows;
	src->cols = cols;
	src->src = malloc(sizeof(FPixel)*rows*cols);
	for (i=0; i<imagesize; i++){
		src->src[i].rgb[0] = 0;
		src->src[i].rgb[1] = 0;
		src->src[i].rgb[2] = 0;
		src->src[i].a = 1.0;
		src->src[i].z = 1.0;
	}
	if (src){
		return 0;
	}
	else{
		return 1;
	}
}	

/*de-allocates image data and resets the Image structure
fields. The function does not free the Image structure*/
void image_dealloc(Image *src){ 
	if (src != NULL){
		free(src->src);
		src->rows = 0;
		src->cols = 0;
		src->src = NULL;
	}
}

/*– reads a PPM image from the given filename. An optional extension is to determine 
the image type from the filename and permit the use of different file types. Initializes 
the alpha channel to 1.0 and the z channel to 1.0. Returns a NULL pointer if the
operation fails.*/

Image *image_read(char *filename){
    int rows, cols, color, r, c;
    
    Pixel *src;
    Image *image;
    
    src = readPPM(&rows, &cols, &color, filename);
    printf("after readPPM: %d %d\n", rows, cols);
	image = image_create(rows,cols);
    
    if (!image){
    	return NULL;
    }
    
    int pix;
    for (r = 0; r<rows; r++){
    	for(c = 0; c<cols; c++){
    		
    		pix = r*cols+c;
    		image->src[pix].rgb[0] = src[pix].r/255.;
    		image->src[pix].rgb[1] = src[pix].g/255.;
    		image->src[pix].rgb[2] = src[pix].b/255.;
    		image->src[pix].a = 1.0;
			image->src[pix].z = 1.0; 
		}
	}
	free(src);
	return image;
}

/*writes a PPM image to the given filename.
Returns 0 on success. Optionally, you can look at the filename extension and write different
file types.*/
int image_write(Image *src, char *filename){ 
	int rows, cols, r, c, pix;
	Pixel *img;
	
	
	rows = src->rows;
	cols = src->cols;

	img = malloc(sizeof(Pixel)*rows*cols);
	for (r = 0; r<rows; r++){
		for(c = 0; c<cols; c++){
			pix = r*cols+c; 
			img[pix].r = src->src[pix].rgb[0]*255;
			img[pix].g = src->src[pix].rgb[1]*255;
			img[pix].b = src->src[pix].rgb[2]*255;
		}
	}
			 
	writePPM(img, rows, cols, 255, filename);
	
	if(!img){
		free(img);
		return 1;
	}
	free(img);
	return 0;
}	

// returns the FPixel at (r, c)
FPixel image_getf(Image *src, int r, int c){
	return src->src [r*src->cols+c];
}

//  returns the value of band b at pixel (r, c)
float image_getc(Image *src, int r, int c, int b){
	return src->src [r*src->cols+c].rgb[b];
}

// returns the alpha value at pixel (r, c)
float image_geta(Image *src, int r, int c){
	return src->src [r*src->cols+c].a;
}

// returns the depth value at pixel (r, c)
float image_getz(Image *src, int r, int c){
		return src->src [r*src->cols+c].z;
}	

// sets the values of pixel (r,c) to the FPixel val
void image_setf(Image *src, int r, int c, FPixel val){
	src->src [r*src->cols+c] = val;
}

//  sets the value of pixel (r, c) band b to val
void image_setc(Image *src, int r, int c, int b, float val){
	src->src [r*src->cols+c].rgb[b] = val;
}

// sets the alpha value of pixel (r, c) to val
void image_seta(Image *src, int r, int c, float val){
	src->src [r*src->cols+c].a = val;
}

//  sets the depth value of pixel (r, c) to val
void image_setz(Image *src, int r, int c, float val){
	
		src->src [r*src->cols+c].z = val;
}

// resets every pixel to a default value (e.g. Black, alpha value of 1.0, z value of 1.0)
void image_reset(Image *src){
	int i;
	long imagesize = src->cols * src->rows;
	for (i=0; i<imagesize; i++){
		src->src[i].rgb[0] = 0;
		src->src[i].rgb[1] = 0;
		src->src[i].rgb[2] = 0;
		src->src[i].a = 1.0;
		src->src[i].z = 1.0;
	}
}

// sets every FPixel to the given value	
void image_fill(Image *src, FPixel val){
	int i;
	long imagesize = src->cols * src->rows;
	for (i=0; i<imagesize; i++){
		src->src[i] = val;
	}
}

// sets the (r, g, b) values of each pixel to the given color
void image_fillrgb(Image *src, float r, float g, float b){
	int i;
	long imagesize = src->cols * src->rows;
	for (i=0; i<imagesize; i++){
		src->src[i].rgb[0] = r;
		src->src[i].rgb[1] = g;
		src->src[i].rgb[2] = b;
	}
}


// sets the alpha value of each pixel to the given value
void image_filla(Image *src, float a){
	int i;
	long imagesize = src->cols * src->rows;
	for (i=0; i<imagesize; i++){
		src->src[i].a = a;
	}
}

// sets the z value of each pixel to the given value
void image_fillz(Image *src, float z){
	int i;
	long imagesize = src->cols * src->rows;
	for (i=0; i<imagesize; i++){
		src->src[i].z = z;
	}
}



		
					
			
			
	
	
	

		


	
