#ifndef LOADER
#define LOADER

#include "ManagerAI.h"
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
  char *AIFile;

  AI_Manager *loadManager(AICompute *game);
  void loadSettings(AI_Manager *game); 
  void loadBrackets(AI_Manager *game); 
  void loadMaster(AI_Manager *game);
  void saveTeams(AI_Manager *game, ofstream &teamOut);
  void saveSettings(AI_Manager *game, ofstream &setOut);
  void saveBrackets(AI_Manager *game, ofstream &brkOut);
  void saveMaster(AI_Manager *game, ofstream &mastOut);
  void saveAI(AI_Manager *game, ofstream &AIOut);
  void errorStatement();

 public:
  Loader();
  AI_Manager *loadGame(AICompute *comp);
  AICompute *loadAI();
  void saveGame(AI_Manager *game);
  void clean();
};
#endif
