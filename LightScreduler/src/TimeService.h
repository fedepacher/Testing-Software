#include "stdint.h"

enum{TIME_UNKNOWN = 0};

enum { MONDAY = 1,
       TUESDAY = 2,
       WEDNESDAY = 3,
       THURSDAY = 4,
       FRIDAY = 5,
       SATURDAY = 6,
       SUNDAY = 7};

typedef struct{
    uint16_t minuteOfDay;
    uint8_t dayOfWeek;
}Time;

void TimeService_GetTime(Time * time);
void FakeTimeService_SetMinute(uint16_t minute);
void FakeTimeService_SetDay(uint8_t day);
