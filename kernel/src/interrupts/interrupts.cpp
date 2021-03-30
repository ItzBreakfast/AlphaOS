#include "interrupts.h"
#include "../memory.h"

__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame *frame)
{
    memset(GlobalRenderer->TargetFramebuffer->BaseAddress, 0, GlobalRenderer->TargetFramebuffer->BufferSize);

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y = 16;

    GlobalRenderer->Print(":(");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 32;

    GlobalRenderer->Print("Alpha OS have problem, and need shut down to prevent damage to your computer");

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y += 32;

    GlobalRenderer->Print("Page fault");

    while (true)
        ;
}