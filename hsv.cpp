#include <iostream>
#include <algorithm>
#ifndef COLOR_H_
#define COLOR_H_
#include "color.h"
#endif

#ifndef UTILS_H_
#define UTILS_H_
#include "utils.h"
#endif


/**
Function rgb2hsv
	Args: pixelRGB
	Returns: hsv3 pixel data
*/
hsv3 rgb2hsv(rgb3 pixelRGB){
	hsv3 pixelHSV;
	float max;
	float min;
	float _hue;

	max = max3(	pixelRGB.R, pixelRGB.G, pixelRGB.B);	// Obtain the maximun value of RGB channel
	min = min3(	pixelRGB.R, pixelRGB.G, pixelRGB.B);	// Obtain the minimun value of RGB channel

	float delta = max-min;							//Obtain the difference between maximun and minimun value

	//std::cout<<"Delta = "<<delta<<", Max = "<<max<<", Min = "<<min<<std::endl;
	pixelHSV.S = ((max == 0)? 0 : delta/max);
	pixelHSV.V = max;

	if(delta == 0){
		_hue = 0;
	}else if(max == pixelRGB.R){
		_hue = (pixelRGB.G-pixelRGB.B)/delta;
	}else if(max == pixelRGB.G){
		_hue = (pixelRGB.B-pixelRGB.R)/delta+2;
	}else if(max == pixelRGB.B){
		_hue = (pixelRGB.R-pixelRGB.G)/delta+4;
	}

	pixelHSV.H = _hue*60;
	if(pixelHSV.H <0){pixelHSV.H +=360;}
	if(pixelHSV.H >360){pixelHSV.H -=360;}
	return pixelHSV;
	
}



/**
 *	Function: hsv2rgb
 *		Args: hsv3 pixel data
 *		Returns: rgb3 pixel data
 *
 */

 
rgb3 hsv2rgb(hsv3 pixelHSV){
	rgb3 pixelRGB;
	float a, d, c;
	float r, g, b;

	//std::cout<<"[HSV2RGB]H = "<<pixelHSV.H<<", S = "<<pixelHSV.S<<", V = "<<pixelHSV.V<<std::endl;

	a = pixelHSV.V*pixelHSV.S;
	d = a*(1-fabs(fmod(pixelHSV.H/60.0, 2)-1));
	c = pixelHSV.V-a;
	//std::cout<<"a = "<<a<<", d = "<<d<<", c = "<<c<<std::endl;
	if(pixelHSV.H < 60){
		r = a;
		g = d;
		b = 0;
	}else if(pixelHSV.H < 120){
		r = d;
		g = a;
		b = 0;
	}else if(pixelHSV.H < 180){
		r = 0;
		g = a;
		b = d;
	}else if(pixelHSV.H < 240){
		r = 0;
		g = d;
		b = a;
	}else if(pixelHSV.H < 300){
		r = d;
		g = 0;
		b = a;
	}else{
		r = a;
		g = 0;
		b = d;
	}
	pixelRGB.R = r+c;
	pixelRGB.G = g+c;
	pixelRGB.B = b+c;
	return pixelRGB;
}
