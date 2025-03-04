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

#include "calctype.h"

#define R_CHANNEL(rgb) (rgb >> 5)
#define G_CHANNEL(rgb) ((rgb & 0b00011100) >> 2)
#define B_CHANNEL(rgb) (rgb & 0b00000011)

static void CalcType_DrawGlyph(TCalcTypeGlyphData *glyph, int x, int y, unsigned short color)
{
    static const unsigned short redMapping[8] =
    {
        0b0000000000000000, // 0
        0b0011000000000000, // 3
        0b0100000000000000, // 8
        0b0110000000000000, // 12
        0b1000100000000000, // 17
        0b1011000000000000, // 22
        0b1101100000000000, // 27
        0b1111100000000000, // 31
    };
    
    static const unsigned short greenMapping[8] =
    {
        0b0000000000000000, // 0
        0b0000000100000000, // 8
        0b0000001000100000, // 17
        0b0000001101000000, // 26
        0b0000010010000000, // 36
        0b0000010110100000, // 45
        0b0000011011100000, // 55
        0b0000011111100000, // 63
    };

    static const unsigned short blueMapping[4] =
    {
        0b0000000000000000, // 0
        0b0000000000000110, // 6
        0b0000000000010001, // 17
        0b0000000000011111, // 31
    };
    
    color_t rgb565;
    color_t invRgb565;
    
    color_t *vram = ((unsigned short*)GetVRAMAddress()) + x + y * 384;
    unsigned char *data = glyph->data;

    for (y = 0; y < glyph->height; y++) {
        for (x = 0; x < glyph->width; x++) {
            int currentPixel = *vram;
            uint8_t rgb = *data++;
            
            rgb565 = redMapping[R_CHANNEL(rgb)] | greenMapping[G_CHANNEL(rgb)] | blueMapping[B_CHANNEL(rgb)];
            
            /*
             In order for fast interpolation to work, the inverse of the mask value
             must be the bit inverse to prevent color overlap
             */
            rgb = ~rgb;
            invRgb565 = redMapping[R_CHANNEL(rgb)] | greenMapping[G_CHANNEL(rgb)] | blueMapping[B_CHANNEL(rgb)];
         
            *vram++ = (color & rgb565) | (currentPixel & invRgb565);
        }
        vram += LCD_WIDTH_PX - glyph->width;
    }
}

unsigned int CalcType_Width(const TCalcTypeFont *font, const char *str)
{
    unsigned int subPixelWidth = 0;
    unsigned short dataOffset;
    
    while (*str) {
        char charactor = *str++;
        switch (charactor) {
            case ' ':
                subPixelWidth += font->space;
                break;
                
            default:
                if (charactor < ' ') continue;
                
                dataOffset = font->glyphOffset[(int)charactor - 32];
                if (dataOffset == 0xFFFF) continue;
                
                subPixelWidth += ((TCalcTypeGlyphData *)(font->glyphData + dataOffset))->xAdvance;
                break;
        }
    }
    
    return subPixelWidth / 3;
}


void CalcType_DrawString(const TCalcTypeFont *font, const char *str, int x, int y, color_t color)
{
    int subX = x * 3;
    unsigned short glyphOffset;
    
    y += font->base;
    
    while (*str && subX < LCD_WIDTH_PX * 3) {
        char charactor = *str++;
 
        switch (charactor) {
            case '\n':
                subX = x * 3;
                y += font->height;
                break;
                
            case ' ':
                subX += font->space;
                break;
                
            default:
                if (charactor < ' ') continue;
                
                glyphOffset = font->glyphOffset[charactor - 32];
                if (glyphOffset == 0xFFFF) continue;
                
                TCalcTypeGlyphData *glyph = (TCalcTypeGlyphData *)(font->glyphData + glyphOffset);
                CalcType_DrawGlyph(glyph, (subX + glyph->xOffset) / 3, y + glyph->yOffset, color);
                subX += glyph->xAdvance;
                if (subX >= LCD_WIDTH_PX * 3) {
                    subX = x * 3;
                    y += font->height;
                }
                break;
        }
    }
}
