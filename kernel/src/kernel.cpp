#include "kernelUtil.h"

void PrintStatus(BasicRenderer *newRenderer, bool isSuccess)
{
    switch (isSuccess)
    {
    case true:
    {
        newRenderer->Colour = 0xffffffff;

        newRenderer->Print("[");

        newRenderer->Colour = 0xff00ff00;
        newRenderer->Print("OK");

        newRenderer->Colour = 0xffffffff;

        newRenderer->Print("] ");

        break;
    }

    case false:
    {
        newRenderer->Colour = 0xffffffff;

        newRenderer->Print("[");

        newRenderer->Colour = 0xff00ff00;

        newRenderer->Print("ERROR");

        newRenderer->Colour = 0xffffffff;

        newRenderer->Print("] ");

        break;
    }
    }
}

extern "C" void _start(BootInfo *bootInfo)
{
    KernelInfo KernelInfo = InitializeKernel(bootInfo);

    PageTableManager *pageTableManager = KernelInfo.pageTableManager;

    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    newRenderer.CursorPosition.X = 16;
    newRenderer.CursorPosition.Y = 24;

    PrintStatus(&newRenderer, true);
    newRenderer.Print("All files loaded successfully");

    newRenderer.CursorPosition.X = 16;
    newRenderer.CursorPosition.Y += 16;

    PrintStatus(&newRenderer, true);
    newRenderer.Print("GOP located successfully");

    newRenderer.CursorPosition.X = 16;
    newRenderer.CursorPosition.Y += 16;

    PrintStatus(&newRenderer, true);
    newRenderer.Print("Renderer was set Successfully");

    newRenderer.CursorPosition.X = 16;
    newRenderer.CursorPosition.Y += 16;

    PrintStatus(&newRenderer, true);
    newRenderer.Print("Page tables was set successfully");

    newRenderer.CursorPosition.X = 16;
    newRenderer.CursorPosition.Y += 16;

    PrintStatus(&newRenderer, true);
    newRenderer.Print("Kernel initialized successfully");

    newRenderer.CursorPosition.X = 16;
    newRenderer.CursorPosition.Y += 32;

    newRenderer.Colour = 0xff00ff00;

    newRenderer.Print("Welcome to Alpha OS");

    newRenderer.Colour = 0xffffffff;

    while (true)
        ;
}