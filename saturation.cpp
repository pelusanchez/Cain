#include <iostream>
#include "EasyBMP.h"

int main(){
	std::cout<<"Started!...\n"<<std::endl;

	BMP imageTest;
	imageTest.ReadFromFile("test.bmp");

	int width = 100;
	int height = 100;
	
	float aR, aG, aB;	//Absolute red/green/blue
	float pR, pG, pB;	//Percent red, green, blue

	aR = (float)imageTest(0,0)->Red/255.0;
	aG = (float)imageTest(0,0)->Green/255.0;
	aB = (float)imageTest(0,0)->Blue/255.0;

	std::cout<<"Red: "<<aR<<", Green: "<<aG<<", Blue: "<<aB<<std::endl;

	//Calculate the maximun
	float maximun = aR;
	if(aG>maximun){maximun = aG;}
	if(aB>maximun){maximun = aB;}

	float minimun = aR;
	if(aG<minimun){minimun = aG;}
	if(aB<minimun){minimun = aB;}
	
	std::cout<<"Proportions:"<<std::endl;
	
	pR = aR/maximun;
	pG = aG/maximun;
	pB = aB/maximun;
	
	std::cout<<"Red: "<<pR<<", Green: "<<pG<<", Blue: "<<pB<<std::endl;
	std::cout<<"Disminuir: "<<std::endl;

	std::cout<<"Current saturation [0-1]: "<<(minimun/maximun)<<std::endl;

	float D;

	std::cin>>D;
	std::cout<<"Saturation [-100-100]: "<<D<<std::endl;


	maximun*=D;
	pR*=maximun;
	pG*=maximun;
	pB*=maximun;

	std::cout<<"[2]Proportions:"<<std::endl;
	std::cout<<"Red: "<<pR<<", Green: "<<pG<<", Blue: "<<pB<<std::endl;

	imageTest(0,0)->Red = (int)(pR*255);
	imageTest(0,0)->Green = (int)(pG*255);
	imageTest(0,0)->Blue = (int)(pB*255);
	imageTest.WriteToFile("copied.bmp");
}