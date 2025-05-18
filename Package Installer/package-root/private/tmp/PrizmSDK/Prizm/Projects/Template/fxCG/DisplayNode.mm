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


#import "DisplayNode.hh"
#import "fxcg.hpp"


@interface DisplayNode () {
    SKMutableTexture *mutableTexture;
    SKSpriteNode *display;
    SKSpriteNode *cursor;
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
    

    NSString *shaderPath = [[NSBundle mainBundle] pathForResource:@"fxCG" ofType:@"fsh"]; // Load from the app's bundle
    NSError *error = nil;
    NSString *shaderSource = [NSString stringWithContentsOfFile:shaderPath encoding:NSUTF8StringEncoding error:&error];

    if (error) {
        NSLog(@"Error loading shader file: %@", error.localizedDescription);
        return;
    }
    
    // Load the shader from the file
    SKShader *shader = [SKShader shaderWithSource:shaderSource];
    
    // Set the RGB adjustment and gamma correction uniforms
    NSArray<SKUniform *> *uniforms = @[
        [SKUniform uniformWithName:@"u_rgbAdjust" vectorFloat3:simd_make_float3(0.75, 1.0, 1.4)],
        [SKUniform uniformWithName:@"u_gamma" float:0.9],
        [SKUniform uniformWithName:@"u_saturation" float:0.8],
        [SKUniform uniformWithName:@"u_brightness" float:1.075]
    ];

    // Apply uniforms to the shader
    shader.uniforms = uniforms;

    
    display.shader = shader;
//    display.texture.filteringMode = SKTextureFilteringNearest;
    
    for (SKSpriteNode *child in display.children) {
        child.shader = shader;
    }
    
    if (display.shader != nil) {
        NSLog(@"Shader applied successfully!");
    } else {
        NSLog(@"Shader not applied!");
    }
}


// Helper method to get the scene resolution
- (vector_float3)getSceneResolution {
    float width = (float)mutableTexture.size.width;
    float height = (float)mutableTexture.size.height;
    vector_float3 size = {width, height, 0.0f};
    return size;
}

// Redraw Method
- (void)redraw {
    void *dramPointer = fxCG_GetDDAddress();
    
    if (!dramPointer) {
        return;
    }
    
    UInt16 *pixelData = (UInt16 *)dramPointer;
    
    
    fxCG_DrawCursor();
    DisplayStatusArea();
    
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
    
    
}

@end
