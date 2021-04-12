#include "kernelUtil.h"

void PrintStatus(BasicRenderer *GlobalRenderer, bool isSuccess);
void PrintLogo(BasicRenderer *GlobalRenderer);
void PrintDesc(BasicRenderer *GlobalRenderer);

extern "C" void _start(BootInfo *bootInfo)
{
    KernelInfo KernelInfo = InitializeKernel(bootInfo);

    PageTableManager *pageTableManager = KernelInfo.pageTableManager;

    // GlobalRenderer->ClearColour = 0xff151515;

    // GlobalRenderer->Clear();

    // GlobalRenderer->CursorPosition.X = 16;
    // GlobalRenderer->CursorPosition.Y = 16;

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
    GlobalRenderer->Print("Interrupts was set successfully");

    GlobalRenderer->Next(1);

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("RSDP was set successfully");

    GlobalRenderer->Next(1);

    PrintDesc(GlobalRenderer);
    GlobalRenderer->Print("Address: 0x");
    GlobalRenderer->Print(to_hstring((uint64_t)bootInfo->rsdp));

    GlobalRenderer->Next(1);

    PrintDesc(GlobalRenderer);
    GlobalRenderer->Print("Vendor Table: ");
    GlobalRenderer->PutChar(*(uint8_t *)bootInfo->rsdp);
    GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 1));
    GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 2));
    GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 3));
    GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 4));
    GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 5));
    GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 6));
    GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 7));

    GlobalRenderer->Next(2);

    PrintStatus(GlobalRenderer, true);
    GlobalRenderer->Print("Kernel initialized successfully");

    GlobalRenderer->Next(2);

    PrintLogo(GlobalRenderer);

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

void PrintStatus(BasicRenderer *GlobalRenderer, bool isSuccess)
{
    switch (isSuccess)
    {
    case true:
    {
        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("[");

        GlobalRenderer->Colour = 0xff00ff00;
        GlobalRenderer->Print("   OK   ");

        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("]   ");

        break;
    }

    case false:
    {
        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("[");

        GlobalRenderer->Colour = 0xff00ff00;

        GlobalRenderer->Print("  ERROR  ");

        GlobalRenderer->Colour = 0xffffffff;

        GlobalRenderer->Print("]   ");

        break;
    }
    }

    return;
}

void PrintLogo(BasicRenderer *GlobalRenderer)
{
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

    return;
}

void PrintDesc(BasicRenderer *GlobalRenderer)
{
    GlobalRenderer->Print("             -   ");

    return;
}