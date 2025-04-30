#include "rtc.h"
#include <drivers/io/io.h>

#define RTC_REG 0x70  // RTC index register
#define RTC_DATA 0x71 // RTC data register

// RTC registers (only some of them are necessary for time/date)
#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS   0x04
#define RTC_DAY      0x07
#define RTC_MONTH    0x08
#define RTC_YEAR     0x09

uint8_t rtc_read(uint8_t reg)
{
    x86_outb(RTC_REG, reg);  // Select the register
    return x86_inb(RTC_DATA); // Read the data
}

// Function to convert BCD to normal integer
uint8_t bcd_to_int(uint8_t bcd)
{
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

// Function to get the current date and time from the RTC
rtc_time_t rtc_get_time()
{
    rtc_time_t rtc_time;

    rtc_time.seconds = bcd_to_int(rtc_read(RTC_SECONDS));
    rtc_time.minutes = bcd_to_int(rtc_read(RTC_MINUTES));
    rtc_time.hours = bcd_to_int(rtc_read(RTC_HOURS));
    rtc_time.day = bcd_to_int(rtc_read(RTC_DAY));
    rtc_time.month = bcd_to_int(rtc_read(RTC_MONTH));
    rtc_time.year = bcd_to_int(rtc_read(RTC_YEAR));

    return rtc_time;
}