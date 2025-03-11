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
#include "graphics.h"

static void FXCG_applyOneThirdFilter(uint8_t *input, uint8_t *output, const int width)
{
    // Handle the first pixel separately (no left neighbor)
    *output++ = (*input + *input + *(input + 1)) / 3;
    input++;

    // Process all middle pixels
    for (int i = 1; i < width - 1; i++) {
        *output++ = (*(input - 1) + *input + *(input + 1)) / 3;
        input++;
    }

    // Handle the last pixel separately (no right neighbor)
    *output = (*(input - 1) + *input + *input) / 3;
}

static void FXCG_applyOneNinthFilter(uint8_t *input, uint8_t *output, const int width)
{
    for (int i = 0; i < width; i++) {
        int sum = 0;
        for (int j = -1; j <= 1; j++) {   // Use 3-pixel neighborhood
            int idx = i + j;
            if (idx >= 0 && idx < width) {
                sum += input[idx];
            } else {
                sum += input[i];  // Edge case: replicate borders
            }
        }
        *output++ = sum / 3;  // Apply 1/9 filter
    }
}

void FXCG_processSubPixels(uint8_t *input, int x, int y, const int width)
{
    uint8_t filteredOneThird[width];
    uint8_t filteredOneNinth[width];

    // 1/3 Filtering
    FXCG_applyOneThirdFilter(input, filteredOneThird, width);

    // 1/9 Filtering
    FXCG_applyOneNinthFilter(filteredOneThird, filteredOneNinth, width);
  
    uint8_t *filter = filteredOneNinth;

    // Convert filtered sub-pixels into final pixels
    for (int i = 0; i < width; i += 3) {
        uint8_t r = *filter++;
        uint8_t g = *filter++;
        uint8_t b = *filter++;
        
        r >>= 3;
        g >>= 2;
        b >>= 3;
        
        Bdisp_SetPoint_VRAM(x++, y, (r << 11) | (g << 5) | b);
    }
}

int FXCG_drawGlyph(short x, short y, unsigned char c, color_t color, FXCG_TFont *font)
{
    if (c < font->first || c > font->last) {
        return 0;
    }
    
    FXCG_TGlyph *glyph = &font->glyph[(int)c - font->first];
    
    int height = glyph->height;
    int width = glyph->width;
   
    x += glyph->dX;
    y += glyph->dY + font->yAdvance;
    
    uint8_t *bitmap = font->bitmap + glyph->offset;
    uint8_t bitPosition = 1 << 7;
    while (height--) {
        for (int xx=0; xx<width; xx++) {
            if (!bitPosition) {
                bitPosition = 1 << 7;
                bitmap++;
            }
            if (*bitmap & bitPosition) {
                Bdisp_SetPoint_VRAM(x + xx, y, color);
            }
            bitPosition >>= 1;
        }
        y++;
    }
    return glyph->xAdvance;
}

int FXCG_drawString(short x, short y, const char *s, color_t color, FXCG_TFont *font)
{
    char *c = (char *)s;
    
    while (*c) {
        x += FXCG_drawGlyph(x, y, (unsigned char)*c, color, font);
        c++;
    }
    return x;
}

