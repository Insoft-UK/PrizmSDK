// MIT License
// 
// Copyright (c) 2025 insoft
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

#include "base.h"

#include <stdio.h>
#include <stdint.h>

#include "graphics.h"
#include "key.h"

void AddIn_quit(void)
{
    FrameColor(FrameModeColor, COLOR_WHITE);
    DrawFrame(COLOR_WHITE);
    Bdisp_EnableColor(ColorModeIndex);
}

void AddIn_setup(void)
{
    SetQuitHandler(AddIn_quit);
    
    FrameColor(FrameModeColor, COLOR_WHITE);
    DrawFrame(COLOR_WHITE);
    
    Bdisp_AllClr_VRAM();
    Bdisp_EnableColor(ColorModeFull);
    
    char indexColor = TEXT_COLOR_WHITE;
    DefineStatusAreaFlags(3, SAF_BATTERY | SAF_TEXT | SAF_GLYPH | SAF_ALPHA_SHIFT, &indexColor, &indexColor);
    EnableStatusArea(StatusAreaEnabled);
}

int AddIn_main(int argc, const char * argv[])
{
    int key;
    int row, col;
    unsigned short keycode = 0;
    
    TScrollbar scrollbar = {
        .I1 = 0, .I5 = 0,
        .barHeight = 150, .barWidth = 6,
        .barTop = 0, .barLeft = 0,
        .indicatorHeight = 50,
        .indicatorMaximum = 100,
        .indicatorPosition = 5
    };
    
    AddIn_setup();

    /*
     The GetKey or GetKeyWait_OS function can interrupt add-in execution
     and transfer control back to the OS. When a new add-in is launched, the
     currently running one is discarded, and the new add-in is loaded and
     executed.
     
     You should *NEVER* exit main in an add-in. If you do, running the
     add-in again (until another add-in is executed) will result in a blank
     screen before returning to the MENU screen. To prevent this, it’s best
     to use a while loop to keep the add-in running.
     */
    
    unsigned char str[256];
    
    TBdispFillArea fillArea = {
        .mode = AreaModeColor,
        .x1 = 0,
        .y1 = 0,
        .x2 = 383,
        .y2 = 239
    };
    
    FXCG_keyReset();
    
    while (true) {
        Bdisp_AreaClr(&fillArea, TargetVRAM, COLOR_WHITE);
        
        Scrollbar(&scrollbar);
        DisplayStatusArea();
        
        // Display the keycode in HEX
        WordToHex((unsigned short)keycode, str);
        Bdisp_MMPrint(140, 0, str, 0, 0xFFFFFFFF, 0, 0, COLOR_BLACK, COLOR_WHITE, 1, 0);
        
        
        Bdisp_PutDisp_DD();
      
        FXCG_keyUpdate();
        if (FXCG_isKeyPressed(K_Menu)) {
            GetKey(&key);
        }
        
        
        
        if (FXCG_isKeyPressed(K_Left) && scrollbar.barWidth > 6) scrollbar.barWidth--;
        if (FXCG_isKeyPressed(K_Right)) scrollbar.barWidth++;
//        if (key.pressed == KEY_PRGM_UP && scrollbar.indicatorPosition > 0) scrollbar.indicatorPosition--;
//        if (key.pressed == KEY_PRGM_DOWN && scrollbar.indicatorPosition < scrollbar.indicatorMaximum) scrollbar.indicatorPosition++;
//        if (key.pressed == KEY_PRGM_F1 && scrollbar.indicatorMaximum > 1) scrollbar.indicatorMaximum--;
//        if (key.pressed == KEY_PRGM_F6) scrollbar.indicatorMaximum++;
//        
//        if (key.pressed == KEY_PRGM_F2 && scrollbar.indicatorHeight > 1) scrollbar.indicatorHeight--;
//        if (key.pressed == KEY_PRGM_F5) scrollbar.indicatorHeight++;
        
        if (scrollbar.indicatorPosition > scrollbar.indicatorMaximum) {
            scrollbar.indicatorPosition = scrollbar.indicatorMaximum;
        }
        
        OS_InnerWait_ms(10);
    }
    
    return 0;
}

