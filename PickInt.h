#ifndef PICKINT
#define PICKINT

#include "globalConst.h"

class Picks_Interface
{
 private:
  AI_Manager *manager;
  string scoringMode[8];
  string negRound[8];
  string AIType[8];
  void newBracket();
  void newAIBracket();
  void pickTeamMenu(int div, int seed, int round);
  int selectBracket();
  void deleteBracket();
  void showBracket();
  void displayDivision(int div, int selection);
  void showTeams();
  void showSet();
  void setSettings();
  void displaySelectedTeam();
  int quitMenu();

 public:
  Picks_Interface();
  void addManager(AI_Manager *game);
  int makePicks();  // 0 is quit (game mode if set, 1 is save and quit, 
                    //2 is save and return
  AI_Manager *getManager();
};
#endif
