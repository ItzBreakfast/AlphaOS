#pragma once

#include "../BasicRenderer.h"

struct interrupts_frame;

__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame *frame);