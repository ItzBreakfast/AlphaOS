#pragma once

#include <stdint.h>

void io_wait();
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);