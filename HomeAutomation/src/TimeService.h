#include "stdint.h"

enum{TIME_UNKNOWN = 0};


typedef struct{
    uint16_t minuteOfDay;
    uint8_t dayOfWeek;
}Time;

void TimeService_GetTime(Time * time);
void FakeTimeService_SetMinute(uint16_t minute);
void FakeTimeService_SetDay(uint8_t day);
