#pragma once

#include <stdint.h>
#include <stddef.h>

#include "efiMemory.h"

void memset(void *start, uint8_t value, uint64_t num);
int memcmp(const void *aptr, const void *bptr, size_t n);
uint64_t strcmp(uint8_t *a, uint8_t *b, uint64_t length);
uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, uint64_t mMapEntries, uint64_t mMapDescSize);