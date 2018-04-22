#include "filter.h"

Filter::Filter()
{
    CleanUp();
}

void Filter::CleanUp(void) {
    
}

// void Filter::CurveFilter(int wid,int hei,unsigned char rgba[],double w) 
// {
//     for(int i=0; i<wid*hei; ++i)
// 	{
// 		auto pixPtr=rgba+i*4;

// 		for(int j=0; j<3; ++j)
// 		{
// 			double x=(double)pixPtr[j]/255.0;
// 			double y=(2.0-4.0*w)*x*x+(4.0*w-1.0)*x;
// 			int v=(int)(y*255.0);
// 			if(v<0)
// 			{
// 				pixPtr[j]=0;
// 			}
// 			else if(255<v)
// 			{
// 				pixPtr[j]=255;
// 			}
// 			else
// 			{
// 				pixPtr[j]=(unsigned char)v;
// 			}
// 		}
// 	}
// }

void Filter::CurveFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double w) 
{

    for(int i=0; i<wid*hei; ++i)
	{
		auto tgtPtr=tgtRgba+i*4;
		auto srcPtr=srcRgba+i*4;

		for(int j=0; j<3; ++j)
		{
			double x=(double)srcPtr[j]/255.0;
			double y=(2.0-4.0*w)*x*x+(4.0*w-1.0)*x;
			int v=(int)(y*255.0);
			if(v<0)
			{
				tgtPtr[j]=0;
			}
			else if(255<v)
			{
				tgtPtr[j]=255;
			}
			else
			{
				tgtPtr[j]=(unsigned char)v;
			}
		}
	}
}

void Filter::ContrastFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double newContrast) {
    double contrast;
    unsigned char r, g, b;
    double pixelR, pixelG, pixelB;
    for (int y = 0; y < hei; y++) {
        for (int x = 0; x < wid; x++) {
            r = srcRgba[(y * wid + x) * 4 + 0];
            g = srcRgba[(y * wid + x) * 4 + 1];
            b = srcRgba[(y * wid + x) * 4 + 2];
            
            contrast = (100.0 + newContrast)/100.0;
            contrast *= contrast;
            
            pixelR = r/255.0;
            pixelR -= 0.5;
            pixelR *= contrast;
            pixelR += 0.5;
            pixelR *= 255;
            if (pixelR > 255) pixelR = 255;
            if (pixelR < 0) pixelR = 0;
            tgtRgba[(y * wid + x) * 4 + 0] = pixelR;
            
            pixelG = r/255.0;
            pixelG -= 0.5;
            pixelG *= contrast;
            pixelG += 0.5;
            pixelG *= 255;
            if (pixelG > 255) pixelG = 255;
            if (pixelG < 0) pixelG = 0;
            tgtRgba[(y * wid + x) * 4 + 1] = pixelG;
            
            pixelB = r/255.0;
            pixelB -= 0.5;
            pixelB *= contrast;
            pixelB += 0.5;
            pixelB *= 255;
            if (pixelB > 255) pixelB = 255;
            if (pixelB < 0) pixelB = 0;
            tgtRgba[(y * wid + x) * 4 + 2] = pixelB;
        }
    }
}

void Filter::BrightnessFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double brightness) {
    int total = wid * hei * 4;
    
    for (int i = 0; i < total; i++) {
        int newPixel;
        if (i % 4 != 3) {
            newPixel = srcRgba[i] + brightness;
            if (newPixel > 255) newPixel = 255;
            if (newPixel < 0) newPixel = 0;
            tgtRgba[i] = newPixel;
        }
    }
}

void Filter::SaturationFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double saturation) {
    for (int y = 0; y < hei; y++) {
        for (int x = 0; x < wid; x++) {
            unsigned char r,g,b;
            int h,s,l;
            r = srcRgba[(y * wid + x) * 4 + 0];
            g = srcRgba[(y * wid + x) * 4 + 1];
            b = srcRgba[(y * wid + x) * 4 + 2];
            
            convertRGBToHSL(r,g,b,&h,&s,&l);
            if (saturation >= 255.0) saturation = 255.0;
            if (saturation <= 0.0) saturation = 0.0;
            s = int(saturation*s/255.0);
            
            convertHSLToRGB(h,s,l,&r,&g,&b);
                     
            tgtRgba[(y * wid + x) * 4 + 0] = r;
            tgtRgba[(y * wid + x) * 4 + 1] = g;
            tgtRgba[(y * wid + x) * 4 + 2] = b;
        }
    }
}

void Filter::convertRGBToHSL(unsigned char srcR,unsigned char srcG,unsigned char srcB,
	int *targetH, int *targetS, int *targetL) {
	float r, g, b, h, s, l;
	r = srcR / 255.0;
	g = srcG / 255.0;
	b = srcB / 255.0;

	float maxColor = r;
	float minColor = r;
    if (g > maxColor) maxColor = g;
    if (b > maxColor) maxColor = b;
    if (g < minColor) minColor = g;
    if (b < minColor) minColor = b;
	
	if((r == g)&&(g == b)) {
		h = 0.0;
		s = 0.0;
		l = r;
	} else {
		float d = maxColor - minColor;
		l = (minColor + maxColor) / 2;
		if(l < 0.5) s = d / (maxColor + minColor);
		else s = d / (2.0 - maxColor - minColor);
		if(r == maxColor) h = (g - b) / (maxColor - minColor);
		else if(g == maxColor) h = 2.0 + (b - r) / (maxColor - minColor);
		else h = 4.0 + (r - g) / (maxColor - minColor);
		h /= 6;
		if(h < 0) h ++;
	}

	*targetH = int(h * 360.0);
	*targetS = int(s * 255.0);
	*targetL = int(l * 255.0);
}

void Filter::convertHSLToRGB(int srcH, int srcS, int srcL, 
	unsigned char *targetR, unsigned char *targetG, unsigned char *targetB) {
	float r, g, b, h, s, l;
	float temp1, temp2, tempr, tempg, tempb;
	h = (srcH % 260) / 360.0;
	s = srcS / 256.0;
	l = srcL / 256.0;

	if(s == 0){
		r = l;
		g = l;
		b = l;
	}

	else {
		if(l < 0.5) temp2 = l * (1 + s);
		else
		temp2 = (l + s) - (l * s);
		temp1 = 2 * l - temp2;
 
		tempr = h + 1.0 / 3.0;
		if(tempr > 1) tempr--;
		tempg = h;
		tempb = h - 1.0 / 3.0;
		if(tempb < 0) tempb++;
 
		//Red
		if(tempr < 1.0 / 6.0) r = temp1 + (temp2 - temp1) * 6.0 * tempr;
		else if(tempr < 0.5) r = temp2;
		else if(tempr < 2.0 / 3.0) r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
		else r = temp1;
 
		//Green
		if(tempg < 1.0 / 6.0) g = temp1 + (temp2 - temp1) * 6.0 * tempg;
		else if(tempg < 0.5) g = temp2;
		else if(tempg < 2.0 / 3.0) g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
		else g = temp1;
 
		//Blue
		if(tempb < 1.0 / 6.0) b = temp1 + (temp2 - temp1) * 6.0 * tempb;
		else if(tempb < 0.5) b = temp2;
		else if(tempb < 2.0 / 3.0) b = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
		else b = temp1;
	}
    *targetR = int(r * 255.0);
    if (int(r * 255.0) > 255) *targetR = 255; 
    if (int(r * 255.0) < 0) *targetR = 0;
	*targetG = int(g * 255.0);
    if (int(g * 255.0) > 255) *targetG = 255; 
    if (int(g * 255.0) < 0) *targetG = 0;
	*targetB = int(b * 255.0);
    if (int(b * 255.0) > 255) *targetB = 255; 
    if (int(b * 255.0) < 0) *targetB = 0;
}

void Filter::ColorBalanceFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],int redLevel, int greenLevel, int blueLevel) {
    float blue, green, red;
    
    float redLevelFloat = redLevel;
    float greenLevelFloat = greenLevel;
    float blueLevelFloat = blueLevel;
    
    for (int i = 0; i+4 < wid*hei*4; i+=4) {
        blue = blueLevelFloat/255.0f * (float )srcRgba[i+2]; 
        green = greenLevelFloat/255.0f * (float)srcRgba[i + 1]; 
        red = redLevelFloat/255.0f * (float)srcRgba[i]; 
  
        if (blue > 255) {blue = 255;}
        else if (blue < 0) {blue = 0;}
  
        if (green > 255) {green = 255;}
        else if (green < 0) {green = 0;}
  
        if (red > 255) {red = 255;}
        else if (red < 0) {red = 0;}
                  
        tgtRgba[i + 2] = (unsigned char)blue; 
        tgtRgba[i + 1] = (unsigned char)green; 
        tgtRgba[i] = (unsigned char)red; 
    }
}

void Filter::CombinedFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgbaIn[],double newContrast, double brightness, double saturation, int redLevel, int greenLevel, int blueLevel) {
    float blue, green, red;
    
    float redLevelFloat = redLevel;
    float greenLevelFloat = greenLevel;
    float blueLevelFloat = blueLevel;
    
    double contrast;
    unsigned char r, g, b;
    double pixelR, pixelG, pixelB;
    
    double tgtRgba[wid*hei*4];
    for (int i = 0; i < wid*hei*4; i++) {
        tgtRgba[i] = (double)tgtRgbaIn[i];
    }
    
    for (int y = 0; y < hei; y++) {
        for (int x = 0; x < wid; x++) {
            // Initilize
            tgtRgba[(y * wid + x) * 4 + 0] = 0;
            tgtRgba[(y * wid + x) * 4 + 1] = 0;
            tgtRgba[(y * wid + x) * 4 + 2] = 0;
            
            // Color Balance
            blue = blueLevelFloat/255.0f * (float )srcRgba[(y * wid + x) * 4 + 2]; 
            green = greenLevelFloat/255.0f * (float)srcRgba[(y * wid + x) * 4 + 1]; 
            red = redLevelFloat/255.0f * (float)srcRgba[(y * wid + x) * 4]; 

            if (blue > 255) {blue = 255;}
            else if (blue < 0) {blue = 0;}

            if (green > 255) {green = 255;}
            else if (green < 0) {green = 0;}

            if (red > 255) {red = 255;}
            else if (red < 0) {red = 0;}

            tgtRgba[(y * wid + x) * 4 + 2] += blue/4; 
            tgtRgba[(y * wid + x) * 4 + 1] += green/4; 
            tgtRgba[(y * wid + x) * 4] += red/4;
            
            //  Brightness
            tgtRgba[(y * wid + x) * 4 + 2] += (srcRgba[(y * wid + x) * 4+2] + brightness)/4; 
            tgtRgba[(y * wid + x) * 4 + 1] += (srcRgba[(y * wid + x) * 4+1] + brightness)/4; 
            tgtRgba[(y * wid + x) * 4] += (srcRgba[(y * wid + x) * 4] + brightness)/4;
            
            // Contrast
            r = srcRgba[(y * wid + x) * 4 + 0];
            g = srcRgba[(y * wid + x) * 4 + 1];
            b = srcRgba[(y * wid + x) * 4 + 2];
            
            contrast = (100.0 + newContrast)/100.0;
            contrast *= contrast;
            
            pixelR = r/255.0;
            pixelR -= 0.5;
            pixelR *= contrast;
            pixelR += 0.5;
            pixelR *= 255;
            if (pixelR > 255) pixelR = 255;
            if (pixelR < 0) pixelR = 0;
            tgtRgba[(y * wid + x) * 4 + 0] += pixelR/4;
            
            pixelG = r/255.0;
            pixelG -= 0.5;
            pixelG *= contrast;
            pixelG += 0.5;
            pixelG *= 255;
            if (pixelG > 255) pixelG = 255;
            if (pixelG < 0) pixelG = 0;
            tgtRgba[(y * wid + x) * 4 + 1] += pixelG/4;
            
            pixelB = r/255.0;
            pixelB -= 0.5;
            pixelB *= contrast;
            pixelB += 0.5;
            pixelB *= 255;
            if (pixelB > 255) pixelB = 255;
            if (pixelB < 0) pixelB = 0;
            tgtRgba[(y * wid + x) * 4 + 2] += pixelB/4;
            
            // Saturation
            int h,s,l;
            r = srcRgba[(y * wid + x) * 4 + 0];
            g = srcRgba[(y * wid + x) * 4 + 1];
            b = srcRgba[(y * wid + x) * 4 + 2];
            
            convertRGBToHSL(r,g,b,&h,&s,&l);
            s = int(saturation*s/255.0);
            convertHSLToRGB(h,s,l,&r,&g,&b);
                     
            tgtRgba[(y * wid + x) * 4 + 0] += r/4;
            tgtRgba[(y * wid + x) * 4 + 1] += g/4;
            tgtRgba[(y * wid + x) * 4 + 2] += b/4;
            
            //Average
//            tgtRgba[(y * wid + x) * 4 + 0] /= 4;
            if (tgtRgba[(y * wid + x) * 4 + 0] > 255) tgtRgba[(y * wid + x) * 4 + 0] = 255;
            if (tgtRgba[(y * wid + x) * 4 + 0] < 0) tgtRgba[(y * wid + x) * 4 + 0] = 0;
//            tgtRgba[(y * wid + x) * 4 + 1] /= 4;
            if (tgtRgba[(y * wid + x) * 4 + 1] > 255) tgtRgba[(y * wid + x) * 4 + 1] = 255;
            if (tgtRgba[(y * wid + x) * 4 + 1] < 0) tgtRgba[(y * wid + x) * 4 + 1] = 0;
//            tgtRgba[(y * wid + x) * 4 + 2] /= 4;
            if (tgtRgba[(y * wid + x) * 4 + 2] > 255) tgtRgba[(y * wid + x) * 4 + 2] = 255;
            if (tgtRgba[(y * wid + x) * 4 + 2] < 0) tgtRgba[(y * wid + x) * 4 + 2] = 0;
        }
    }
    for (int i = 0; i < wid*hei*4; i++) {
        tgtRgbaIn[i] = (unsigned char)tgtRgba[i];
    }
}