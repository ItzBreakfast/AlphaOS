#include "kernelUtil.h"

KernelInfo kernelInfo;

void PrepareMemory(BootInfo *bootInfo)
{
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GlobalAllocator = PageFrameAllocator();

    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    PageMapIndexer pageIndexer = PageMapIndexer(0x1000);

    // Kernel size and lock kernel pages

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable *PML4 = (PageTable *)GlobalAllocator.RequestPage();

    memset(PML4, 0, 0x1000);

    g_PageTableManager = PageTableManager(PML4);

    for (uint64_t i = 0; i < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); i += 0x1000)
    {
        g_PageTableManager.MapMemory((void *)i, (void *)i);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;

    GlobalAllocator.LockPages((void *)fbBase, fbSize / 0x1000 + 1);

    for (uint64_t i = fbBase; i < fbBase + fbSize; i += 0x1000)
    {
        g_PageTableManager.MapMemory((void *)i, (void *)i);
    }

    asm("mov %0, %%cr3"
        :
        : "r"(PML4));

    kernelInfo.pageTableManager = &g_PageTableManager;

    return;
}

IDTR idtr;

void SetIDTGate(void *handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector)
{
    IDTDescEntry *interrupt = (IDTDescEntry *)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));

    interrupt->SetOffset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void PrepareInterrupts()
{
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();

    SetIDTGate((void *)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)KeyboardInt_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void *)MouseInt_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);

    asm("lidt %0"
        :
        : "m"(idtr));

    RemapPIC();

    asm("sti");

    return;
}

void PrepareACPI(BootInfo *bootInfo)
{
    ACPI::SDTHeader *xsdt = (ACPI::SDTHeader *)(bootInfo->rsdp->XSDTAddress);
    ACPI::MCFGHeader *mcfg = (ACPI::MCFGHeader *)ACPI::FindTable(xsdt, (char *)"MCFG");

    GlobalRenderer->Print("Address: ");
    GlobalRenderer->Print(to_hstring((uint64_t)mcfg));

    GlobalRenderer->Next(2);

    for (int t = 0; t < 4; t++)
    {
        GlobalRenderer->Print(to_hstring((uint64_t)mcfg->Header.Signature[t]));
        GlobalRenderer->PutChar(' ');
        GlobalRenderer->PutChar(mcfg->Header.Signature[t]);

        GlobalRenderer->Next(1);
    }

    GlobalRenderer->Next(1);

    PCI::EnumratePCI(mcfg);

    GlobalRenderer->Next(1);

    return;
}

BasicRenderer renderer = BasicRenderer(NULL, NULL);

KernelInfo InitializeKernel(BootInfo *bootInfo)
{
    renderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);

    GlobalRenderer = &renderer;

    GlobalRenderer->ClearColour = 0xff151515;

    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition.X = 16;
    GlobalRenderer->CursorPosition.Y = 16;

    GDTDescriptor gdtDescriptor;

    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;

    LoadGDT(&gdtDescriptor);

    PrepareMemory(bootInfo);

    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    PrepareInterrupts();

    InitPS2Mouse();

    PrepareACPI(bootInfo);

    outb(PIC1_DATA, 0b11111001);
    outb(PIC2_DATA, 0b11101111);

    return kernelInfo;
}