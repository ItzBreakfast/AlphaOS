#pragma once

#include <stdint.h>

#include "kbScancodeTranslation.h"
#include "../BasicRenderer.h"

void HandleKeyboard(uint8_t scancode);

extern bool TermMode;
extern long BaseLineX;