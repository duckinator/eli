#define _DEFAULT_SOURCE
#include <termios.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminal.h"

static struct termios original_termios;

void eli_terminal_disable_raw_mode()
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

bool eli_terminal_enable_raw_mode()
{
    int ret;

    ret = tcgetattr(STDIN_FILENO, &original_termios);
    if (ret == -1) {
        return false;
    }
    atexit(eli_terminal_disable_raw_mode);
    struct termios raw = original_termios;

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
