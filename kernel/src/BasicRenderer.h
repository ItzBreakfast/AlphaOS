#pragma once

#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h"
#include <stdint.h>

class BasicRenderer
{
public:
    Point CursorPosition;
    Framebuffer *TargetFramebuffer;
    PSF1_FONT *PSF1_Font;
    unsigned int Colour;
    unsigned int ClearColour;

    BasicRenderer(Framebuffer *TargetFramebuffer, PSF1_FONT *psf1_Font);

    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void Print(const char *str);
    void Clear();
    void ClearChar();
    void Next(int times);
};

extern BasicRenderer *GlobalRenderer;