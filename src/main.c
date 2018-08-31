#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "die.h"
#include "terminal.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    eli_terminal_enable_raw_mode();

    while (true) {
        char c = '\0';
        read(STDIN_FILENO, &c, 1);

        if(c == -1) {
            if (errno == EAGAIN) {
                continue;
            }
            eli_die("read()");
        }

        if (iscntrl(c)) {
            printf("%d\r\n", c);
        } else {
            printf("%d ('%c')\r\n", c, c);
        }

        if (c == 'q') { break; }
    }

    return 0;
}
