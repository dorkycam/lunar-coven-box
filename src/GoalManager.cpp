#include "GoalManager.h"

#include <Arduino.h>

#include "TagManager.h"

GoalManager::GoalManager(MFRC522* controller) : nfc(controller) {
    GOAL_ONE_SCANNED = false;
    GOAL_TWO_SCANNED = false;
    GOAL_THREE_SCANNED = false;
}

bool GoalManager::isNewNfcFound() {
    if (!this->nfc->PICC_IsNewCardPresent()) {
        return false;
    }

    Serial.println("card present");
    if (!this->nfc->PICC_ReadCardSerial()) {  // Since a PICC placed get Serial and continue
        return false;
    }

    if (uidEqual(this->nfc->uid.uidByte, lastUid)) {
        return false;
    }

    Serial.println("new card read");
    copyUid(this->nfc->uid.uidByte, this->lastUid);
    this->nfc->PICC_DumpToSerial(&this->nfc->uid);

    printUuid(lastUid);
    return true;
}

// GOAL RELATED FUNCTIONS

bool GoalManager::isResetFound() {
    if (isGoalFound(RESET_TAGS, 2)) {
        Serial.println("Reset found");
        return true;
    }

    return false;
}

int GoalManager::getFoundGoal(Tag goals[], int goalCount) {
    int foundGoal = -1;
    for (int i = 0; i < goalCount; i++) {
        if (uidEqual(goals[i].rfid, lastUid)) {
            foundGoal = i;
            break;
        }
    }

    return foundGoal;
}

bool GoalManager::isGoalFound(Tag goals[], int goalCount) {
    return getFoundGoal(goals, goalCount) > -1;
}

bool GoalManager::isGoalOneScanned() {
    int foundGoal = -1;
    for (int i = 0; i < GOAL_ONE_COUNT; i++) {
        if (uidEqual(GOAL_ONES[i].rfid, lastUid)) {
            foundGoal = i;
            break;
        }
    }

    GOAL_ONE_SCANNED = foundGoal > -1;

    return GOAL_ONE_SCANNED;
}

bool GoalManager::isGoalTwoScanned() {
    int foundGoal = -1;
    for (int i = 0; i < GOAL_TWO_COUNT; i++) {
        if (uidEqual(GOAL_TWOS[i].rfid, lastUid)) {
            foundGoal = i;
            break;
        }
    }

    GOAL_TWO_SCANNED = foundGoal > -1;

    return GOAL_TWO_SCANNED;
}

bool GoalManager::isGoalThreeScanned() {
    int foundGoal = -1;
    for (int i = 0; i < GOAL_THREE_COUNT; i++) {
        if (uidEqual(GOAL_THREES[i].rfid, lastUid)) {
            foundGoal = i;
            break;
        }
    }

    GOAL_THREE_SCANNED = foundGoal > -1;

    return GOAL_THREE_SCANNED;
}

bool GoalManager::isAllGoalsScanned() {
    if (GOAL_ONE_SCANNED && GOAL_TWO_SCANNED && GOAL_THREE_SCANNED) {
       return true;
    }

    return false;
}

void GoalManager::resetGoals() {
    GOAL_ONE_SCANNED = false;
    GOAL_TWO_SCANNED = false;
    GOAL_THREE_SCANNED = false;
    return;
}


// UTILITY FUNCTIONS
void GoalManager::printUuid(uint8_t uuid[]) {
    Serial.print("{");
    for (int i = 0; i < 10; i++) {
        Serial.print("0x");
        Serial.print(uuid[i], HEX);
        Serial.print(", ");
    }
    Serial.println("}");
}

bool GoalManager::uidEqual(uint8_t left[], uint8_t right[]) {
    for (int i = 0; i < 10; i++) {
        if (left[i] != right[i]) {
            return false;
        }
    }
    return true;
}

void GoalManager::copyUid(uint8_t from[], uint8_t to[]) {
    for (int i = 0; i < 10; i++) {
        to[i] = from[i];
    }
}