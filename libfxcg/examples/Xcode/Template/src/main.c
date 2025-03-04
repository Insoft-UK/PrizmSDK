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

#ifndef __clang__
#define AddIn_main main
#endif

#include <stdio.h>
#include <stdint.h>

#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/system.h>

#include "graphics.h"
#include "calctype.h"

#include "fonts/consolas.h"
#include "fonts/garamond.h"
#include "fonts/commodore.h"
#include "fonts/arial.h"

#define true 1

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
    
    AddIn_setup();

    /*
     The GetKey function can interrupt add-in execution and transfer
     control back to the OS. When a new add-in is launched, the currently
     running one is discarded, and the new add-in is loaded and executed.
     
     You should *NEVER* exit main in an add-in. If you do, running the
     add-in again (until another add-in is executed) will result in a blank
     screen before returning to the MENU screen. To prevent this, it’s best
     to use a while loop to keep the add-in running.
     */
    
    while (true) {
        CalcType_DrawString(&Garamond, "Press MENU to exit", 0, 22 + 15, COLOR_RED);
        CalcType_DrawString(&Consolas, "You should *NEVER* exit main in an add-in.", 0, 22 + Garamond.height + 9, 0);
        
        char str[225];
        for (int i = 0; i < 224; i++) {
            str[i]=i+33;
        }
        str[224]=0;
        
        int y = 70;
        
        FXCG_drawLine(0, 54, LCD_WIDTH_PX - 1, 54, COLOR_BLACK);
        
        CalcType_DrawString(&Garamond, str, 0, y, 0);
        y += Garamond.height * 3;
        CalcType_DrawString(&Consolas, str, 0, y, 0);
        y += Consolas.height * 2;
        CalcType_DrawString(&Arial, str, 0, y, 0);
        y += Arial.height * 2;
        CalcType_DrawString(&Commodore, str, 0, y, 0);
      
        GetKey(&key);
    }
    
    return 0;
}
