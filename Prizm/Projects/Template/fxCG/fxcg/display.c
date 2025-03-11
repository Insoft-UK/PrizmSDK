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

#include <fxcg/display.h>
#include <string.h>

extern int _fxCG_KMI_Shift;
extern int _fxCG_KMI_Alpha;
extern int _fxCG_KMI_Clip;

static struct {
    unsigned short B : 1;
} _fxCG_DDRegister = {
    .B = 1 /// 1 = Enable 8 color mode
};

static struct {
    int x;  /// x Must be in range of [0,21]
    int y;  /// y Must be in range
} _fxCG_Cursor = {
    .x = 0, .y = 0
};

int _fxCG_StatusArea = 1;
static unsigned short _fxCG_SAF = SAF_BATTERY | SAF_ALPHA_SHIFT;
static char _fxCG_StatusArea_ColorA = TEXT_COLOR_WHITE, _fxCG_StatusArea_ColorB = TEXT_COLOR_WHITE;

// DRAM is RGB565 regardless of VRAM RGB565 or RGB111
static color_t _DD[396 * 224];
static color_t _VRAM[LCD_WIDTH_PX * LCD_HEIGHT_PX];
static color_t _SecondaryVRAM[LCD_WIDTH_PX * LCD_HEIGHT_PX];

static unsigned short _fxCG_0xFD801460 = 0xFFFF;
static int _fxCG_FrameMode = 0;


// MARK: -

typedef struct {
    unsigned short offset;   // Offset address to the bitmap data for this glypth.
    unsigned char  width;    // Bitmap dimensions in pixels.
    unsigned char  height;   // Bitmap dimensions in pixels.
    unsigned char  xAdvance; // Distance to advance cursor in the x-axis.
    char   dX;       // Used to position the glyph within the cell in the horizontal direction.
    char   dY;       // Distance from the baseline of the character to the top of the glyph.
} GFXglyph;

typedef struct {
    unsigned char   *bitmap;   // Bitmap data array.
    GFXglyph  *glyph;    // Glyph data.
    unsigned char    first;    // The first ASCII value of your first character.
    unsigned char    last;     // The last ASCII value of your last character.
    unsigned char    yAdvance; // Newline distance in the y-axis.
} GFXfont;

typedef enum FontSize{
    FontSize24pt,
    FontSize18pt,
    FontSize16pt,
    FontSize10pt
} TFontSize;

void *GetDDAddress(void)
{
    return _DD;
}

#include "CASIO/fxCG50_10pt0xXX.h"
#include "CASIO/fxCG50_10pt0x7FXX.h"
#include "CASIO/fxCG50_10pt0xE5XX.h"
#include "CASIO/fxCG50_10pt0xE6XX.h"
#include "CASIO/fxCG50_16pt0xXX.h"
#include "CASIO/fxCG50_16pt0xE5XX.h"
#include "CASIO/fxCG50_16pt0xE6XX.h"
#include "CASIO/fxCG50_18pt0xXX.h"
#include "CASIO/fxCG50_18pt0x7FXX.h"
#include "CASIO/fxCG50_18pt0xE5XX.h"
#include "CASIO/fxCG50_18pt0xE6XX.h"
#include "CASIO/fxCG50_24pt0xXX.h"
#include "CASIO/fxCG50_24pt0x7FXX.h"
#include "CASIO/fxCG50_24pt0xE5XX.h"
#include "CASIO/fxCG50_24pt0xE6XX.h"


unsigned short fxCG_SAF(void)
{
    return _fxCG_SAF;
}

static GFXfont Get24ptFont(unsigned char extendedCode)
{
    switch (extendedCode) {
        case 0x7F:
            return fxCG50_24pt0x7FXX;
            break;
            
        case 0xE5:
            return fxCG50_24pt0xE5XX;
            break;
            
        case 0xE6:
            return fxCG50_24pt0xE6XX;
            break;
            
        default:
            return fxCG50_24pt0xXX;
            break;
    }
}

static GFXfont Get18ptFont(unsigned char extendedCode)
{
    switch (extendedCode) {
        case 0x7F:
            return fxCG50_18pt0x7FXX;
            break;
            
        case 0xE5:
            return fxCG50_18pt0xE5XX;
            break;
            
        case 0xE6:
            return fxCG50_18pt0xE6XX;
            break;
            
        default:
            return fxCG50_18pt0xXX;
            break;
    }
}

static GFXfont Get16ptFont(unsigned char extendedCode)
{
    switch (extendedCode) {
        case 0xE5:
            return fxCG50_16pt0xE5XX;
            break;
            
        case 0xE6:
            return fxCG50_16pt0xE6XX;
            break;
            
        default:
            return fxCG50_16pt0xXX;
            break;
    }
}

static GFXfont Get10ptFont(unsigned char extendedCode)
{
    switch (extendedCode) {
        case 0x7F:
            return fxCG50_10pt0x7FXX;
            break;
            
        case 0xE5:
            return fxCG50_10pt0xE5XX;
            break;
            
        case 0xE6:
            return fxCG50_10pt0xE6XX;
            break;
            
        default:
            return fxCG50_10pt0xXX;
            break;
    }
}

static GFXfont GetFont(TFontSize size, unsigned char extendedCode)
{
    switch (size) {
        case FontSize24pt:
            return Get24ptFont(extendedCode);
            break;
            
        case FontSize18pt:
            return Get18ptFont(extendedCode);
            break;
            
        case FontSize16pt:
            return Get16ptFont(extendedCode);
            break;
            
        case FontSize10pt:
            return Get10ptFont(extendedCode);
            break;
    }
}

static int DrawGFXGlyph(short x, short y, unsigned char c, unsigned short color, GFXfont font)
{
    if (c < font.first || c > font.last) {
        return 0;
    }
    
    GFXglyph *glyph = &font.glyph[(int)c - font.first];
    
    int height = glyph->height;
    int width = glyph->width;
   
    x += glyph->dX;
    y += glyph->dY + font.yAdvance;
    
    unsigned char *bitmap = font.bitmap + glyph->offset;
    unsigned char bitPosition = 1 << 7;
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

static int DrawString(short x, short y, const char *s, unsigned short color, GFXfont font)
{
    unsigned char *c = (unsigned char *)s;
    
    while (*c) {
        x += DrawGFXGlyph(x, y, (unsigned char)*c, color, font);
        c++;
    }
    return x;
}

static int DrawGlyph(int x, int y, unsigned char *c, unsigned short color, TFontSize size)
{
    GFXfont font;
    
    if (*c == 0x7F || *c == 0xE5 || *c == 0xE6) {
        font = GetFont(size, *c++);
    } else {
        font = GetFont(size, 0);
    }
    
    return DrawGFXGlyph(x, y, *c, color, font);
}

static int DrawText(int x, int y, const char *s, unsigned short color, TFontSize size)
{
    unsigned char *c = (unsigned char *)s;
    GFXfont font;
    
    while (*c) {
        if (*c == 0x7F || *c == 0xE5 || *c == 0xE6) {
            font = GetFont(size, *c++);
        } else {
            font = GetFont(size, 0);
        }
        x += DrawGFXGlyph(x, y, *c, color, font);
        c++;
    }
    return x;
    
}

static int GetTextSize(unsigned char *c, TFontSize size)
{
    GFXfont font = GetFont(size, 0);
    int width = 0;
    while (*c) {
        if (*c == 0x7F || *c == 0xE5 || *c == 0xE6)
            c++;
        if (*c < font.first || *c > font.last)
            continue;
        GFXglyph *glyph = &font.glyph[(int)*c - font.first];
        width += glyph->xAdvance;
        c++;
    }
    return width;
}


static int fxCG_Range(int min, int max, int value) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

color_t convertTextColorToRGB565(char ink)
{
    static color_t color[] = {
        0x0000, 0x001F, 0x07E0, 0x07FF, 0xF800, 0xF81F, 0xFFE0, 0xFFFF
    };
    return color[ink & 0x7];
}

// MARK: - fxcg

void Bdisp_AreaClr(TBdispFillArea *area, TTarget target, color_t color)
{
    if (area->mode == AreaModeWhite) color = 0xFFFF;
    
    for (int y = area->y1; y <= area->y2 && y < LCD_HEIGHT_PX - 1; y++)
    {
        if (y < 0) continue;
        for (int x = area->x1; x <= area->x2 && x < LCD_WIDTH_PX - 1; x++)
        {
            if (x < 0) continue;
            if (x > 384) break;
            if (target == TargetVRAM) {
                _VRAM[x + y * 384] = color;
            } else {
                _DD[x + 6 + y * 396] = color;
            }
        }
    }
}

void Bdisp_EnableColor(TColorMode mode)
{
    _fxCG_DDRegister.B = mode == ColorModeFull ? 0 : 1;
}

void DrawFrame(int color)
{
    _fxCG_0xFD801460 = color;
    
    for (int y = 0; y < 224; y++)
    {
        for (int x = 0; x < 396; x++)
        {
            if (x >= 6 && x < LCD_WIDTH_PX && y < LCD_HEIGHT_PX) continue;
            _VRAM[x + y * 396] = (unsigned short)color;
        }
    }
}

color_t FrameColor(int mode, color_t color)
{
    switch (mode) {
        case 0:
            _fxCG_0xFD801460 = 0xFFFF;
            break;
            
        case 1:
            _fxCG_0xFD801460 = color;
            
        default:
            break;
    }
    
    return _fxCG_0xFD801460;
}

void *GetVRAMAddress(void)
{
    return _VRAM;
}

void* GetSecondaryVRAMAddress(void)
{
    return _SecondaryVRAM;
}

void Bdisp_AllClr_VRAM(void)
{
    memset(_VRAM, 255, sizeof(_VRAM));
}

void Bdisp_SetPoint_VRAM( int x, int y, color_t color ) {
    if (x < 0 || x >= LCD_WIDTH_PX || y < 0 || y >= LCD_HEIGHT_PX) return;
    
    unsigned short *VRAM = (unsigned short *)GetVRAMAddress();
    
    if (_fxCG_DDRegister.B != 0) {
        color = convertTextColorToRGB565(color);
    }
    
    VRAM[x + y * LCD_WIDTH_PX] = color;
}

color_t Bdisp_GetPoint_VRAM( int x, int y )
{
    if (x < 0 || x > LCD_WIDTH_PX - 1) return 0xFFFF;
    if (y < 0 || y > LCD_HEIGHT_PX - 1) return 0xFFFF;
    
    color_t* VRAM = (color_t *)GetVRAMAddress();
        return VRAM[x + y * LCD_WIDTH_PX];

}

void SaveVRAM_1(void) {
    unsigned short *src = (unsigned short *)_VRAM;
    unsigned short *dest = (unsigned short *)GetSecondaryVRAMAddress();
    
    size_t length = LCD_WIDTH_PX * LCD_HEIGHT_PX;
    do {
        *dest++ = *src++;
    } while (--length);
}

void LoadVRAM_1(void) {
    unsigned short *src = (unsigned short *)GetSecondaryVRAMAddress();
    unsigned short *dest = (unsigned short *)_VRAM;
    
    size_t length = LCD_WIDTH_PX * LCD_HEIGHT_PX;
    do {
        *dest++ = *src++;
    } while (--length);
}

void Bdisp_Fill_VRAM(int color, int mode)
{
    if (mode == 0 || mode > 4) return;
    
    TBdispFillArea fillAria = {
        0, 0, 383, 215, 1
    };
    
    switch (mode) {
        case 1:
            fillAria.y1 += 24;
            break;
            
        case 2:
            fillAria.y1 += 24;
            fillAria.y2 -= 20;
            break;
            
        default:
            break;
    }
    
    Bdisp_AreaClr(&fillAria, 0, color);
}

void Bdisp_Rectangle(int x1, int y1, int x2, int y2, char color)
{
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 > 383) x2 = 383;
    if (y2 > 191) y2 = 191;
    
    if (x1 >= x2 || y1 >= y2) return;
    
    y1 += 24;
    y2 += 24;
    
    for (int x = x1; x <= x2; x++) {
        _VRAM[x + y1 * LCD_WIDTH_PX] = convertTextColorToRGB565(color);
        _VRAM[x + y2 * LCD_WIDTH_PX] = convertTextColorToRGB565(color);
    }
    
    for (int y = y1; y <= y2; y++) {
        _VRAM[x1 + y * LCD_WIDTH_PX] = convertTextColorToRGB565(color);
        _VRAM[x2 + y * LCD_WIDTH_PX] = convertTextColorToRGB565(color);
    }
}

// MARK: - DD Display Manipulating Syscalls:

void Bdisp_PutDisp_DD(void) {
    DisplayStatusArea();
    
    for (int y = 0; y < 240; y++) {
        for (int x = 0; x < 396; x++) {
            if (y >= LCD_HEIGHT_PX || (x < 6 || x >= 390)) {
                _DD[x + y * 396] = _fxCG_0xFD801460;
                continue;
            }
            _DD[x + y * 396] = _VRAM[x - 6 + y * 384];
        }
    }
}


void Bdisp_PutDisp_DD_stripe(int y1, int y2)
{
    unsigned short color;
    
    for (int y = y1; y <= y2; y++) {
        for (int x = 0; x < LCD_WIDTH_PX; x++) {
            color = Bdisp_GetPoint_VRAM(x, y);
            Bdisp_SetPoint_DD(6 + x, y, color);
        }
    }
}

void Bdisp_SetPoint_DD( int x, int y, int color ) {
    if (x < 0 || x >= LCD_WIDTH_PX || y < 0 || y >= LCD_HEIGHT_PX) return;
    _DD[6 + x + y * 396] = (unsigned short)color;
}

unsigned short Bdisp_GetPoint_DD_Workbench(int x, int y)
{
    return Bdisp_GetPoint_DD(x, y + 24);
}
unsigned short Bdisp_GetPoint_DD(int x, int y)
{
    if (x < 0 || x >= LCD_WIDTH_PX || y < 0 || y >= LCD_HEIGHT_PX) return 0;
    return _DD[6 + x + y * 396];
}
void DirectDrawRectangle( int x1, int y1, int x2, int y2, unsigned short color )
{
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 > 395) x2 = 395;
    if (y2 > 223) y2 = 223;
    
    if (x1 >= x2 || y1 >= y2) return;
    
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            _DD[x + y * 396] = color;
        }
    }
}

// MARK: - Cursor manipulating syscalls:

int locate_OS( int x, int y )
{
    if (x < 1 || x > 21) return 0;
    if (y < 1 || y > 8) return 0;
    _fxCG_Cursor.x = x;
    _fxCG_Cursor.y = y;
    
    return 1;
}



// MARK: - Character printing syscalls:

void PrintXY( int x, int y, const char *string, int mode, int color ) {
    
    PrintCXY(x, y, string + 2, mode, 0, color, Bdisp_GetPoint_VRAM(x, y), 0, 0);
}

void PrintCXY( int x, int y, const char *text, int mode, int P5, int color, int bgcolor, int P8, int P9 )
{
    y += 24;
    if (mode & 0x01) {
        unsigned short tmp = color;
        color = bgcolor;
        bgcolor = tmp;
    }
    
    TBdispFillArea area = {
        .x1 = x, .y1 = y, .x2 = x + GetTextSize((unsigned char *)text, FontSize24pt) - 1, .y2 = y + 23
    };
    Bdisp_AreaClr(&area, 0x01, bgcolor);
    DrawText(x, y, text, color, FontSize24pt);
}

void PrintGlyph(int x, int y, unsigned char *glyph, int mode_flags, int color, int bgcolor, int P7)
{
    
    if (!(mode_flags & 0x20)) {
        TBdispFillArea area;
    
        area.mode = AreaModeColor;
        area.x1 = x;
        area.y1 = y;
        area.x2 = x + 17;
        area.y2 = y + 23;
        Bdisp_AreaClr(&area, 0x01, color);
    }

    if (mode_flags & 1) {
        unsigned short tmp = color;
        color = bgcolor;
        bgcolor = tmp;
    }
    
    DrawGlyph(x, y, glyph, color, FontSize24pt);
    
}

void*GetMiniGlyphPtr( unsigned short mb_glyph_no, unsigned short*glyph_info )
{
    return 0;
}

void PrintMiniGlyph(int x, int y, void *glyph, int mode, int glyph_width, int P6, int P7, int P8, int P9, int color, int bgcolor, int P12)
{
    DrawGlyph(x, y, (unsigned char *)glyph, color, FontSize18pt);
}

void PrintMini( int *x, int *y, const char *MB_string, int mode_flags, unsigned int xlimit, int P6, int P7, int color, int back_color, int writeflag, int P11 )
{
    int xx = *x, yy = *y;
    yy += (mode_flags & 0x40 ? 0 : 24);
    
    if (mode_flags & 0x01) {
        unsigned short tmp = color;
        color = back_color;
        back_color = tmp;
    }
    if (!(mode_flags & 0x2)) {
        TBdispFillArea area = {
            .x1 = *x, .y1 = *y, .x2 = *x + GetTextSize((unsigned char *)MB_string, FontSize24pt) - 1, .y2 = *y + 17
        };
        Bdisp_AreaClr(&area, 0x01, back_color);
    }
    
    if (mode_flags & 0x1) {
        *x = DrawText(xx, yy, MB_string, back_color, FontSize18pt);
        return;
    }
    *x = DrawText(xx, yy, MB_string, color, FontSize18pt);
}

void PrintMiniMini( int *x, int *y, const char *MB_string, int mode1, char color, int mode2 )
{
    unsigned short colors[8] = {0x0000, 0x001F, 0x07E0, 0x07FF, 0xF800, 0xF81F, 0xFFE0, 0xFFFF};
    if (mode1 & 0x1) {
        DrawText(*x, *y + 24, MB_string, colors[color], FontSize10pt);\
        return;
    }
    DrawText(*x, *y + 24, MB_string, colors[color], FontSize10pt);
    
}

void Print_OS(const char* msg, int invers, int zero2)
{
    PrintCXY(_fxCG_Cursor.x * 18, _fxCG_Cursor.y * 24, msg, invers ? 0x01 : 0x00, -1, 0, 0xFFFF, 1, 0);
    _fxCG_Cursor.x = fxCG_Range(0, 20, _fxCG_Cursor.x + 1);
}

void Bdisp_MMPrintRef(int*x, int*y, unsigned char *s, int mode, int xmax, int P6, int P5, int color, int P9, int P10, int P11)
{
    DrawText(*x, *y + 24, (const char*)s, color, FontSize16pt);
}

void Bdisp_MMPrint(int x, int y, unsigned char *s, int mode, int xmax, int P6, int P7, int color, int backcolor, int P10, int P11)
{
    DrawText(x, y + 24, (const char*)s, color, FontSize16pt);
}


// MARK: - Scrollbar

static void drawScrollBarTrack(unsigned short x, unsigned short y, unsigned short w, unsigned short h)
{
    color_t color;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (x == 0 || x == w - 1 || y == 0 || y == h - 1) {
                color = COLOR_BLACK;
            } else {
                color = COLOR_BLUE;
                if (x > 1) {
                    color = COLOR_WHITE;
                    if (y & 1) {
                        if (!(x & 1)) color = COLOR_CYAN;
                    } else {
                        if (x & 1) color = COLOR_CYAN;
                    }
                }
            }
            _VRAM[x + (y + 24) * 384] = color;
        }
    }
}

static void drawScrollBarThumb(unsigned short x, unsigned short y, unsigned short w, unsigned short h)
{
    TBdispFillArea fillArea = {
        .mode = AreaModeColor,
        .x1 = x + 1,
        .y1 = y,
        .x2 = x + w - 2,
        .y2 = y + h - 1
    };
    
    Bdisp_AreaClr(&fillArea, TargetVRAM, COLOR_BLACK);
    
    fillArea.y1++;
    fillArea.x2--;
    fillArea.y2-=2;
    Bdisp_AreaClr(&fillArea, TargetVRAM, COLOR_CYAN);
    
    fillArea.x1++;
    fillArea.y1++;
    Bdisp_AreaClr(&fillArea, TargetVRAM, COLOR_BLUE);
}


void Scrollbar(TScrollbar *scrollbar)
{
    if (scrollbar->indicatorHeight > scrollbar->indicatorMaximum) {
        scrollbar->indicatorHeight = scrollbar->indicatorMaximum;
    }
    
    if (scrollbar->indicatorPosition > scrollbar->indicatorMaximum) {
        scrollbar->indicatorPosition = scrollbar->indicatorMaximum;
    }
    
    drawScrollBarTrack(scrollbar->barLeft, scrollbar->barTop, scrollbar->barWidth, scrollbar->barHeight);


    int indicatorHeight = scrollbar->indicatorHeight * 100 / scrollbar->indicatorMaximum * scrollbar->barHeight / 100;
    
    int thumbY = scrollbar->indicatorPosition * 100 /
             scrollbar->indicatorMaximum *
            (scrollbar->barHeight - indicatorHeight) / 100;
    
    drawScrollBarThumb(scrollbar->barLeft, thumbY + 24, scrollbar->barWidth, indicatorHeight);
}


// MARK: - Status area/header related syscalls:

int DefineStatusAreaFlags( int mode, int flags, char *color1, char *color2 )
{
    
    switch (mode) {
        case 0:
            _fxCG_SAF = 0;
            break;
            
        case 1:
            _fxCG_SAF = 0x303;
            break;
            
        case 2:
            if (*color1) *color1 = _fxCG_StatusArea_ColorA;
            if (*color2) *color2 = _fxCG_StatusArea_ColorB;
            break;
            
        case 3:
            if (*color1) _fxCG_StatusArea_ColorA = *color1;
            if (*color2) _fxCG_StatusArea_ColorB = *color2;
            _fxCG_SAF = flags;
            break;
            
        case 4:
            _fxCG_SAF |= flags;
            break;
            
        case 5:
            _fxCG_SAF &= ~flags;
            break;
            
        default:
            break;
    }
    
    return 0;
}

void DisplayStatusArea(void)
{
    if (_fxCG_StatusArea == 0) return;

    
    for (int y = 0; y <= 22; y++)
    {
        for (int x = 0; x < LCD_WIDTH_PX; x++)
        {
            if (y & 1) {
                _VRAM[x + y * LCD_WIDTH_PX] = (x & 1) ? convertTextColorToRGB565(_fxCG_StatusArea_ColorA) : convertTextColorToRGB565(_fxCG_StatusArea_ColorB);
            } else {
                _VRAM[x + y * LCD_WIDTH_PX] = (x & 1) ? convertTextColorToRGB565(_fxCG_StatusArea_ColorB) : convertTextColorToRGB565(_fxCG_StatusArea_ColorA);
            }
        }
    }
    
    for (int x = 0; x < LCD_WIDTH_PX; x++) {
        _VRAM[x + 22 * LCD_WIDTH_PX] = 0;
    }
    
    if (_fxCG_SAF & SAF_BATTERY)
//        DrawImage(0,0,18,22,Battery);
    
    if (_fxCG_SAF & SAF_ALPHA_SHIFT) {
        if (_fxCG_KMI_Shift) {
            if (_fxCG_KMI_Alpha) {
                //                DrawImage(18,0,24,22,Alpha+24*22*2);
            }
                else {
                    //                DrawImage(18,0,24,22,Shift);
                }
        } else {
            if (_fxCG_KMI_Alpha) {
                //                DrawImage(18,0,24,22,Alpha);
            }
        }
    }
}

void BatteryIcon( unsigned int p1)
{
    
}

void EnableStatusArea(TStatusArea opt)
{
    _fxCG_StatusArea = (opt == StatusAreaDisable) ? 0 : 1;
}

void EnableDisplayHeader(int action, int value)
{
    
}


