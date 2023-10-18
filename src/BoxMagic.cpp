#include "BoxMagic.h"

#include "rfid_lights.h"

BoxMagic::BoxMagic() {
    this->resetGame();
}

bool BoxMagic::isGameStarted() {
    for (int i = 0; i < GOAL_COUNT; i++) {
        if (this->goals[i]) {
            return true;
        }
    }
    return false;
}

bool BoxMagic::isAllGoalsScanned() {
    for (int i = 0; i < GOAL_COUNT; i++) {
        if (!this->goals[i]) {
            return false;
        }
    }
    return true;
}

void BoxMagic::resetGame() {
    for (int i = 0; i < GOAL_COUNT; i++) {
        this->goals[i] = false;
    }
}

bool BoxMagic::isGameFinished() {
    return this->isAllGoalsScanned();
}

bool BoxMagic::scanGoal(int goalNum) {
    // Serial.println("GOAL VALUES: ");
    // for (int i = 0; i < GOAL_COUNT; i++) {
    //     Serial.println(this->goals[i]);
    // }

    if (this->goals[goalNum]) {
         Serial.println("Goal ALready Scannerered ");
        return false;
    }
    this->goals[goalNum] = true;

    Serial.println("Goal not scanned yetee ");
    return true;
}

bool BoxMagic::isGoalScanned(int goalNum) {
    return this->goals[goalNum];
}
