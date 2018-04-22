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
    