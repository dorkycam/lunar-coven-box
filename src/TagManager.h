
#ifndef TagManager_H
#define TagManager_H

#include <Arduino.h>

#define GOAL_ONE_COUNT 1
#define GOAL_TWO_COUNT 1
#define GOAL_THREE_COUNT 1

struct Tag {
    uint8_t rfid[10];
};

extern Tag RESET_TAGS[2];

extern Tag GOAL_ONES[GOAL_ONE_COUNT];
extern Tag GOAL_TWOS[GOAL_TWO_COUNT];
extern Tag GOAL_THREES[GOAL_THREE_COUNT];

#endif
