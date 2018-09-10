/* Aziz Ghadiali, Project 2, Fractals library 2/18/18*/

//include
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

#include "image.h"
#include "ppmIO.h"
#include "fractals.h"

// Makes the fractal noise
void fractalNoise(Image *dst, int noiseIter){
	int rows, cols;
	
	rows = dst->rows;
	cols = dst->cols;
	dst->src = malloc(sizeof(FPixel)*rows*cols);
	
// 	creates the 2-D noise array and assigns each index a random value
	double noise[rows][cols];
	float value = (rand() % 32768) / 32768.0;
// 	random value is marginally increased each iteration
	for (int y = 0; y < rows; y++){
  		for (int x = 0; x < cols; x++){
  			noise[y][x] = (rand() % 32768) / value;
  			value += .005;
  		}
  	}
//   Write the noise into an image structure
  	for(int i = 0; i < rows; i+=noiseIter){
  		for(int j = 0; j < cols; j+=noiseIter){
    		dst->src [i*dst->cols+j].rgb[0] = noise[i][j];
    		dst->src [i*dst->cols+j].rgb[1] = noise[i][j];
    		dst->src [i*dst->cols+j].rgb[2] = noise[i][j];
    		
  		}
  	}
	
}	
	
// Creates the julia set
void julia(Image *dst, float x0, float y0, float dx){
	int rows, cols, i, j, n,  numIter;
	float cx, cy, zx, zy, tempzx, tempzy, dy, zcolor; 
// 	assign rows and cols values. Allocate image space.
	rows = dst->rows;
	cols = dst->cols;
	dst->src = malloc(sizeof(FPixel)*rows*cols);
// 	calculate dy
	dy = (dx*rows)/cols;
// 	loop through rows and cols of image 
	for (i=0;i<rows;i++){
		for(j=0;j<cols;j++){
// 		calculate the julia set values with constants cx and cy
			cx = -1.037;
			cy = 0.17;
			zx = 1.5*(j-cols/2)/(0.5*dx*cols) + x0;
			zy = (i-rows/2)/(.5*dy*rows) + y0;
			tempzx = zx;
			tempzy = zy;
			numIter = 501;
// 			run test 500 times
			for(n=0; n<500; n++){
				zx = (pow(tempzx, 2))-(pow(tempzy, 2))-cx;
				zy = 2*tempzx*tempzy-cy;
// 				test if the magnitude of z is greater than 2
				if(sqrt(pow(zx,2)+pow(zy,2))>2){
					zcolor = sqrt(pow(zx,2)+pow(zy,2));
					numIter = n;
					break;
				}
// 				holds value of n-1 iteration
				tempzx = zx;
				tempzy = zy;
				
			}
// 			coloring methods

//			Method 1
			if (numIter>500){
				image_setc(dst, i, j, 0, numIter%500/1.0);
				image_setc(dst, i, j, 1, 0);
				image_setc(dst, i, j, 2, 0);
			}
			else{
				image_setc(dst, i, j, 0, .9);
				image_setc(dst, i, j, 1, log(numIter));
				image_setc(dst, i, j, 2, 0);
			}

// 			Method 2
// 			image_setc(dst, i, j, 0, 0);
// 			image_setc(dst, i, j, 1, numIter%500/1.0);
// 			image_setc(dst, i, j, 2, 0);
			
// 			Method 3			
// 			image_setc(dst, i, j, 0, numIter%500/1.0);
// 			image_setc(dst, i, j, 1, numIter%500/1.0);
// 			image_setc(dst, i, j, 2, numIter%500/1.0);
// 			
// 			Method 4			
		// 	image_setc(dst, i, j, 0, logf(logf(zcolor))/logf(2.0));
// 			image_setc(dst, i, j, 1, logf(logf(zcolor))/logf(2.0));
// 			image_setc(dst, i, j, 2, logf(logf(zcolor))/logf(2.0));
// 			Method 6
			// image_setc(dst, i, j, 0, sin((numIter%500/1.0)));
// 			image_setc(dst, i, j, 1, cos((numIter%500/1.0)));
// 			image_setc(dst, i, j, 2, .3);



			
			
		}
	}
}
	
// create mandelbrot set
void mandelbrot( Image *dst, float x0, float y0, float dx){
	int rows, cols, i, j, n, numIter;
	float cx, cy, zx, zy, tempzx, tempzy, dy, zcolor; 
// 	assign rows and cols values. Allocate image space.
	rows = dst->rows;
	cols = dst->cols;
	dst->src = malloc(sizeof(FPixel)*rows*cols);
// 	calculate dy	
	dy = (dx*rows)/cols;
//  loop through the image	
	for (i=0;i<rows;i++){
		for(j=0;j<cols;j++){
// 		calculate the mandelbrot set values with constants cx and cy
			cx = (dx/cols)*j+x0;
			cy = -(dy/rows)*i+(y0+dy);
			zx = 0.0;
			zy = 0.0;
			tempzx = zx;
			tempzy = zy;
			numIter = 501;
// 			run test 500 times
			for(n=0; n<500; n++){
				zx = (pow(tempzx, 2))-(pow(tempzy, 2))-cx;
				zy = 2*tempzx*tempzy-cy;
// 				test if the magnitude of z is greater than 2
				if(sqrt(pow(zx,2)+pow(zy,2))>2){
					zcolor = sqrt(pow(zx,2)+pow(zy,2));
					numIter = n;
					break;
				}
// 				holds value of n-1 iteration

				tempzx = zx;
				tempzy = zy;
				
			}
// 			coloring methods
			
			
//			Method 1
			// image_setc(dst, i, j, 0, (numIter%500)/1.0);
// 			image_setc(dst, i, j, 1, (numIter%500)/1.0);
// 			image_setc(dst, i, j, 2, (numIter%500)/1.0);

//			Method 2			
			// image_setc(dst, i, j, 0, .2);
// 			image_setc(dst, i, j, 1, (numIter%500)/1.0);
// 			image_setc(dst, i, j, 2, .5);

//			Method 3
			// image_setc(dst, i, j, 0, logf(logf(zcolor))/logf(2.0));
// 			image_setc(dst, i, j, 1, logf(logf(zcolor))/logf(2.0));
// 			image_setc(dst, i, j, 2, logf(logf(zcolor))/logf(2.0));

// 			Method 4
			// image_setc(dst, i, j, 0, .2);
// 			image_setc(dst, i, j, 1, (numIter%50)/10);
// 			image_setc(dst, i, j, 2, .6);

// 			Method 5
			// image_setc(dst, i, j, 0, logf(logf(numIter))/logf(2.0));
// 			image_setc(dst, i, j, 1, .1);
// 			image_setc(dst, i, j, 2, .3);
// 			Method 6
			image_setc(dst, i, j, 0, sin((numIter%500/1.0)));
			image_setc(dst, i, j, 1, cos((numIter%500/1.0)));
			image_setc(dst, i, j, 2, .3);



		}
	}
}
	