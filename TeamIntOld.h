#ifndef TEAMINT
#define TEAMINT

#include "globalConst.h"

class Team_Interface  // The purpose of this interface is to create the teams
{
 private:
  char divName[DIV][MAXINPUT];  // DIV is a constant defined in FullBracket.h
  char finalName[MAXINPUT];
  int noDiv;
  AI_Manager *manager;
  void enterBracketDesc(AICompute *AIData);
  void enterTeams();
  
 public:
  Team_Interface();
  void enterData(AICompute *AIData);
  AI_Manager *getManager();
};
#endif
