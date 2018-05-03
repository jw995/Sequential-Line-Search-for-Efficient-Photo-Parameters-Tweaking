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
//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fslazywindow.h>
//#include <ysglfontdata.h>
#include <Eigen/Dense>
//#include <nlopt.h>

//#include "core.h"
//#include "mathutility.h"
#include "core.h"
#include "regressor_hy.h"

namespace
{
    constexpr double   theta_d1   = 0.500;
    constexpr double   theta      = 0.500;
    constexpr double   noise      = 0.001;
    constexpr double   btl_scale  = 0.010;
    constexpr double   variance   = 0.100;
    constexpr bool     use_MAP    = true;
}


class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
    bool needRedraw;
    int wid, hei;
    int lb, mb, rb, mx, my;
    Core core;
    unsigned n_trials;
    unsigned n_iterations;

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
};

FsLazyWindowApplication::FsLazyWindowApplication() {
    needRedraw=false;
}

/* virtual */
void FsLazyWindowApplication::BeforeEverything(int argc,char *argv[]) {
    srand(time(NULL));  // For rand()
}
/* virtual */
void FsLazyWindowApplication::GetOpenWindowOption(FsOpenWindowOption &opt) const {
    opt.x0=16;
    opt.y0=16;
    opt.wid=1200;
    opt.hei=800;
}
/* virtual */
void FsLazyWindowApplication::Initialize(int argc,char *argv[]) {
    //////////////////////////////////////
    core.use_MAP_hyperparameters = use_MAP;
    PreferenceRegressor::Params::getInstance().theta_d1  = theta_d1;
    PreferenceRegressor::Params::getInstance().theta     = theta;
    PreferenceRegressor::Params::getInstance().variance  = variance;
    PreferenceRegressor::Params::getInstance().theta_d2  = noise;
    PreferenceRegressor::Params::getInstance().btl_scale = btl_scale;
    core.computeRegression();
    core.updateSliderEnds();
    n_trials = 0;
    n_iterations = 0;

    //////////////////////////////////////
}
/* virtual */
void FsLazyWindowApplication::Interval(void) {
    FsGetWindowSize(wid, hei);

    auto key=FsInkey();
    if(FSKEY_ESC==key) {
        SetMustTerminate(true);
    }

    /*
     ************************************************************************
     * Manual:
     *     When user choose a position x_chosen, call
     *         core.proceedOptimization(x_chosen);
     *     where x_chosen must be between 0(sliderStart) and 1(sliderEnd)
     *
     *     To get next slider ends of slider
     *         core.updateSliderEnds(sliderStart, sliderEnd);
     *     this function will modify the value of sliderStart and sliderEnd
     ************************************************************************
     * EXAMPLE:
     *     // Before a position is chosen
     *     double x_chosen;
     *     Eigen::VectorXd sliderStart, sliderEnd;
     *
     *     // Get next slider ends
     *     core.updateSliderEnds(sliderStart, sliderEnd);
     *
     *     // Pass sliderStart and sliderEnd to GUI, and wait for return
     *
     *     // After a position is chosen
     *     core.proceedOptimization(x_chosen);
     ************************************************************************
     */

    // Test Code
    if (FSKEY_ESC == key) {
        std::cout << std::endl << "Found maximizer: " << core.x_max.transpose() << std::endl;
        std::cout << "Found maximum: " << core.evaluateObjectiveFunction(core.x_max) << std::endl << std::endl;
    }
    if (FSKEY_SPACE == key) {
        std::cout << "---- Iteration " << n_iterations + 1 << " ----" << std::endl;

        // search the best position
        double max_slider_position = 0.0;
        double max_y               = - 1e+10;
        for (double slider_position = 0.0; slider_position <= 1.0; slider_position += 0.0001) {
            const double y = core.evaluateObjectiveFunction(core.computeParametersFromSlider(slider_position));
            if (y > max_y) {
                max_y = y;
                max_slider_position = slider_position;
            }
        }
        std::cout << "x: " << core.computeParametersFromSlider(max_slider_position).transpose() << std::endl;
        std::cout << "y: " << max_y << std::endl;

        core.proceedOptimization(max_slider_position);
        n_iterations++;
    }

    needRedraw = true;
}
/* virtual */
void FsLazyWindowApplication::Draw(void) {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glViewport(0,0,wid,hei);
    //bar.Show();
    //toolbar.Draw();
    //for (auto btn: toolbar.GetButtons()) {
        //btn.draw();
    //}
    needRedraw=false;
    FsSwapBuffers();
}
/* virtual */
bool FsLazyWindowApplication::UserWantToCloseProgram(void) {
    return true; // Returning true will just close the program.
}
/* virtual */
bool FsLazyWindowApplication::MustTerminate(void) const {
    return FsLazyWindowApplicationBase::MustTerminate();
}
/* virtual */
long long int FsLazyWindowApplication::GetMinimumSleepPerInterval(void) const {
    return 10;
}
/* virtual */
void FsLazyWindowApplication::BeforeTerminate(void) {
}
/* virtual */
bool FsLazyWindowApplication::NeedRedraw(void) const {
    return needRedraw;
}


static FsLazyWindowApplication *appPtr=nullptr;

/* static */
FsLazyWindowApplicationBase *FsLazyWindowApplicationBase::GetApplication(void) {
    if(nullptr==appPtr) {
        appPtr=new FsLazyWindowApplication;
    }
    return appPtr;
}

