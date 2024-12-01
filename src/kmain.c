#include "../include/fb.h"
#include "../include/serial.h"

void kmain(void) {
    serial_configure_baud_rate(SERIAL_COM1_BASE, 1);  // Set baud rate to 115200
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_buffers(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);

    char *log_message = "Serial Port Initialized!\n";
    serial_write(log_message, 25);

    char *message = "Hello, World!";
    serial_write("Writing to framebuffer...\n", 27);
    write(message, 13);  // Writes "Hello, World!" to the screen
    serial_write("Finished writing to framebuffer.\n", 33);

    while (1) {
        // Infinite loop to keep the kernel running
    }
}
