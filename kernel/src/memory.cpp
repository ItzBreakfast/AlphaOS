#include "memory.h"

void memset(void *start, uint8_t value, uint64_t num)
{
    for (uint64_t i = 0; i < num; i++)
    {
        *(uint8_t *)((uint64_t)start + i) = value;
    }
}

int memcmp(const void *aptr, const void *bptr, size_t n)
{
	const unsigned char *a = (unsigned char *)aptr, *b = (unsigned char *)bptr;

	for (size_t i = 0; i < n; i++)
	{
		if (a[i] < b[i])
			return -1;

		else if (a[i] > b[i])
			return 1;
	}

	return 0;
}

uint64_t strcmp(uint8_t *a, uint8_t *b, uint64_t length)
{
	for (uint64_t i = 0; i < length; i++)
	{
		if (*a != *b)
			return 0;
	}

	return 1;
}

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR *mMap, uint64_t mMapEntries, uint64_t mMapDescSize)
{
    static uint64_t memorySizeBytes = 0;

    if (memorySizeBytes > 0)
        return memorySizeBytes;

    for (int i = 0; i < mMapEntries; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR *)((uint64_t)mMap + (i * mMapDescSize));
        memorySizeBytes += desc->numPages * 4096;
    }

    return memorySizeBytes;
}