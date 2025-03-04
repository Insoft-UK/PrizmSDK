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

#include <stdbool.h>

int ItoA_10digit(int value, unsigned char *result)
{
    bool isNeg=false;
    if(value < 0)
        isNeg = true;
    
    int idx = 0;
    do {
        int j = value % 10;
        j = j < 0 ? j * -1 : j ;
        result[idx++]=j+48;
        value=value/10;
    } while (value!=0);
    if(isNeg)
        result[idx++]='-';
    result[idx]='\0';
    
    int j = idx-1;
    int i=0;
    while (i<j) {
        char tmp = result[j];
        result[j] = result[i];
        result[i] = tmp;
        i++;
        j--;
    }
    
    return  0;
}

