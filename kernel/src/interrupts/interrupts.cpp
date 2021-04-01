#include "interrupts.h"

__attribute__((interrupt)) void PageFault_Handler(interrupts_frame *frame)
{
    Panic("Page fault");

    while (true)
        ;
}

__attribute__((interrupt)) void DoubleFault_Handler(interrupts_frame *frame)
{
    Panic("Double fault");

    while (true)
        ;
}

__attribute__((interrupt)) void GPFault_Handler(interrupts_frame *frame)
{
    Panic("General Protection fault");

    while (true)
        ;
}

__attribute__((interrupt)) void KeyboardInt_Handler(interrupts_frame *frame)
{
    uint8_t scancode = inb(0x60);

    HandleKeyboard(scancode);

    PIC_EndMaster();
}

__attribute__((interrupt)) void MouseInt_Handler(interrupts_frame *frame)
{
    uint8_t mouseData = inb(0x60);

    GlobalRenderer->Print("m");

    PIC_EndSlave();
}

void RemapPIC()
{
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    io_wait();

    a2 = inb(PIC2_DATA);
    io_wait();

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    outb(PIC1_DATA, 0x20);
    io_wait();

    outb(PIC2_DATA, 0x28);
    io_wait();

    outb(PIC1_DATA, 4);
    io_wait();

    outb(PIC2_DATA, 2);
    io_wait();

    outb(PIC1_DATA, ICW4_8086);
    io_wait();

    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);
    io_wait();

    outb(PIC2_DATA, a2);
}

void PIC_EndMaster()
{
    outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave()
{
    outb(PIC2_COMMAND, PIC_EOI);
    outb(PIC1_COMMAND, PIC_EOI);
}