
#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
//Includes the Arduino Stepper Library
#include <Stepper.h>

#include "GoalManager.h"
#include "LedManager.h"
#include "BoxMagic.h"
#include "rfid_lights.h"

// for RFID scanner driver setup?
MFRC522 mfrc522(10, 9);

// for LED driver setup
Adafruit_AW9523 aw;

BoxMagic game;
// LedManager ledManager(&aw);
GoalManager goalManager(&mfrc522);

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 6, 4, 5, 3);

bool boxIsOpen = false;

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
}

void loop() {
    // set speed of stepper motor
    myStepper.setSpeed(18);

    if (!goalManager.isNewNfcFound()) {
        if (game.isAllGoalsScanned()) {
            if (!boxIsOpen) {
                myStepper.step(-(stepsPerRevolution / 2));
                Serial.println("Game is finished");
                boxIsOpen = true;
            }
            return;
        }

        return;
    }

    if (goalManager.isResetFound()) {
        game.resetGame();
        myStepper.step(stepsPerRevolution / 2);
        // ledManager.setAllLightsBrightness(0);
        boxIsOpen = false;
        return;
    }

    int scannedGoal = goalManager.getFoundGoal();
    if (scannedGoal != -1) {
        if (!game.scanGoal(scannedGoal)) {
            Serial.println("Already scanned this goal");
            return;
        }

        // ledManager.turnOnLight(scannedGoal);
        // ledManager.setTwinkle(scannedGoal, true);

        Serial.println("Succesfully scanned goal");
        return;
    }
}