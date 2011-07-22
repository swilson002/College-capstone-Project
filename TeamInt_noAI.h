#ifndef TEAMINT
#define TEAMINT

#include "Manager.h"
#include "globalConst.h"

class Team_Interface  // The purpose of this interface is to create the teams
{
 private:
  char divName[DIV][MAXINPUT];  // DIV is a constant defined in FullBracket.h
  char finalName[MAXINPUT];
  int noDiv;
  Player_Manager *manager;
  void enterBracketDesc();
  void enterTeams();
  
 public:
  Team_Interface();
  void enterData();
  Player_Manager *getManager();
};
#endif
