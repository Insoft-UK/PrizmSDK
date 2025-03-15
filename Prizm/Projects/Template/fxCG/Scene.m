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

#import "Scene.h"
#import "DisplayNode.h"
#import <keyboard.h>

typedef NS_ENUM(UInt8, FXCG_KeyCode){
    K_F1    = 79, K_F2       = 69, K_F3     = 59, K_F4    = 49, K_F5     = 39, K_F6    = 29,
    K_Shift = 78, K_Optn     = 68, K_Vars   = 58, K_Menu  = 48, K_Left   = 38, K_Up    = 28,
    K_Alpha = 77, K_Sq       = 67, K_Power  = 57, K_Exit  = 47, K_Down   = 37, K_Right = 27,
    K_XAngT = 76, K_Log      = 66, K_Ln     = 56, K_Sin   = 46, K_Cos    = 36, K_Tan   = 26,
    K_Abc   = 75, K_SwapDisp = 65, K_CubeRt = 55, K_InvX  = 45, K_Comma  = 35, K_Ans   = 25,
    K_7     = 74, K_8        = 64, K_9      = 54, K_Del   = 44, K_On     = 10,
    K_4     = 73, K_5        = 63, K_6      = 53, K_Mult  = 43, K_Div    = 33,
    K_1     = 72, K_2        = 62, K_3      = 52, K_Add   = 42, K_Minus  = 32,
    K_0     = 71, K_Dot      = 61, K_Exp    = 51, K_Neg   = 41, K_Return = 31, K_NONE  = 0
};


// C function declarations
extern void fxCG_KeyDown(FXCG_KeyCode keyCode);
extern void fxCG_KeyUp(FXCG_KeyCode keyCode);
extern void fxCG_KeyClearAll(void);
extern int AddIn_main(int argc, const char *argv[]);

@interface Scene ()
@property (nonatomic, strong) DisplayNode *displayNode;
@property (nonatomic, assign) NSInteger frameCounter;
@end

@implementation Scene

- (void)didMoveToView:(SKView *)view {
    self.displayNode = [[DisplayNode alloc] init];
    [self addChild:self.displayNode];

    self.size = CGSizeMake(396, 224);
    self.displayNode.position = CGPointMake(396 / 2, 224 / 2);

    [self startInfiniteLoop];
}

- (void)willMoveFromView:(SKView *)view {
    // Cleanup if needed
}

// MARK: - Keyboard Events

- (void)keyDown:(NSEvent *)event {
//    BOOL shift = (event.modifierFlags & NSEventModifierFlagShift) != 0;

    switch (event.keyCode) {
        case 1:  fxCG_KeyDown(K_Sin); break;
        case 8:  fxCG_KeyDown(K_Cos); break;
        case 17: fxCG_KeyDown(K_Tan); break;
        case 37: fxCG_KeyDown(K_Ln); break;

        // Function keys (F1–F6)
        case 122: fxCG_KeyDown(KEY_PRGM_F1); break;  // F1
        case 120: fxCG_KeyDown(KEY_PRGM_F2); break;  // F2
        case 99:  fxCG_KeyDown(KEY_PRGM_F3); break;  // F3
        case 118: fxCG_KeyDown(KEY_PRGM_F4); break;  // F4
        case 96:  fxCG_KeyDown(KEY_PRGM_F5); break;  // F5
        case 97:  fxCG_KeyDown(KEY_PRGM_F6); break;  // F6

        // Operators & Other Keys
        case 44:  fxCG_KeyDown(K_Div); break;
        case 51:  fxCG_KeyDown(K_Del); break;
        case 53:  fxCG_KeyDown(KEY_PRGM_EXIT); break;
        case 36:  fxCG_KeyDown(KEY_PRGM_RETURN); break;
        case 76:  fxCG_KeyDown(KEY_PRGM_MENU); break;
        case 117: fxCG_KeyDown(KEY_PRGM_ACON); break;

        // Number keys
        case 29:  fxCG_KeyDown(KEY_PRGM_0); break;
        case 18:  fxCG_KeyDown(KEY_PRGM_1); break;
        case 19:  fxCG_KeyDown(KEY_PRGM_2); break;
        case 20:  fxCG_KeyDown(KEY_PRGM_3); break;
        case 21:  fxCG_KeyDown(KEY_PRGM_4); break;
        case 23:  fxCG_KeyDown(KEY_PRGM_5); break;
        case 22:  fxCG_KeyDown(KEY_PRGM_6); break;
        case 26:  fxCG_KeyDown(KEY_PRGM_7); break;
        case 28:  fxCG_KeyDown(KEY_PRGM_8); break;
        case 25:  fxCG_KeyDown(KEY_PRGM_9); break;
        case 24:  fxCG_KeyDown(K_Add); break;
        case 27:  fxCG_KeyDown(K_Minus); break;

        // Arrow keys
        case 124: fxCG_KeyDown(KEY_PRGM_RIGHT); break;
        case 123: fxCG_KeyDown(KEY_PRGM_LEFT); break;
        case 126: fxCG_KeyDown(KEY_PRGM_UP); break;
        case 125: fxCG_KeyDown(KEY_PRGM_DOWN); break;

        default:
#if DEBUG
            NSLog(@"keyDown: '%@' keyCode: 0x%02X", event.characters, event.keyCode);
#endif
            break;
    }
}

- (void)keyUp:(NSEvent *)event {
    switch (event.keyCode) {
        case 1:  fxCG_KeyUp(K_Sin); break;
        case 8:  fxCG_KeyUp(K_Cos); break;
        case 17: fxCG_KeyUp(K_Tan); break;
        case 37: fxCG_KeyUp(K_Ln); break;

        // Function keys (F1–F6)
        case 122: fxCG_KeyUp(K_F1); break;  // F1
        case 120: fxCG_KeyUp(K_F2); break;  // F2
        case 99:  fxCG_KeyUp(K_F3); break;  // F3
        case 118: fxCG_KeyUp(K_F4); break;  // F4
        case 96:  fxCG_KeyUp(K_F5); break;  // F5
        case 97:  fxCG_KeyUp(K_F6); break;  // F6

        // Operators & Other Keys
        case 44:  fxCG_KeyUp(K_Div); break;
        case 51:  fxCG_KeyUp(K_Del); break;
        case 53:  fxCG_KeyUp(K_Exit); break;
        case 36:  fxCG_KeyUp(K_Return); break;
        case 76:  fxCG_KeyUp(K_Menu); break;
        case 117: fxCG_KeyUp(K_On); break;

        // Number keys
        case 29:  fxCG_KeyUp(K_0); break;
        case 18:  fxCG_KeyUp(K_1); break;
        case 19:  fxCG_KeyUp(K_2); break;
        case 20:  fxCG_KeyUp(K_3); break;
        case 21:  fxCG_KeyUp(K_4); break;
        case 23:  fxCG_KeyUp(K_5); break;
        case 22:  fxCG_KeyUp(K_6); break;
        case 26:  fxCG_KeyUp(K_7); break;
        case 28:  fxCG_KeyUp(K_8); break;
        case 25:  fxCG_KeyUp(K_9); break;
        case 24:  fxCG_KeyUp(K_Add); break;
        case 27:  fxCG_KeyUp(K_Minus); break;

        // Arrow keys
        case 124: fxCG_KeyUp(K_Right); break;
        case 123: fxCG_KeyUp(K_Left); break;
        case 126: fxCG_KeyUp(K_Up); break;
        case 125: fxCG_KeyUp(K_Down); break;
            
        default:
#if DEBUG
            NSLog(@"keyUp: '%@' keyCode: 0x%02X", event.characters, event.keyCode);
#endif
            break;
    }
    
    fxCG_KeyClearAll();
}

// MARK: - Update Loop

- (void)update:(NSTimeInterval)currentTime {
    self.frameCounter++;

    if (self.frameCounter % 60 == 0) {
        [self.displayNode redraw];
    }
}

// MARK: - Infinite Loop

- (void)startInfiniteLoop {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
        char *argv[] = { "Add-In", "arg1", "arg2", NULL };
        int result = AddIn_main(3, (const char **)argv);
        NSLog(@"AddIn_main returned: %d", result);
    });
}

@end
