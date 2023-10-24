#include "TagManager.h"

Tag RESET_TAGS[2] = {
    {
        rfid : {0x04, 0x84, 0x46, 0x06, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00}
    },
    {
        rfid : {0x04, 0x84, 0x46, 0x06, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00}
    }};

Tag GOAL_ONES[GOAL_ONE_COUNT] = {
    {
        rfid : {0x04, 0x60, 0x6C, 0x05, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00}
    }};

Tag GOAL_TWOS[GOAL_TWO_COUNT] = {
    {
        rfid : {0x04, 0xE7, 0x18, 0x05, 0x39, 0x6C, 0x80, 0x00, 0x00, 0x00}
    }};

Tag GOAL_THREES[GOAL_THREE_COUNT] = {
    {
        rfid : {0x04, 0x5B, 0xC6, 0x00, 0x19, 0x6C, 0x80, 0x00, 0x00, 0x00}
    }};