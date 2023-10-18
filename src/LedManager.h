#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#define LED_MAX 255
#define LED_MIN 0

#define LED_TWINKLE_MAX 255
#define LED_TWINKLE_MIN 50

#include <Adafruit_AW9523.h>

#include "rfid_lights.h"

class LedManager {
   public:
    LedManager(Adafruit_AW9523* controller);
    void turnOnLight(int goalNum, uint8_t brightness = LED_MAX);
    void turnOffLight(int goalNum);
    void setAllLightsBrightness(uint8_t brightness = LED_MAX);
    void setTwinkle(int goalNum, bool value);
    void twinkle(int goalNum);
    void doTwinkles();

    void fadeAllOut(float seconds);
    void fadeOneOut(float seconds, int goalNum);
    void fadeAllIn(float seconds);
    int spin(float seconds, int startGoalNum, float spinDelay, int stopGoalNum = -1);

   private:
    Adafruit_AW9523* aw;
    bool twinkles[GOAL_COUNT];
    bool led[GOAL_COUNT];
};

#endif
