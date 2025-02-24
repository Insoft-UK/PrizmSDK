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

#include "key.h"


/*
 The Casio fx-CG50, like many calculators and embedded systems, handles key presses
 at a low level through direct memory access (DMA) to a specific memory-mapped register.
 Each key on the calculator corresponds to a specific bit or set of bits within this
 register.
 
 When a key is pressed, the corresponding bit or bits in the register are set
 to indicate the key press event. Conversely, when a key is released, the corresponding
 bit or bits are cleared to indicate the key release event.
 
                                                                    Row : 16-bit (reg 0-4)
     +-----------------------------------------------------------------------------------+
     |   [F1]      [F2]      [F3]      [F4]      [F5]      [F6]                          | 9 = (4)
     |                                                                                   |
     |   [SHIFT]   [OPTN]    [VARS]    [MENU]    [◂]       [▴]                           | 8 = (4)
     |                                                                                   |
     |   [ALPHA]   [𝓍²]      [x√]      [EXIT]    [▾]       [▸]                           | 7 = (3)
     |                                                                                   |
     |   [X,T,θ]   [log]     [ln]      [sin]     [cos]     [tan]                         | 6 = (3)
     |                                                                                   |
     |   [ab/c]    [S↔D]     [(]       [)]       [,]       [→]                           | 5 = (2)
     |                                                                                   |
     |   [7]       [8]       [9]       [DEL]                                             | 4 = (2)
     |                                                                                   |
     |   [4]       [5]       [6]       [×]       [÷]                                     | 3 = (1)
     |                                                                                   |
     |   [1]       [2]       [3]       [+]       [-]                                     | 2 = (1)
     |                                                                                   |
     |   [0]       [.]       [EXP]     [(‒)]     [EXE]                                   | 1 = (0)
     |                                                                                   |
     |                                                               [AC/ON]   [RESET]   | 0 = (0)
     +----------------------------------------------------------------------------------+
  Col    7         6         5         4         3         2         1         0
 
 *Bit    8         9         10        11        12        13        14       15
**Bit    0         1         2         3         4         5         6        7
 
 * When Row is odd
** When Row is even
 
 
 */

#define FXCG_KEY_REG 0xA44B0000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static const uint16_t *_keyboardRegister = (uint16_t *)FXCG_KEY_REG;

static struct {
    uint16_t held[5];
    uint16_t last[5];   // Key/s that were last held down.
    uint16_t pressed[5];
    uint16_t released[5];
} _key = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
};

uint16_t* FXCG_keyReg(void)
{
    return (uint16_t *)FXCG_KEY_REG;
}

void FXCG_keyUpdate(void)
{
    for (int i=0; i<5; i++) {
        _key.held[i] = _keyboardRegister[i];
        
        _key.pressed[i] = ~_key.last[i] & _key.held[i];
        _key.released[i] = _key.last[i] & ~_key.held[i];
        
        _key.last[i] = _key.held[i];
    }
}

void FXCG_keyReset(void)
{
    for (int i=0; i<5; i++) {
        _key.held[i] = 0;
        _key.last[i] = 0;
        _key.pressed[i] = 0;
        _key.released[i] = 0;
    }
}

//static uint16_t FXCG_keyCode(const uint16_t* reg)
//{
//    for (int row = 0; row < 9; row++) {
//        int word = row >> 1;
//        if (!reg[word]) continue;
//        
//        for (int col = 0; col < 8; col++) {
//            int bit = col + 8 * ( row & 1 );
//            if (reg[word] & (1 << bit))
//                return (uint16_t)((col + 1) * 10 + row);
//        }
//    }
//
//    return 0;
//}

uint16_t *FXCG_keyHeld(void)
{
    return _key.held;
}

uint16_t *FXCG_keyPessed(void)
{
    return _key.pressed;
}

/**
 @brief    Returns true if key has is being hold down.
 @param    keycode  The fx-CGxx key code.
 @param    data The status data of the keyboard.
 */
static bool FXCG_isKeyHold(FXCG_TKeyCode code, const uint16_t *data)
{
    int row = code % 10;
    int col = code / 10 - 1;
    
    int word = row >> 1;
    int bit = col + 8 * ( row & 1 );
    
    return (0 != (data[word] & 1 << bit));
}


bool FXCG_isKeyHeld(FXCG_TKeyCode code)
{
    return FXCG_isKeyHold(code, _keyboardRegister);
}


bool FXCG_isKeyPressed(FXCG_TKeyCode code)
{
    return FXCG_isKeyHold(code, _key.pressed);
}


bool FXCG_isKeyReleased(FXCG_TKeyCode code)
{
    return FXCG_isKeyHold(code, _key.released);
}
