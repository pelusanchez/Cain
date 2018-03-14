/*
	rgb3** out = filter_blur(imageRGB, width, height, 5);

	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			imageRGB[i][j].R -= 0.3*out[i][j].R;
			imageRGB[i][j].G -= 0.3*out[i][j].G;
			imageRGB[i][j].B -= 0.3*out[i][j].B;
			if(imageRGB[i][j].R<0){imageRGB[i][j].R = 0;}
			if(imageRGB[i][j].G<0){imageRGB[i][j].G = 0;}
			if(imageRGB[i][j].B<0){imageRGB[i][j].B = 0;}
			pixelHSV.H = imageHSV[i][j].H;
			pixelHSV.S = imageHSV[i][j].S;
			pixelHSV.V = imageRGB[i][j].R;
			pixelRGB = hsv2rgb(pixelHSV);
			imageRGB[i][j].R = pixelRGB.R;
			imageRGB[i][j].G = pixelRGB.G;
			imageRGB[i][j].B = pixelRGB.B;
			
		}
	}*/

	/*

	rgb3 pixelRGB;
	hsv3 pixelHSV;
	float min, back;

	for(int i = 0; i<width; i++){
		for(int j = 0; j<height; j++){
			pixelRGB.R = image(i,j)->Red/255.0;
			pixelRGB.G = image(i,j)->Green/255.0;
			pixelRGB.B = image(i,j)->Blue/255.0;
			pixelHSV = rgb2hsv(pixelRGB);
			
			min = image(i,j)->Red;
			if(image(i,j)->Green < min){min = image(i,j)->Green;}
			if(image(i,j)->Blue < min){min = image(i,j)->Blue;}

			image(i,j)->Red = (int)((1.0-min)*255.0);
			image(i,j)->Green = image(i,j)->Red;
			image(i,j)->Blue = image(i,j)->Red;

			/*if(pixelHSV.S<0.05 ){
				image(i,j)->Red = (int)(min*255.0);
				image(i,j)->Green = image(i,j)->Red;
				image(i,j)->Blue = image(i,j)->Red;
				
			}else{
				image(i,j)->Red = 0;
				image(i,j)->Green = 0;
				image(i,j)->Blue = 0;
				//imageA(i,j)->Red = 0;
				//imageA(i,j)->Green = 0;
				//imageA(i,j)->Blue = 0;
			}
		}
	}*/