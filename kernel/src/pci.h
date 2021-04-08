#pragma once

#include <stdint.h>

#include "BasicRenderer.h"
#include "cstr.h"
#include "acpi.h"
#include "paging/PageTableManager.h"

namespace PCI
{
    struct PCIDeviceHeader
    {
        uint16_t VendorID;
        uint16_t DeviceID;
        uint16_t Command;
        uint16_t Status;
        uint8_t RevisionID;
        uint8_t ProgIF;
        uint8_t Subclass;
        uint8_t Class;
        uint8_t CacheLineSize;
        uint8_t LatencyTimer;
        uint8_t HeaderType;
        uint8_t BIST;
    };

    void EnumratePCI(ACPI::MCFGHeader *mcfg);
    const char *GetVendorName(uint16_t vendorID);
    const char *GetDeviceName(uint16_t vendorID, uint16_t deviceID);
    const char *GetSubclassName(uint8_t classCode, uint8_t subclassCode);
    const char *MassStorageControllerSubclassName(uint8_t subclassCode);
    const char *GetProgIFName(uint8_t classCode, uint8_t subclassCode, uint8_t progIF);

    extern const char *DeviceClasses[];
}