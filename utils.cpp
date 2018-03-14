#include <iostream>
#include <math.h>

#include "EasyBMP.h"
#include "color/hsv.h"
#include "color/color.h"


/*
void createCanvasHSV(hsv3** canvas, int width, int height){
	canvas = new hsv3*[width];
	for(int i = 0; i<width; i++){
		canvas[i] = new hsv3[height];
	}

}*/

hsv3** createCanvasHSV(int width, int height){
	hsv3** canvas;
	canvas = new hsv3*[width];
	for(int i = 0; i<width; i++){
		canvas[i] = new hsv3[height];
	}

	return canvas;

}

bw1** createCanvasBW(int width, int height){
	bw1** canvas;
	canvas = new bw1*[width];
	for(int i = 0; i<width; i++){
		canvas[i] = new bw1[height];
	}

	return canvas;

}


rgb3** createCanvasRGB(int width, int height){
	rgb3** canvas;
	canvas = new rgb3*[width];
	for(int i = 0; i<width; i++){
		canvas[i] = new rgb3[height];
	}

	return canvas;

}


rgb3** EasyBMPtoRGB(BMP image){
	int width = image.TellWidth();
	int height = image.TellHeight();

	
	rgb3** canvas = createCanvasRGB(width, height);

	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			canvas[i][j].R = (float)image(i,j)->Red/255.0;
			canvas[i][j].G = (float)image(i,j)->Green/255.0;
			canvas[i][j].B = (float)image(i,j)->Blue/255.0;
		}
	}

	return canvas;
}


hsv3** convertRGBtoHSV(rgb3** imageRGB, int width, int height){
	

	
	hsv3** imageHSV = createCanvasHSV(width, height);

	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			imageHSV[i][j] = rgb2hsv(imageRGB[i][j]);
		}
	}

	return imageHSV;
}


rgb3** convertHSVtoRGB(hsv3** imageHSV, int width, int height){

	rgb3** imageRGB = createCanvasRGB(width, height);

	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			imageRGB[i][j] = hsv2rgb(imageHSV[i][j]);
		}
	}

	return imageRGB;
}

