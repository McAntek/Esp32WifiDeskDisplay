#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "screen.h"

typedef enum {
    MESSAGE,
    CLOCK,
    WEATHER
} state_t;

void controller_update(void);
void controller_init(void);
void set_state(state_t state, row_t row);

#endif