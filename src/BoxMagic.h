#ifndef BOX_MAGIC_H
#define BOX_MAGIC_H

class BoxMagic {
   public:
    BoxMagic();                     // consturctor
    bool isGameStarted();             // is the game started
    void resetGame();                 // turns off all the lights
    bool scanGoal(int goalNum);       // turns on light for specific goal
    bool isGoalScanned(int goalNum);  // returns if the goal has been met
    bool isGameFinished();
    bool isAllGoalsScanned();

   private:
    bool goals[2];
};

#endif
