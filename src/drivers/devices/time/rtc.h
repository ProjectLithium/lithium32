#pragma once
#include <stdint.h>

typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} rtc_time_t;

rtc_time_t rtc_get_time();