
#ifndef GOAL_MANAGER_H
#define GOAL_MANAGER_H

#include <Arduino.h>
#include <MFRC522.h>
#include <TagManager.h>

class GoalManager {
   public:
    GoalManager(MFRC522* controller);
    void printUuid(uint8_t uuid[]);
    bool uidEqual(uint8_t left[], uint8_t right[]);
    void copyUid(uint8_t from[], uint8_t to[]);
    int getFoundGoal(Tag goals[], int goalCount);      // finds the index of the goal in the passed in goal arrau
    bool isGoalFound(Tag goals[], int goalCount);      // returns whether or not the scanned item is a goal of passed in array
    bool isResetFound();                                // returns whether or not the reset tag was scanned
    bool isNewNfcFound();                               // returns whether or not a new NFC tag was presented (different from previous scanned)

    bool isGoalOneScanned();
    bool isGoalTwoScanned();
    bool isGoalThreeScanned();
    bool isAllGoalsScanned();
    void resetGoals();

    bool GOAL_ONE_SCANNED;
    bool GOAL_TWO_SCANNED;
    bool GOAL_THREE_SCANNED;

   private:
    MFRC522* nfc;
    uint8_t lastUid[10];
};

#endif
