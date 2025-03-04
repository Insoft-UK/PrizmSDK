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

@_silgen_name("GetDDAddress")
func GetDDAddress() -> UnsafeMutableRawPointer?

@_silgen_name("FrameColor")
func FrameColor(mode: Int, color: UInt16) -> UInt16?


@objc class DisplayNode: SKNode {
    enum StatusFlag: UInt16 {
        case Battery = 0x0001
        case AlphaShift = 0x0002
        case SetupInputOutput = 0x0004
        case SetupFracResult = 0x0008
        case SetupAngle = 0x0010
        case SetupComplexMode = 0x0020
        case SetupDisplay = 0x0040
        case Text = 0x0100
        case Glyph = 0x0200
    }
    
    static let shared = DisplayNode()
    
    // MARK: - Private class constants
    private var mutableTexture: SKMutableTexture!
    private var display: SKSpriteNode!
    
    private var battery: SKSpriteNode!
    private var shift: SKSpriteNode!
    private var alphaSymbol: SKSpriteNode!
    private var alphaFrames: [SKTexture] = []
    
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
        addChild(display)

        mutableTexture = SKMutableTexture(size: display.size)
        display.texture = mutableTexture
        display.blendMode = .replace
        display.texture?.filteringMode = .nearest
        zPosition = 1
        
        setupBattery()
        
        alphaFrames.append(SKTexture(imageNamed: "Alpha"))
        alphaFrames.append(SKTexture(imageNamed: "AlphaLocked"))
        
        alphaSymbol = SKSpriteNode(texture: alphaFrames[0])
        alphaSymbol.anchorPoint = .zero
        alphaSymbol.position = CGPoint(x: -198 + 6 + 18, y: 112 - 22)
        alphaSymbol.texture?.filteringMode = .nearest
        display.addChild(alphaSymbol)
        
        shift = SKSpriteNode(imageNamed: "Shift")
        shift.anchorPoint = .zero
        shift.position = CGPoint(x: -198 + 6 + 18, y: 112 - 22)
        shift.texture?.filteringMode = .nearest
        display.addChild(shift)
    }
    
    func setupBattery() {
        let batteryAnimatedAtlas = SKTextureAtlas(named: "Battery")
        var batteryLevelframes: [SKTexture] = []
        
        batteryLevelframes.append(batteryAnimatedAtlas.textureNamed("Bat100%"))
        batteryLevelframes.append(batteryAnimatedAtlas.textureNamed("Bat75%"))
        batteryLevelframes.append(batteryAnimatedAtlas.textureNamed("Bat25%"))
        batteryLevelframes.append(batteryAnimatedAtlas.textureNamed("Bat0%"))
        
        
        battery = SKSpriteNode(texture: batteryLevelframes[0])
        battery.anchorPoint = .zero
        battery.position = CGPoint(x: -198 + 6, y: 112 - 22)
        battery.texture?.filteringMode = .nearest
        display.addChild(battery)
        
        battery.run(SKAction.repeatForever(
        SKAction.animate(with: batteryLevelframes,
                         timePerFrame: 60,
                         resize: false,
                         restore: true)),
        withKey:"battery")
    }
    
    @objc func redraw() {
        mutableTexture.modifyPixelData { pixelData, lengthInBytes in
            guard let dramPointer = GetDDAddress()?.assumingMemoryBound(to: UInt16.self),
                  let pixelBuffer = pixelData?.assumingMemoryBound(to: UInt32.self) else {
                return
            }

            // Iterate through the VRAM and convert each pixel
            for y in 0..<224 {
                for x in 0..<396 {
                    let rgb565 = dramPointer[y * 396 + x]
                    
                    let r = UInt8(((rgb565 >> 11) & 0x1F) * 255 / 31)  // 5-bit Red to 8-bit
                    let g = UInt8(((rgb565 >> 5)  & 0x3F) * 255 / 63)  // 6-bit Green to 8-bit
                    let b = UInt8((rgb565 & 0x1F) * 255 / 31)         // 5-bit Blue to 8-bit
                    
                    pixelBuffer[(223 - y) * 396 + x] = UInt32(r) | (UInt32(g) << 8) | (UInt32(b) << 16) | 0xFF000000
                }
            }
        }
        
        battery.isHidden = (fxCG_SAF() & 0x0001 == 0)
        shift.isHidden = (fxCG_SAF() & 0x0002 == 0)
        alphaSymbol.isHidden = (fxCG_SAF() & 0x0100 == 0)
        if fxCG_SAF() & 0x0002 == 1 {
            alphaSymbol.texture = alphaFrames[1]
        } else {
            alphaSymbol.texture = alphaFrames[0]
        }
        
    }

}


