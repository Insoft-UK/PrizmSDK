// The MIT License (MIT)
//
// Copyright (c) 2023 Insoft. All rights reserved.
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

// Function to adjust saturation
vec3 adjustSaturation(vec3 color, float saturation) {
    // Calculate the luminance (perceived brightness)
    float luminance = dot(color, vec3(0.2126, 0.7152, 0.0722));
    // Interpolate between the grayscale color and the original color
    return mix(vec3(luminance), color, saturation);
}

void main() {
    // Sample the original color from the texture
    vec4 color = texture2D(u_texture, v_tex_coord);
    
    // Apply RGB adjustments
    color.rgb *= u_rgbAdjust;

    // Apply saturation adjustment
    color.rgb = adjustSaturation(color.rgb, u_saturation);

    // Apply gamma correction
    color.rgb = pow(color.rgb, vec3(u_gamma));
    
    // Increase the brightness by adding the brightness factor to each color component
    color.rgb *= u_brightness;

    // Ensure the values stay within the valid range [0.0, 1.0]
       color.rgb = clamp(color.rgb, 0.0, 1.0);

     

    // Set the final color
    gl_FragColor = vec4(color.rgb, color.a);
}


