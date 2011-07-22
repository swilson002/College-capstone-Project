#ifndef LOADER
#define LOADER

#include "Manager.h"
#include "globalConst.h"

#include<fstream>
using namespace std;

class Loader
{
 private:
  char *teamFile;
  char *setFile;
  char *bracketFile;
  char *masterFile;
  Player_Manager *loadTeams();
  void loadSettings(Player_Manager *game); 
  void loadBrackets(Player_Manager *game); 
  void loadMaster(Player_Manager *game);
  void loadAI();  // will be blank until AI is implemented
  void saveTeams(Player_Manager *game, ofstream &teamOut);
  void saveSettings(Player_Manager *game, ofstream &setOut);
  void saveBrackets(Player_Manager *game, ofstream &brkOut);
  void saveMaster(Player_Manager *game, ofstream &mastOut);
  void saveAI();  // will be blank until AI is implemented
  void errorStatement();

 public:
  Loader();
  Player_Manager *loadGame();
  void saveGame(Player_Manager *game);
  void clean();
};
#endif
