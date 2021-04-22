#include "keyboard.h"

bool isLeftShiftPressed;
bool isRightShiftPressed;

bool TermMode = true;
long BaseLineX = 8 * 3;

void HandleKeyboard(uint8_t scancode)
{
    switch (scancode)
    {
    case LeftShift:
    {
        isLeftShiftPressed = true;

        return;
    }

    case LeftShift + 0x80:
    {
        isLeftShiftPressed = false;

        return;
    }

    case RightShift:
    {
        isLeftShiftPressed = true;

        return;
    }

    case RightShift + 0x80:
    {
        isLeftShiftPressed = false;

        return;
    }

    case Enter:
    {
        if (TermMode)
        {
            uint32_t originColour = GlobalRenderer->Colour;
            GlobalRenderer->Colour = 0xffcccccc;

            GlobalRenderer->Next(1);
            GlobalRenderer->Print("Shell: This is not valid command in this shell");
            GlobalRenderer->Next(2);

            GlobalRenderer->Colour = originColour;

            BaseLineX = 8 * 3;
            GlobalRenderer->Print("$ ");
        }
        else
        {
            GlobalRenderer->Next(1);
        }

        return;
    }

    case Spacebar:
    {
        GlobalRenderer->PutChar(' ');

        return;
    }

    case BackSpace:
    {
        if (GlobalRenderer->CursorPosition.X - 8 > BaseLineX)
            GlobalRenderer->ClearChar();

        return;
    }
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);

    if (ascii != 0)
    {
        GlobalRenderer->PutChar(ascii);
    }
}