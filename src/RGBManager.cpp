#include <Arduino.h>
#include "RGBManager.h"

RGBManager::RGBManager(int rPin, int gPin, int bPin, int fadeSpeed) {
    R_PIN = rPin;
    G_PIN = gPin;
    B_PIN = bPin;
    FADE_SPEED = fadeSpeed;

    CURRENT_R_VALUE = LED_MIN;
    CURRENT_G_VALUE = LED_MIN;
    CURRENT_B_VALUE = LED_MIN;
}

void RGBManager::setR(int value) {
    CURRENT_R_VALUE = value;
    analogWrite(R_PIN, value);
    return;
};

void RGBManager::setG(int value) {
    CURRENT_G_VALUE = value;
    analogWrite(G_PIN, value);
    return;
};

void RGBManager::setB(int value) {
    CURRENT_B_VALUE = value;
    analogWrite(B_PIN, value);
    return;
};

void RGBManager::setRGB(int r, int g, int b) {
    setR(r);
    setG(g);
    setB(b);
    return;
};

void RGBManager::turnOffLight() {
    setRGB(LED_MIN, LED_MIN, LED_MIN);
    return;
};

int getBiggestDiff(int r, int g, int b) {
    if (r > g) {
        if (r > b) {
            return r;
        }
    }

    if (g > b) {
        return g;
    }

    return b;
};

void RGBManager::fadeToRGB(int r, int g, int b) {
    int loopCounter = 0;

    bool isRinc = r > CURRENT_R_VALUE;
    bool isGinc = g > CURRENT_G_VALUE;
    bool isBinc = b > CURRENT_B_VALUE;

    int rDiff = abs(r - CURRENT_R_VALUE);
    int gDiff = abs(g - CURRENT_G_VALUE);
    int bDiff = abs(b - CURRENT_B_VALUE);

    loopCounter = getBiggestDiff(rDiff, gDiff, bDiff);

    for (int i = 0; i < loopCounter; i++) { 
        // SET R
        if (CURRENT_R_VALUE != r) {
            if (isRinc && CURRENT_R_VALUE < LED_MAX) {
                setR(CURRENT_R_VALUE + 1);
            } else if (!isRinc && CURRENT_R_VALUE > LED_MIN) {
                setR(CURRENT_R_VALUE - 1);
            }
        }
        // SET G
        if (CURRENT_G_VALUE != g) {
            if (isGinc && CURRENT_G_VALUE < LED_MAX) {
                setG(CURRENT_G_VALUE + 1);
            } else if (!isGinc && CURRENT_G_VALUE > LED_MIN) {
                setG(CURRENT_G_VALUE - 1);
            }
        }
        // SET B
        if (CURRENT_B_VALUE != b) {
            if (isBinc && CURRENT_B_VALUE < LED_MAX) {
                setB(CURRENT_B_VALUE + 1);
            } else if (!isBinc && CURRENT_B_VALUE > LED_MIN) {
                setB(CURRENT_B_VALUE - 1);
            }
        }
        // WAIT
        delay(FADE_SPEED);
    } 

    
    return;
};

void RGBManager::pulse() {
    // Check if all values are at the bottom, and if so, start pulsing up
    if (CURRENT_R_VALUE == bottomPulseValue || CURRENT_G_VALUE == bottomPulseValue || CURRENT_B_VALUE == bottomPulseValue) {
        pulsingUp = true;
    }
    // Check if all values are at the top, and if so, start pulsing down
    else if (CURRENT_R_VALUE == topPulseValue || CURRENT_G_VALUE == topPulseValue || CURRENT_B_VALUE == topPulseValue) {
        pulsingUp = false;
    }

    if (pulsingUp) {
        if (CURRENT_R_VALUE > 0) CURRENT_R_VALUE += pulseSpeed;
        if (CURRENT_G_VALUE > 0) CURRENT_G_VALUE += pulseSpeed;
        if (CURRENT_B_VALUE > 0) CURRENT_B_VALUE += pulseSpeed;
    } else {
        if (CURRENT_R_VALUE > 0) CURRENT_R_VALUE -= pulseSpeed;
        if (CURRENT_G_VALUE > 0) CURRENT_G_VALUE -= pulseSpeed;
        if (CURRENT_B_VALUE > 0) CURRENT_B_VALUE -= pulseSpeed;
    }

    // Constrain the values to ensure they are within the valid range
    CURRENT_R_VALUE = constrain(CURRENT_R_VALUE, 0, topPulseValue);
    CURRENT_G_VALUE = constrain(CURRENT_G_VALUE, 0, topPulseValue);
    CURRENT_B_VALUE = constrain(CURRENT_B_VALUE, 0, topPulseValue);

    setRGB(CURRENT_R_VALUE, CURRENT_G_VALUE, CURRENT_B_VALUE);
}

void RGBManager::rainbowAnimation() {
    fadeToRGB(255, 0, 0);       // Vibrant Red
    fadeToRGB(255, 127, 0);     // Vibrant Orange
    fadeToRGB(255, 255, 0);     // Vibrant Yellow
    fadeToRGB(127, 255, 0);     // Vibrant Green
    fadeToRGB(0, 255, 127);     // Vibrant Spring Green
    fadeToRGB(0, 255, 255);     // Vibrant Cyan
    fadeToRGB(0, 127, 255);     // Vibrant Azure
    fadeToRGB(0, 0, 255);       // Vibrant Blue
    fadeToRGB(127, 0, 255);     // Vibrant Violet
    fadeToRGB(255, 0, 255);     // Vibrant Magenta
    fadeToRGB(255, 0, 127);    // Vibrant Rose
    return;
}
