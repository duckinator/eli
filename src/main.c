#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "die.h"
#include "editor.h"
#include "terminal.h"

#include <string.h>

void eli_init()
{
    if (!eli_terminal_get_size()) {
        eli_die("eli_terminal_get_size()");
    }
}

bool eli_process_keypress(char c)
{
    bool running = true;

    switch (c) {
    case CTRL_KEY('q'):
        running = false;
        break;
    default:
        printf("%c", c);
        break;
    }

    return running;
}

bool eli_get_and_process_keypress()
{
    char c = eli_terminal_read_key();
    return eli_process_keypress(c);
}

void eli_draw()
{
  int y;
  for (y = 0; y < editor.rows; y++) {
    write(STDOUT_FILENO, "~\r\n", 3);
  }
}

void eli_redraw()
{
    eli_terminal_reset();
    eli_draw();
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!eli_terminal_enable_raw_mode()) {
        eli_die("can't enable raw mode");
    }

    eli_init();

    bool running = true;
    while (running) {
        eli_redraw();
        running = eli_get_and_process_keypress();
    }

    eli_terminal_reset();
    return 0;
}
