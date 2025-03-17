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

#ifndef fxcg_h
#define fxcg_h

#include <stdint.h>
#include <stdbool.h>

#include <display.h>
#include <keyboard.h>

#define FXCG_KEY_REG _fxCG_0xA44B0000
#define FXCG_DD_REG  _fxCG_DDRegister

typedef struct {
    unsigned short B : 1;
} fxCG_DDRegister;

extern fxCG_DDRegister _fxCG_DDRegister;

extern int _fxCG_KMI_Shift;
extern int _fxCG_KMI_Alpha;
extern int _fxCG_KMI_Clip;

extern int _fxCG_StatusArea;
extern unsigned short _fxCG_SAF;

extern unsigned char _fxCG_0xA44B0000[12];

#ifdef __cplusplus
extern "C" {
#endif
    
    void *GetDDAddress(void);
    uint16_t fxCG_SAF(void);
    
#ifdef __cplusplus
}
#endif

#endif /* fxcg_h */
