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

@_silgen_name("GetVRAMAddress")
func GetVRAMAddress() -> UnsafeMutableRawPointer?

@_silgen_name("FrameColor")
func FrameColor(mode: Int, color: UInt16) -> UInt16?


@objc class DisplayNode: SKNode {
    
    static let shared = DisplayNode()
    
    // MARK: - Private class constants
    private var mutableTexture: SKMutableTexture!
    private var display: SKSpriteNode!
    
    // MARK: - Private class variables

    
    // MARK: - Init
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    override init() {
        super.init()
        setup()
    }
    

    // MARK: - Settings...
    private func setup() {
        isUserInteractionEnabled = false
        let size = CGSize(width: CGFloat(396), height: CGFloat(224))
        
        display = SKSpriteNode(color: .clear, size: size)
        display.yScale = -1
        addChild(display)

        mutableTexture = SKMutableTexture(size: display.size)
        display.texture = mutableTexture
        display.blendMode = .replace
        zPosition = 1
    }
    
    
    @objc func redraw() {
        mutableTexture.modifyPixelData { pixelData, lengthInBytes in
            guard let vramPointer = GetVRAMAddress()?.assumingMemoryBound(to: UInt16.self),
                  let pixelBuffer = pixelData?.assumingMemoryBound(to: UInt32.self) else {
                return
            }

            // Iterate through the VRAM and convert each pixel
            for y in 0..<224 {
                for x in 0..<396 {
                    let index: Int = (y * 396 + x)
                    
                    if ((x < 6 || x >= 390) || y >= 216) {
                        pixelBuffer[index] = 0xFFFFFFFF
                        continue
                    }
                    
                    let rgb565 = vramPointer[y * 384 + x - 6]
                    
                    let r = UInt8(((rgb565 >> 11) & 0x1F) * 255 / 31)  // 5-bit Red to 8-bit
                    let g = UInt8(((rgb565 >> 5)  & 0x3F) * 255 / 63)  // 6-bit Green to 8-bit
                    let b = UInt8((rgb565 & 0x1F) * 255 / 31)         // 5-bit Blue to 8-bit
                    
                    pixelBuffer[index] = (UInt32(r) << 24) | (UInt32(g) << 16) | (UInt32(b) << 8) | 0xFF
                }
            }
        }
    }

}


