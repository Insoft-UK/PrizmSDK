// The MIT License (MIT)
//
// Copyright (c) 2025 Insoft. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "fxcg.h"
#include <stdio.h>
#include <string.h>
#include <display.h>

static char _BundlePath[256];

fxCG_DDRegister _fxCG_DDRegister = {
    .B = 1 /// 1 = Enable 8 color mode
};



int _fxCG_StatusArea = 1;
unsigned short _fxCG_SAF = SAF_BATTERY | SAF_ALPHA_SHIFT;

unsigned char _fxCG_0xA44B0000[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; // keyboard_register

int _fxCG_KMI_Shift = 0;
int _fxCG_KMI_Alpha = 0;
int _fxCG_KMI_Clip = 0;

void SetBundlePath(const char *path)
{
    memcpy(_BundlePath, path, 256);
}

const char *GetBundlePath(void)
{
    return _BundlePath;
}
