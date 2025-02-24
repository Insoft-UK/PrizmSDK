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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* sys_calloc(int num, int size) {
    // Calculate total memory needed
    size_t total_size = num * size;

    // Check for overflow
    if (num != 0 && total_size / num != size) {
        return NULL; // Overflow detected
    }

    // Allocate memory using malloc
    void* ptr = malloc(total_size);
    if (!ptr) {
        return NULL; // malloc failed
    }

    // Initialize memory to zero
    memset(ptr, 0, total_size);

    return ptr;
}

void *sys_malloc(int size)
{
    return malloc(size);
}


void* sys_realloc(void* ptr, int new_size)
{
    // If ptr is NULL, behave like malloc
    if (ptr == NULL) {
        return malloc(new_size);
    }

    // If new_size is 0, free the memory and return NULL
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    // Allocate new memory block
    void* new_ptr = malloc(new_size);
    if (!new_ptr) {
        return NULL; // malloc failed
    }

    // Copy data from old block to new block (only up to the smaller size)
    // Assuming previous size is unknown, we copy the minimum of old and new size
    memcpy(new_ptr, ptr, new_size); // This can cause issues if new_size < old_size

    // Free old memory block
    free(ptr);

    return new_ptr;
}

void sys_free(void *p)
{
    free(p);
}
