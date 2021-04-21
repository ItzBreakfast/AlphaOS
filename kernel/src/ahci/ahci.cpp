#include "ahci.h"

namespace AHCI
{
    AHCIDriver::AHCIDriver(PCI::PCIDeviceHeader *pciBaseAddress)
    {
        this->PCIBaseAddress = pciBaseAddress;

        PrintStatus(true);
        GlobalRenderer->Print("AHCI Driver instance initialized successfully");
        GlobalRenderer->Next(1);
    }

    AHCIDriver::~AHCIDriver()
    {
    }
}