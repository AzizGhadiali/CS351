// Aziz Ghadiali, Project 2, 2/18/18
// include image file

#ifndef IMAGE_H
#define IMAGE_H

typedef struct{

	float rgb[3];
	float a;
	float z;
} FPixel;

//define image structure
typedef struct{

	int rows;
	int cols;
	FPixel *src;
} Image;



//prototypes

//Image create function
Image *image_create( int rows, int cols);

/*– reads a PPM image from the given filename. An optional extension is to determine 
the image type from the filename and permit the use of different file types. Initializes 
the alpha channel to 1.0 and the z channel to 1.0. Returns a NULL pointer if the
operation fails.*/
Image *image_read(char *filename);

/*writes a PPM image to the given filename.
Returns 0 on success. Optionally, you can look at the filename extension and write different
file types.*/
int image_write(Image *src, char *filename);

// de-allocates image data and frees the Image structure.
void image_free(Image *src);

/* given an uninitialized Image structure, sets the rows and cols
fields to zero and the data field to NULL.*/
void image_init(Image *src);

/*de-allocates image data and resets the Image structure
fields. The function does not free the Image structure*/
void image_dealloc(Image *src);

/* allocates space for the image data given rows and columns and initializes the image 
data to appropriate values */
int image_alloc(Image *src, int rows, int cols);

// returns the FPixel at (r, c)
FPixel image_getf(Image *src, int r, int c);

//  returns the value of band b at pixel (r, c)
float image_getc(Image *src, int r, int c, int b);

// returns the alpha value at pixel (r, c)
float image_geta(Image *src, int r, int c);

// returns the depth value at pixel (r, c)
float image_getz(Image *src, int r, int c);

// sets the values of pixel (r,c) to the FPixel val
void image_setf(Image *src, int r, int c, FPixel val);

//  sets the value of pixel (r, c) band b to val
void image_setc(Image *src, int r, int c, int b, float val);

// sets the alpha value of pixel (r, c) to val
void image_seta(Image *src, int r, int c, float val);

//  sets the depth value of pixel (r, c) to val
void image_setz(Image *src, int r, int c, float val);

// resets every pixel to a default value (e.g. Black, alpha value of 1.0, z value of 1.0)
void image_reset(Image *src);

// sets every FPixel to the given value	
void image_fill(Image *src, FPixel val);

// sets the (r, g, b) values of each pixel to the given color
void image_fillrgb(Image *src, float r, float g, float b);

// sets the alpha value of each pixel to the given value
void image_filla(Image *src, float a);

// sets the z value of each pixel to the given value
void image_fillz(Image *src, float z);


#endif