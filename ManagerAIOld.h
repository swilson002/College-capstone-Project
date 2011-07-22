#ifndef MANAGERAI
#define MANAGERAI

#include "AIcomp.h"
#include "Manager.h"
#include "Team.h"

#define KEEPDATA

#define NO_AI 0
#define MARGIN 1000

class AI_Manager : public Player_Manager
{
 public:
  AI_Manager(string divName[], string finalName, int noDivisions, 
	     AICompute *AI);
  AI_Manager(string divName[], string finalName, int noDivisions);
  ~AI_Manager();
  void newAI(string brName, int AIType);
  int getAIMaxSize();
  int getAIDifMaxSize();
  int getAIGames(int seed1, int seed2);
  int getAIDifGames(int difference);
  int getAIWins(int seed1, int seed2);
  int getAIDifWins(int difference);
  void Learn();

 private:
  AICompute *compute;
};

#endif
