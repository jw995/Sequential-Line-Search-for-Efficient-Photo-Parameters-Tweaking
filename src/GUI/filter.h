#ifndef FILTER_IS_INCLUDED
#define FILTER_IS_INCLUDED

class Filter
{
public:
    Filter();

    void CleanUp(void);

    void CurveFilter(int wid,int hei,unsigned char srcRgba[], unsigned char tgtRgba[],double w);
};
#endif