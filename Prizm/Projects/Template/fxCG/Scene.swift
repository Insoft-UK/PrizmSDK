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

import SpriteKit
import AppKit

class Scene: SKScene {
    
    enum FXCGKeyCode: Int {
        case F1    = 79, F2       = 69, F3     = 59, F4    = 49, F5     = 39, F6    = 29
        case Shift = 78, Optn     = 68, Vars   = 58, Menu  = 48, Left   = 38, Up    = 28
        case Alpha = 77, Sq       = 67, Power  = 57, Exit  = 47, Down   = 37, Right = 27
        case XAngT = 76, Log      = 66, Ln     = 56, Sin   = 46, Cos    = 36, Tan   = 26
        case Abc   = 75, SwapDisp = 65, CubeRt = 55, InvX  = 45, Comma  = 35, Ans   = 25
        case K7    = 74, K8       = 64, K9     = 54, Del   = 44, On     = 10
        case K4    = 73, K5       = 63, K6     = 53, Mult  = 43, Div    = 33
        case K1    = 72, K2       = 62, K3     = 52, Add   = 42, Minus  = 32
        case K0    = 71, Dot      = 61, Exp    = 51, Neg   = 41, Return = 31
        case NONE  = 0
    }
    
    @_silgen_name("fxCG_KeyDown")
    func fxCG_KeyDown(keyCode: FXCGKeyCode)
    
    @_silgen_name("fxCG_KeyUp")
    func fxCG_KeyUp(keyCode: FXCGKeyCode)
    
    @_silgen_name("AddIn_main")
    func AddIn_main(argc: Int32, argv: UnsafeMutablePointer<UnsafePointer<CChar>?>) -> Int32
    
    // References to view controller and app delegate
    var displayNode: DisplayNode!
    
    var frameCounter = 0
    
    // MARK: - View Lifecycle
    
    override func didMove(to view: SKView) {
        displayNode = DisplayNode()
        addChild(displayNode)
        
        self.size = CGSize(width: 396, height: 224)
        displayNode.position = CGPoint(x: 396 / 2, y: 224 / 2)
        
        startInfiniteLoop()
    }
    
    
    
    override func willMove(from view: SKView) {
        // Cleanup if needed
    }
    
    
    // MARK: - Keyboard Events
    
    override func keyDown(with event: NSEvent) {
        let shift = event.modifierFlags == .shift;
        
        switch event.keyCode {
        case 1:
            fxCG_KeyDown(keyCode: .Sin)
        case 8:
            fxCG_KeyDown(keyCode: .Cos)
        case 17:
            fxCG_KeyDown(keyCode: .Tan)
        case 37:
            fxCG_KeyDown(keyCode: .Ln)
        case 122:
            fxCG_KeyDown(keyCode: .F1)
        case 120:
            fxCG_KeyDown(keyCode: .F2)
        case 99:
            fxCG_KeyDown(keyCode: .F3)
        case 118:
            fxCG_KeyDown(keyCode: .F4)
        case 96:
            fxCG_KeyDown(keyCode: .F5)
        case 97:
            fxCG_KeyDown(keyCode: .F6)
        case 44:
            fxCG_KeyDown(keyCode: .Div)
        case 51:
            fxCG_KeyDown(keyCode: .Del)
        case 53:
            fxCG_KeyDown(keyCode: .Exit)
        case 36:
            fxCG_KeyDown(keyCode: .Return)
        case 76:
            fxCG_KeyDown(keyCode: .Menu)
        case 117:
            fxCG_KeyDown(keyCode: .On)
        case 29:
            fxCG_KeyDown(keyCode: .K0)
        case 18:
            fxCG_KeyDown(keyCode:  .K1)
        case 19:
            fxCG_KeyDown(keyCode:  .K2)
        case 20:
            fxCG_KeyDown(keyCode:  .K3)
        case 21:
            fxCG_KeyDown(keyCode:  .K4)
        case 23:
            fxCG_KeyDown(keyCode:  .K5)
        case 22:
            fxCG_KeyDown(keyCode:  .K6)
        case 24:
            fxCG_KeyDown(keyCode: .Add)
        case 27:
            fxCG_KeyDown(keyCode: .Minus)
        case 26:
            fxCG_KeyDown(keyCode:  .K7)
        case 45:
            fxCG_KeyDown(keyCode: .Neg)
        case 47:
            fxCG_KeyDown(keyCode: .Exp)
        case 28:
            if shift == true {
                fxCG_KeyDown(keyCode: .Mult)
            } else {
                fxCG_KeyDown(keyCode: .K8)
            }
        case 25:
            fxCG_KeyDown(keyCode:  .K9)
        case 124:
            fxCG_KeyDown(keyCode:  .Right)
        case 123:
            fxCG_KeyDown(keyCode:  .Left)
        case 126:
            fxCG_KeyDown(keyCode:  .Up)
        case 125:
            fxCG_KeyDown(keyCode:  .Down)
        default:
#if DEBUG
            print("keyDown: '\(event.characters ?? "")' keyCode: 0x\(String(format: "%02X", event.keyCode))")
#endif
            break
        }
        
#if DEBUG
            print("keyDown: '\(event.characters ?? "")' keyCode: 0x\(String(format: "%02d", event.keyCode))")
#endif
    }
    
    override func keyUp(with event: NSEvent) {
        enum KeyCode: UInt16 {
            case space = 0x31
        }
        
        let shift = event.modifierFlags == .shift;
        
        switch event.keyCode {
        case 1:
            fxCG_KeyUp(keyCode: .Sin)
        case 8:
            fxCG_KeyUp(keyCode: .Cos)
        case 17:
            fxCG_KeyUp(keyCode: .Tan)
        case 37:
            fxCG_KeyUp(keyCode: .Ln)
        case 122:
            fxCG_KeyUp(keyCode: .F1)
        case 120:
            fxCG_KeyUp(keyCode: .F2)
        case 99:
            fxCG_KeyUp(keyCode: .F3)
        case 118:
            fxCG_KeyUp(keyCode: .F4)
        case 96:
            fxCG_KeyUp(keyCode: .F5)
        case 97:
            fxCG_KeyUp(keyCode: .F6)
        case 44:
            fxCG_KeyUp(keyCode: .Div) // '/'
        case 51:
            fxCG_KeyUp(keyCode: .Del)
        case 53:
            fxCG_KeyUp(keyCode: .Exit)
        case 76:
            fxCG_KeyUp(keyCode: .Menu)
        case 117:
            fxCG_KeyUp(keyCode: .On)
        case 36:
            fxCG_KeyUp(keyCode: .Return)
        case 29:
            fxCG_KeyUp(keyCode: .K0)
        case 18:
            fxCG_KeyUp(keyCode: .K1)
        case 19:
            fxCG_KeyUp(keyCode: .K2)
        case 20:
            fxCG_KeyUp(keyCode: .K3)
        case 21:
            fxCG_KeyUp(keyCode: .K4)
        case 23:
            fxCG_KeyUp(keyCode: .K5)
        case 22:
            fxCG_KeyUp(keyCode: .K6)
        case 26:
            fxCG_KeyUp(keyCode: .K7)
        case 45:
            fxCG_KeyDown(keyCode: .Neg)
        case 47:
            fxCG_KeyDown(keyCode: .Exp)
        case 24:
            fxCG_KeyUp(keyCode: .Neg)
        case 27:
            fxCG_KeyUp(keyCode: .Exp)
        case 28:
            if shift == true {
                fxCG_KeyUp(keyCode: .Mult)
            } else {
                fxCG_KeyUp(keyCode:  .K8)
            }
        case 25:
            fxCG_KeyUp(keyCode: .K9)
        case 124:
            fxCG_KeyUp(keyCode: .Right)
        case 123:
            fxCG_KeyUp(keyCode: .Left)
        case 126:
            fxCG_KeyUp(keyCode: .Up)
        case 125:
            fxCG_KeyUp(keyCode: .Down)
        default:
#if DEBUG
            print("keyUp: '\(event.characters ?? "")' keyCode: 0x\(String(format: "%02X", event.keyCode))")
#endif
            break
        }
    }
    
    // MARK: - Mouse Events
    
    override func mouseDown(with event: NSEvent) {
        let location = event.locationInWindow
#if DEBUG
        print("locationInWindow.x: \(location.x) locationInWindow.y: \(location.y)")
#endif
    }
    
    // MARK: - Update
    
    override func update(_ currentTime: TimeInterval) {
        frameCounter += 1
        
        if frameCounter % 60 == 0 {
            // Perform heavy updates
            displayNode.redraw()
        }
        
    }
    
    func startInfiniteLoop() {
        DispatchQueue.global(qos: .background).async {
            // Prepare arguments (Simulating `int argc, const char *argv[]`)
            
            // Prepare Swift arguments
            var args: [String] = ["Add-In", "arg1", "arg2"]

            // Convert Swift Strings to C Strings (char *)
            var cArgs: [UnsafePointer<CChar>?] = args.map { UnsafePointer(strdup($0)) } + [nil] // Convert and null-terminate

            // Pass to the C function
            let result = cArgs.withUnsafeMutableBufferPointer { buffer in
                let argvPointer = buffer.baseAddress!
                return self.AddIn_main(argc: Int32(args.count), argv: argvPointer)
            }

            // Free allocated memory
            for ptr in cArgs where ptr != nil {
                free(UnsafeMutableRawPointer(mutating: ptr))
            }

            print("AddIn_main returned: \(result)")

        }
    }
}
