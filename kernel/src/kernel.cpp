#include <stddef.h>

#include "BasicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "Bitmap.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"

struct BootInfo
{
    Framebuffer *framebuffer;
    PSF1_FONT *psf1_Font;
    EFI_MEMORY_DESCRIPTOR *mMap;
    uint64_t mMapSize;
    uint64_t mMapDescSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

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

    // Setup basic renderer and Memory tools

    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GlobalAllocator = PageFrameAllocator();

    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    PageMapIndexer pageIndexer = PageMapIndexer(0x1000);

    // Kernel size and lock kernel pages

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

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

    newRenderer.CursorPosition.X = 500;

    newRenderer.Print("!! Memory informations !!");

    newRenderer.CursorPosition.X = 1000 - 24;

    newRenderer.Print("!! Memory Request !!");

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Result One: ");
    newRenderer.Print(to_string((uint64_t)1234567890));

    newRenderer.CursorPosition.X = 500;

    newRenderer.Print("Total RAM: ");
    newRenderer.Print(to_string(GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize) / 1024));
    newRenderer.Print(" KB");

    unsigned int OriginalYPos = newRenderer.CursorPosition.Y;

    newRenderer.CursorPosition.X = 1000 - 24;

    for (int t = 0; t < 4; t++)
    {
        for (int i = 0; i < 5; i++)
        {
            void *address = newAllocator.RequestPage();

            newRenderer.Print(to_hstring((uint64_t)address));
            newRenderer.Print(" ");
        }

        newRenderer.CursorPosition.X = 1000 - 24;
        newRenderer.CursorPosition.Y += 16;
    }

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y = OriginalYPos + 32;

    newRenderer.Print("Result Two: ");
    newRenderer.Print(to_string((int64_t)-1234567890));

    newRenderer.CursorPosition.X = 500;

    newRenderer.Print("Free RAM: ");
    newRenderer.Print(to_string(newAllocator.GetFreeRAM() / 1024));
    newRenderer.Print(" KB");

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Result Three: ");
    newRenderer.Print(to_string((double)-12345.67890, 5));

    newRenderer.CursorPosition.X = 500;

    newRenderer.Print("Used RAM: ");
    newRenderer.Print(to_string(newAllocator.GetUsedRAM() / 1024));
    newRenderer.Print(" KB");

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Result Four: 0x");
    newRenderer.Print(to_hstring((uint64_t)0x123456F89ABCDEF));

    newRenderer.CursorPosition.X = 500;

    newRenderer.Print("Reserved RAM: ");
    newRenderer.Print(to_string(newAllocator.GetReservedRAM() / 1024));
    newRenderer.Print(" KB");

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 32;

    PrintLine(&newRenderer, 2);

    // Print memory map entry details

    newRenderer.CursorPosition.X = 24;
    newRenderer.CursorPosition.Y += 16;

    newRenderer.Print("!! Memory map entry details !!");

    newRenderer.CursorPosition.X = 500;

    newRenderer.Print("!! Page map index details !!");

    OriginalYPos = newRenderer.CursorPosition.Y;

    newRenderer.CursorPosition.X = 500;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Page : ");
    newRenderer.Print(to_string(pageIndexer.P_i));

    newRenderer.CursorPosition.X = 500;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Page Table : ");
    newRenderer.Print(to_string(pageIndexer.PT_i));

    newRenderer.CursorPosition.X = 500;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Page Directory : ");
    newRenderer.Print(to_string(pageIndexer.PD_i));

    newRenderer.CursorPosition.X = 500;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Print("Page Directory Pointer : ");
    newRenderer.Print(to_string(pageIndexer.PDP_i));

    newRenderer.CursorPosition.Y = OriginalYPos;

    newRenderer.CursorPosition.X = 24;

    for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));

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