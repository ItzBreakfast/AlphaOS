#include "ahci.h"

namespace AHCI
{
    AHCIDriver::AHCIDriver(PCI::PCIDeviceHeader *pciBaseAddress)
    {
        this->portCount = 0;
        this->PCIBaseAddress = pciBaseAddress;

        PrintStatus(true);
        GlobalRenderer->Print("AHCI Driver instance initialized successfully");
        GlobalRenderer->Next(1);

        ABAR = (HBAMemory *)((PCI::PCIHeader0 *)pciBaseAddress)->BAR5;

        g_PageTableManager.MapMemory(ABAR, ABAR);

        ProbePorts();

        for (int i = 0; i < portCount; i++)
        {
            Port *port = Ports[i];

            port->Configure();
        }
    }

    AHCIDriver::~AHCIDriver()
    {
    }

    PortType CheckPortType(HBAPort *port)
    {
        uint32_t sataStatus = port->sataStatus;

        uint8_t interfacePowerManagement = (sataStatus >> 8) & 0b111;
        uint8_t deviceDetection = sataStatus & 0b111;

        if (deviceDetection != HBA_PORT_DEV_PRESENT)
            return PortType::None;

        if (interfacePowerManagement != HBA_PORT_IPM_ACTIVE)
            return PortType::None;

        switch (port->signature)
        {
        case SATA_SIG_ATAPI:
        {
            return PortType::SATAPI;
        }

        case SATA_SIG_ATA:
        {
            return PortType::SATA;
        }

        case SATA_SIG_PM:
        {
            return PortType::PM;
        }

        case SATA_SIG_SEMB:
        {
            return PortType::SEMB;
        }

        default:
        {
            return PortType::None;
        }
        }
    }

    void AHCIDriver::ProbePorts()
    {
        uint32_t portsImplemented = ABAR->portsImplemented;

        for (int i = 0; i < 32; i++)
        {
            if (portsImplemented & (1 << i))
            {
                PortType portType = CheckPortType(&ABAR->ports[i]);

                if (portType == PortType::SATA || portType == PortType::SATAPI)
                {
                    Ports[portCount] = new Port();
                    Ports[portCount]->portType = portType;
                    Ports[portCount]->hbaPort = &ABAR->ports[i];
                    Ports[portCount]->portNumber = portCount;

                    portCount++;
                }
            }
        }

        return;
    }

    void Port::Configure()
    {
        StopCMD();

        void *newBase = GlobalAllocator.RequestPage();

        hbaPort->commandListBase = (uint32_t)(uint64_t)newBase;
        hbaPort->commandListBaseUpper = (uint32_t)((uint64_t)newBase >> 32);

        memset((void *)(hbaPort->commandListBase), 0, 1024);

        void *fisBase = GlobalAllocator.RequestPage();

        hbaPort->fisBaseAddress = (uint32_t)(uint64_t)fisBase;
        hbaPort->fisBaseAddressUpper = (uint32_t)((uint64_t)fisBase >> 32);

        memset(fisBase, 0, 256);

        HBACommandHeader *cmdHeader = (HBACommandHeader *)((uint64_t)hbaPort->commandListBase + ((uint64_t)hbaPort->commandListBaseUpper << 32));

        for (int i = 0; i < 32; i++)
        {
            cmdHeader[i].prdtLength = 8;

            void *cmdTableAddress = GlobalAllocator.RequestPage();

            uint64_t address = (uint64_t)cmdTableAddress + (i << 8);

            cmdHeader[i].commandTableBaseAddress = (uint32_t)(uint64_t)address;
            cmdHeader[i].commandTableBaseAddressUpper = (uint32_t)((uint64_t)address >> 32);

            memset(cmdTableAddress, 0, 256);
        }

        StartCMD();

        return;
    }

    void Port::StartCMD()
    {
        while (hbaPort->cmdSts & HBA_PxCMD_CR)
            ;

        hbaPort->cmdSts |= HBA_PxCMD_FRE;
        hbaPort->cmdSts |= HBA_PxCMD_ST;

        return;
    }

    void Port::StopCMD()
    {
        hbaPort->cmdSts &= ~HBA_PxCMD_ST;
        hbaPort->cmdSts &= ~HBA_PxCMD_FRE;

        while (true)
        {
            if (hbaPort->cmdSts & HBA_PxCMD_FR)
                continue;

            if (hbaPort->cmdSts & HBA_PxCMD_CR)
                continue;

            break;
        }

        return;
    }
}