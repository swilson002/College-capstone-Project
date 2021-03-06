#ifndef GAMEINT
#define GAMEINT

#include "Manager.h"
#include "globalConst.h"
#include "stringconv.h"

class Game_Interface
{
 private:
  string scoringMode[8];
  string negRound[8];
  Player_Manager *manager;
  int selectBracket();
  void displayTeams();
  void selectGame();  // int will be based off seed
  void advanceTeam(int div, int seed);
  void displayTeam(int div, int seed);
  void displayBracket();
  void displaySelectedDivision(int div, int selection); // div == -1 is result
  void displayTourn();
  void displayPlayers();
  void displayPlayersAltScore();
  void showScoringMode();
  int quitMenu();
  bool clearMenu();

 public:
  Game_Interface();
  void addManager(Player_Manager *game);
  int playGame();  // 0 is quit, 1 is save and quit, 2 is save and return
  // 3 is clear game
};
#endif
