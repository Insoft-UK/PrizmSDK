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

#ifndef __FXCG_KEY_H
#define __FXCG_KEY_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    K_F1    = 79, K_F2       = 69, K_F3     = 59, K_F4    = 49, K_F5     = 39, K_F6    = 29,
    K_Shift = 78, K_Optn     = 68, K_Vars   = 58, K_Menu  = 48, K_Left   = 38, K_Up    = 28,
    K_Alpha = 77, K_Sq       = 67, K_Power  = 57, K_Exit  = 47, K_Down   = 37, K_Right = 27,
    K_XAngT = 76, K_Log      = 66, K_Ln     = 56, K_Sin   = 46, K_Cos    = 36, K_Tan   = 26,
    K_Abc   = 75, K_SwapDisp = 65, K_CubeRt = 55, K_InvX  = 45, K_Comma  = 35, K_Ans   = 25,
    K_7     = 74, K_8        = 64, K_9      = 54, K_Del   = 44, K_On     = 10,
    K_4     = 73, K_5        = 63, K_6      = 53, K_Mult  = 43, K_Div    = 33,
    K_1     = 72, K_2        = 62, K_3      = 52, K_Add   = 42, K_Minus  = 32,
    K_0     = 71, K_Dot      = 61, K_Exp    = 51, K_Neg   = 41, K_Return = 31, K_NONE  = 0
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
    uint8_t *FXCG_keyHeld(void);
    
    /**
     @brief    Returns key code of key that has been pressed down.
     
     keyUpdate required before using this function.
     */
    uint8_t *FXCG_keyPressed(void);
    
    /**
     @brief    Returns true if key has is being held down.
     @param    keycode  The fx-CGxx key code.
     
     keyUpdate not required.
     */
    bool FXCG_isKeyHeld(FXCG_TKeyCode keycode);
    
    /**
     @brief    Returns true if key has just been pressed.
     @param    keycode  The fx-CGxx key code.
     
     keyUpdate required before using this function.
     */
    bool FXCG_isKeyPressed(FXCG_TKeyCode keycode);
    
    /**
     @brief    Returns true if key has just been released
     @param    keycode  The fx-CGxx key code.
     
     keyUpdate required before using this function.
     */
    bool FXCG_isKeyReleased(FXCG_TKeyCode keycode);
    
#ifdef __cplusplus
}
#endif

#endif /* key_h */
