#include "TimeService.h"

static Time time_ex;

void TimeService_GetTime(Time * time){
    *time = time_ex;
}

void FakeTimeService_SetMinute(uint16_t minute){
    time_ex.minuteOfDay = minute;
}

void FakeTimeService_SetDay(uint8_t day){
    time_ex.dayOfWeek = day;
}