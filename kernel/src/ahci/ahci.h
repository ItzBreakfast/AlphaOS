#pragma once

#include <stdint.h>

#include "../pci.h"

namespace AHCI
{
    class AHCIDriver
    {
    public:
        PCI::PCIDeviceHeader *PCIBaseAddress;

        AHCIDriver(PCI::PCIDeviceHeader *pciBaseAddress);
        ~AHCIDriver();
    };
}