#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include "die.h"

noreturn void eli_die(const char *s)
{
    perror(s);
    exit(1);
}
