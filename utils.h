#ifndef UTILS_H_
#define UTILS_H_ 1

#include <iostream>
#include <math.h>


#include "color/hsv.h"
#include "color/color.h"
#include "EasyBMP.h"


template <typename T>
inline T max3(T a, T b, T c){
	if(a<c){a = c;}
	if(a<b){a = b;}
	return a;
}

template <typename T>
inline T min3(T a, T b, T c){
	if(a>c){a = c;}
	if(a>b){a = b;}
	return a;
}

hsv3** createCanvasHSV(int width, int height);
rgb3** createCanvasRGB(int width, int height);
bw1** createCanvasBW(int width, int height);

rgb3** EasyBMPtoRGB(BMP image);

hsv3** convertRGBtoHSV(rgb3** imageRGB, int width, int height);
rgb3** convertHSVtoRGB(hsv3** imageHSV, int width, int height);

#endif /* UTILS_H_ */