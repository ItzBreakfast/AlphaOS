#pragma once

#include <stdint.h>

#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h"

class BasicRenderer
{
public:
    Point CursorPosition;
    Framebuffer *TargetFramebuffer;
    PSF1_FONT *PSF1_Font;
    unsigned int Colour;
    unsigned int ClearColour;
    bool MouseDrawn;
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];

    BasicRenderer(Framebuffer *TargetFramebuffer, PSF1_FONT *psf1_Font);

    void PutPix(uint32_t x, uint32_t y, uint32_t colour);
    void PutChar(char chr, long xOff, long yOff);
    void PutChar(char chr);
    void Print(const char *str);
    void Clear();
    void ClearChar();
    void ClearMouseCursor(uint8_t *mouseCursor, Point position);
    void Next(int times);
    void DrawOverlayMouseCursor(uint8_t *mouseCursor, Point position, uint32_t colour);
    uint32_t GetPix(uint32_t x, uint32_t y);
};

void PrintDesc();
void PrintLogo(long xOff, long yOff);
void PrintStatus(bool isSuccess);

extern BasicRenderer *GlobalRenderer;