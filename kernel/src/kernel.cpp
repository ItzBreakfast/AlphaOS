#include "kernelUtil.h"

void PrintStatus(BasicRenderer *GlobalRenderer, bool isSuccess)
{
    switch (isSuccess)
    {
    case true:
    {
        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("[");

        GlobalRenderer->Colour = 0xff00ff00;
        GlobalRenderer->Print(" OK ");

        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("] ");

        break;
    }

    case false:
    {
        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("[");

        GlobalRenderer->Colour = 0xff00ff00;

        GlobalRenderer->Print(" ERROR ");

        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("] ");

        break;
    }
    }
}

extern "C" void _start(BootInfo *bootInfo)
{
    KernelInfo KernelInfo = InitializeKernel(bootInfo);

    PageTableManager *pageTableManager = KernelInfo.pageTableManager;

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y = 24;

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("All files loaded successfully");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("GOP located successfully");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("Renderer was set Successfully");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("Page tables was set successfully");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("Kernel initialized successfully");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 32;

    GlobalRenderer->Print("     ___       __      .______    __    __       ___           ______        _______.");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    GlobalRenderer->Print("    /   \\     |  |     |   _  \\  |  |  |  |     /   \\         /  __  \\      /       |");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    GlobalRenderer->Print("   /  ^  \\    |  |     |  |_)  | |  |__|  |    /  ^  \\       |  |  |  |    |   (----`");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    GlobalRenderer->Print("  /  /_\\  \\   |  |     |   ___/  |   __   |   /  /_\\  \\      |  |  |  |     \\   \\    ");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    GlobalRenderer->Print(" /  _____  \\  |  `----.|  |      |  |  |  |  /  _____  \\     |  `--'  | .----)   |   ");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    GlobalRenderer->Print("/__/     \\__\\ |_______|| _|      |__|  |__| /__/     \\__\\     \\______/  |_______/    ");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 16;

    GlobalRenderer->Print("                                                                                     ");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 32;

    GlobalRenderer->Colour = 0xff00ff00;

    GlobalRenderer->Print("Welcome to Alpha OS terminal");

    GlobalRenderer->Colour = 0xffffffff;

    // asm ("int $0x0e");

    while (true)
        ;
}