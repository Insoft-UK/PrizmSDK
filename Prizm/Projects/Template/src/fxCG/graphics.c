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

#include "graphics.h"
#include <stdbool.h>

// Global variable to track the state of half opacity drawing.
static bool is_half_opacity_enabled = false;


void FXCG_enableHalfOpacityDrawing()
{
    is_half_opacity_enabled = true;
}

void FXCG_disableHalfOpacityDrawing()
{
    is_half_opacity_enabled = false;
}

void FXCG_clearDisplay(color_t color)
{
    color_t *VRAM = (color_t *)GetVRAMAddress();
    int length = 82944;
    while(length--){
        *VRAM++ = color;
    }
}

color_t FXCG_color(uint8_t r, uint8_t g, uint8_t b)
{
    return (r / 8) << 11 | (g / 4) << 6 | (b / 8);
}

color_t FXCG_gray(int shade)
{
    return  shade * 0x0841;
}

/**
 @brief    Draw a perfectly horizontal line (this is often optimized in a subclass!)
 @param    x   Left-most x coordinate
 @param    y   Left-most y coordinate
 @param    w   Width in pixels
 @param    color Specifies what color the plotted pixel will be. It is in RGB 565 format.
 */
static void FXCG_drawFastHLine(unsigned x, unsigned y, unsigned w, color_t color)
{
    if (y > 215) return;
    color_t *VRAM = (color_t *)GetVRAMAddress();
    while (w--) {
        VRAM[x + y * 384] = color;
        if (++x > 383) return;
    }
}

/**
 @brief    Draw a perfectly vertical line (this is often optimized in a subclass!)
 @param    x   Top-most x coordinate
 @param    y   Top-most y coordinate
 @param    h   Height in pixels
 @param    color Specifies what color the plotted pixel will be. It is in RGB 565 format.
 */
static void FXCG_drawFastVLine(unsigned x, unsigned y, unsigned h, color_t color)
{
    if (x > 383) return;
    color_t *VRAM = (color_t *)GetVRAMAddress();
    while (h--) {
        VRAM[x + y * 384] = color;
        if (++y > 215) return;
    }
}


static void swap(int *x, int *y) {
    *x = *x ^ *y;    // x = x ^ y
    *y = *x ^ *y;    // y = (x ^ y) ^ y wich means now y = original x
    *x = *x ^ *y;    // x = (x ^ y) ^ y but since y is now original x then
    // it is really x = (x ^ y) ^ x, so x = original y
}


void FXCG_drawLine(int x1, int y1, int x2, int y2, color_t color)
{
    if (x1 == x2) {
        if (y1 > y2)
            swap(&y1, &y2);
        if (!is_half_opacity_enabled) {
            FXCG_drawFastVLine(x1, y1, y2 - y1 + 1, color);
            return;
        }
        for (; y1 < y2; y1++)
            FXCG_drawPixel(x1, y1, color);
        return;
    }
    
    if (y1 == y2) {
        if (x1 > x2)
            swap(&x1, &x2);
        if (!is_half_opacity_enabled) {
            FXCG_drawFastHLine(x1, y1, x2 - x1 + 1, color);
            return;
        }
        for (; x1 < x2; x1++)
            FXCG_drawPixel(x1, y1, color);
        
        return;
    }
    
    signed char ix;
    signed char iy;
    
    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x;
    int delta_y;
    
    if (x2 > x1) {
        ix = 1;
        delta_x = x2 - x1;
    } else {
        ix = -1;
        delta_x = x1 - x2;
    }
    
    if (y2 > y1) {
        iy = 1;
        delta_y = y2 - y1;
    } else {
        iy = -1;
        delta_y = y1 - y2;
    }
    
    FXCG_drawPixel(x1, y1, color);
    if (delta_x >= delta_y) {
        int error = delta_y - (delta_x >> 1);        // error may go below zero
        while (x1 != x2) {
            if (error >= 0) {
                if (error || (ix > 0)) {
                    y1 += iy;
                    error -= delta_x;
                }                           // else do nothing
            }                              // else do nothing
            x1 += ix;
            error += delta_y;
            FXCG_drawPixel(x1, y1, color);
        }
    } else {
        int error = delta_x - (delta_y >> 1);      // error may go below zero
        while (y1 != y2) {
            if (error >= 0) {
                if (error || (iy > 0)) {
                    x1 += ix;
                    error -= delta_y;
                }                           // else do nothing
            }                              // else do nothing
            y1 += iy;
            error += delta_x;
            FXCG_drawPixel(x1, y1, color);
        }
    }
}

void FXCG_drawRect(int x, int y, short w, short h, color_t color)
{
    FXCG_drawFastHLine(x, y, w, color);
    FXCG_drawFastHLine(x, y + h - 1, w, color);
    FXCG_drawFastVLine(x, y, h, color);
    FXCG_drawFastVLine(x + w - 1, y, h, color);
}

/**
 @brief    Quarter-circle drawer, used to do circles and roundrects.
 @param    x   Center-point x coordinate.
 @param    y   Center-point y coordinate.
 @param    r   Radius of circle.
 @param    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing.
 @param    color Specifies what color to draw with. It is in RGB 565 format.
 */
static void FXCG_drawCircleHelper(int x, int y, short r, uint8_t cornername, color_t color)
{
    short f = 1 - r;
    short ddF_x = 1;
    short ddF_y = -2 * r;
    short xx = 0;
    short yy = r;
    
    while (xx < yy) {
        if (f >= 0) {
            yy--;
            ddF_y += 2;
            f += ddF_y;
        }
        xx++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4) {
            FXCG_drawPixel(x + xx, y + yy, color);
            FXCG_drawPixel(x + yy, y + xx, color);
        }
        if (cornername & 0x2) {
            FXCG_drawPixel(x + xx, y - yy, color);
            FXCG_drawPixel(x + yy, y - xx, color);
        }
        if (cornername & 0x8) {
            FXCG_drawPixel(x - yy, y + xx, color);
            FXCG_drawPixel(x - xx, y + yy, color);
        }
        if (cornername & 0x1) {
            FXCG_drawPixel(x - yy, y - xx, color);
            FXCG_drawPixel(x - xx, y - yy, color);
        }
    }
}

void FXCG_drawCircle(int x, int y, short r, color_t color)
{
    short f = 1 - r;
    short ddF_x = 1;
    short ddF_y = -2 * r;
    short xx = 0;
    short yy = r;
    
    FXCG_drawPixel(x, y + r, color);
    FXCG_drawPixel(x, y - r, color);
    FXCG_drawPixel(x + r, y, color);
    FXCG_drawPixel(x - r, y, color);
    
    while (xx < yy) {
        if (f >= 0) {
            yy--;
            ddF_y += 2;
            f += ddF_y;
        }
        xx++;
        ddF_x += 2;
        f += ddF_x;
        
        FXCG_drawPixel(x + xx, y + yy, color);
        FXCG_drawPixel(x - xx, y + yy, color);
        FXCG_drawPixel(x + xx, y - yy, color);
        FXCG_drawPixel(x - xx, y - yy, color);
        FXCG_drawPixel(x + yy, y + xx, color);
        FXCG_drawPixel(x - yy, y + xx, color);
        FXCG_drawPixel(x + yy, y - xx, color);
        FXCG_drawPixel(x - yy, y - xx, color);
    }
}

/**
 @brief    Quarter-circle drawer with fill, used for circles and roundrects.
 @param    x Center-point x coordinate.
 @param    y Center-point y coordinate.
 @param    r  Radius of circle.
 @param    corners  Mask bits indicating which quarters we're doing.
 @param    delta    Offset from center-point, used for round-rects.
 @param    color Specifies what color to draw with. It is in RGB 565 format.
 */
static void FXCG_drawFillCircleHelper(int x, int y, short r, uint8_t corners, short delta, color_t color)
{
    short f = 1 - r;
    short ddF_x = 1;
    short ddF_y = -2 * r;
    short xx = 0;
    short yy = r;
    short px = xx;
    short py = yy;
    
    delta++; // Avoid some +1's in the loop
    
    while (xx < yy) {
        if (f >= 0) {
            yy--;
            ddF_y += 2;
            f += ddF_y;
        }
        xx++;
        ddF_x += 2;
        f += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
        if (xx < (yy + 1)) {
            if (corners & 1)
                FXCG_drawFastVLine(x + xx, y - yy, 2 * yy + delta, color);
            if (corners & 2)
                FXCG_drawFastVLine(x - xx, y - yy, 2 * yy + delta, color);
        }
        if (yy != py) {
            if (corners & 1)
                FXCG_drawFastVLine(x + py, y - px, 2 * px + delta, color);
            if (corners & 2)
                FXCG_drawFastVLine(x - py, y - px, 2 * px + delta, color);
            py = yy;
        }
        px = xx;
    }
}


void FXCG_drawFillCircle(int x, int y, short r, color_t color)
{
    
    FXCG_drawFastVLine(x, y - r, 2 * r + 1, color);
    FXCG_drawFillCircleHelper(x, y, r, 3, 0, color);
    
}


void FXCG_drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, color_t color)
{
    FXCG_drawLine(x1, y1, x2, y2, color);
    FXCG_drawLine(x2, y2, x3, y3, color);
    FXCG_drawLine(x3, y3, x1, y1, color);
}

void FXCG_drawFillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, color_t color)
{
//    int a, b, y, last;
//    
//    // Sort coordinates by Y order (y3 >= y2 >= y1)
//    if (y1 > y2) {
//        swap(&y1, &y2);
//        swap(&x1, &x2);
//    }
//    if (y2 > y3) {
//        swap(&y3, &y2);
//        swap(&x3, &x2);
//    }
//    if (y1 > y2) {
//        swap(&y1, &y2);
//        swap(&x1, &x2);
//    }
//    
//    if (y1 == y3) { // Handle awkward all-on-same-line case as its own thing
//        a = b = x1;
//        if (x2 < a)
//            a = x2;
//        else if (x2 > b)
//            b = x2;
//        if (x3 < a)
//            a = x3;
//        else if (x3 > b)
//            b = x3;
//        FXCG_drawFastHLine(a, y1, b - a + 1, color);
//        return;
//    }
//    
//    int dx01 = x2 - x1, dy01 = y2 - y1, dx02 = x3 - x1, dy02 = y3 - y1, dx12 = x3 - x2, dy12 = y3 - y2;
//    int sa = 0, sb = 0;
//    
//    /*
//     For upper part of triangle, find scanline crossings for segments
//     0-1 and 0-2.  If y2=y3 (flat-bottomed triangle), the scanline y2
//     is included here (and second loop will be skipped, avoiding a /0
//     error there), otherwise scanline y2 is skipped here and handled
//     in the second loop...which also avoids a /0 error here if y1=y2
//     (flat-topped triangle).
//     */
//    
//    if (y2 == y3)
//        last = y2; // Include y2 scanline
//    else
//        last = y2 - 1; // Skip it
//    
//    for (y = y1; y <= last; y++) {
//        a = x1 + sa / dy01;
//        b = x1 + sb / dy02;
//        sa += dx01;
//        sb += dx02;
//        
//        if (a > b)
//            swap(&a, &b);
//        FXCG_drawFastHLine(a, y, b - a + 1, color);
//    }
//    
//    // For lower part of triangle, find scanline crossings for segments
//    // 0-2 and 1-2.  This loop is skipped if y2=y3.
//    sa = dx12 * (y - y2);
//    sb = dx02 * (y - y1);
//    for (; y <= y3; y++) {
//        a = x2 + sa / dy12;
//        b = x1 + sb / dy02;
//        sa += dx12;
//        sb += dx02;
//        
//        if (a > b)
//            swap(&a, &b);
//        FXCG_drawFastHLine(a, y, b - a + 1, color);
//    }
}

void FXCG_drawRoundRect(int x, int y, int w, int h, short r, color_t color)
{
    int max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
    if (r > max_radius)
        r = max_radius;
    // smarter version
  
    FXCG_drawFastHLine(x + r, y, w - 2 * r, color);         // Top
    FXCG_drawFastHLine(x + r, y + h - 1, w - 2 * r, color); // Bottom
    FXCG_drawFastVLine(x, y + r, h - 2 * r, color);         // Left
    FXCG_drawFastVLine(x + w - 1, y + r, h - 2 * r, color); // Right
    // draw four corners
    FXCG_drawCircleHelper(x + r, y + r, r, 1, color);
    FXCG_drawCircleHelper(x + w - r - 1, y + r, r, 2, color);
    FXCG_drawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
    FXCG_drawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

/**
 @brief    Draw a rounded rectangle with fill color
 @param    x   Top left corner x coordinate
 @param    y   Top left corner y coordinate
 @param    w   Width in pixels
 @param    h   Height in pixels
 @param    r   Radius of corner rounding
 @param    color Specifies what color to draw with. It is in RGB 565 format.
 */
void FXCG_drawFillRoundRect(int x, int y, int w, int h, short r, color_t color)
{
    int max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
    if (r > max_radius)
        r = max_radius;
  
    FXCG_drawFillArea(x + r, y, w - 2 * r, h, color);
    FXCG_drawFillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
    FXCG_drawFillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}


void FXCG_drawFillArea(unsigned x, unsigned y, unsigned w, unsigned h, color_t color)
{
    if (x > 383 || y > 215) return;
    while(h--){
        unsigned w2 = w;
        while(w2--) {
            FXCG_drawPixel(x++, y, color);
        }
        x -= w;
        y += 1;
    }
}


void FXCG_drawPixel(int x, int y, color_t color)
{
    if (x < 0 || y < 0) return;
    if (x > 383 || y > 215) return;
    uint16_t *VRAM = (uint16_t *)GetVRAMAddress();
    if (is_half_opacity_enabled == true) {
        if (x & 1 && y & 1) return;
        if (!(x & 1) && !(y & 1)) return;
    }
    VRAM[x + y * 384] = color;
}


void FXCG_drawImage(uint16_t* data, int x, int y, int w, int h)
{
    uint16_t *VRAM = (uint16_t*)GetVRAMAddress();
    VRAM += 384*y + x;
    for(int j=y; j<y+h; j++) {
        for(int i=x; i<x+w; i++) {
            *(VRAM++) = *(data++);
        }
        VRAM += 384 - w;
    }
}


void FXCG_drawImageMaskedAlpha(uint16_t* data, int x, int y, int w, int h, color_t maskColor, int alpha)
{
    uint16_t* VRAM = (uint16_t*)GetVRAMAddress();
    VRAM += LCD_WIDTH_PX*y + x;
    for(int j=y; j<y+h; j++) {
        for(int i=x; i<x+w; i++) {
            if (*data != maskColor) {
                *(VRAM) = (uint16_t)((((int)(*data & 0xf81f) * alpha + (int)(*VRAM & 0xf81f) * (32-alpha) + 0x8010) >> 5) & 0xf81f) |
                (uint16_t)((((int)(*data & 0x07e0) * alpha + (int)(*VRAM & 0x07e0) * (32-alpha) + 0x0400) >> 6) & 0x07e0);
                VRAM++; data++;
            } else {
                VRAM++;
                data++;
            }
        }
        VRAM += LCD_WIDTH_PX - w;
    }
}


void FXCG_drawImageNbit(const uint8_t* data, int x, int y, int w, int h, color_t* palette, unsigned int bitWidth)
{
    color_t* VRAM = (color_t*) GetVRAMAddress();
    VRAM += (LCD_WIDTH_PX*y + x);
    int offset = 0;
    uint8_t buf = 0;
    for(int j=y; j < y+h; j++) {
        int availbits = 0;
        for(int i=x; i < x+w; i++) {
            if (!availbits) {
                buf = data[offset++];
                availbits = 8;
            }
            uint16_t self = ((uint16_t)buf >> (8-bitWidth));
            *VRAM = palette[(uint16_t)self];
            VRAM++;
            buf <<= bitWidth;
            availbits -= bitWidth;
        }
        VRAM += (LCD_WIDTH_PX - w);
    }
}


void FXCG_drawImageNbitMasked(const uint8_t *data, int x, int y, int w, int h, const color_t* palette, color_t maskColor, unsigned int bitWidth)
{
    color_t* VRAM = (color_t*) GetVRAMAddress();
    VRAM += (LCD_WIDTH_PX*y + x);
    int offset = 0;
    uint8_t buf = 0;
    for(int j=y; j<y+h; j++) {
        int availbits = 0;
        for(int i=x; i<x+w; i++) {
            if (!availbits) {
                buf = data[offset++];
                availbits = 8;
            }
            uint16_t self = ((uint16_t)buf>>(8-bitWidth));
            uint16_t color = palette[self];
            if(color != maskColor) {
                *VRAM = color;
            }
            VRAM++;
            buf <<= bitWidth;
            availbits -= bitWidth;
        }
        VRAM += (LCD_WIDTH_PX - w);
    }
}



