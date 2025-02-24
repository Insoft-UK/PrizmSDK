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

#ifndef font_h
#define font_h

#include <fxcg/display.h>
#include "types.h"

#define GFXglyph FXCG_TGlyph
#define GFXfont FXCG_TFont

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned short offset;   // Offset address to the bitmap data for this glypth.
    unsigned char  width;    // Bitmap dimensions in pixels.
    unsigned char  height;   // Bitmap dimensions in pixels.
    unsigned char  xAdvance; // Distance to advance cursor in the x-axis.
    char           dX;       // Used to position the glyph within the cell in the horizontal direction.
    char           dY;       // Distance from the baseline of the character to the top of the glyph.
} FXCG_TGlyph;

typedef struct {
    unsigned char      *bitmap;   // Bitmap data array.
    FXCG_TGlyph        *glyph;    // Glyph data.
    unsigned char       first;    // The first ASCII value of your first character.
    unsigned char       last;     // The last ASCII value of your last character.
    unsigned char       yAdvance; // Newline distance in the y-axis.
} FXCG_TFont;

int FXCG_drawGlyph(short x, short y, unsigned char c, color_t color, FXCG_TFont *font);
int FXCG_drawString(short x, short y, const char *str, color_t color, FXCG_TFont *font);

#ifdef __cplusplus
}
#endif

#endif /* font_h */
