#include <iostream>
#include <math.h>
#include "EasyBMP.h"


void test(float *histogram){
	float x = histogram[0];
	std::cout<<x<<std::endl;
	delete[] histogram;
}


int main(int argc, char** argv){
	BMP A;
	A.ReadFromFile(argv[1]);

	int cas = int(*argv[2])-'0';
	std::cout<<"Cas = "<<cas<<std::endl;


	int width = A.TellWidth();
	int height = A.TellHeight();

	int i = 0;
	int *_i = new int[256];

	for(int i = 0; i<256; i++){
		if(i<=128){
			_i[i] = (int)(128*pow((float)i/128.0,(float)cas/2.0));
		}else{
			_i[i] = 255-_i[255-i];
		}
		std::cout<<"["<<i<<"] = "<<_i[i]<<std::endl;
	}

	int max = 0;
	float R, G, B;
	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			
			max = A(i,j)->Red;
			
			if(A(i,j)->Green > max){
				max = A(i,j)->Green;
			}

			if(A(i,j)->Blue > max){
				max = A(i,j)->Blue;
			}

			if(max == 0){ continue;}
			R = A(i,j)->Red;
			G = A(i,j)->Green;
			B = A(i,j)->Blue;

			R *= (float)_i[max]/(float)max;
			G *= (float)_i[max]/(float)max;
			B *= (float)_i[max]/(float)max;
			if(R>255.0 || G>255.0 || B> 255.0){
				std::cout<<"Error clipping with :"<<std::endl;
				std::cout<<"\t R = "<<R<<std::endl;
				std::cout<<"\t G = "<<G<<std::endl;
				std::cout<<"\t B = "<<B<<std::endl;
				std::cout<<"\t max = "<<max<<std::endl;
				std::cout<<"\t _i[max] = "<<_i[max]<<std::endl;

			}
			
			A(i,j)->Red   = int(R);
			A(i,j)->Green = int(G);
			A(i,j)->Blue  = int(B);
			
		}
	}

	A.WriteToFile("out.bmp");
}