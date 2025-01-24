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

#include "ui.h"
#include "draw.h"

static void FXCG_drawScrollBar(int x, int y, int length)
{
    FXCG_drawFillArea(x, y, 6, length, 0);
    FXCG_drawFillArea(x + 2, y + 1, 3, length - 2, white);
    FXCG_enableHalfOpacityDrawing();
    FXCG_drawFillArea(x + 2, y + 1, 3, length - 2, gray(24));
    FXCG_disableHalfOpacityDrawing();
}

static void FXCG_drawScrollBarThumb(int x, int y, int length)
{
    FXCG_drawFillArea(x, y, 4, length - 1, white);
    FXCG_drawFillArea(x + 1, y + 2, 3, length - 3, gray(16));
    FXCG_drawLine(x, y, x + 3, y, 0);
    FXCG_drawLine(x, y + length - 2, x + 3, y + length - 2, 0);
}

void FXCG_scrollBar(FXCG_TScrollBar *scrollBar)
{
    const int visible_content = 3;
    
    drawScrollBar(scrollBar->x, scrollBar->y, scrollBar->length);
    
    /*
     Input Validation:
         •    Checks if min is less than max, if position is within the range [min, max], and if visible_content is greater than 0.
    */
    if (scrollBar->min >= scrollBar->max || scrollBar->position > scrollBar->max) {
        return;
    }
    
    /*
     Calculate Thumb Size and Position:
         •    Determines the range of the scroll bar (range = max - min).
         •    Calculates the dynamic thumb length based on the ratio of visible content to the total content plus the visible content:
     */
    int range = scrollBar->max - scrollBar->min;
    int thumb_length = (visible_content * scrollBar->length) / (range + visible_content);
    
    /*
         •    Ensures the thumb length is at least 1 character wide and does not exceed the scroll bar length.
         •    Calculates the position of the scroll thumb relative to the scroll bar length:
     */
    if (thumb_length < 1) thumb_length = 1;
    if (thumb_length > scrollBar->length) thumb_length = scrollBar->length;
    int thumb_position = (scrollBar->position - scrollBar->min) * (scrollBar->length - thumb_length) / range;
    
    // Draw the Scroll Bar Thumb:
    drawScrollBarThumb(scrollBar->x + 1, scrollBar->y + thumb_position, thumb_length);
}
