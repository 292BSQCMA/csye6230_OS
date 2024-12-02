
#include "../include/fs.h"
#include "../include/fb.h"
#include "../include/serial.h"
#include "../include/shell.h"
#include "../include/keyboard.h" 

void kmain(void) {
    // Clear the screen to remove initial bootloader messages
    clear_screen();

    // Display authors, professor, and reference info
    write("Authors:\n", 9);
    write("Shen Wang: wang.shen3@northeastern.edu\n", 39);
    write("Xingxing Xiao: xiao.xingx@northeastern.edu\n", 43);
    write("Hsuanpei Lee: lee.hsua@northeastern.edu\n", 40);
    
    write("\nInstructor:\n", 14);
    write("Professor Ahmed Banafa: a.banafa@northeastern.edu\n", 49);
    
    write("\nReference:\n", 12);
    write("https://littleosbook.github.io/\n", 32);
    
    write("\nAI Assistance:\n", 16);
    write("Microsoft Copilot\n", 18);

    // Initialize serial port
    serial_configure_baud_rate(SERIAL_COM1_BASE, 1);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_buffers(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);

    // Initialize framebuffer
    char *message = "Welcome to 6230OS\n";
    write(message, 18);

    // Initialize file system
    fs_init();
    write("File system initialized.\n", 25);

    // Start shell for basic command interface
    shell();  // Call shell function for I/O interaction
}
