// Aziz Ghadiali, Project 2, 2/18/18
// include file

#ifndef FRACTALS_H
#define FRACTALS_H

//prototypes
void mandelbrot( Image *dst, float x0, float y0, float dx);

void julia(Image *dst, float x0, float y0, float dx);

void fractalNoise(Image *dst, int noiseIter);


#endif