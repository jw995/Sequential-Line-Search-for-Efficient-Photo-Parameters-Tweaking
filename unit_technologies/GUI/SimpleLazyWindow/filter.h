#ifndef FILTER_IS_INCLUDED
#define FILTER_IS_INCLUDED

#include "fslazywindow.h"
class Filter
{
public:
    Filter();

    void CleanUp(void);

    void CurveFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double w);
    void ContrastFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double contrast);
    void BrightnessFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double brightness);
    void SaturationFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double saturation);
    void convertRGBToHSL(unsigned char srcR,unsigned char srcG,unsigned char srcB, int *targetH, int *targetS, int *targetL);
    void convertHSLToRGB(int srcH, int srcS, int srcL, unsigned char *targetR, unsigned char *targetG, unsigned char *targetB);
    void ColorBalanceFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],int redLevel, int greenLevel, int blueLevel);
    void CombinedFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double contrast, double brightness, double saturation, int redLevel, int greenLevel, int blueLevel);
};
#endif