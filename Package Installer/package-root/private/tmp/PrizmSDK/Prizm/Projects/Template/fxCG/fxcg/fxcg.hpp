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

#pragma once

#include <stdint.h>

#include <display.h>
#include <keyboard.h>

//typedef NS_ENUM(UInt8, FXCG_KeyCode){


extern int _fxCG_KMI_Shift;
extern int _fxCG_KMI_Alpha;
extern int _fxCG_KMI_Clip;

typedef enum {
    KeyboardModifierIndicatorShift,
    KeyboardModifierIndicatorAlpha,
    KeyboardModifierIndicatorAlphaLock,
    KeyboardModifierIndicatorClip
} TKeyboardModifierIndicator;


#ifdef __cplusplus
extern "C" {
#endif
    
    void fxCG_Init(const char *bundlePath);
    const char *fxCG_GetBundlePath(void);
    void *fxCG_GetDDAddress(void);
    uint8_t *fxCG_GetKeyRegAddress(void);
    
    TStatusArea fxCG_GetSAS(void);
    void fxCG_SetSAS(TStatusArea opt);
    
    TColorMode fxCG_GetDDRegisterB(void);
    void fxCG_SetDDRegisterB(TColorMode colorMode);
    
    uint16_t fxCG_GetSAF(void);
    void fxCG_SetSAF(uint16_t flags);
    
    void fxCG_KeyDown(int keyCode);
    void fxCG_KeyUp(int keyCode);
    void fxCG_KeyClearAll(void);
    
    void *fxCG_GetDDAddress(void);
    color_t fxCG_TextColorToColor(char textColor);
    void fxCG_DrawImageToVRAM(uint16_t* data, int x, int y, int w, int h);
    void fxCG_DrawImageToDD(uint16_t* data, int x, int y, int w, int h);
    
    void fxCG_DrawBattery(int level);
    void fxCG_DrawKeyboardModifierIndicator(TKeyboardModifierIndicator indicator);
    
    void fxCG_DrawCursor(void);
    
#ifdef __cplusplus
}
#endif
