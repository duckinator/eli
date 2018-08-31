#include <stdbool.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "die.h"
#include "editor.h"
#include "terminal.h"

void eli_init()
{
    eli_terminal_get_size();
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

    eli_terminal_reset();

    bool running = true;
    while (running) {
        eli_refresh_screen();
        running = eli_get_and_process_keypress();
    }

    eli_terminal_reset();
    return 0;
}
