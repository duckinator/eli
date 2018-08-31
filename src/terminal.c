#define _DEFAULT_SOURCE
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "die.h"
#include "terminal.h"

static struct termios original_termios;

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
