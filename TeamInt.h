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
  void enterBracketDesc();
  void enterTeams();
  string enterTeamName();
  int verifyTeam(string team);  // returns the team id

 public:
  Team_Interface();
  Team_Interface(AI_Manager *game);
  void enterData();
  AI_Manager *getManager();
};
#endif
