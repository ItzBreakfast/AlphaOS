#include "efiMemory.h"

const char *EFI_MEMORY_TYPE_STRINGS[]
{
    "EfiReservedMemoryType", 
    "EfiLoaderCode", 
    "EfiLoaderData", 
    "EfiBootServicesCode", 
    "EfiBootServicesData", 
    "EfiRuntimeServicesCode", 
    "EFIRuntimeServicesData", 
    "EfiConvertionalMemory", 
    "EfiUnusableMemory", 
    "EfiACPIReclaimMemory", 
    "EfiACPIMemoryNVS", 
    "EfiMemoryMappedIO", 
    "EfiMemoryMappedIOPortSpace", 
    "EfiPalCode"
};