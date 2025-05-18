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

#include "fxcg.hpp"

#include "bmp.hpp"

#include <stdio.h>
#include <string.h>
#include <display.h>

#include <iomanip>
#include <sstream>
#include <cstdint>

static std::string _bundlePath;
static bmp::TImage _battery, _alpha, _alphaLock, _shift, _clip, _cursor, _menu;

// DRAM is RGB565 regardless of VRAM RGB565 or RGB111
static color_t _DD[396 * 224];

static TColorMode _fxCG_DDRegisterB = ColorModeFull;
static TStatusArea _fxCG_0x8804F5EC = StatusAreaDisable; // System variable that enables or disables the status area.
static unsigned short _fxCG_SAF = SAF_BATTERY;
static unsigned char _fxCG_0xA44B0000[12] = {0,0,0,0,0,0,0,0,0,0,0,0}; // keyboard_register

int _fxCG_KMI_Shift = 0;
int _fxCG_KMI_Alpha = 0;
int _fxCG_KMI_Clip = 0;

void fxCG_Init(const char *bundlePath)
{
    _bundlePath = std::string(bundlePath);
    
    _battery = bmp::load((_bundlePath + "/Battery.bmp").c_str());
    _alpha = bmp::load((_bundlePath + "/Alpha.bmp").c_str());
    _alphaLock = bmp::load((_bundlePath + "/AlphaLock.bmp").c_str());
    _shift = bmp::load((_bundlePath + "/Shift.bmp").c_str());
    _clip = bmp::load((_bundlePath + "/Clip.bmp").c_str());
    _cursor = bmp::load((_bundlePath + "/Cursor.bmp").c_str());
    _menu = bmp::load((_bundlePath + "/Menu.bmp").c_str());
}

const char *fxCG_GetBundlePath(void)
{
    return _bundlePath.c_str();
}

void *fxCG_GetDDAddress(void)
{
    return (void *)_DD;
}

uint8_t *fxCG_GetKeyRegAddress(void)
{
    return _fxCG_0xA44B0000;
}

TColorMode fxCG_GetDDRegisterB(void)
{
    return _fxCG_DDRegisterB;
}

void fxCG_SetDDRegisterB(TColorMode colorMode)
{
    _fxCG_DDRegisterB = colorMode;
}

TStatusArea fxCG_GetSAS(void)
{
    return _fxCG_0x8804F5EC;
}

void fxCG_SetSAS(TStatusArea opt)
{
    _fxCG_0x8804F5EC = opt;
}

uint16_t fxCG_GetSAF(void)
{
    return _fxCG_SAF;
}

void fxCG_SetSAF(uint16_t flags)
{
    _fxCG_SAF = flags;
}

void fxCG_KeyDown(int keyCode) {
    int row = keyCode % 10;
    int col = keyCode / 10 - 1;
    
    int bit = 7 - col;
    
    _fxCG_0xA44B0000[row] |= 1 << bit;
    
    switch (keyCode) {
        case K_Shift:
            _fxCG_KMI_Shift = !_fxCG_KMI_Shift;
            _fxCG_KMI_Alpha = _fxCG_KMI_Clip = 0;
            break;
            
        case K_Alpha:
            _fxCG_KMI_Alpha = !_fxCG_KMI_Alpha;
            if (_fxCG_KMI_Alpha == 0) _fxCG_KMI_Shift = 0;
            _fxCG_KMI_Clip = 0;
            break;
            
        case K_8:
            _fxCG_KMI_Clip = 1;
            break;
            
        case K_Menu:
            fxCG_DrawImageToDD((uint16_t *)_menu.bytes.data(), 0, 0, _menu.width, _menu.height);
            break;
            
        default:
            if (_fxCG_KMI_Shift && _fxCG_KMI_Alpha) break;
            break;
    }
    
    DisplayStatusArea();
}

void fxCG_KeyUp(int keyCode) {
    int row = keyCode % 10;
    int col = keyCode / 10 - 1;
    
    int bit = 7 - col;
    
    _fxCG_0xA44B0000[row] &= ~(1 << bit);
}

void fxCG_KeyClearAll(void) {
    for (int i = 0; i < 10; i++) {
        _fxCG_0xA44B0000[i] = 0;
    }
}

color_t fxCG_TextColorToColor(char textColor)
{
    static color_t color[] = {
        0x0000, 0x001F, 0x07E0, 0x07FF, 0xF800, 0xF81F, 0xFFE0, 0xFFFF
    };
    return color[textColor & 0x7];
}

void fxCG_DrawImageToVRAM(uint16_t *data, int x, int y, int w, int h)
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

void fxCG_DrawImageToDD(uint16_t *data, int x, int y, int w, int h)
{
    uint16_t *DD = (uint16_t *)fxCG_GetDDAddress();
    DD += 396*y + x + 6;
    for(int j=y; j<y+h; j++) {
        for(int i=x; i<x+w; i++) {
            *(DD++) = *(data++);
        }
        DD += 396 - w;
    }
}

void fxCG_DrawBattery(int level)
{
    fxCG_DrawImageToVRAM((uint16_t *)_battery.bytes.data() + (352 * level), 0, 0, 16, 22);
}



void fxCG_DrawKeyboardModifierIndicator(TKeyboardModifierIndicator indicator)
{
    switch (indicator) {
        case KeyboardModifierIndicatorShift:
            fxCG_DrawImageToVRAM((uint16_t *)_shift.bytes.data(), 16, 0, 22, 22);
            break;
            
        case KeyboardModifierIndicatorAlpha:
            fxCG_DrawImageToVRAM((uint16_t *)_alpha.bytes.data(), 16, 0, 22, 22);
            break;
            
        case KeyboardModifierIndicatorAlphaLock:
            fxCG_DrawImageToVRAM((uint16_t *)_alphaLock.bytes.data(), 16, 0, 22, 22);
            break;
            
        case KeyboardModifierIndicatorClip:
            fxCG_DrawImageToVRAM((uint16_t *)_clip.bytes.data(), 16, 0, 22, 22);
            break;
            
        default:
            break;
    }
}

void fxCG_DrawCursor(void)
{
    TCursorSettings cursorSettings;
    Cursor_GetSettings(&cursorSettings);
    
    if (!cursorSettings._unknown) return;
    
    static int frm = 0;
    if (frm++ & 0x40) return;
  
    int x,y;
    x = 6 + cursorSettings.cursorX * _cursor.width;
    y = cursorSettings.cursorY * _cursor.height;
    
    
        switch (cursorSettings.cursorFlashFlag) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 8:
            case 11:
                fxCG_DrawImageToDD((uint16_t *)_cursor.bytes.data(), cursorSettings.cursorX * 16, cursorSettings.cursorY * 22, 16, 22);
                break;
                
            case 12:
                fxCG_DrawImageToDD((uint16_t *)_cursor.bytes.data() + 352, cursorSettings.cursorX * 16, cursorSettings.cursorY * 22, 16, 22);
                break;
                
            default:
                fxCG_DrawImageToDD((uint16_t *)_cursor.bytes.data() + 704, cursorSettings.cursorX * 16, cursorSettings.cursorY * 22, 16, 22);
                break;
        }
}

