#include "panic.h"

void Panic(const char *panicMessage)
{
    GlobalRenderer->Clear(0x3075ff);

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y = 16;

    GlobalRenderer->Print(":(");

    GlobalRenderer->Next(2);

    GlobalRenderer->Print("Alpha OS have a problem, and need shut down to prevent damage your computer");

    GlobalRenderer->Next(1);

    GlobalRenderer->Print("Hold down the Power button for several seconds to shutdown you computer");

    GlobalRenderer->Next(2);

    GlobalRenderer->Print("Problem: ");
    GlobalRenderer->Print(panicMessage);

    return;
}