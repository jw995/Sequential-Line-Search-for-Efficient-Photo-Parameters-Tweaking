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
#include <algorithm>

#include <fslazywindow.h>
#include <yspng.h>
#include <yspngenc.h>
#include <fssimplefiledialog.h>
#include <ysglfontdata.h>

#include <Eigen/Dense>

#include "guislidebar.h"
#include "guitoolbar.h"
#include "filter.h"

#include "core.h"
#include "preferenceregressor.h"


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
    YsRawPngEncoder encoder;
    ToolbarButton *nextButton = new ToolbarButton(1000, 700, (char *)" Next ");;

    Eigen::VectorXd start;
    Eigen::VectorXd startlength;
    Eigen::VectorXd userChoosed;
    Eigen::VectorXd barStart;
    Eigen::VectorXd barEnd;


    std::vector<Eigen::VectorXd> barPos;
    Filter filter;
    Core core;


    int next;
    int currentTime;
    int first;
    int nextClicked;
    int barMoved;
    int doFilter;
    int firstEver;

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
    void FileExported(FsSimpleFileDialog *fdlg,int returnCode);
};

FsLazyWindowApplication::FsLazyWindowApplication()
{
    needRedraw=false;
    start.resize(6);
    startlength.resize(6);
    userChoosed.resize(6);
    barStart.resize(6);
    barEnd.resize(6);

}

/* virtual */ void FsLazyWindowApplication::BeforeEverything(int argc,char *argv[])
{
    toolbar.addButton((char *)" Open ");
    toolbar.addButton((char *)"Finish");
    toolbar.addButton((char *)"Export");
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

    next = 0;
    first = 1;
    nextClicked = 0;
    barMoved = 0;
    doFilter = 0;
    firstEver = 1;
    currentTime = static_cast <unsigned int> (time(NULL));
    srand(currentTime);

    startlength(0) = (double) rand()/RAND_MAX;
    startlength(1) = (double) rand()/RAND_MAX;
    startlength(2) = (double) rand()/RAND_MAX;
    startlength(3) = (double) rand()/RAND_MAX;
    startlength(4) = (double) rand()/RAND_MAX;
    startlength(5) = (double) rand()/RAND_MAX;

    start(0) = 0-startlength(0);
    start(1) = 0-startlength(1);
    start(2) = 1-startlength(2);
    start(3) = 1-startlength(3);
    start(4) = 1-startlength(4);
    start(5) = 1-startlength(5);

    barPos.push_back(start);

    printf("%f, %f, %f, %f, %f, %f\n", start(0), start(1), start(2), start(3), start(4), start(5));

    start(0) = 0+startlength(0);
    start(1) = 0+startlength(1);
    start(2) = 1+startlength(2);
    start(3) = 1+startlength(3);
    start(4) = 1+startlength(4);
    start(5) = 1+startlength(5);

    barPos.push_back(start);

    printf("%f, %f, %f, %f, %f, %f\n", start(0), start(1), start(2), start(3), start(4), start(5));

}
/* virtual */ void FsLazyWindowApplication::Interval(void)
{
    FsGetWindowSize(wid, hei);

    auto key=FsInkey();
    if(FSKEY_ESC==key)
    {
        SetMustTerminate(true);
    }

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
        fileDialog.BindCloseModalCallBack(&FsLazyWindowApplication::FileSelected,this);
        fileDialog.Show();
    }
    if (toolbar.getButton(2).isClicked(mx, my, lb)) {
        fileDialog.Initialize();
        fileDialog.mode = FsSimpleFileDialog::MODE_SAVE;
        fileDialog.fileExtensionArray.clear();
        fileDialog.fileExtensionArray.push_back(L".png");
        fileDialog.BindCloseModalCallBack(&FsLazyWindowApplication::FileExported,this);
        fileDialog.Show();
    }
    
    if (nextButton->isClicked(mx, my, lb) && nextClicked == 0) {
        next = 1;
        nextClicked = 1;
    }

    if(!nextButton->isClicked(mx, my, lb)){
        nextClicked = 0;
        next = 0;
    }


    if(bar.GetDragging()){
        doFilter = 1;
    }

    if(doFilter && !bar.GetDragging()){

        double ratio = bar.GetPercent();

        if(firstEver){
            next = 1;
        }

        core.updateSliderEnds(barStart, barEnd);

        userChoosed(0) = barStart(0) + (barEnd(0)-barStart(0)) * ratio;
        userChoosed(1) = barStart(1) + (barEnd(1)-barStart(1)) * ratio;
        userChoosed(2) = barStart(2) + (barEnd(2)-barStart(2)) * ratio;
        userChoosed(3) = barStart(3) + (barEnd(3)-barStart(3)) * ratio;
        userChoosed(4) = barStart(4) + (barEnd(4)-barStart(4)) * ratio;
        userChoosed(5) = barStart(5) + (barEnd(5)-barStart(5)) * ratio;

        filter.CombinedFilter(png.wid, png.hei, png.rgba, pngTgt.rgba, userChoosed(0), userChoosed(1), userChoosed(2)*255, userChoosed(3)*255, userChoosed(4)*255, userChoosed(5)*255);

        doFilter = 0;
    }


    if(next){
        core.proceedOptimization(bar.GetPercent());
        if(firstEver){
            firstEver = 0;
            next = 0;
            first = 0;
        }
        else{
            bar.percent = 0.2;
            next = 0;
            first = 0;
        }
    }
    
    needRedraw=true;
}
/* virtual */ void FsLazyWindowApplication::Draw(void)
{
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glViewport(0,0,wid,hei);
    // Left-bottom
    glRasterPos2i(20,png.hei + 60);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,pngTgt.rgba);
    glRasterPos2i(wid - 20 -png.wid, png.hei + 60);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);

    bar.Show();
    toolbar.Draw();
    for (auto btn: toolbar.GetButtons()) {
        btn.draw();
    }
    nextButton->draw();
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

void FsLazyWindowApplication::FileExported(FsSimpleFileDialog *fileDialog, int returnCode)
{
    if(0!=returnCode && 0<fileDialog->selectedFileArray.size())
    {
        auto wStr=fileDialog->selectedFileArray[0];
        auto utf8=wStr.GetUTF8String();
        
        char *fn;
        fn = (char *)utf8.c_str();
        pngTgt.Flip();
        if(YSOK==encoder.EncodeToFile(fn, pngTgt.wid, pngTgt.hei, 8, 6, pngTgt.rgba))
        {
            printf("Saved successfully!\n");
        }
        else
        {
            printf("Cannot open file.\n");
        }
        pngTgt.Flip();
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

