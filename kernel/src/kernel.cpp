#include <stddef.h>

#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"

struct BootInfo
{
    Framebuffer *framebuffer;
    PSF1_FONT *psf1_Font;
    void *mMap;
    uint64_t mMapSize;
    uint64_t mMapDescSize;
};

void PrintLine(BasicRenderer *basicRenderer, int lines)
{
    for (int i = 0; i < lines; i++)
    {
        basicRenderer->Print("==========================================================================================================================================================================================================================================");
    }

    return;
}

extern "C" void _start(BootInfo *bootInfo)
{
    /* unsigned int y = 50;
    unsigned int BPP = 4;

    for (unsigned int x = 0; x < framebuffer->Width / 2 * BPP; x += BPP)
    {
        *(unsigned int *)(x + (y * framebuffer->PixelsPerScanLine * BPP) + framebuffer->BaseAddress) = 0xffffffff;
    } */

    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    // Basic information and Number to String conversion test

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y = 24;

    PrintLine(&newRenderer, 2);

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 16;

    newRenderer.Print("!! All files loaded successfully !!");

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Welcome to Alpha OS");

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    PrintLine(&newRenderer, 1);

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 16;

    newRenderer.Print("!! Test Number to String conversion !!");

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Result One: ");
    newRenderer.Print(to_string((uint64_t)1234567890));

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Result Two: ");
    newRenderer.Print(to_string((int64_t)-1234567890));

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Result Three: ");
    newRenderer.Print(to_string((double)-12345.67890, 5));

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Result Four: 0x");
    newRenderer.Print(to_hstring((uint64_t)0x123456789ABCDEF));

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    PrintLine(&newRenderer, 2);

    // Print memory map entry details

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 16;

    newRenderer.Print("!! Memory map entry details !!");

    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DECSCRIPTOR *desc = (EFI_MEMORY_DECSCRIPTOR *)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));

        newRenderer.CursorPosition.X = 24;
        newRenderer.CursorPosition.Y += 32;

        newRenderer.Print("TYPE: ");
        newRenderer.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);

        newRenderer.Colour = 0xffff00ff;

        newRenderer.Print(" SIZE: ");
        newRenderer.Print(to_string(desc->numPages * 4096 / 1024));
        newRenderer.Print(" KB");

        newRenderer.Colour = 0xffffffff;
    }

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    PrintLine(&newRenderer, 2);

    return;
}