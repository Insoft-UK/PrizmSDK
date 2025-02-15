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

#include "font.h"
#include "draw.h"

int FXCG_glyph(int16_t x, int16_t y, uint8_t c, uint16_t color, FXCG_TFont font)
{
    if (c < font.first || c > font.last) {
        return 0;
    }
    
    GFXglyph *glyph = &font.glyph[(int)c - font.first];
    
    int height = glyph->height;
    int width = glyph->width;
   
    x += glyph->dX;
    y += glyph->dY + font.yAdvance;
    
    uint8_t *bitmap = font.bitmap + glyph->offset;
    uint8_t bitPosition = 1 << 7;
    while (height--) {
        for (int xx=0; xx<width; xx++) {
            if (!bitPosition) {
                bitPosition = 1 << 7;
                bitmap++;
            }
            if (*bitmap & bitPosition) {
                FXCG_drawPixel(x + xx, y, color);
            }
            bitPosition >>= 1;
        }
        y++;
    }
    return glyph->xAdvance;
}

int FXCG_print(int16_t x, int16_t y, const char *s, uint16_t color, GFXfont font)
{
    uint8_t *c = (uint8_t *)s;
    
    while (*c) {
        x += glyph(x, y, (uint8_t)*c, color, font);
        c++;
    }
    return x;
}

