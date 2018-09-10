// Aziz Ghadiali & Brit Biddle, Project 3, 2/18/18
// color header file


#ifndef COLOR_H
#define COLOR_H

// define color structure
typedef struct {

	float c[3];

} Color;

//  copies the Color data
void color_copy(Color *to, Color *from);

// sets the Color data
void color_set(Color *to, float r, float g, float b);

// copies the Color data to the proper pixel
void image_setColor( Image *src, int r, int c, Color val );

// returns a Color structure built from the pixel values
Color image_getColor( Image *src, int r, int c );

void image_setColorShade( Image *img, int r, int c, Color val, double curZ );

// Saves image after setting color
void image_setColorSave( Image *img, int r, int c, Color val, int i  );

#endif