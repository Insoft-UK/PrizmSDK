#ifndef __FXCG_DISPLAY_H
#define __FXCG_DISPLAY_H

// MARK: - Defines

#define LCD_WIDTH_PX 384
#define LCD_HEIGHT_PX 216

#define TEXT_MODE_NORMAL                 0x00
#define TEXT_MODE_INVERT                 0x01
#define TEXT_MODE_TRANSPARENT_BACKGROUND 0x20
#define TEXT_MODE_AND                    0x21

// Define Status Area
#define DSA_CLEAR                        0
#define DSA_SETDEFAULT                   1

// Status Area Flags
#define SAF_BATTERY                      0x0001
#define SAF_ALPHA_SHIFT                  0x0002
#define SAF_SETUP_INPUT_OUTPUT           0x0004
#define SAF_SETUP_FRAC_RESULT            0x0008
#define SAF_SETUP_ANGLE                  0x0010
#define SAF_SETUP_COMPLEX_MODE           0x0020
#define SAF_SETUP_DISPLAY                0x0040
#define SAF_TEXT                         0x0100
#define SAF_GLYPH                        0x0200

#define COLOR_ALICEBLUE                  0xF7DF
#define COLOR_ANTIQUEWHITE               0xFF5A
#define COLOR_AQUA                       0x07FF
#define COLOR_AQUAMARINE                 0x7FFA
#define COLOR_AZURE                      0xF7FF
#define COLOR_BEIGE                      0xF7BB
#define COLOR_BISQUE                     0xFF38
#define COLOR_BLACK                      0x0000
#define COLOR_BLANCHEDALMOND             0xFF59
#define COLOR_BLUE                       0x001F
#define COLOR_BLUEVIOLET                 0x895C
#define COLOR_BROWN                      0xA145
#define COLOR_BURLYWOOD                  0xDDD0
#define COLOR_CADETBLUE                  0x5CF4
#define COLOR_CHARTREUSE                 0x7FE0
#define COLOR_CHOCOLATE                  0xD343
#define COLOR_CORAL                      0xFBEA
#define COLOR_CORNFLOWERBLUE             0x64BD
#define COLOR_CORNSILK                   0xFFDB
#define COLOR_CRIMSON                    0xD8A7
#define COLOR_CYAN                       0x07FF
#define COLOR_DARKBLUE                   0x0011
#define COLOR_DARKCYAN                   0x0451
#define COLOR_DARKGOLDENROD              0xBC21
#define COLOR_DARKGRAY                   0xAD55
#define COLOR_DARKGREEN                  0x0320
#define COLOR_DARKKHAKI                  0xBDAD
#define COLOR_DARKMAGENTA                0x8811
#define COLOR_DARKOLIVEGREEN             0x5345
#define COLOR_DARKORANGE                 0xFC60
#define COLOR_DARKORCHID                 0x9999
#define COLOR_DARKRED                    0x8800
#define COLOR_DARKSALMON                 0xECAF
#define COLOR_DARKSEAGREEN               0x8DF1
#define COLOR_DARKSLATEBLUE              0x49F1
#define COLOR_DARKSLATEGRAY              0x2A69
#define COLOR_DARKTURQUOISE              0x067A
#define COLOR_DARKVIOLET                 0x901A
#define COLOR_DEEPPINK                   0xF8B2
#define COLOR_DEEPSKYBLUE                0x05FF
#define COLOR_DIMGRAY                    0x6B4D
#define COLOR_DODGERBLUE                 0x1C9F
#define COLOR_FIREBRICK                  0xB104
#define COLOR_FLORALWHITE                0xFFDE
#define COLOR_FORESTGREEN                0x2444
#define COLOR_FUCHSIA                    0xF81F
#define COLOR_GAINSBORO                  0xDEFB
#define COLOR_GHOSTWHITE                 0xFFDF
#define COLOR_GOLD                       0xFEA0
#define COLOR_GOLDENROD                 0xDD24
#define COLOR_GRAY                 0x8410
#define COLOR_GREEN                 0x0400
#define COLOR_GREENYELLOW                 0xAFE5
#define COLOR_HONEYDEW                 0xF7FE
#define COLOR_HOTPINK                 0xFB56
#define COLOR_INDIANRED                 0xCAEB
#define COLOR_INDIGO                 0x4810
#define COLOR_IVORY                 0xFFFE
#define COLOR_KHAKI                 0xF731
#define COLOR_LAVENDER                 0xE73F
#define COLOR_LAVENDERBLUSH                 0xFF9E
#define COLOR_LAWNGREEN                 0x7FE0
#define COLOR_LEMONCHIFFON                 0xFFD9
#define COLOR_LIGHTBLUE                 0xAEDC
#define COLOR_LIGHTCORAL                 0xF410
#define COLOR_LIGHTCYAN                 0xE7FF
#define COLOR_LIGHTGOLDENRODYELLOW                 0xFFDA
#define COLOR_LIGHTGRAY                 0xD69A
#define COLOR_LIGHTGREEN                 0x9772
#define COLOR_LIGHTPINK                 0xFDB8
#define COLOR_LIGHTSALMON                 0xFD0F
#define COLOR_LIGHTSEAGREEN                 0x2595
#define COLOR_LIGHTSKYBLUE                 0x867F
#define COLOR_LIGHTSLATEGRAY                 0x7453
#define COLOR_LIGHTSTEELBLUE                 0xB63B
#define COLOR_LIGHTYELLOW                 0xFFFC
#define COLOR_LIME                 0x07E0
#define COLOR_LIMEGREEN                 0x3666
#define COLOR_LINEN                 0xFF9C
#define COLOR_MAGENTA                 0xF81F
#define COLOR_MAROON                 0x8000
#define COLOR_MEDIUMAQUAMARINE                 0x6675
#define COLOR_MEDIUMBLUE                 0x0019
#define COLOR_MEDIUMORCHID                 0xBABA
#define COLOR_MEDIUMPURPLE                 0x939B
#define COLOR_MEDIUMSEAGREEN                 0x3D8E
#define COLOR_MEDIUMSLATEBLUE                 0x7B5D
#define COLOR_MEDIUMSPRINGGREEN                 0x07D3
#define COLOR_MEDIUMTURQUOISE                 0x4E99
#define COLOR_MEDIUMVIOLETRED                 0xC0B0
#define COLOR_MIDNIGHTBLUE                 0x18CE
#define COLOR_MINTCREAM                 0xF7FF
#define COLOR_MISTYROSE                 0xFF3C
#define COLOR_MOCCASIN                 0xFF36
#define COLOR_NAVAJOWHITE                 0xFEF5
#define COLOR_NAVY                 0x0010
#define COLOR_OLDLACE                 0xFFBC
#define COLOR_OLIVE                 0x8400
#define COLOR_OLIVEDRAB                 0x6C64
#define COLOR_ORANGE                 0xFD20
#define COLOR_ORANGERED                 0xFA20
#define COLOR_ORCHID                 0xDB9A
#define COLOR_PALEGOLDENROD                 0xEF55
#define COLOR_PALEGREEN                 0x9FD3
#define COLOR_PALETURQUOISE                 0xAF7D
#define COLOR_PALEVIOLETRED                 0xDB92
#define COLOR_PAPAYAWHIP                 0xFF7A
#define COLOR_PEACHPUFF                 0xFED7
#define COLOR_PERU                 0xCC27
#define COLOR_PINK                 0xFE19
#define COLOR_PLUM                 0xDD1B
#define COLOR_POWDERBLUE                 0xB71C
#define COLOR_PURPLE                 0x8010
#define COLOR_RED                 0xF800
#define COLOR_ROSYBROWN                 0xBC71
#define COLOR_ROYALBLUE                 0x435C
#define COLOR_SADDLEBROWN                 0x8A22
#define COLOR_SALMON                 0xFC0E
#define COLOR_SANDYBROWN                 0xF52C
#define COLOR_SEAGREEN                 0x2C4A
#define COLOR_SEASHELL                 0xFFBD
#define COLOR_SIENNA                 0xA285
#define COLOR_SILVER                 0xC618
#define COLOR_SKYBLUE                 0x867D
#define COLOR_SLATEBLUE                 0x6AD9
#define COLOR_SLATEGRAY                 0x7412
#define COLOR_SNOW                 0xFFDF
#define COLOR_SPRINGGREEN                 0x07EF
#define COLOR_STEELBLUE                 0x4416
#define COLOR_TAN                 0xD5B1
#define COLOR_TEAL                 0x0410
#define COLOR_THISTLE                 0xDDFB
#define COLOR_TOMATO                 0xFB08
#define COLOR_TURQUOISE                 0x471A
#define COLOR_VIOLET                 0xEC1D
#define COLOR_WHEAT                 0xF6F6
#define COLOR_WHITE                 0xFFFF
#define COLOR_WHITESMOKE                 0xF7BE
#define COLOR_YELLOW                 0xFFE0
#define COLOR_YELLOWGREEN                 0x9E66

// MARK: - Types

typedef unsigned short color_t;

typedef struct {
    unsigned cursorX;
    unsigned cursorY;
    unsigned _unknown;
    unsigned cursorFlashFlag;
    unsigned char _unknownChar;
} TCursorSettings;

typedef enum : char {
    CursorTypeNormal = 0, CursorTypeFull = 6, CursorTypeArrow = 12
} TCursorType;

typedef enum : int {
    ColorModeIndex = 0, ColorModeFull = 1
} TColorMode;

typedef enum : char {
    TextColorBlack   = 0,
    TextColorBlue    = 1,
    TextColorGreen   = 2,
    TextColorCyan    = 3,
    TextColorRed     = 4,
    TextColorMagenta = 5,
    TextColorYellow  = 6,
    TextColorWhite   = 7
} TTextColor;

typedef enum : int {
    FrameModeWhite = 0, FrameModeColor = 1
} TFrameMode;

typedef enum : unsigned char {
    AreaModeWhite = 0, AreaModeColor = 1
} TAreaMode;

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
    TAreaMode mode;
} TBdispFillArea;

typedef enum {
    TargetVRAM = 0, TargetDD = 1
} TTarget;

typedef struct {
    int dx;
    int dy;
    int wx;
    int wy;
    int color;
    TBdispFillArea saved;
} TBdispShape;

typedef struct {
    int x;
    int y;
    int xofs;
    int yofs;
    int width;
    int height;
    char colormode;
    char zero4;
    char P20_1;
    char P20_2;
    int bitmap;
    char color_idx1;
    char color_idx2;
    char color_idx3;
    char P20_3;
    char writemodify;
    char writekind;
    char zero6;
    char one1;
    int transparency;
} TBdispGrapth;

typedef enum : int {
    StatusAreaEnabled = 0, StatusAreaDisable = 3
} TStatusArea;

typedef enum : int {
    BatteryIconHide = 0, BatteryIconShow = 1
} TBatteryIcon;

typedef enum : int {
    BatteryTypeAlkaline = 1, BatteryTypeNiMH = 2
} TBatteryType;

typedef struct {
    unsigned int   _unknown_1;         // unknown: changes indicator height, set to 0
    unsigned int    indicatorMaximum;  // max logical indicator range
    unsigned int    indicatorHeight;   // height of the indicator in units
    unsigned int    indicatorPosition; // indicator position in units of max
    unsigned int   _unknown_2;         // unknown: set to 0
    unsigned short  barLeft;           // x position of bar
    unsigned short  barTop;            // y position of bar
    unsigned short  barHeight;         // height of bar
    unsigned short  barWidth;          // width of bar
} TScrollbar;

typedef struct {
  unsigned short  width;     // set to 384
  unsigned short  height;    // set to 192
  unsigned short _unknown_1; // set to 0x10
  unsigned short _unknown_2; // set to 0x00
  unsigned short _unknown_3; // set to 0x01
  unsigned short _unknown_4; // set to 0xF800
  unsigned short *bitmap;    // pointer to the bitmap to set as background.
} TBGRbitmap

inline TBGRbitmap BGRbitmapMake(color_t *bitmap) {
    return (TBGRbitmap){.width = 384, .height = 192, 0x10, 0, 1, 0xF800, .bitmap = bitmap};
}

typedef enum {
    DeviceTypeCG10 = 0,
    DeviceTypeCG20 = 0,
    DeviceTypeCG50 = 1,
    DeviceTypeSimulator = -1
} TDeviceType;

inline TDeviceType GetDeviceType(void) {
#if TARGET_PRIZM
    return (unsigned int)GetVRAMAddress() == 0xAC000000 ? DeviceTypeCG50 : DeviceTypeCG20;
#else
    return DeviceTypeSimulator;
#endif
}

typedef enum {
    BackgroundModeMatrix               = 0,  // Matrix Mode Background
    BackgroundModeEquation             = 1,  // Equation Mode Background
    BackgroundModeEActivity            = 2,  // eActivity Mode Background
    BackgroundModeProgram              = 3,  // Program Mode Background
    BackgroundModeFinancial            = 4,  // Financial Mode Background
    BackgroundModeWakeupEnable         = 5,  // "Wakeup enable" background (Link mode)
    BackgroundModeBackup               = 6,  // "Backup" background (Memory mode)
    BackgroundModeSystem               = 7,  // System Mode Background
    BackgroundModeLanguage             = 8,  // Language Background
    BackgroundModeSearchForProgram     = 9,  // "Search For Program" background (Program mode)
    BackgroundModeNewFile              = 10, // "New File" Background
    BackgroundModeConversion           = 11, // Conversion Mode Background
    BackgroundModeOpenSpreadsheet      = 12, // "Open Spreadsheet" Background
    BackgroundModeSaveSpreadsheet      = 13, // "Save" Background (Spreadsheet mode)
    BackgroundModeCaptureSet           = 14, // "Capture Set Mode" background (Link Mode)
    BackgroundModeOpenGeometryFile     = 15, // Open Geometry File Background
    BackgroundModeSelectCableType      = 16, // "Select Cable Type" background (Link Mode)
    BackgroundModeSelectCableTypeAlt   = 17, // Same as 16
    BackgroundModePCToCalcTransfer     = 18  // PC => Calc Transfer Background (Link Mode)
} TBackgroundMode;

#ifdef __cplusplus
extern "C" {
#endif
    
    // MARK: - General display manipulating syscalls:
    /**
     @brief Performs a VRAM or DD operation to fill an area with a color, depending on the mode of area.
     @param area area to fill, and mode
     @param target where to perform the operation, VRAM or DD. If bit target.0 is set, the function performs a VRAM operation. If bit target.1 is set, the function performs a DD operation.
     @param color color that will be used to fill when certain modes are used.
     */
    void Bdisp_AreaClr(TBdispFillArea *area, TTarget target, color_t color);
    
    /**
     @brief Switches the screen between full color mode (16 bits per pixel, RGB565) and indexed color mode (3 bits per pixel, 8 colors - the same that can be used with PrintXY).
     @param mode  0 to disable full color, 1 to enable full color.
     */
    void Bdisp_EnableColor(TColorMode mode);
    
    // MARK: - Frame control:
    void DrawFrame(int color);
    color_t FrameColor(TFrameMode mode, color_t color);
    void DrawFrameWorkbench(int, int, int, int, int);
    
    // MARK: - VRAM general display manipulating syscalls:
    void *GetVRAMAddress(void); // Return a pointer to the system's video memory.
    void *GetSecondaryVRAMAddress(void); // Return a pointer to the memory used by SaveVRAM_1 and LoadVRAM_1.
    void Bdisp_AllClr_VRAM(void);
    void Bdisp_SetPoint_VRAM(int x, int y, color_t color);
    void Bdisp_SetPointWB_VRAM(int x, int y, color_t color);
    color_t Bdisp_GetPoint_VRAM(int x, int y);
    void SaveVRAM_1(void);
    void LoadVRAM_1(void);
    void Bdisp_Fill_VRAM(int color, int mode);
    
    void SetBackGround(TBackgroundMode mode);
    void WriteBackground(void* target, int width, int height, void* source, int P5, int P6, int P7);
    
    // MARK: - DD display manipulating syscalls:
    void Bdisp_AreaClr_DD_x3(void*p1);
    void Bdisp_DDRegisterSelect(int registerno);
    void Bdisp_PutDisp_DD(void);
    void Bdisp_PutDisp_DD_stripe(int y1, int y2);
    void Bdisp_SetPoint_DD(int x, int y, int color);
    color_t Bdisp_GetPoint_DD_Workbench(int x, int y);
    color_t Bdisp_GetPoint_DD(int x, int y);
    void DirectDrawRectangle(int x1, int y1, int x2, int y2, color_t color);
    void HourGlass(void);
    void Bdisp_DefineDMARange(int x1, int x2, int y1, int y2);
    unsigned short Bdisp_WriteDDRegister3_bit7(int value);
    
    // MARK: - Graphic writing:
    void Bdisp_WriteGraphVRAM(TBdispGrapth *gd);
    void Bdisp_WriteGraphDD_WB(TBdispGrapth *gd);
    
    // MARK: - Shape drawing:
    void Bdisp_ShapeBase3XVRAM(void*shape);
    void Bdisp_ShapeBase(unsigned char *work, TBdispShape *shape, int color, int line_width, int zero1, int zero2);
    void Bdisp_ShapeToVRAM16C(void*, int color);
    void Bdisp_ShapeToDD(void*shape, int color);
    
    // The following rectangle-related syscalls draw a rectangle to VRAM, x between 0 and 383 (inclusive), y between 0 and 191 (inclusive).
    // These add 24 pixels automatically, avoiding the status area:
    
    // Draws a rectangle to VRAM
    void Bdisp_Rectangle(int x1, int y1, int x2, int y2, TTextColor color);
    // Draws a filled rectangle to VRAM
    void Bdisp_FilledRectangle(int x1, int y1, int x2, int y2, TTextColor color);
    // Draws a filled rectangle to VRAM using a color_t
    void Bdisp_FilledRectangleFullColor(int x1, int y1, int x2, int y2, color_t color);
    
    
    // MARK: - Background-related syscalls
    void SetBackGround(int);
    void WriteBackground(void *target, int width, int height, void*source, int, int, int);
    
    // MARK: - Message boxes, error messages, dialogs and the like:
    void Box(int, int, int, int, int);
    void BoxInnerClear(int);
    void Box2(int, int);
    void BoxYLimits(int lines, int*top, int*bottom);
    void AUX_DisplayErrorMessage(int msgno);
    void MsgBoxPush(int lines);
    void MsgBoxPop(void);
    void DisplayMessageBox(unsigned char*message);
    short CharacterSelectDialog(void);
    unsigned char ColorIndexDialog1(unsigned char initial_index, unsigned short disable_mask);
    void MsgBoxMoveWB(void*buffer, int x0, int y0, int x1, int y1, int direction); //it's more general purpose, works not only for MsgBoxes but for any VRAM contents.
    
    // MARK: - Cursor manipulating syscalls:
    int locate_OS(int X, int y);
    
    /**
     * @brief Retrieves the current cursor settings.
     *
     * This function returns the cursor settings, including position and flashing state.
     *
     * @param settings Either an array of 17 bytes or a pointer to a variable of type `struct cursorSettings`.
     *
     * @return The value of `cursorFlashFlag`.
     *
     * @note
     * - Header: `fxcg/display.h` (Not yet in libfxcg)
     * - Syscall index: `0x01F5`
     * - Function signature: `unsigned int Cursor_GetSettings(struct cursorSettings*);`
     */
    unsigned int Cursor_GetSettings(TCursorSettings *cursorSettings);
    
    /**
     * @brief Enables the cursor display at the current cursor position.
     *
     * This function enables the cursor display at the position set by locate_OS.
     * The cursor type is specified by the `cursor_type` parameter and is stored in
     * FlashStyle by syscall 0x01F2 according to the predefined cursor type map.
     *
     * @param cursor_type The cursor type to be displayed.
     *
     * @note
     * - Header: fxcg/display.h
     * - Syscall index: 0x08C7
     * - Function signature: `void Cursor_SetFlashOn(unsigned char cursor_type)`
     */
    void Cursor_SetFlashOn(CursorType cursorType);
    
    void Cursor_SetFlashOff(void);
    
    /**
     * @brief Sets the cursor position for Print_OS.
     *
     * This function sets the cursor position to the specified (x, y) coordinates.
     *
     * @param x The horizontal position, must be in the range [0, 20].
     * @param y The vertical position, must be in the range [0, 7].
     *
     * @return Returns 1 on success, 0 on failure.
     *
     * @note
     * Syscall index: 0x01F1
     */
    int Cursor_SetPosition(int x, int y);
    
    int SetCursorFlashToggle(int);
    void Keyboard_CursorFlash(void);
    
    // MARK: - Character printing syscalls:
    
    void PrintLine(const char *msg, int imax);
    void PrintLine2(int, int, const char *, int, int, int, int, int);
    void PrintXY_2(int mode, int x, int y, int msgno, int color);
    void PrintXY(int x, int y, const char *string, int mode, int color);
    void PrintCXY(int, int, const char *, int, int, int, int, int, int);
    void PrintGlyph(int, int, unsigned char*glyph, int, int color, int back_color, int);
    void*GetMiniGlyphPtr(unsigned short mb_glyph_no, unsigned short*glyph_info);
    void PrintMiniGlyph(int x, int y, void*glyph, int mode_flags, int glyph_width, int, int, int, int, int color, int back_color, int );
    void PrintMini(int *x, int *y, const char *MB_string, int mode_flags, unsigned int xlimit, int P6, int P7, int color, int back_color, int writeflag, int P11);
    void PrintMiniMini(int *x, int *y, const char *MB_string, int mode1, char color, int mode2);
    void Print_OS(const char*msg, int mode, int zero2);
    void Bdisp_WriteSystemMessage(int x, int y, int msgno, int mode, char color3);
    void Bdisp_MMPrintRef(int*x, int*y, unsigned char*, int mode, int xmax, int, int, int color, int, int, int);
    void Bdisp_MMPrint(int x, int y, unsigned char*, int mode, int xmax, int, int, int color, int backcolor, int, int);
    
    enum
    {
        PRINT_CHARSET_DEFAULT = 0,
        PRINT_CHARSET_GB18030 = 0x03a8,
    };
    
    /**
     * Set the character set used for following text output functions.
     *
     * Known values are provided as PRINT_CHARSET_* constants.
     *
     * Returns 1 if the provided charset code is recognized, 0 otherwise.
     */
    int ProcessPrintChars(unsigned short charset);
    
    /** Set the character set to GB18030. */
    void EnableGB18030(void);
    /** Set the character set to latin. */
    void DisableGB18030(void);
    
    // MARK: - Progressbars and scrollbars:
    
    
    void Scrollbar(TScrollbar *scrollbar);
    void StandardScrollbar(void*);
    void ProgressBar(int, int );
    void ProgressBar0(int P1, int P2, int P3, int current, int max);
    void ProgressBar2(unsigned char *heading, int current, int max);
    
    // MARK: - Status Area/Header Related syscalls:
    
    int DefineStatusAreaFlags(int mode, int flags, char *color1, char *color2);
    void DefineStatusGlyph(int, void*);
    void DefineStatusMessage(char*msg, short P2, char P3, char P4);
    void DisplayStatusArea(void);
    void DrawHeaderLine(void);
    void EnableStatusArea(TStatusArea opt);
    void Bdisp_HeaderFill(unsigned char color_idx1, unsigned char color_idx2);
    void Bdisp_HeaderFill2(unsigned int, unsigned int, unsigned char, unsigned char);
    void Bdisp_HeaderText(void);
    void Bdisp_HeaderText2(void);
    void EnableDisplayHeader(int, int);
    
    // MARK: - Status area icon syscalls: (it may be more appropriate to use the status area flags)
    void APP_EACT_StatusIcon(int); //not sure what this is exactly for, if it displays something on screen it's here, otherwise in app.h. will test some day (gbl08ma)
    void SetupMode_StatusIcon(void); //not sure what this does, doesn't seem to be documented anywhere. will test some day (gbl08ma)
    void d_c_Icon(unsigned int);
    
    void BatteryIcon(TBatteryIcon);
    TBatteryType GetBatteryType(void);
    
    void KeyboardIcon(unsigned int);
    void LineIcon(unsigned int);
    void NormIcon(unsigned int);
    void RadIcon(unsigned int);
    void RealIcon(unsigned int);
    
    // MARK: - Other:
    void FKey_Display(int, void*);
    void GetFKeyPtr(int, void*);
    void DispInt(int, int); //not sure what this does, doesn't seem to be documented anywhere. will test some day (gbl08ma)
    int LocalizeMessage1(int msgno, char*result);
    int SMEM_MapIconToExt(unsigned char*filename, unsigned short*foldername, unsigned int*msgno, unsigned short*iconbuffer); // despite starting with SMEM, this is mostly a graphical function used to get icons for different file types.
    
    // MARK: - Not syscalls (defined within libfxcg):
    void VRAM_CopySprite(const color_t* data, int x, int y, int width, int height);
    void VRAM_XORSprite(const color_t* data, int x, int y, int width, int height);


    
#ifdef __cplusplus
}
#endif

#endif /* __FXCG_DISPLAY_H */
