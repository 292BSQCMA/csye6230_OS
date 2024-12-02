#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

extern unsigned short cursor_position;  // Declare cursor_position as external
extern const unsigned int FB_WIDTH;     // Declare FB_WIDTH as external

void write(char *buf, unsigned int len);
void clear_screen();
void move_cursor(unsigned int row, unsigned int col);
void newline();

#endif /* INCLUDE_FB_H */
