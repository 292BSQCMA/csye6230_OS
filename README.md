# csye6230_OS
creating os from scratch, following "https://littleosbook.github.io/"

# Custom OS Project

This repository contains the source code and build instructions for a custom operating system.

## Prerequisites
- Bochs x86 Emulator
- VirtualBox (optional)
- GNU Compiler Collection (GCC)
- GNU Make
- NASM Assembler

## Building the OS
1. Follow the tutorial at [The little book about OS development](https://littleosbook.github.io/) up to section 2.3.4 to create `os.iso`.

## Running the OS

### Using VirtualBox
1. Open VirtualBox and create a new virtual machine.
2. Set the boot order to boot from the CD/DVD drive first.
3. Mount the `os.iso` file as a virtual CD/DVD drive.
4. Start the virtual machine.


## Detailed Steps for Building and Running the OS
### Step 1: Install Required Packages
sudo apt-get install build-essential nasm genisoimage
## Step 2: Create the Loader
### Save the following code in a file called loader.s:
global loader                   ; the entry symbol for ELF

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                    ; (magic number + checksum + flags should equal 0)

section .text:                  ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum

loader:                         ; the loader label (defined as entry point in linker script)
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax
.loop:
    jmp .loop                   ; loop forever
## Step 3: Compile the Loader
### Compile the file loader.s into a 32-bit ELF object file:
nasm -f elf32 loader.s
## Step 4: Create the Linker Script
### Save the following linker script into a file called link.ld:
ENTRY(loader)                /* the name of the entry label */

SECTIONS {
    . = 0x00100000;          /* the code should be loaded at 1 MB */

    .text ALIGN (0x1000) :   /* align at 4 KB */
    {
        *(.text)             /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) : /* align at 4 KB */
    {
        *(.rodata*)          /* all read-only data sections from all files */
    }

    .data ALIGN (0x1000) :   /* align at 4 KB */
    {
        *(.data)             /* all data sections from all files */
    }

    .bss ALIGN (0x1000) :    /* align at 4 KB */
    {
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all bss sections from all files */
    }
}
### Link the executable:
ld -T link.ld -melf_i386 loader.o -o kernel.elf
## Step 5: Download the Bootloader
### Download the binary file from stage2_eltorito and copy it to the folder containing loader.s and link.ld.

## Step 6: Create the ISO Structure
mkdir -p iso/boot/grub              # create the folder structure
cp stage2_eltorito iso/boot/grub/   # copy the bootloader
cp kernel.elf iso/boot/             # copy the kernel
## Create a menu.lst file for GRUB:
default=0
timeout=0

title os
kernel /boot/kernel.elf
### place the menu.lst file in the folder iso/boot/grub/.

## Step 7: Generate the ISO Image
genisoimage -R                              \
            -b boot/grub/stage2_eltorito    \
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A os                           \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o os.iso                       \
            iso
## Step 8: Running the OS in VirtualBox
### 1. Open VirtualBox and create a new virtual machine.

### 2. Set the boot order to boot from the CD/DVD drive first.

### 3. Mount the os.iso file as a virtual CD/DVD drive.

### 4. Start the virtual machine.

## Expected Output
### When running the OS in VirtualBox, you should see the following message:

Booting 'os' 
kernel /boot/kernel.elf [Multiboot-elf, <0x100000:0x13:0x0>, shtab=0x1010cb, entry=0x10000c]




## from Chapter 4: Output

### Key Concepts

1. **Interacting with Hardware**:
   - **Memory-Mapped I/O**: Writing to specific memory addresses updates the hardware. Example: Framebuffer at `0x000B8000`.
   - **I/O Ports**: Using assembly instructions `in` and `out` to communicate with hardware. Example: Controlling the cursor on the screen.

2. **Framebuffer**:
   - **Text Display**: Writing text to the console using memory-mapped I/O.
   - **Cursor Movement**: Moving the cursor using I/O ports `0x3D4` and `0x3D5`.
   - **Driver**: Abstracts low-level hardware interaction, providing a higher-level interface for the OS.

3. **Serial Ports**:
   - **Baud Rate**: Setting the speed of data transmission.
   - **Line Configuration**: Setting data length, parity, and stop bits.
   - **FIFO Buffers**: Managing data transmission using buffers.
   - **Modem Configuration**: Hardware flow control via RTS and DTR signals.
   - **Reading/Writing Data**: Ensuring the transmit FIFO is empty before sending data.

### Implementation Steps

1. **Framebuffer Implementation**:
   - Create functions to write text and move the cursor:
     ```c
     void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
     void fb_move_cursor(unsigned short pos);
     int write(char *buf, unsigned int len);
     ```
   - Update `kmain` to use the framebuffer functions.

2. **Serial Port Configuration**:
   - Set up serial port configuration and data transmission:
     ```c
     void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
     void serial_configure_line(unsigned short com);
     void serial_configure_buffers(unsigned short com);
     void serial_configure_modem(unsigned short com);
     int serial_is_transmit_fifo_empty(unsigned int com);
     void serial_write(char *buf, unsigned int len);
     ```
   - Add debug messages via `serial_write` to trace execution.

3. **Multiboot Header**:
   - Ensure the kernel is Multiboot-compliant by adding a Multiboot header in assembly:
     ```assembly
     section .multiboot
     align 4
     dd 0x1BADB002
     dd 0x00
     dd -(0x1BADB002 + 0x00)
     section .text
     global loader
     ```

4. **Update Linker Script**:
   - Include the `.multiboot` section in the linker script:
     ```ld
     SECTIONS {
         . = 0x00100000;

         .multiboot ALIGN(4) : { *(.multiboot) }

         .text ALIGN (0x1000) : { *(.text) }
         .rodata ALIGN (0x1000) : { *(.rodata*) }
         .data ALIGN (0x1000) :