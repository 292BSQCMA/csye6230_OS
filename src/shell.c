#include "../include/shell.h"
#include "../include/fs.h"
#include "../include/fb.h"
#include "../include/keyboard.h"
#include "../include/string.h"

void shell() {
    char input[256];
    write("Entering shell...\n", 18);  // Debug message
    newline();  // Move to the next line

    while (1) {  // Infinite loop to keep the shell running
        write("> ", 2);  // Print prompt to framebuffer
        int i = 0;
        char c;

        // Wait for input
        while ((c = keyboard_read_char()) != '\n') {
            if (c == 0) {
                // Invalid character, skip it
                continue;
            }
            if (c == '\b' && i > 0) {
                i--;
                move_cursor(cursor_position / FB_WIDTH, cursor_position % FB_WIDTH - 1); // Move cursor back
                write(" ", 1);  // Overwrite character with space
                move_cursor(cursor_position / FB_WIDTH, cursor_position % FB_WIDTH - 1); // Move cursor back
            } else if (c != '\b') {
                input[i++] = c;
                write(&c, 1);  // Echo input to framebuffer
            }
        }
        input[i] = '\0';
        newline();  // Move to a new line

        // Debug message to confirm input received
        write("Input received: ", 16);
        write(input, i);
        write("\n", 1);

        // Process commands
        if (strcmp(input, "lst") == 0) {
            fs_ls(fs_current);
        } else if (strncmp(input, "mkd ", 4) == 0) {
            fs_mkdir(input + 4, fs_current);
            write("Directory created.\n", 19);
        } else if (strncmp(input, "mkf ", 4) == 0) {
            fs_create(input + 4, fs_current);
            write("File created.\n", 14);
        } else if (strncmp(input, "del ", 4) == 0) {
            fs_delete(input + 4, fs_current);
            write("File deleted.\n", 14);
        } else if (strncmp(input, "rnm ", 4) == 0) {
            char *src = input + 4;
            char *dest = strchr(src, ' ');
            if (dest != NULL) {
                *dest = '\0';
                dest++;
                fs_move(src, dest, fs_current);
                write("File renamed.\n", 14);
            }
        } else if (strcmp(input, "cwd") == 0) {
            fs_pwd(fs_current);
            write("\n", 1);
        } else if (strncmp(input, "chd ", 4) == 0) {
            fs_cd(input + 4);
            write("Directory changed.\n", 20);
        } else if (strncmp(input, "mov ", 4) == 0) {
            char* src = input + 4;
            char* dest = strchr(src, ' ');
            if (dest != NULL) {
                *dest = '\0';
                dest++;
                fs_move(src, dest, fs_current);
                write("File/directory moved.\n", 21);
            }
            else {
                write("Usage: mov <source> <destination>\n", 35);
            }
        }else {
            write("Unknown command: ", 17);
            write(input, strlen(input));
            write("\n", 1);
        }
        newline();  // Move to a new line after each command
    }
}
