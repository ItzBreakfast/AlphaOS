#include "kernelUtil.h"

void BootingTimeTest(long xOff, long yOff);

extern "C" void _start(BootInfo *bootInfo)
{
    KernelInfo KernelInfo = InitializeKernel(bootInfo);

    PageTableManager *pageTableManager = KernelInfo.pageTableManager;

    PIT::SetDivisor(65535);

    // GlobalRenderer->ClearColour = 0xff151515;

    // GlobalRenderer->Clear();

    // GlobalRenderer->CursorPosition.X = 16;
    // GlobalRenderer->CursorPosition.Y = 16;

    /* =----------= < PRINT SOME IMPORTANT INFORMATIONS > =----------= */

    PrintStatus(true);
    GlobalRenderer->Print("All files loaded successfully");

    GlobalRenderer->Next(1);

    PrintStatus(true);
    GlobalRenderer->Print("GOP located successfully");

    GlobalRenderer->Next(1);

    PrintStatus(true);
    GlobalRenderer->Print("Renderer set Successfully");

    GlobalRenderer->Next(1);

    PrintStatus(true);
    GlobalRenderer->Print("Page tables set successfully");

    GlobalRenderer->Next(1);

    PrintStatus(true);
    GlobalRenderer->Print("Interrupts set successfully");

    GlobalRenderer->Next(1);

    PrintStatus(true);
    GlobalRenderer->Print("RSDP set successfully");

    GlobalRenderer->Next(1);

    // PrintDesc();
    // GlobalRenderer->Print("Address: 0x");
    // GlobalRenderer->Print(to_hstring((uint64_t)bootInfo->rsdp));

    // GlobalRenderer->Next(1);

    // PrintDesc();
    // GlobalRenderer->Print("Vendor Table: ");
    // GlobalRenderer->PutChar(*(uint8_t *)bootInfo->rsdp);
    // GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 1));
    // GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 2));
    // GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 3));
    // GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 4));
    // GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 5));
    // GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 6));
    // GlobalRenderer->PutChar(*((uint8_t *)bootInfo->rsdp + 7));

    // GlobalRenderer->Next(2);

    PrintStatus(true);
    GlobalRenderer->Print("Heap set successfully");

    GlobalRenderer->Next(1);

    PrintStatus(true);
    GlobalRenderer->Print("Timer set successfully");

    GlobalRenderer->Next(1);

    PrintStatus(true);
    GlobalRenderer->Print("Kernel initialized successfully");

    GlobalRenderer->Next(2);

    GlobalRenderer->Print("Successfully set everything");

    PIT::Sleep(2500);

    /* =----------= < PRINT LOADING SCREEN WITH LOGO > =----------= */

    GlobalRenderer->ClearColour = 0xff151515;
    GlobalRenderer->Clear();

    PrintLogo(GlobalRenderer->TargetFramebuffer->Width / 2 - 272, GlobalRenderer->TargetFramebuffer->Height / 2 - 112);

    uint32_t originColour = GlobalRenderer->Colour;
    GlobalRenderer->Colour = 0xffcccccc;

    GlobalRenderer->CursorPosition = {GlobalRenderer->TargetFramebuffer->Width - (16 + (8 * 13)), GlobalRenderer->TargetFramebuffer->Height - 32};

    GlobalRenderer->Print("AlphaOS Beta");

    GlobalRenderer->Colour = originColour;

    BootingTimeTest(GlobalRenderer->TargetFramebuffer->Width / 2 - 128, GlobalRenderer->TargetFramebuffer->Height / 2 + 96);

    GlobalRenderer->Clear();

    originColour = GlobalRenderer->Colour;
    GlobalRenderer->Colour = 0xffcccccc;

    GlobalRenderer->CursorPosition = {GlobalRenderer->TargetFramebuffer->Width - (16 + (8 * 13)), GlobalRenderer->TargetFramebuffer->Height - 32};

    GlobalRenderer->Print("AlphaOS Beta");

    GlobalRenderer->Colour = originColour;

    GlobalRenderer->CursorPosition = {16, 16};

    /* =----------= < SETTING UP TERMINAL WITH LOGO > =----------= */

    GlobalRenderer->Print("Thank you for using AlphaOS!");

    GlobalRenderer->Next(2);

    GlobalRenderer->Print("This version of AlphaOS can be unstable.");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print("Anyways, enjoy the AlphaOS.");

    GlobalRenderer->Next(3);

    PrintLogo(GlobalRenderer->CursorPosition.X, GlobalRenderer->CursorPosition.Y);

    GlobalRenderer->Next(2);

    GlobalRenderer->Colour = 0xff00ff00;

    GlobalRenderer->Print("Welcome to Alpha OS terminal!");

    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->Next(2);

    GlobalRenderer->Print("$ ");

    // asm ("int $0x0e"); // Make page fault

    while (true)
    {
        asm("hlt");
    }
}

void BootingTimeTest(long xOff, long yOff)
{
    uint32_t originColour = GlobalRenderer->Colour;
    GlobalRenderer->Colour = 0xffffffff;

    GlobalRenderer->CursorPosition = {xOff, yOff};

    // GlobalRenderer->Print("| ");

    // GlobalRenderer->PutChar('|', xOff + (8 * 54), yOff);

    for (int t = 0; t < 10; t++)
    {
        GlobalRenderer->Print("■");

        PIT::Sleep(250);
    }

    GlobalRenderer->Colour = originColour;

    return;
}