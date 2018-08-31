#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "die.h"
#include "terminal.h"

typedef struct eli_keypress_result_s {
    bool should_exit;
    int exit_code;
} eli_keypress_result;

bool eli_process_keypress(char c)
{
    bool should_exit = false;

    switch (c) {
    case CTRL_KEY('q'):
        should_exit = true;
        break;
    default:
        printf("%c", c);
        break;
    }

    return should_exit;
}

void eli_refresh_screen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!eli_terminal_enable_raw_mode()) {
        eli_die("can't enable raw mode");
    }

    while (true) {
        eli_refresh_screen();
        char c = eli_terminal_read_key();
        bool should_exit = eli_process_keypress(c);

        if (should_exit) {
            break;
        }
    }

    return 0;
}
