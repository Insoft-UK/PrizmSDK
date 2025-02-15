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
#include "math.h"

double FXCG_floor(double num)
{
    return (int)num;
}

double FXCG_fmod(double a, double b)
{
    return (a/b - floor(a/b));
}

// Function to calculate factorial
double FXCG_factorial(int n) {
    if (n == 0) {
        return 1.0;
    }
    double result = 1.0;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Function to reduce the angle to the range [0, 2*pi)
static double reduce_angle(double angle) {
    while (angle >= 2 * PI) {
        angle -= 2 * PI;
    }
    while (angle < 0) {
        angle += 2 * PI;
    }
    return angle;
}

// Function to calculate sine using Taylor series
double FXCG_sin(double x) {
    x = reduce_angle(x);
    const int MAX_ITERATIONS = 10;  // More iterations increase accuracy
    double term = x;  // First term x
    double sum = x;   // Initialize sum of series with the first term
    int sign = -1;    // Alternating signs in series
    
    for (int i = 1; i < MAX_ITERATIONS; ++i) {
        int power = 2 * i + 1;
        term = term * x * x / (power * (power - 1));  // Calculate next term
        sum += sign * term;  // Add term to sum with alternating sign
        sign = -sign;  // Flip the sign for next term
    }

    return sum;
}


// Function to calculate cosine using Taylor series
double FXCG_cos(double x) {
    x = reduce_angle(x);
    const int MAX_ITERATIONS = 10;  // More iterations increase accuracy
    double term = 1.0;  // First term is 1
    double sum = 1.0;   // Initialize sum of series with the first term
    int sign = -1;      // Alternating signs in series
    
    for (int i = 1; i < MAX_ITERATIONS; ++i) {
        int power = 2 * i;
        term = term * x * x / (power * (power - 1));  // Calculate next term
        sum += sign * term;  // Add term to sum with alternating sign
        sign = -sign;  // Flip the sign for next term
    }

    return sum;
}

// Function to calculate tangent
double math::tan(double x) {
    x = reduce_angle(x);
    double sin_x = sin(x);
    double cos_x = cos(x);
    if (cos_x == 0.0) {
        // Handle case when cosine is zero to avoid division by zero
        // Return a large value or handle it as per the requirements
        return NAN;  // Here, returning NAN
    }
    return sin_x / cos_x;
}

double FXCG_frexp(double value, int *exp) {
    if (value == 0.0) {
        *exp = 0;
        return 0.0;
    }

    // Extract the raw bits of the double
    union {
        double d;
        unsigned long long ull;
    } u;
    u.d = value;

    // Extract exponent bits (11 bits for double precision)
    int raw_exp = (u.ull >> 52) & 0x7FF;

    // Handle denormalized numbers
    if (raw_exp == 0) {
        // Shift the value to normalize it
        u.d *= 4503599627370496.0; // 2^52
        raw_exp = ((u.ull >> 52) & 0x7FF) - 52;
    }

    // Bias adjustment: raw exponent is stored with a bias of 1023
    *exp = raw_exp - 1022;

    // Clear the exponent bits and set the normalized exponent to 1022
    u.ull = (u.ull & 0x800FFFFFFFFFFFFFULL) | 0x3FE0000000000000ULL;

    return u.d;
}

// Define a constant for ln(2)
#define LN2 0.6931471805599453

// Function to calculate natural logarithm using decomposition and Taylor series
double FXCG_log(double x) {
    if (x <= 0.0) {
        // Logarithm is not defined for non-positive values
        return NAN;
    }
    
    // Decompose x into mantissa m and exponent n such that x = m * 2^n and 1 <= m < 2
    int n;
    double m = frexp(x, &n);
    
    // Convert m to the form (1 + z) where z = m - 1
    double z = m - 1.0;
    
    // Calculate ln(1 + z) using the Taylor series
    double term = z;
    double sum = z;
    for (int i = 2; i < 20; ++i) {
        term *= -z;
        sum += term / i;
    }
    
    // Combine the results
    double result = sum + n * LN2;
    
    return result;
}

#define LN10 2.302585092994046  // Precomputed value of ln(10)

// Function to calculate log base 10 using the natural logarithm
double FXCG_log10(double x) {
    return log(x) / LN10;
}

// Function to calculate exponential using Taylor series
double FXCG_exp(double x) {
    const int MAX_ITERATIONS = 100;
    double term = 1.0;  // First term is 1
    double sum = 1.0;   // Initialize sum of series with the first term
    
    for (int i = 1; i < MAX_ITERATIONS; ++i) {
        term *= x / i;  // Calculate next term
        sum += term;    // Add term to sum
    }
    
    return sum;
}

// Function to calculate x^y
double FXCG_pow(double x, double y) {
    if (x == 0.0 && y > 0.0) {
        return 0.0;
    }
    if (x == 0.0 && y <= 0.0) {
        return NAN;  // Undefined
    }
    if (x < 0.0) {
        return NAN;  // Handling for negative base is not included in this example
    }
    double ln_x = log(x);
    return exp(y * ln_x);
}

