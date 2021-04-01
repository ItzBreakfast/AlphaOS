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

    GlobalRenderer->ClearColour = 0xff151515;

    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y = 16;

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("All files loaded successfully");

    GlobalRenderer->Next(1);

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("GOP located successfully");

    GlobalRenderer->Next(1);

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("Renderer was set Successfully");

    GlobalRenderer->Next(1);

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("Page tables was set successfully");

    GlobalRenderer->Next(1);

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("Kernel initialized successfully");

    GlobalRenderer->Next(2);

    GlobalRenderer->Print("     ___       __      .______    __    __       ___           ______        _______.");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print("    /   \\     |  |     |   _  \\  |  |  |  |     /   \\         /  __  \\      /       |");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print("   /  ^  \\    |  |     |  |_)  | |  |__|  |    /  ^  \\       |  |  |  |    |   (----`");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print("  /  /_\\  \\   |  |     |   ___/  |   __   |   /  /_\\  \\      |  |  |  |     \\   \\    ");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print(" /  _____  \\  |  `----.|  |      |  |  |  |  /  _____  \\     |  `--'  | .----)   |   ");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print("/__/     \\__\\ |_______|| _|      |__|  |__| /__/     \\__\\     \\______/  |_______/    ");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print("                                                                                     ");

    GlobalRenderer->Next(2);

    GlobalRenderer->Colour = 0xff00ff00;

    GlobalRenderer->Print("Welcome to Alpha OS terminal!");

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Next(2);

    GlobalRenderer->Print("$ ");

    // asm ("int $0x0e"); // Make page fault

    while (true)
        ;
}