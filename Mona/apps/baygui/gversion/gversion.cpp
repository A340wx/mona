/*
Copyright (c) 2004 bayside
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <baygui.h>

/**
 バージョンクラス
*/
class GVersion : public Window {
public:
	GVersion::GVersion();
	virtual GVersion::~GVersion();
	virtual void onPaint(Graphics *g);
};

#if defined(PEKOE)
/** バージョンアイコン */
static int versionIcon [31][24] = {
	{0xcccecc,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0xcccecc},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x444644,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xcccefc,0xf4f6f4,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xf4f6f4,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0x4be04,0x4be04,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xdc0604,0xdc0604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0x40604,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x40604},
	{0xcccecc,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0xcccecc},
	{0xcccecc,0x40604,0x545654,0x545654,0x444644,0x545654,0x545654,0x444644,0x444644,0x444644,0x444644,0x444644,0x444644,0x242624,0x242624,0x242624,0x242624,0x242624,0x242624,0x242624,0x242624,0x242624,0x40604,0xcccecc},
	{0xcccecc,0x40604,0x747674,0x747674,0x747674,0x747674,0x747674,0x747674,0x747674,0x747674,0x545654,0x545654,0x444644,0x444644,0x444644,0x444644,0x242624,0x242624,0x242624,0x242624,0x242624,0x242624,0x40604,0xcccecc},
	{0xcccecc,0x40604,0x8c8e8c,0x8c8e8c,0x8c8e8c,0x8c8e8c,0x8c8e8c,0x8c8e8c,0x8c8e8c,0x8c8e8c,0x747674,0x747674,0x747674,0x545654,0x545654,0x444644,0x444644,0x444644,0x444644,0x242624,0x242624,0x242624,0x40604,0xcccecc},
	{0xcccecc,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0x40604,0xcccecc},
};
#elif defined(MONA)
/** バージョンアイコン */
static int versionIcon [30][21] = {
	{0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x242224,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x242224,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc},
	{0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x242224,0xeceeec,0x242224,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x242224,0xeceeec,0x242224,0xcccecc,0xcccecc,0xcccecc,0xcccecc},
	{0xcccecc,0xcccecc,0xcccecc,0x242224,0xdcdedc,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x242224,0xeceeec,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0xdcdedc,0xeceeec,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0xcccecc,0x242224,0xeceeec,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0xdcdedc,0xeceeec,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0x242224,0x242224,0x242224,0x242224,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc},
	{0xcccecc,0x242224,0xdcdedc,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xcccecc,0x242224,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0x242224,0xcccecc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0x242224,0xfcfefc,0xfcfefc,0xfcfefc,0x242224,0xfcfefc,0xfcfefc,0xfcfefc,0x242224,0xfcfefc,0xfcfefc,0x242224,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0x9c9a9c,0x242224,0x242224,0x242224,0x9c9a9c,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0x242224,0xec7264,0x242224,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0xcccecc,0x242224,0xdcdedc,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0x9c9a9c,0x242224,0x9c9a9c,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc},
	{0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0x242224,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0xeceeec,0x242224,0xcccecc,0xcccecc},
	{0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0xeceeec,0x242224,0xcccecc,0xcccecc},
	{0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xcccecc},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0x242224,0xdcdedc,0xeceeec,0xeceeec,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224,0xdcdedc,0xfcfefc,0xfcfefc,0xfcfefc,0xfcfefc,0xeceeec,0x242224},
	{0xcccecc,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0x242224,0xdcdedc,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0xeceeec,0x242224,0xcccecc},
	{0xcccecc,0xcccecc,0x242224,0x242224,0x242224,0x242224,0x242224,0x242224,0x242224,0x242224,0x242224,0x242224,0xfcfefc,0x242224,0x242224,0x242224,0x242224,0x242224,0x242224,0xcccecc,0xcccecc},
};
#endif

GVersion::GVersion()
{
	setRect(20, 240, 270 + INSETS_LEFT + INSETS_RIGHT , 150 + INSETS_TOP + INSETS_BOTTOM);
	setTitle("ﾊﾞｰｼﾞｮﾝ情報");
}

GVersion::~GVersion()
{
}

void GVersion::onPaint(Graphics *g)
{
#if defined(PEKOE)
	char line[128];

	gbc_blt_screen(32, x + INSETS_LEFT + 14, y + INSETS_TOP + 11, 24, 31, versionIcon);

	g->setColor(0,0,0);
	g->drawText(GUILIB_VERSION, 50, 10);
	g->drawText("copyright (C) 2004, bayside", 50, 26);
	g->setColor(96,96,96);
	g->drawRect(10,50,250,90);
	sprintf(line, "シェル %dbit / カーネル %dbit", sizeof(void*)*8, (sys_get_version()&0x80000000)?32:64);
	g->drawText(line, 15, 55);
	sprintf(line, "全物理メモリ　　　　　%dKB", (sys_get_memory_status(0)>>10));
	g->drawText(line, 15, 71);
	sprintf(line, "有効ページプール　　　%dKB", (sys_get_memory_status(1)>>10));
	g->drawText(line, 15, 87);
	sprintf(line, "システムリソース残り　%dKB", (sys_get_memory_status(2)>>10));
	g->drawText(line, 15, 103);
	sprintf(line, "カレントプロセス　　　%dKB/%dKB\n", 
		(sys_get_memory_status(0x1001)>>10), (sys_get_memory_status(0x1000)>>10));
	g->drawText(line, 15, 119);
#elif defined(MONA)
	int i, j;
	
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 21; j++) {
			_g->screen->putPixel16(x + INSETS_LEFT + 16 + j, y + INSETS_TOP + 11 + i, versionIcon[i][j]);
		}
	}

	MemoryInfo info;
	syscall_get_memory_info(&info);
	
	char mesg1[64], mesg2[64], mesg3[64];
	toDecimalString(info.totalMemoryL / 1024, mesg1);
	toDecimalString(info.freePageNum * info.pageSize / 1024, mesg2);
	toDecimalString(info.totalPageNum * info.pageSize / 1024, mesg3);
	//toDecimalString(32768, mesg1);
	//toDecimalString(16384, mesg2);
	//toDecimalString(32768, mesg3);
	strcat(mesg1, "KB");
	strcat(mesg2, "KB");
	strcat(mesg3, "KB");

	g->setColor(0,0,0);
	g->drawText(GUILIB_VERSION, 50, 10);
	g->drawText("copyright (C) 2004, bayside", 50, 26);
	g->setColor(96,96,96);
	g->drawRect(10,50,250,90);
	g->drawText("シェル 32bit / カーネル 32bit", 15, 55);
	g->drawText("全物理メモリ", 15, 71);
	g->drawText("有効ページプール", 15, 87);
	g->drawText("全ページプール", 15, 103);
	g->drawText("システムリソース残り", 15, 119);
	g->drawText(mesg1, 156, 71);
	g->drawText(mesg2, 156, 87);
	g->drawText(mesg3, 156, 103);
	g->drawText("0KB", 156, 119);
#endif
}

/** メイン */
#if defined(MONA)
int MonaMain(List<char*>* pekoe)
#else
int main(int argc, char **argv)
#endif
{
	GVersion *version = new GVersion();
	version->run();
	return 0;
}
