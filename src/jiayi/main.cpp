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
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fslazywindow.h>
//#include <ysglfontdata.h>
#include <Eigen/Dense>
//#include <nlopt.h>
# include "math0.h"

using namespace Eigen;


class FsLazyWindowApplication : public FsLazyWindowApplicationBase
{
protected:
	bool needRedraw;
	int wid, hei;
	int lb, mb, rb, mx, my;	
	VectorXd slideStart; 
	VectorXd slideEnd;

	MatrixXd X;
	VectorXd x;
	VectorXd f;
	


public:
	FsLazyWindowApplication();
	virtual void BeforeEverything(int argc, char *argv[]);
	virtual void GetOpenWindowOption(FsOpenWindowOption &OPT) const;
	virtual void Initialize(int argc, char *argv[]);
	virtual void Interval(void);
	virtual void BeforeTerminate(void);
	virtual void Draw(void);
	virtual bool UserWantToCloseProgram(void);
	virtual bool MustTerminate(void) const;
	virtual long long int GetMinimumSleepPerInterval(void) const;
	virtual bool NeedRedraw(void) const;
};

FsLazyWindowApplication::FsLazyWindowApplication() {
	needRedraw = false;
}

/* virtual */
void FsLazyWindowApplication::BeforeEverything(int argc, char *argv[]) {
	srand(time(NULL));  // For rand()
	slideStart.resize(6);
	slideEnd.resize(6);
}
/* virtual */
void FsLazyWindowApplication::GetOpenWindowOption(FsOpenWindowOption &opt) const {
	opt.x0 = 16;
	opt.y0 = 16;
	opt.wid = 1200;
	opt.hei = 800;
}
/* virtual */
void FsLazyWindowApplication::Initialize(int argc, char *argv[]) {
	// Randomly generate the end points of slide bar and print their values
	slideStart(0) = (double)rand() / RAND_MAX;
	slideStart(1) = (double)rand() / RAND_MAX;
	slideStart(2) = (double)rand() / RAND_MAX;
	slideStart(3) = (double)rand() / RAND_MAX;
	slideStart(4) = (double)rand() / RAND_MAX;
	slideStart(5) = (double)rand() / RAND_MAX;
	slideEnd(0) = (double)rand() / RAND_MAX;
	slideEnd(1) = (double)rand() / RAND_MAX;
	slideEnd(2) = (double)rand() / RAND_MAX;
	slideEnd(3) = (double)rand() / RAND_MAX;
	slideEnd(4) = (double)rand() / RAND_MAX;
	slideEnd(5) = (double)rand() / RAND_MAX;
	/*std::cout << "Starting point of slider\n" << slideStart << std::endl;
	std::cout << "Ending point of slider\n" << slideEnd << std::endl;*/

	X = MatrixXd::Random(6, 6);
	x = VectorXd::Random(6);
	f = VectorXd::Random(6);


	GaussianProcess test_gau(X, f, 3.5, 0.8, slideEnd);

	auto k_vector = test_gau.calc_k(x);
	auto K_matrix=test_gau.calc_K();
	auto miu = test_gau.estimate_miu(x);
	auto sigma_sq = test_gau.estimate_sigma_sq(x);

	std::cout << "k_vector: \n" << k_vector << std::endl;
	std::cout << "K_matrix: \n" << K_matrix << std::endl;
	std::cout << "miu: \n" << miu << std::endl;
	std::cout << "sigma: \n" << sigma_sq << std::endl;


}
/* virtual */
void FsLazyWindowApplication::Interval(void) {
	FsGetWindowSize(wid, hei);

	auto key = FsInkey();
	if (FSKEY_ESC == key) {
		SetMustTerminate(true);
	}

	FsGetMouseState(lb, mb, rb, mx, my);
	//if (lb && bar.IsInside(mx, my)) {
	//bar.SetDragging(true);
	//}
	//if (bar.GetDragging() && !lb) {
	//bar.SetDragging(false);
	//}
	//if (bar.GetDragging()) {
	//bar.Move(mx, my);
	//}

	//toolbar.hover(mx, my);

	needRedraw = true;
}
/* virtual */
void FsLazyWindowApplication::Draw(void) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, wid, hei);
	//bar.Show();
	//toolbar.Draw();
	//for (auto btn: toolbar.GetButtons()) {
	//btn.draw();
	//}
	needRedraw = false;
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


static FsLazyWindowApplication *appPtr = nullptr;

/* static */
FsLazyWindowApplicationBase *FsLazyWindowApplicationBase::GetApplication(void) {
	if (nullptr == appPtr) {
		appPtr = new FsLazyWindowApplication;
	}
	return appPtr;
}





