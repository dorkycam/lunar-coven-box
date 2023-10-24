
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
//Includes the Arduino Stepper Library
#include <Stepper.h>

#include "GoalManager.h"
#include "RGBManager.h"
#include "TagManager.h"

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3
#define FADESPEED 5     // make this higher to slow down

// for RFID scanner driver setup?
MFRC522 mfrc522(10, 9);

RGBManager rgbManager(REDPIN, GREENPIN, BLUEPIN, FADESPEED);
GoalManager goalManager(&mfrc522);

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 4, 7, 2);

bool boxIsOpen = false;
int TOP_LED_PULSE = LED_MAX;
int BOTTOM_LED_PULSE = 100;
int PULSE_INCR = false;

void setup() {
    Serial.begin(9600);
    while (!Serial)
        delay(1);  // wait for serial port to open

    Serial.println("beginning");

    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("rfc works");

    // RFID scanner pin setup
    pinMode(7, OUTPUT);

    Serial.println("Setup complete! (but check for errors)");

    pinMode(REDPIN, OUTPUT);
    pinMode(GREENPIN, OUTPUT);
    pinMode(BLUEPIN, OUTPUT);

    rgbManager.setRGB(LED_MAX, 0, LED_MAX);

}

void loop() {
    // set speed of stepper motor
    myStepper.setSpeed(18);
      

    if (!goalManager.isNewNfcFound()) {
        if (goalManager.isAllGoalsScanned()) {
            if (!boxIsOpen) {
                myStepper.step(-(stepsPerRevolution / 2));
                Serial.println("Game is finished");
                boxIsOpen = true;

                rgbManager.fadeToRGB(LED_MAX, LED_MAX, LED_MAX);
            }
            return;
        }

        rgbManager.pulse();
        return;
    }

    if (goalManager.isResetFound()) {
        goalManager.resetGoals();
        myStepper.step(stepsPerRevolution / 2);

        rgbManager.fadeToRGB(LED_MAX, 0, LED_MAX);

        boxIsOpen = false;
        return;
    }

    if (!goalManager.GOAL_ONE_SCANNED && !goalManager.GOAL_TWO_SCANNED && !goalManager.GOAL_THREE_SCANNED) {
         Serial.println("still at one");
        if (goalManager.isGoalOneScanned()) {
            Serial.println("goal one scanned");
            rgbManager.fadeToRGB(0, 100, LED_MAX);
        }
        return;
    }

    if (goalManager.GOAL_ONE_SCANNED && !goalManager.GOAL_TWO_SCANNED && !goalManager.GOAL_THREE_SCANNED) {
         Serial.println("got to two");
        if (goalManager.isGoalTwoScanned()) {
             Serial.println("goal two scanned");
            rgbManager.fadeToRGB(LED_MAX, 0, 0);
        }
        return;
    }

    if (goalManager.GOAL_ONE_SCANNED && goalManager.GOAL_TWO_SCANNED && !goalManager.GOAL_THREE_SCANNED) {
         Serial.println("got to three");
        if (goalManager.isGoalThreeScanned()) {
            Serial.println("goal three scanned");
            rgbManager.rainbowAnimation();
            rgbManager.rainbowAnimation();
            rgbManager.rainbowAnimation();
        }
    }

}