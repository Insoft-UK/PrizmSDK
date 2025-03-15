// The MIT License (MIT)
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

#pragma once

#ifndef __clang__
#include <fxcg/display.h>
#else
#include <display.h>
#endif

#include <stdint.h>

typedef struct CalcTypeFont {
    uint8_t        height;           // Total height of the font in pixels.
    int8_t         base;             // Baseline offset in pixels.
    uint8_t        space;            // Width of a space character in subpixels.
    const uint8_t *glyphData;        // Pointer to the raw glyph data.
    uint16_t       glyphOffset[224]; // Array of offsets to each character’s glyph data (indexed by ASCII - 32), 0xFFFF if the glyph is not available.
} TCalcTypeFont;

typedef struct CalcTypeGlyphData {
    int8_t   xOffset;                // Horizontal offset (in subpixels) of the glyph relative to the origin.
    int8_t   yOffset;                // Vertical offset (in pixels) of the glyph relative to the baseline.
    uint8_t  xAdvance;               // Horizontal distance (in subpixels) to advance after drawing this glyph.
    uint8_t  width;                  // Width of the glyph in real pixels (subpixel encoded).
    uint8_t  height;                 // Height of the glyph in real pixels.
    uint8_t  data[1];                // Placeholder for glyph pixel data, stored as RGB332.
} TCalcTypeGlyphData;

#ifdef __cplusplus
extern "C" {
#endif

    unsigned int CalcType_Width(const TCalcTypeFont *font, const char *str);
    void CalcType_DrawString(const TCalcTypeFont *font, const char *str, int x, int y, color_t color);

#ifdef __cplusplus
};
#endif
