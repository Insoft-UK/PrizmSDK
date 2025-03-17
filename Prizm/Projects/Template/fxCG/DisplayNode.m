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


#import "DisplayNode.h"
#import "fxcg.h"

@interface DisplayNode () {
    SKMutableTexture *mutableTexture;
    SKSpriteNode *display;
    SKSpriteNode *battery;
    SKSpriteNode *shift;
    SKSpriteNode *alphaSymbol;
    SKSpriteNode *cursor;
    NSArray<SKTexture *> *alphaFrames;
}

@end

@implementation DisplayNode

// Singleton Instance
+ (instancetype)sharedInstance {
    static DisplayNode *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

// Init Method
- (instancetype)init {
    if (self = [super init]) {
        [self setup];
    }
    return self;
}

// Setup Display Node
- (void)setup {
    self.userInteractionEnabled = NO;
    CGSize size = CGSizeMake(396, 224);
    
    display = [SKSpriteNode spriteNodeWithColor:[NSColor clearColor] size:size];
    [self addChild:display];
    
    mutableTexture = [[SKMutableTexture alloc] initWithSize:size];
    display.texture = mutableTexture;
    display.blendMode = SKBlendModeReplace;
    display.texture.filteringMode = SKTextureFilteringNearest;
    display.zPosition = 1;
    
    [self setupBattery];

    alphaFrames = @[
        [SKTexture textureWithImageNamed:@"Alpha"],
        [SKTexture textureWithImageNamed:@"AlphaLocked"]
    ];
    
    alphaSymbol = [SKSpriteNode spriteNodeWithTexture:alphaFrames[0]];
    alphaSymbol.anchorPoint = CGPointZero;
    alphaSymbol.position = CGPointMake(-198 + 6 + 18, 112 - 22);
    alphaSymbol.texture.filteringMode = SKTextureFilteringNearest;
    [display addChild:alphaSymbol];
    
    shift = [SKSpriteNode spriteNodeWithImageNamed:@"Shift"];
    shift.anchorPoint = CGPointZero;
    shift.position = CGPointMake(-198 + 6 + 18, 112 - 22);
    shift.texture.filteringMode = SKTextureFilteringNearest;
    [display addChild:shift];
    
    
    // Cursor
    cursor = [SKSpriteNode spriteNodeWithImageNamed:@"Cursor"];
    cursor.texture.filteringMode = SKTextureFilteringNearest;
    cursor.anchorPoint = CGPointZero;
    SKAction *animateCursor = [SKAction repeatActionForever:[SKAction sequence:@[
        [SKAction unhide],
        [SKAction waitForDuration:0.5],
        [SKAction hide],
        [SKAction waitForDuration:0.5]
    ]]];
    [cursor runAction:animateCursor];
    TCursorSettings cursorSettings;
    Cursor_GetSettings(&cursorSettings);
    cursor.position = CGPointMake(-198 + 6 + cursorSettings.cursorX * cursor.size.width, -120 + cursorSettings.cursorY * cursor.size.height + cursor.size.height / 2);
    [display addChild:cursor];
}

// Setup Battery Animation
- (void)setupBattery {
    SKTextureAtlas *batteryAtlas = [SKTextureAtlas atlasNamed:@"Battery"];
    
    NSArray *batteryFrames = @[
        [batteryAtlas textureNamed:@"Bat100%"],
        [batteryAtlas textureNamed:@"Bat75%"],
        [batteryAtlas textureNamed:@"Bat25%"],
        [batteryAtlas textureNamed:@"Bat0%"]
    ];
    
    battery = [SKSpriteNode spriteNodeWithTexture:batteryFrames[0]];
    battery.anchorPoint = CGPointZero;
    battery.position = CGPointMake(-198 + 6, 112 - 22);
    battery.texture.filteringMode = SKTextureFilteringNearest;
    [display addChild:battery];

    SKAction *animateBattery = [SKAction repeatActionForever:
        [SKAction animateWithTextures:batteryFrames timePerFrame:60 resize:NO restore:YES]];
    
    [battery runAction:animateBattery withKey:@"battery"];
}

// Redraw Method
- (void)redraw {
    void *dramPointer = GetDDAddress();
    
    if (!dramPointer) {
        return;
    }
    
    UInt16 *pixelData = (UInt16 *)dramPointer;
    
    
    static int cursorFlashFlag = 0;
    
    TCursorSettings cursorSettings;
    Cursor_GetSettings(&cursorSettings);
    
    cursor.position = CGPointMake(-198 + 6 + cursorSettings.cursorX * cursor.size.width, -120 + cursorSettings.cursorY * cursor.size.height + cursor.size.height / 2);
    
    
    if (cursorFlashFlag != cursorSettings.cursorFlashFlag) {
        cursorFlashFlag = cursorSettings.cursorFlashFlag;
        switch (cursorFlashFlag) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 8:
            case 11:
                cursor.texture = [SKTexture textureWithImageNamed:@"Cursor"];
                break;
                
            case 12:
                cursor.texture = [SKTexture textureWithImageNamed:@"ArrowCursor"];
                break;
                
            default:
                cursor.texture = [SKTexture textureWithImageNamed:@"FullCursor"];
                break;
        }
        cursor.texture.filteringMode = SKTextureFilteringNearest;
    }
    cursor.hidden = (!cursorSettings._uknown);
    
    
    [mutableTexture modifyPixelDataWithBlock:^(void * _Nullable pixelDataPtr, NSUInteger lengthInBytes) {
        if (!pixelDataPtr) return;
        
        UInt32 *pixelBuffer = (UInt32 *)pixelDataPtr;
        
        for (int y = 0; y < 224; y++) {
            for (int x = 0; x < 396; x++) {
                UInt16 rgb565 = pixelData[y * 396 + x];
                
                UInt8 r = ((rgb565 >> 11) & 0x1F) * 255 / 31;  // 5-bit Red to 8-bit
                UInt8 g = ((rgb565 >> 5)  & 0x3F) * 255 / 63;  // 6-bit Green to 8-bit
                UInt8 b = (rgb565 & 0x1F) * 255 / 31;         // 5-bit Blue to 8-bit
                
                pixelBuffer[(223 - y) * 396 + x] = (UInt32)r | ((UInt32)g << 8) | ((UInt32)b << 16) | 0xFF000000;
            }
        }
    }];
    
    battery.hidden = !(fxCG_SAF() & StatusFlagBattery);
    shift.hidden = !(fxCG_SAF() & StatusFlagAlphaShift);
    alphaSymbol.hidden = !(fxCG_SAF() & StatusFlagText);
    
    if (fxCG_SAF() & StatusFlagAlphaShift) {
        alphaSymbol.texture = alphaFrames[1];
    } else {
        alphaSymbol.texture = alphaFrames[0];
    }
}

@end
