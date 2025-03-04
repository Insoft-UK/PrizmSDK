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

#ifndef key_h
#define key_h

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    F1    = 79, F2       = 69, F3     = 59, F4    = 49, F5     = 39, F6    = 29,
    Shift = 78, Optn     = 68, Vars   = 58, Menu  = 48, Left   = 38, Up    = 28,
    Alpha = 77, Sq       = 67, Power  = 57, Exit  = 47, Down   = 37, Right = 27,
    XAngT = 76, Log      = 66, Ln     = 56, Sin   = 46, Cos    = 36, Tan   = 26,
    Abc   = 75, SwapDisp = 65, CubeRt = 55, InvX  = 45, Comma  = 35, Ans   = 25,
    K7    = 74, K8       = 64, K9     = 54, Del   = 44, On     = 10,
    K4    = 73, K5       = 63, K6     = 53, Mult  = 43, Div    = 33,
    K1    = 72, K2       = 62, K3     = 52, Add   = 42, Minus  = 32,
    K0    = 71, Dot      = 61, Exp    = 51, Neg   = 41, Return = 31, NONE  = 0
} FXCG_KeyCode;

uint16_t* reg(void);

typedef uint8_t FXCG_TKeyCode;

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     @brief    Reset key states.
     */
    void FXCG_keyReset(void);
    
    /**
     @brief    Takes a key reading of the keyboard register.
     */
    void FXCG_keyUpdate(void);
    
    /**
     @brief    Returns key code of key that is being held down.
     
     keyUpdate required before using this function.
     */
    uint16_t *FXCG_keyHeld(void);
    
    /**
     @brief    Returns key code of key that has been pressed down.
     
     keyUpdate required before using this function.
     */
    uint16_t *FXCG_keyPressed(void);
    
    /**
     @brief    Returns true if key has is being held down.
     @param    code  The fx-CGxx key code.
     
     keyUpdate not required.
     */
    bool FXCG_isKeyHeld(FXCG_TKeyCode code);
    
    /**
     @brief    Returns true if key has just been pressed.
     @param    code  The fx-CGxx key code.
     
     keyUpdate required before using this function.
     */
    bool FXCG_isKeyPressed(FXCG_TKeyCode code);
    
    /**
     @brief    Returns true if key has just been released
     @param    code  The fx-CGxx key code.
     
     keyUpdate required before using this function.
     */
    bool FXCG_isKeyReleased(FXCG_TKeyCode code);
    
#ifdef __cplusplus
}
#endif

#endif /* key_h */
