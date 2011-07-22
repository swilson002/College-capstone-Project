#ifndef PICKINT
#define PICKINT

#include "Manager.h"
#include "globalConst.h"

class Picks_Interface
{
 private:
  Player_Manager *manager;
  string scoringMode[8];
  string negRound[8];
  void newBracket();
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
  void addManager(Player_Manager *game);
  int makePicks();  // 0 is quit (game mode if set, 1 is save and quit, 
                    //2 is save and return
  Player_Manager *getManager();
};
#endif
