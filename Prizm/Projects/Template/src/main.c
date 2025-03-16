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
    DefineStatusAreaFlags(3, SAF_BATTERY , &indexColor, &indexColor);
    EnableStatusArea(StatusAreaEnabled);
}

int AddIn_main(int argc, const char * argv[])
{
    int key;
    
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
    
    

    
    unsigned char cursor_type = 0;
    
    locate_OS(1, 7);
    
    Cursor_SetFlashOn(0);
    
    while (true) {
        
        GetKey(&key);
        
        if (key == 0x7542 && cursor_type <= 12) Cursor_SetFlashOn(++cursor_type);
        if (key == 0x7547 && cursor_type > 0) Cursor_SetFlashOn(--cursor_type);
    }
    
    return 0;
}

