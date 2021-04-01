#include "keyboard.h"

bool isLeftShiftPressed;
bool isRightShiftPressed;

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
        GlobalRenderer->Next(1);

        return;
    }

    case Spacebar:
    {
        GlobalRenderer->PutChar(' ');

        return;
    }

    case BackSpace:
    {
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