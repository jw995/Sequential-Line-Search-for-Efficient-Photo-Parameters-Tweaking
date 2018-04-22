/* ////////////////////////////////////////////////////////////

File Name: ysfileio.cpp
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

#include "ysfileio.h"

/* static */ YsWString YsFileIO::Getcwd(void)
{
	YsWString cwd;
	Getcwd(cwd);
	return cwd;
}

/* static */ YSBOOL YsFileIO::CheckFileExist(const wchar_t fn[])
{
	auto fp=Fopen(fn,"rb");
	if(NULL!=fp)
	{
		fclose(fp);
		return YSTRUE;
	}
	return YSFALSE;
}
/* static */ YSBOOL YsFileIO::CheckFileExist(const char fn[])
{
	auto fp=Fopen(fn,"rb");
	if(NULL!=fp)
	{
		fclose(fp);
		return YSTRUE;
	}
	return YSFALSE;
}


////////////////////////////////////////////////////////////

YsFileIO::File::File()
{
	fp=NULL;
}

YsFileIO::File::File(const wchar_t fn[],const char mode[])
{
	fp=YsFileIO::Fopen(fn,mode);
}

YsFileIO::File::File(const char fn[],const char mode[])
{
	fp=YsFileIO::Fopen(fn,mode);
}

void YsFileIO::File::MoveFrom(File &incoming)
{
	if(this!=&incoming)
	{
		this->fp=incoming.fp;
		incoming.fp=nullptr;
	}
}

YsFileIO::File::File(File &&incoming)
{
	MoveFrom(incoming);
}
YsFileIO::File &YsFileIO::File::operator=(File &&incoming)
{
	MoveFrom(incoming);
	return *this;
}

YsFileIO::File::~File()
{
	Fclose();
}
void YsFileIO::File::Fclose(void)
{
	if(NULL!=fp)
	{
		fclose(fp);
		fp=NULL;
	}
}

FILE *YsFileIO::File::Fp(void) const
{
	return fp;
}
