#include "BasicRenderer.h"

BasicRenderer *GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer *targetFramebuffer, PSF1_FONT *psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    Colour = 0xffffffff;
    CursorPosition = {0, 0};
}

void BasicRenderer::Clear()
{
    uint64_t fbBase = (uint64_t)TargetFramebuffer->BaseAddress;
    uint64_t fbSize = TargetFramebuffer->BufferSize;
    uint64_t fbHeight = TargetFramebuffer->Height;
    uint64_t bytesPerScanLine = TargetFramebuffer->PixelsPerScanLine * 4;

    for (int verticalScanLine = 0; verticalScanLine < fbHeight; verticalScanLine++)
    {
        uint64_t pixPtrBase = fbBase + (bytesPerScanLine * verticalScanLine);

        for (uint32_t *pixPtr = (uint32_t *)pixPtrBase; pixPtr < (uint32_t *)(pixPtrBase + bytesPerScanLine); pixPtr++)
        {
            *pixPtr = ClearColour;
        }
    }

    return;
}

void BasicRenderer::ClearChar()
{
    if (CursorPosition.X == 16)
    {
        CursorPosition.X = TargetFramebuffer->Width;
        CursorPosition.Y -= 16;

        if (CursorPosition.Y < 16)
            CursorPosition.Y = 16;
    }

    unsigned int xOff = CursorPosition.X;
    unsigned int yOff = CursorPosition.Y;

    unsigned int *pixPtr = (unsigned int *)TargetFramebuffer->BaseAddress;

    for (unsigned long y = yOff; y < yOff + 16; y++)
    {
        for (unsigned long x = xOff - 8; x < xOff + 8; x++)
        {
            *(unsigned int *)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = ClearColour;
        }
    }

    CursorPosition.X -= 8;

    if (CursorPosition.X < 16)
    {
        CursorPosition.X = TargetFramebuffer->Width;
        CursorPosition.Y -= 16;

        if (CursorPosition.Y < 16)
            CursorPosition.Y = 16;
    }

    return;
}

void BasicRenderer::Next(int times)
{
    for (int i = 0; i < times; i++)
    {
        CursorPosition.X = 16;
        CursorPosition.Y += 16;
    }

    return;
}

void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int *pixPtr = (unsigned int *)TargetFramebuffer->BaseAddress;

    char *fontPtr = (char *)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);

    for (unsigned long y = yOff; y < yOff + 16; y++)
    {
        for (unsigned long x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int *)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Colour;
            }
        }

        fontPtr++;
    }

    return;
}

void BasicRenderer::PutChar(char chr)
{
    PutChar(chr, CursorPosition.X, CursorPosition.Y);

    CursorPosition.X += 8;

    if (CursorPosition.X + 8 > TargetFramebuffer->Width)
    {
        CursorPosition.X = 16;
        CursorPosition.Y += 16;
    }

    return;
}

void BasicRenderer::Print(const char *str)
{
    unsigned int x = 0;
    unsigned int baseCursorPosition = CursorPosition.X;

    if (baseCursorPosition > 24)
        baseCursorPosition = 24;

    char *chr = (char *)str;

    while (*chr != 0)
    {
        PutChar(*chr, CursorPosition.X, CursorPosition.Y);

        CursorPosition.X += 8;

        if (CursorPosition.X + 8 > TargetFramebuffer->Width - baseCursorPosition)
        {
            CursorPosition.X = baseCursorPosition;
            CursorPosition.Y += 16;
        }

        chr++;
    }

    return;
}