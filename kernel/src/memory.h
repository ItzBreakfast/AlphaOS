#pragma once

#include <stdint.h>

#include "efiMemory.h"

void memset(void *start, uint8_t value, uint64_t num);
uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, uint64_t mMapEntries, uint64_t mMapDescSize);