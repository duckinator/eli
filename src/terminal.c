#define _DEFAULT_SOURCE
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include "die.h"
#include "editor.h"
#include "terminal.h"

bool eli_terminal_get_size()
{
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        return false;
    }

    editor.cols = ws.ws_col;
    editor.rows = ws.ws_row;
    return true;
}

void eli_terminal_clear()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
}

void eli_terminal_move_cursor(size_t row, size_t col)
{
    char str[32];
    snprintf(str, 10, "\x1b[%zu;%zuH", row, col);
    write(STDOUT_FILENO, str, strlen(str));
}

void eli_terminal_reset()
{
    eli_terminal_clear();
    eli_terminal_move_cursor(0, 0);
}

char eli_terminal_read_key()
{
    ssize_t nread;
    char c;

    while (true) {
        nread = read(STDIN_FILENO, &c, 1);
        if (nread == 1) {
            break;
        }

        if (nread == -1 && errno != EAGAIN) {
            eli_die("read()");
        }
    }

    return c;
}

void eli_terminal_disable_raw_mode()
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &(editor.original_termios));
}

bool eli_terminal_enable_raw_mode()
{
    int ret;

    ret = tcgetattr(STDIN_FILENO, &(editor.original_termios));
    if (ret == -1) {
        return false;
    }
    atexit(eli_terminal_disable_raw_mode);
    struct termios raw = editor.original_termios;

    // Actually enter raw mode.
    cfmakeraw(&raw);

    // Allow read() to return as soon as a character is typed.
    raw.c_cc[VMIN] = 0;
    // Force read() to time out after 1/10th of a second.
    raw.c_cc[VTIME] = 1;

    ret = tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    if (ret == -1) {
        return false;
    }

    return true;
}
