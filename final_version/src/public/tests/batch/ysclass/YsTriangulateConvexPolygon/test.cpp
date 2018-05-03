/* ////////////////////////////////////////////////////////////

File Name: test.cpp
Copyright (c) 2017 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include <ysclass.h>

template <class Vec>
YSRESULT Test(const YsConstArrayMask <Vec> &plg)
{
	YSRESULT res=YSOK;

	auto triIdx=YsTriangulateConvexPolygon(plg);
	for(YSSIZE_T idx=0; idx<triIdx.size(); idx+=3)
	{
		printf("%d %d %d\n",triIdx[idx],triIdx[idx+1],triIdx[idx+2]);
	}


	if(0!=triIdx.size()%3)
	{
		fprintf(stderr,"Number of triangle vertex indices must be 3*N\n");
		res=YSERR;
	}


	double areaBefore=YsGetPolygonArea(plg);
	double areaAfter=0.0;
	for(YSSIZE_T idx=0; idx<=triIdx.size()-3; idx+=3)
	{
		Vec tri[3]=
		{
			plg[triIdx[idx]],
			plg[triIdx[idx+1]],
			plg[triIdx[idx+2]],
		};
		areaAfter+=YsGetPolygonArea(3,tri);
	}
	fprintf(stderr,"Original Area %lf Area of All Triangles %lf\n",areaBefore,areaAfter);
	if(YSTRUE!=YsEqual(areaBefore,areaAfter))
	{
		fprintf(stderr,"Total areas do not match\n");
		res=YSERR;
	}


	YsShell tst;
	YsShellSearchTable tstSearch;
	tst.AttachSearchTable(&tstSearch);
	YsArray <YsShell::VertexHandle> plVtHd;
	for(auto v : plg)
	{
		YsVec3 pos(v.x(),v.y(),0.0);
		plVtHd.push_back(tst.AddVertexH(pos));
	}
	for(YSSIZE_T idx=0; idx<=triIdx.size()-3; idx+=3)
	{
		YsShell::VertexHandle tri[3]=
		{
			plVtHd[triIdx[idx]],
			plVtHd[triIdx[idx+1]],
			plVtHd[triIdx[idx+2]],
		};
		tst.AddPolygonH(3,tri);
	}
	YSSIZE_T nSingleUse=0;
	YsShellEdgeEnumHandle edHd=nullptr;
	while(YSOK==tstSearch.FindNextEdge(tst,edHd))
	{
		if(1==tstSearch.GetNumPolygonUsingEdge(tst,edHd))
		{
			++nSingleUse;
		}
	}
	fprintf(stderr,"Number of Vertices %d Number of Single-Use Edges %d\n",(int)plg.size(),(int)nSingleUse);
	if(nSingleUse!=plg.size())
	{
		fprintf(stderr,"Number of single-use-edge is different from number of vertices.\n");
		res=YSERR;
	}


	if(YSOK!=res)
	{
		fprintf(stderr,"Failed!\n");
	}
	return res;
}

int main(void)
{

	int nFail=0;

	{
		YsArray <YsVec3> plg;
		plg.Add(YsVec3::Origin());
		for(int i=0; i<50; ++i)
		{
			plg.Add(YsVec3(1,i,0));
		}
		if(YSOK!=Test<YsVec3>(plg))
		{
			++nFail;
		}
	}
	{
		YsArray <YsVec2> plg;
		plg.Add(YsVec2::Origin());
		for(int i=0; i<50; ++i)
		{
			plg.Add(YsVec2(1,i));
		}
		if(YSOK!=Test<YsVec2>(plg))
		{
			++nFail;
		}
	}

	{
		YsArray <YsVec3> plg;
		plg.Add(YsVec3::Origin());
		plg.Add(YsVec3(1.0,0.0, 0.0));
		plg.Add(YsVec3(1.0,1.0, 0.0));
		plg.Add(YsVec3(0.0,1.0, 0.0));
		if(YSOK!=Test<YsVec3>(plg))
		{
			++nFail;
		}
	}
	{
		YsArray <YsVec2> plg;
		plg.Add(YsVec2::Origin());
		plg.Add(YsVec2(1.0,0.0));
		plg.Add(YsVec2(1.0,1.0));
		plg.Add(YsVec2(0.0,1.0));
		if(YSOK!=Test<YsVec2>(plg))
		{
			++nFail;
		}
	}

	{
		YsArray <YsVec3> plg;
		plg.Add(YsVec3( 0.0000000000000000,  0.0000000000000000, 0.0));
		plg.Add(YsVec3(-2.4650187265917589,  4.2695376760656618, 0.0));
		plg.Add(YsVec3(-7.3950561797752776,  4.2695376760656627, 0.0));
		plg.Add(YsVec3(-9.8600749063670374,  0.0000000000000000, 0.0));
		plg.Add(YsVec3(-7.3950561797752803, -4.2695376760656618, 0.0));
		plg.Add(YsVec3(-2.4650187265917589, -4.2695376760656618, 0.0));
		if(YSOK!=Test<YsVec3>(plg))
		{
			++nFail;
		}
	}
	{
		YsArray <YsVec2> plg;
		plg.Add(YsVec2( 0.0000000000000000,  0.0000000000000000));
		plg.Add(YsVec2(-2.4650187265917589,  4.2695376760656618));
		plg.Add(YsVec2(-7.3950561797752776,  4.2695376760656627));
		plg.Add(YsVec2(-9.8600749063670374,  0.0000000000000000));
		plg.Add(YsVec2(-7.3950561797752803, -4.2695376760656618));
		plg.Add(YsVec2(-2.4650187265917589, -4.2695376760656618));
		if(YSOK!=Test<YsVec2>(plg))
		{
			++nFail;
		}
	}

	printf("%d failed.\n",nFail);
	if(0<nFail)
	{
		return 1;
	}
	return 0;
}
