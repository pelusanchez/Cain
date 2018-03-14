#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <cstdlib>

#include "EasyBMP.h"



#include "color/hsv.h"		// HSV color model functions
#include "color/color.h"	// Color models conversions
#include "color/image.h"	// Image canvas class



#include "data.h"		// Global variables
#include "utils.h"		// Utilities





// Filters
#include "filter/filter_histogram.h"
#include "filter/filter_gaussian_blur.h"
#include "filter/filter_blur.h"
#include "filter/filter_transmission_map.h"
#include "filter/filter_unsharp.h"
#include "filter/filter_hipass.h"
#include "filter/filter_darkest.h"
#include "filter/filter_graytocolor.h"
#include "filter/filter_contrast_stretch_cumulative.h"
#include "filter/filter_rx_falsecolor.h"



// Macros
#include "macros/dehaze.h"
#include "macros/histogram.h"
#include "macros/contrast.h"


bool verbose = false;



/**
	Function: main

	Look for arguments, opens the images and execute the operation passed
	in the argument list.
*/
int main(int argc, char** argv){

	

	CanvasRGB **inputImages;	// Images given in the arguments
	CanvasRGB *canvas;			// Main canvas (First image)
	CanvasRGB *output;			// Output canvas
	BMP imageBMP;


	int inputImagesNumber = 0;	// Number of input images
	char* outputFilename;		// Output filename
	
	char *arg;					// For each argument
	int operation = -1; 		// Operation to do.

	
	if(argc == 1){
		std::cout<<"Type "<<argv[0]<<" --help for usage."<<std::endl;
		exit(0);
	}

	int i, j;

	// Look for -v or --verbose command line
	for(i = 1; i<argc; i++){
		arg = argv[i];
		if(strcmp(arg,"-v") == 0 || strcmp(arg,"--verbose") == 0 ){
			verbose = true;
			std::cout<<"Verbose mode."<<std::endl;
			break;
		}
	}
	


	// Command line arguments parse
	for(i = 1; i<argc; i++){

		// Current argument
		arg = argv[i];

		if(verbose){
			std::cout<<"Arg["<<i<<"] = "<<arg<<std::endl;
		}


		// Input image(s)
		if(strcmp(arg,"-i") == 0 || strcmp(arg,"--input") == 0){
			std::cout<<"-i"<<std::endl;
			if(argc>i){
				
				// Increment by 1 argument pointer (get the first image name)
				i++;
				j = 0;

				
				// Get the number of images
				while((i+inputImagesNumber)<argc && argv[j+i][0]!= '-'){
					inputImagesNumber++;
					std::cout<<"FOUND!"<<std::endl;
					j++;
				}

				// Allocate memory
				inputImages = new CanvasRGB*[inputImagesNumber];

				// Dummy variable to open each file
				j = 0;

				// Open image files
				while(j<inputImagesNumber){
					

					if(verbose){std::cout<<"[INFO] Opening file "<<argv[i]<<std::endl;}	/* VERBOSE */

					imageBMP.ReadFromFile(argv[i]);

					if(verbose){std::cout<<"[INFO] Converting to RGB space... ";}	/* VERBOSE */




					// Create the RGB canvas.
					inputImages[j] = new CanvasRGB(imageBMP);

					if(verbose){std::cout<<"[DONE]"<<std::endl;}	/* VERBOSE */
					i++;
					j++;
				}

				if(verbose){std::cout<<"[INFO] Creating the canvas"<<std::endl;}	/* VERBOSE */
				canvas = inputImages[0]; 				// The first image is always the canvas
			}else{
				std::cout<<"ERROR: Need at least a input filename."<<std::endl;
			}


		// Output image name
		}else if(strcmp(arg, "-o") == 0 || strcmp(arg,"--output") == 0){
			if(argc>i){
				// Open output image file
				i++;

				if(verbose){
					std::cout<<"[INFO] Output file :"<<argv[i]<<std::endl;
				}
				outputFilename = argv[i];

			}else{
				std::cout<<"ERROR: Need an output filename."<<std::endl;
			}
			
		/**
			Gaussian blur
		*/
		}else if(strcmp(arg, "--gaussian") == 0){

			if(verbose){std::cout<<"[INFO] Operation: Gaussian filter."<<std::endl;}
			operation = 1;
			

		}else if(strcmp(arg, "--unsharp") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: unmask filter."<<std::endl;}
			operation = 2;
			

		}else if(strcmp(arg, "--blur") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: Blur filter."<<std::endl;}
			operation = 3;
			

		}else if(strcmp(arg, "--contrast-cumulative") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: contrast stretch cumulative."<<std::endl;}
			operation = 4;
			

		}else if(strcmp(arg, "--dehaze") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: dehaze."<<std::endl;}
			operation = 5;
			

		}else if(strcmp(arg, "--transmissionmap") == 0){
			if(verbose){std::cout<<"[INFO] Operation: transmission map."<<std::endl;}
			operation = 6;

		}else if(strcmp(arg, "--rxfalsecolor") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: RX_falsecolor."<<std::endl;}
			operation = 7;
			

		}else if(strcmp(arg, "--contrast") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: contrast."<<std::endl;}
			operation = 8;
			

		}else if(strcmp(arg, "--lcontrast") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: lightness-contrast."<<std::endl;}
			operation = 9;
			

		}else if(strcmp(arg, "--hipass") == 0){
			
			if(verbose){std::cout<<"[INFO] Operation: Hi-Pass filter."<<std::endl;}
			operation = 10;
			

		}	// End arguments if


		//if(operation>0){ break; }	// Exit loop if we had the operation.

	}		// End arguments loop


	/*
		After getting the operation, the program calls the main function of
		the operation passing the arguments list. This allow to each
		operation get the parameters or argumets it needs (i.e. radius of a filter, amount...)
	 
	 
	 */
	switch(operation){

		case 1:	/* Gaussian filter */
			output = main_filter_gaussian_blur(inputImages[0], argc, argv);

		break;

		case 2: /* Unmask filter */
			output = main_filter_unsharp(inputImages[0], argc, argv);
		break;

		case 3: /* Blur filter */

		break;

		case 4: /* Contrast stretch */
			output = main_filter_contrast_stretch_cumulative(inputImages[0], argc, argv);

		break;

		case 5:
			output = main_macro_dehaze(inputImages[0], argc, argv);
		break;

		case 6:
			output = main_filter_transmission_map(inputImages[0], argc, argv);
		break;

		case 7:
			output = main_filter_rx_falsecolor(inputImages[0], argc, argv);
		break;

		case 8:
			output = main_macro_contrast(inputImages[0], argc, argv);
		break;

		case 9:
			output = main_macro_lightness_contrast(inputImages[0], argc, argv);
		break;

		case 10:
			output = main_filter_hipass(inputImages[0], argc, argv);
		break;



		default:
			output = canvas;
			std::cout<<"Operation not passed by argument..."<<std::endl;
			std::cout<<"Use --help for documentation."<<std::endl;
			std::cout<<"Use --version to print version."<<std::endl;
		break;
	}

	output->toBMP(outputFilename);


/*
	std::cout<<" "<<argv[1]<<std::endl;

	BMP image;
	image.ReadFromFile(argv[1]);



	int width = image.TellWidth();
	int height = image.TellHeight();


	rgb3** imageRGB = EasyBMPtoRGB(image);
*/
//	imageHistogramRGB(imageRGB, width, height);
	/*
	bw1** transmissionMap = filter_transmission_map(imageRGB, width, height);

	bw1** out = transmissionMap; //filter_gaussian_blurBW(transmissionMap, width, height, 5);

	hsv3** imageHSV = convertRGBtoHSV(imageRGB, width, height);
*/
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

/*
	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			image(i,j)->Red = (int)(out[i][j].V*255.0);
			image(i,j)->Green = (int)(out[i][j].V*255.0);
			image(i,j)->Blue = (int)(out[i][j].V*255.0);
		}
	}



	image.WriteToFile("test_o.bmp");
	std::cout<<"Completed!"<<std::endl;*/
} /* END MAIN */