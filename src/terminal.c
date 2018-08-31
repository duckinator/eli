#define _DEFAULT_SOURCE
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include "terminal.h"

static struct termios original_termios;

void eli_terminal_disable_raw_mode()
{
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void eli_terminal_enable_raw_mode()
{
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(eli_terminal_disable_raw_mode);
    struct termios raw = original_termios;
    cfmakeraw(&raw);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
