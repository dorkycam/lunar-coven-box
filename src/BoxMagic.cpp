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
    if (this->goals[goalNum]) {
        return false;
    }
    this->goals[goalNum] = true;

    return true;
}

bool BoxMagic::isGoalScanned(int goalNum) {
    return this->goals[goalNum];
}
