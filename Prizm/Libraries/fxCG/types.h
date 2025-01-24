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

#ifndef types_h
#define types_h

#include <stdint.h>
#include <stdio.h>

#define SAF_BATTERY             0x0001
#define SAF_ALPHA_SHIFT         0x0002
#define SAF_SETUP_INPUT_OUTPUT  0x0004
#define SAF_SETUP_FRAC_RESULT   0x0008
#define SAF_SETUP_ANGLE         0x0010
#define SAF_SETUP_COMPLEX_MODE  0x0020
#define SAF_SETUP_DISPLAY       0x0040
#define SAF_TEXT                0x0100
#define SAF_GLYPH               0x0200

typedef unsigned short FXCG_TColor;

enum Screen : uint16_t {
    FXCG_SCREEN_WIDTH = 384,
    FXCG_SCREEN_HEIGHT = 216
} FXCG_Screen;

enum Color : color_t {
    FXCG_COLOR_BLACK   = 0,
    FXCG_COLOR_BLUE    = 0x001F,
    FXCG_COLOR_GREEN   = 0x07E0,
    FXCG_COLOR_CYAN    = 0x07FF,
    FXCG_COLOR_RED     = 0xF800,
    FXCG_COLOR_MAGENTA = 0xF81F,
    FXCG_COLOR_YELLOW  = 0xFFE0,
    FXCG_COLOR_WHITE   = 0xFFFF
} FXCG_Color;

#endif // types_h
