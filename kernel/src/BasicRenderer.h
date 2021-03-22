#pragma once

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

    BasicRenderer(Framebuffer *TargetFramebuffer, PSF1_FONT *psf1_Font);

    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void Print(const char *str);
};