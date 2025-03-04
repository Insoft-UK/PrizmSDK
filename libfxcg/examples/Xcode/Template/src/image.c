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

#include "image.h"

static void Image_OrderedDitherChannel(uint8_t *image, const int width, const int height, const int x, const int y, const int channel)
{
    static uint8_t bayer4x4[4][4] = {
        {0, 8, 2, 10},
        {12, 4, 14, 6},
        {3, 11, 1, 9},
        {15, 7, 13, 5}
    };
    
    int index = (y * width + x) * 3 + channel;
    uint8_t threshold = bayer4x4[x % 4][y % 4] * 16;  // Scale to 0-255
    image[index] = (image[index] > threshold) ? 255 : 0; // Convert to 1-bit per channel
}

void Image_OrderedDitherRGB(uint8_t *image, const int width, const int height)
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int channel = 0; channel < 3; channel++) {
                Image_OrderedDitherChannel(image, width, height, x, y, channel);
            }
        }
    }
}

static void Image_FloydSteinbergDitherChannel(uint8_t *image, const int width, const int height, const int x, const int y, const int channel)
{
    int index = (y * width + x) * 3 + channel;
    uint8_t oldPixel = image[index];
    uint8_t newPixel = (oldPixel < 128) ? 0 : 255;  // Simple thresholding
    int error = oldPixel - newPixel;
    image[index] = newPixel;

    // Distribute error to neighboring pixels
    if (x + 1 < width) image[index + 3] += error * 7 / 16;
    if (y + 1 >= height) return;
   
    if (x > 0) image[index + (width - 1) * 3] += error * 3 / 16;
    image[index + width * 3] += error * 5 / 16;
    if (x + 1 < width) image[index + (width + 1) * 3] += error * 1 / 16;
}

void Image_FloydSteinbergDitherRGB(uint8_t *image, const int width, const int height)
{
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int channel = 0; channel < 3; channel++) { // Process R, G, B separately
                Image_FloydSteinbergDitherChannel(image, width, height, x, y, channel);
            }
        }
    }
}
