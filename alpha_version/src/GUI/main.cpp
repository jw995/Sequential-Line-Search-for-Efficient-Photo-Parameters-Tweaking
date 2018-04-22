/* ////////////////////////////////////////////////////////////

File Name: main.cpp
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fslazywindow.h>
#include "guislidebar.h"
#include "guitoolbar.h"
#include "filter.h"
#include <yspng.h>
#include <yspngenc.h>
#include <fssimplefiledialog.h>
#include <ysglfontdata.h>


class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
    bool needRedraw;
    int wid, hei;
    int lb, mb, rb, mx, my;
    GuiSlideBar bar;
    GUIToolbar toolbar;
    FsSimpleFileDialog fileDialog;
    YsRawPngDecoder png;
    YsRawPngDecoder pngTgt;
    Filter filter;
    double brightness;
    double contrast;
    double saturation;
    int r, g, b;
    
public:
    FsLazyWindowApplication();
    virtual void BeforeEverything(int argc,char *argv[]);
    virtual void GetOpenWindowOption(FsOpenWindowOption &OPT) const;
    virtual void Initialize(int argc,char *argv[]);
    virtual void Interval(void);
    virtual void BeforeTerminate(void);
    virtual void Draw(void);
    virtual bool UserWantToCloseProgram(void);
    virtual bool MustTerminate(void) const;
    virtual long long int GetMinimumSleepPerInterval(void) const;
    virtual bool NeedRedraw(void) const;
    
    void FileSelected(FsSimpleFileDialog *fdlg,int returnCode);
};

FsLazyWindowApplication::FsLazyWindowApplication()
{
    needRedraw=false;
}

/* virtual */ void FsLazyWindowApplication::BeforeEverything(int argc,char *argv[])
{
    toolbar.addButton((char *)" Open ");
    toolbar.addButton((char *)"Finish");
    toolbar.addButton((char *)"Export");
    brightness = 0.0;
    contrast = 0.0;
    saturation = 255.0;
    r = 255;
    g = 255;
    b = 255;
}
/* virtual */ void FsLazyWindowApplication::GetOpenWindowOption(FsOpenWindowOption &opt) const
{
    opt.x0=16;
    opt.y0=16;
    opt.wid=1200;
    opt.hei=800;
}
/* virtual */ void FsLazyWindowApplication::Initialize(int argc,char *argv[])
{
    bar.SetLength(600);
    bar.SetHeight(15);
    glShadeModel(GL_SMOOTH);
}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
    FsGetWindowSize(wid, hei);

    auto key=FsInkey();
    if(FSKEY_ESC==key)
    {
        SetMustTerminate(true);
    }
    
    //Filter Testing
    if (FSKEY_UP==key) {
        brightness += 1;
        filter.BrightnessFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, brightness);
    }
    if (FSKEY_DOWN==key) {
        brightness -= 1;
        filter.BrightnessFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, brightness);
    }
    if (FSKEY_RIGHT==key) {
        contrast += 1;
        filter.BrightnessFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, contrast);
    }
    if (FSKEY_LEFT==key) {
        contrast -= 1;
        filter.BrightnessFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, contrast);
    }
    if (FSKEY_D==key) {
        saturation += 1.0;
        if (saturation>255.0) saturation = 255.0;
        if (saturation<0.0) saturation = 0.0;
        filter.SaturationFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, saturation);
    }
    if (FSKEY_A==key) {
        saturation -= 1;
        if (saturation>255.0) saturation = 255.0;
        if (saturation<0.0) saturation = 0.0;
        filter.SaturationFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, saturation);
    }
    if (FSKEY_R==key) {
        r += 1;
        if (r>255.0) r = 255.0;
        if (r<0.0) r = 0.0;
        filter.ColorBalanceFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, r, g, b);
    }
    if (FSKEY_G==key) {
        g += 1;
        if (g>255.0) g = 255.0;
        if (g<0.0) g = 0.0;
        filter.ColorBalanceFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, r, g, b);
    }
    if (FSKEY_B==key) {
        b += 1;
        if (b>255.0) b = 255.0;
        if (b<0.0) b = 0.0;
        filter.ColorBalanceFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, r, g, b);
    }
    if (FSKEY_T==key) {
        r -= 1;
        if (r>255.0) r = 255.0;
        if (r<0.0) r = 0.0;
        filter.ColorBalanceFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, r, g, b);
    }
    if (FSKEY_H==key) {
        g -= 1;
        if (g>255.0) g = 255.0;
        if (g<0.0) g = 0.0;
        filter.ColorBalanceFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, r, g, b);
    }
    if (FSKEY_N==key) {
        b -= 1;
        if (b>255.0) b = 255.0;
        if (b<0.0) b = 0.0;
        filter.ColorBalanceFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, r, g, b);
    }
    if (FSKEY_C==key) {
        brightness += 1;
        saturation += 1;
        contrast += 1;
        r += 1;
        g += 1;
        b += 1;
        if (saturation>255.0) saturation = 255.0;
        if (saturation<0.0) saturation = 0.0;
        if (r>255.0) r = 255.0;
        if (r<0.0) r = 0.0;
        if (g>255.0) g = 255.0;
        if (g<0.0) g = 0.0;
        if (b>255.0) b = 255.0;
        if (b<0.0) b = 0.0;
        filter.CombinedFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, contrast, brightness, saturation, r, g, b);
    }
    if (FSKEY_X==key) {
        brightness -= 1;
        saturation -= 1;
        contrast -= 1;
        r -= 1;
        g -= 1;
        b -= 1;
        if (saturation>255.0) saturation = 255.0;
        if (saturation<0.0) saturation = 0.0;
        if (r>255.0) r = 255.0;
        if (r<0.0) r = 0.0;
        if (g>255.0) g = 255.0;
        if (g<0.0) g = 0.0;
        if (b>255.0) b = 255.0;
        if (b<0.0) b = 0.0;
        filter.CombinedFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, contrast, brightness, saturation, r, g, b);
    }
    //////////////////////////////////////

    FsGetMouseState(lb, mb, rb, mx, my);
    if (lb && bar.IsInside(mx, my))
    {
        bar.SetDragging(true);
    }
    if (bar.GetDragging() && !lb)
    {
        bar.SetDragging(false);
    }
    if (bar.GetDragging())
    {
        bar.Move(mx, my);
    }
    
    toolbar.hover(mx, my);
    if (toolbar.getButton(0).isClicked(mx, my, lb)) {
        fileDialog.Initialize();
        fileDialog.fileExtensionArray.clear();
        fileDialog.fileExtensionArray.push_back(L".png");
//        fileDialog.fileExtensionArray.push_back(L".jpeg");
//        fileDialog.fileExtensionArray.push_back(L".jpg");
        fileDialog.BindCloseModalCallBack(&FsLazyWindowApplication::FileSelected,this);
        fileDialog.Show();
    }
    
    needRedraw=true;
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glViewport(0,0,wid,hei);
    // Left-bottom
    glRasterPos2i(20,png.hei + 60);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
    
    glRasterPos2i(wid - 20 - pngTgt.wid,pngTgt.hei + 60);
    glDrawPixels(pngTgt.wid,pngTgt.hei,GL_RGBA,GL_UNSIGNED_BYTE,pngTgt.rgba);
    
    bar.Show();
    toolbar.Draw();
    for (auto btn: toolbar.GetButtons()) {
        btn.draw();
    }
    
    needRedraw=false;
    FsSwapBuffers();
}
/* virtual */ bool FsLazyWindowApplication::UserWantToCloseProgram(void)
{
    return true; // Returning true will just close the program.
}
/* virtual */ bool FsLazyWindowApplication::MustTerminate(void) const
{
    return FsLazyWindowApplicationBase::MustTerminate();
}
/* virtual */ long long int FsLazyWindowApplication::GetMinimumSleepPerInterval(void) const
{
    return 10;
}
/* virtual */ void FsLazyWindowApplication::BeforeTerminate(void)
{
}
/* virtual */ bool FsLazyWindowApplication::NeedRedraw(void) const
{
    return needRedraw;
}

void FsLazyWindowApplication::FileSelected(FsSimpleFileDialog *fileDialog,int returnCode)
{
	if(0!=returnCode && 0<fileDialog->selectedFileArray.size())
	{
		auto wStr=fileDialog->selectedFileArray[0];
		auto utf8=wStr.GetUTF8String();
        
        char *fn;
        fn = (char *)utf8.c_str();
        
        if(YSOK==png.Decode(fn))
        {
            png.Flip();
            pngTgt.Decode(fn);
            pngTgt.Flip();
            printf("%dx%d\n",png.wid,png.hei);
        }
        else
        {
            printf("Cannot open file.\n");
        }
	}
}


static FsLazyWindowApplication *appPtr=nullptr;

/* static */ FsLazyWindowApplicationBase *FsLazyWindowApplicationBase::GetApplication(void)
{
    if(nullptr==appPtr)
    {
        appPtr=new FsLazyWindowApplication;
    }
    return appPtr;
}

