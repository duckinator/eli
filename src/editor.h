#ifndef ELI_EDITOR_H
#define ELI_EDITOR_H

#include <termios.h>

struct eli_editor_s {
  int rows;
  int cols;
  struct termios original_termios;
};

static struct eli_editor_s editor = {
    .rows = 0,
    .cols = 0,
    .original_termios = {0},
};

#endif
