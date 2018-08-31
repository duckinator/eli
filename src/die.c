#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include "die.h"
#include "terminal.h"

noreturn void eli_die(const char *s)
{
    eli_terminal_reset();

    perror(s);
    exit(1);
}
