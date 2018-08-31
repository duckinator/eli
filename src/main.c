#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "die.h"
#include "terminal.h"

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

void eli_refresh_screen()
{
    eli_terminal_clear();
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!eli_terminal_enable_raw_mode()) {
        eli_die("can't enable raw mode");
    }

    bool running = true;
    while (running) {
        eli_refresh_screen();
        running = eli_get_and_process_keypress();
    }

    return 0;
}
