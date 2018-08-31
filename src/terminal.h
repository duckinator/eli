#ifndef ELI_TERMINAL_H
#define ELI_TERMINAL_H

#include <stdbool.h>

#define CTRL_KEY(k) ((k) & 0x1f)

char eli_terminal_read_key(void);
bool eli_terminal_enable_raw_mode(void);

#endif
