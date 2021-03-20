typedef unsigned long long size_t;

typedef struct
{
    void *BaseAddress;
    size_t BufferSize;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelsPerScanLine;
} FrameBuffer;

typedef struct
{
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
} PSF1_HEADER;

typedef struct
{
    PSF1_HEADER *psf1_Header;
    void *glyphBuffer;
} PSF1_FONT;

typedef struct
{
    unsigned int X;
    unsigned int Y;
} Point;


void putChar(FrameBuffer *frameBuffer, PSF1_FONT *psf1_Font, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int *pixPtr = (unsigned int *)frameBuffer->BaseAddress;

    char *fontPtr = psf1_Font->glyphBuffer + (chr * psf1_Font->psf1_Header->charsize);

    for (unsigned long y = yOff; y < yOff + 16; y++)
    {
        for (unsigned long x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int *)(pixPtr + x + (y * frameBuffer->PixelsPerScanLine)) = colour;
            }
        }

        fontPtr++;
    }

    return;
}

Point CursorPosition;

void Print(FrameBuffer *frameBuffer, PSF1_FONT *psf1_Font, unsigned int colour, char* str)
{
    unsigned int x = 0;

    char* chr = str;

    while (*chr != 0)
    {
        putChar(frameBuffer, psf1_Font, colour, *chr, CursorPosition.X, CursorPosition.Y);

        CursorPosition.X += 8;

        if (CursorPosition.X + 8 > frameBuffer->Width - 24)
        {
            CursorPosition.X = 24;
            CursorPosition.Y += 16;
        }

        chr++;
    }
    
    return;
}

void _start(FrameBuffer *frameBuffer, PSF1_FONT *psf1_Font)
{
    /* unsigned int y = 50;
    unsigned int BPP = 4;

    for (unsigned int x = 0; x < frameBuffer->Width / 2 * BPP; x += BPP)
    {
        *(unsigned int *)(x + (y * frameBuffer->PixelsPerScanLine * BPP) + frameBuffer->BaseAddress) = 0xffffffff;
    } */

    CursorPosition.X = 24;
    CursorPosition.Y = 24;

    Print(frameBuffer, psf1_Font, 0xffffffff, "====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================");
    
    CursorPosition.X = 24;
    CursorPosition.Y += 16;

    Print(frameBuffer, psf1_Font, 0xffffffff, "Font loaded successfully");

    CursorPosition.X = 24;
    CursorPosition.Y += 32;

    Print(frameBuffer, psf1_Font, 0xffffffff, "Welcome to Alpha OS");

    CursorPosition.X = 24;
    CursorPosition.Y += 32;

    Print(frameBuffer, psf1_Font, 0xffffffff, "====================================================================================================================================================================================================================================================================================================================================================================================================================================================================================");

    return;
}