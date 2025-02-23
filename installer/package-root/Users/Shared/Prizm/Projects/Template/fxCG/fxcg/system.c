// The MIT License (MIT)
//
// Copyright (c) 2025 Insoft. All rights reserved.
// Originaly created 2023
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

#include <fxcg/system.h>
#include <_time.h>

static void SleepMilliseconds(int milliseconds) {
    struct timespec req;
    req.tv_sec = milliseconds / 1000;             // seconds portion
    req.tv_nsec = (milliseconds % 1000) * 1000000;  // nanoseconds portion
    nanosleep(&req, 0);
}

static void Callback(void)
{
    return;
}
void (*_callback)(void) = Callback;

void OS_InnerWait_ms(int ms)
{
    SleepMilliseconds(ms);
}

int MB_ElementCount(char* buf)
{
    int length = 0;
    unsigned char *p = (unsigned char *)buf;
    do {
        if (*p >= 0 && *p <= 0x7E) {
            p++;
            length++;
        }
        if (*p > 0x7E) {
            p+=2;
            length++;
        }
    } while (*p != 0);
    return length;
}


void TakeScreenshot(void)
{
    
}

void SetQuitHandler(void (*callback)(void))
{
    _callback = callback;
}
