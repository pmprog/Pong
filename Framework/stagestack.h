
#pragma once

#include "stage.h"

// Constant: MAX_STACK_SIZE
// Maximum number of stages that can be held in the game loop
#define MAX_STACK_SIZE	12

class StageStack
{
  private:
    int StackIndex;
    Stage* Stack[MAX_STACK_SIZE];

  public:
    StageStack();
    int Push( Stage* newStage );
    Stage* Pop();
    Stage* Current();
    int GetStackIndex();
    Stage* Item(int index);
		Stage* Previous( Stage* checkStage );
		Stage* Previous( Stage* checkStage, bool includeTransitions );
		bool IsEmpty();

};
