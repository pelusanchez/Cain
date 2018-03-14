#include <iostream>
#include <math.h>

#include "EasyBMP.h"



#include "color/hsv.h"
#include "color/color.h"



#include "utils.h"





#include "filter/filter_histogram.h"


#include "filter/filter_gaussian_blur.h"
#include "filter/filter_blur.h"
#include "filter/filter_transmission_map.h"
#include "filter/filter_unsharp.h"
#include "filter/filter_hipass.h"
#include "filter/filter_darkest.h"
#include "filter/filter_graytocolor.h"

#include "macros/dehaze.h"
#include "macros/histogram.h"



int main(int argc, char** argv){

	std::cout<<"[] = "<<argv[1]<<std::endl;

	BMP image;
	image.ReadFromFile(argv[1]);



	int width = image.TellWidth();
	int height = image.TellHeight();


	rgb3** imageRGB = EasyBMPtoRGB(image);

//	imageHistogramRGB(imageRGB, width, height);
	bw1** transmissionMap = filter_transmission_map(imageRGB, width, height);

	bw1** out = transmissionMap; //filter_gaussian_blurBW(transmissionMap, width, height, 5);

	hsv3** imageHSV = convertRGBtoHSV(imageRGB, width, height);

	/*for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			image(i,j)->Red = (int)(out[i][j].R*255.0);
			image(i,j)->Green = (int)(out[i][j].G*255.0);
			image(i,j)->Blue = (int)(out[i][j].B*255.0);
		}
	}*/
	//rgb3** out = filter_graytocolor(imageBlur, width, height, GRAYTOCOLOR_RGB);

	
//	

//	hsv3** outHSV = filter_histogram_stretch(imageHSV, width, height);

//	rgb3** out = convertHSVtoRGB(outHSV, width, height);


	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			image(i,j)->Red = (int)(out[i][j].V*255.0);
			image(i,j)->Green = (int)(out[i][j].V*255.0);
			image(i,j)->Blue = (int)(out[i][j].V*255.0);
		}
	}



	image.WriteToFile("test_o.bmp");
	std::cout<<"Completed!"<<std::endl;
}