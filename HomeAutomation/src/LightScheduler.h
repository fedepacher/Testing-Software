#include "stdint.h"

enum Day {
NONE=-1, EVERYDAY=10, WEEKDAY, WEEKEND,
SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

enum{UNUSED = 0};
enum{TURN_ON = 1,
    TURN_OFF = 0};

typedef enum Day Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_Wakeup(void);