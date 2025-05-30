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

#import <SpriteKit/SpriteKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface DisplayNode : SKNode

typedef NS_ENUM(UInt16, StatusFlag) {
    StatusFlagBattery = 0x0001,
    StatusFlagAlphaShift = 0x0002,
    StatusFlagSetupInputOutput = 0x0004,
    StatusFlagSetupFracResult = 0x0008,
    StatusFlagSetupAngle = 0x0010,
    StatusFlagSetupComplexMode = 0x0020,
    StatusFlagSetupDisplay = 0x0040,
    StatusFlagText = 0x0100,
    StatusFlagGlyph = 0x0200
};

+ (instancetype)sharedInstance;
- (void)redraw;

@end

NS_ASSUME_NONNULL_END
