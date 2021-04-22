#include "ahci.h"

namespace AHCI
{
    PortType CheckPortType(HBAPort *port)
    {
    }

    AHCIDriver::AHCIDriver(PCI::PCIDeviceHeader *pciBaseAddress)
    {
        this->PCIBaseAddress = pciBaseAddress;

        PrintStatus(true);
        GlobalRenderer->Print("AHCI Driver instance initialized successfully");
        GlobalRenderer->Next(1);

        ABAR = (HBAMemory *)((PCI::PCIHeader0 *)pciBaseAddress)->BAR5;

        g_PageTableManager.MapMemory(ABAR, ABAR);
    }

    AHCIDriver::~AHCIDriver()
    {
    }

    void AHCIDriver::ProbePorts()
    {
        uint32_t portsImplemented = ABAR->portsImplemented;

        for (int i = 0; i < 32; i++)
        {
            if (portsImplemented & (1 << i))
            {
            }
        }
    }
}