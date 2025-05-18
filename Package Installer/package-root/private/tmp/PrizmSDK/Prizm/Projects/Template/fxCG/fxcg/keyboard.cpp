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

#include <string.h>

#include <keyboard.h>
#include <display.h>
#include <system.h>

#include "fxcg.hpp"

// MARK: - Keyboard Functions

int Keyboard_PutKeycode(int x, int y, int keycode)
{
    int bit = 7 - x;
    
    if (keycode)
        fxCG_GetKeyRegAddress()[y] |= 1 << bit;
    else
        fxCG_GetKeyRegAddress()[y] &= ~(1 << bit);
    
    return fxCG_GetKeyRegAddress()[y];
}

int Keyboard_SpyMatrixCode(char *column, char *row)
{
    const unsigned char *reg =  fxCG_GetKeyRegAddress();
    
    for (int r = 0; r < 10; r++) {
        if (!reg[r]) continue;
        
        for (int c = 0; c < 8; c++) {
            int bit = 7 - c;
            if (reg[r] & (1 << bit)) {
                *column = c + 1;
                *row = r;
                return ((c + 1) * 10 + r);
            }
        }
    }
    
    return 0;
}

static const unsigned short CC[] = {
    0x7539,   // F1
    0x753A,   // F2
    0x753B,   // F3
    0x753C,   // F4
    0x753D,   // F5
    0x753E,   // F6
    
    0x7536,   // Shift
    0x7538,   // Optn
    0x7540,   // Vars
    0x7533,   // Menu
    0x7544,   // ◂
    0x7542,   // ▴
    
    0x7537,   // Alpha
    0x008B,   // 𝓍²
    0x00A8,   // ^
    0x7532,   // Exit
    0x7547,   // ▾
    0x7545,   // ▸

    
    0x7531,   // X,θ,T
    0x0095,   // log
    0x0085,   // ln
    0x0081,   // sin
    0x0082,   // cos
    0x0083,   // tan
    
    0x00BB,   // ab/c
    0x755E,   // S↔D
    0x0028,   // (
    0x0029,   // )
    0x002C,   // ,
    0x000E,   // →
    
    0x0037,   // 7
    0x0038,   // 8
    0x0039,   // 9
    0x7549,   // DEL
    0x753F,   // AC/ON
    0x0000,
    
    0x0034,   // 4
    0x0035,   // 5
    0x0036,   // 6
    0x00A9,   // ×
    0x00B9,   // ÷
    0x0000,
    
    0x0031,   // 1
    0x0032,   // 2
    0x0033,   // 3
    0x0089,   // +
    0x0099,   // -
    0x0000,
    
    0x0030,   // 0
    0x002E,   // .
    0x000F,   // EXP
    0x0087,   // (‒)
    0x7534,   // EXE
    0x0000
};

static const unsigned short CC_Shift[] = {
    0x7539,   // F1
    0x753A,   // F2
    0x753B,   // F3
    0x753C,   // F4
    0x753D,   // F5
    0x753E,   // F6
    
    0x7536,   // Shift
    0x756B,   // Optn
    0x754C,   // Vars
    0x7555,   // Menu
    0x7564,   // ◂
    0x756E,   // ▴
    
    0x7537,   // Alpha
    0x0086,   // 𝓍²
    0x00B8,   // ^
    0x754D,   // Exit
    0x7565,   // ▾
    0x756F,   // ▸
    
    0x7F54,   // X,θ,T
    0x00B5,   // log
    0x00A5,   // ln
    0x0091,   // sin
    0x0092,   // cos
    0x0093,   // tan
    
    0x7566,   // ab/c
    0x754A,   // F↔D
    0x0096,   // (
    0x009B,   // )
    0x0000,   // ,
    0x0000,   // →
    
    0x7567,   // 7
    0x7562,   // 8
    0x7554,   // 9
    0x7551,   // DEL
    0x0000,   // AC/ON

    0x7594,   // 4
    0x7595,   // 5
    0x0000,   // 6
    0x007B,   // ×
    0x007D,   // ÷
    
    0x7F51,   // 1
    0x7F40,   // 2
    0x0000,   // 3
    0x005B,   // +
    0x005D,   // -
    
    0x7F50,   // 0
    0x003D,   // .
    0x00D0,   // EXP
    0x00C0,   // (‒)
    0x000D    // EXE
};

void PRGM_GetKey_OS(unsigned char* p)
{
    memcpy(p, fxCG_GetKeyRegAddress(), 12);
}


int GetKey( int *key )
{
    Bdisp_PutDisp_DD();
    DisplayStatusArea();
    
    int keycode;
    *key = 0;
    
    do {
        keycode = PRGM_GetKey();
        OS_InnerWait_ms(5);
    } while (!keycode);
    
    // CR
    int col = 7 - keycode / 10;
    int row = 9 - keycode % 10;
    
    if (_fxCG_KMI_Shift) {
        *key = CC_Shift[row * 6 + col];
    } else {
        *key = CC[row * 6 + col];
    }
    
    for (;PRGM_GetKey(););

    return 0;
}



int GetKeyWait_OS(int *column, int *row, int type_of_waiting, int timeout_period, int menu, unsigned short* keycode )
{
    unsigned int time = 0;
    
    if (timeout_period < 0 || timeout_period > 3600) timeout_period = 0;
    
    do {
        char c, r;
        if (Keyboard_SpyMatrixCode(&c, &r)) {
            *keycode = c << 8 | (r + 1);
            *column = c;
            *row = r + 1;
            return KEYREP_KEYEVENT;
        }
        
        if (type_of_waiting == KEYWAIT_HALTOFF_TIMEROFF && *keycode == 0) return KEYREP_NOEVENT;
        
        OS_InnerWait_ms(5);
        
        if (type_of_waiting == KEYWAIT_HALTON_TIMERON) {
            time++;
            if (time * 100 >= timeout_period) return KEYWAIT_HALTON_TIMERON;
        }
        
    } while (1);
}

int PRGM_GetKey(void)
{
    const unsigned char *reg = fxCG_GetKeyRegAddress();
    
    for (int r = 0; r < 10; r++) {
        if (!reg[r]) continue;
        
        for (int c = 0; c < 8; c++) {
            int bit = 7 - c;
            if (reg[r] & (1 << bit))
                return ((c + 1) * 10 + r);
        }
    }
    
    return 0;
}


