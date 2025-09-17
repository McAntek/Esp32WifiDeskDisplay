#ifndef CLOCK_APP_H
#define CLOCK_APP_H

#include "screen.h"

void clock_init(long gmt_offset, int daylight_offset, const char* ntp_server);
void clock_update(row_t row);

#endif