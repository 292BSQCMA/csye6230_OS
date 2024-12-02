# CSYE6230 Custom OS Project

Creating an OS from scratch, following [The little book about OS development](https://littleosbook.github.io/).

## Authors
- **Shen Wang**: wang.shen3@northeastern.edu
- **Xingxing Xiao**: xiao.xingx@northeastern.edu
- **Hsuanpei Lee**: lee.hsua@northeastern.edu

## Instructor
- **Professor Ahmed Banafa**: a.banafa@northeastern.edu 

## Course
CSYE6230 21600 Operating Systems SEC 01 Fall 2024

## Prerequisites
- Bochs x86 Emulator
- VirtualBox (optional)
- GNU Compiler Collection (GCC)
- GNU Make
- NASM Assembler

## Building the OS
1. **Install Required Packages**:
    ```sh
    sudo apt-get install build-essential nasm genisoimage
    ```

2. **Clone the Repository**:
    ```sh
    git clone https://github.com/your-repo/csye6230_OS.git
    cd csye6230_OS
    ```

3. **Build the OS**:
    ```sh
    make
    ```


## Running the OS

### Using VirtualBox
1. Open VirtualBox and create a new virtual machine.
2. Set the boot order to boot from the CD/DVD drive first.
3. Mount the `os.iso` file as a virtual CD/DVD drive.
4. Start the virtual machine.



## Chapter-wise Explanation of the Files Corresponding to Each Chapter

### Chapter 2: First Steps
- **Booting**: Initial setup and booting process.
- **Hello Cafebabe**: Bootloader and initial boot message.
- **Files**: `loader.s`, `multiboot_header.s`, `link.ld`

### Chapter 3: Getting to C
- **Setting Up a Stack**: Basic stack setup for function calls.
- **Calling C Code From Assembly**: Integration between assembly and C code.
- **Files**: `kmain.c` (setup and calling C from assembly)

### Chapter 4: Output
- **Interacting with the Hardware**: Basic hardware interaction.
    - Understanding how to communicate with hardware using I/O ports and memory-mapped I/O.
- **Framebuffer**: Writing text and moving the cursor.
    - Implementing functions to write text to the screen and move the cursor using the framebuffer.
- **Serial Ports**: Serial port communication.
    - Configuring and using serial ports for debugging and output.
- **Files**: `fb.c`, `serial.c`, `fb.h`, `serial.h`

### Chapter 5: Segmentation
- **Global Descriptor Table (GDT)**: Setup and loading the GDT.
    - Defining and loading the GDT to manage memory segments.
- **Files**: `gdt.c`, `gdt_flush.s`, `gdt.h`

### Chapter 6: Interrupts and Input
- **Interrupt Handlers**: Setting up and handling interrupts.
    - Creating and managing interrupt service routines (ISRs) to handle hardware and software interrupts.
- **Interrupt Descriptor Table (IDT)**: Setup and loading the IDT.
    - Defining and loading the IDT to manage interrupt vectors.
- **Programmable Interrupt Controller (PIC)**: Managing hardware interrupts.
    - Configuring the PIC to handle hardware interrupts.
- **Keyboard Input**: Reading input from the keyboard.
    - Implementing functions to read and process keyboard input.
- **Files**: `idt.c`, `idt_load.s`, `keyboard.c`, `idt.h`, `keyboard.h`

### Chapter 9: Paging
- **Paging in x86**: Implementing paging.
    - Setting up paging to manage virtual memory and improve security and efficiency.
- **Files**: `paging.c`, `paging.h`

### Chapter 12: File Systems
- **Implementing a Simple File System**: Basic file system operations.
    - Creating, deleting, renaming, and listing files and directories.
- **Files**: `fs.c`, `fs.h`

### Chapter 8: Shell
- **Interactive Shell**: Command-line interface to interact with the OS.
    - Implementing a basic shell to process user commands and interact with the file system.
- **Files**: `shell.c`, `shell.h`

## Commands Introduction

### Available Commands:
- **lst**: Lists the contents of the current directory.
- **mkd <directory_name>**: Creates a new directory with the specified name in the current directory.
- **mkf <file_name>**: Creates a new file with the specified name in the current directory.
- **del <file_or_directory_name>**: Deletes the specified file or directory.
- **rnm <old_name> <new_name>**: Renames the specified file or directory.
- **cwd**: Displays the current working directory.
- **chd <directory_name>**: Changes the current working directory to the specified directory.



## License
Currently, this project has no License.


## Contact
For any inquiries, please contact wang.shen3@northeastern.edu.

## Acknowledgments 
This project was created with the assistance of Microsoft Copilot, an AI companion by Microsoft, which provided guidance and support throughout the development process.