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
  AI_Manager();
  AI_Manager(AICompute *AI);
  AI_Manager(string divName[], string finalName, int noDivisions, 
	     AICompute *AI);
  AI_Manager(string divName[], string finalName, int noDivisions);
  ~AI_Manager();
  int addAITeamName(string newName);  // returns the id assigned to that name
  void addAITeamAlias(string newName, int id);
  int getAITeamID(string name);
  string getAITeamName(int id);
  void newAI(string brName, int AIType);
  int getAIMaxSize();
  int getAIDifMaxSize();
  int getAITeamTotalMaxSize();
  int getAITeamMaxSize(int id);
  int getAITeamMaxSize();
  int getAIGames(int seed1, int seed2);
  int getAIDifGames(int difference);
  int getAITeamGames(int id, int seed1, int seed2);
  int getAITeamGames(int seed1, int seed2);
  int getAIWins(int seed1, int seed2);
  int getAIDifWins(int difference);
  int getAITeamWins(int id, int seed1, int seed2);
  int getAITeamWins(int seed1, int seed2);
  int getAITeamTotalWins(int id);
  int getAITeamTotalWins();
  int getAITeamTotalGames(int id);
  int getAITeamTotalGames();
  int getAITeamVisits(int id);
  int getAITeamVisits();
  int getAITeamRoundVisits(int id, int round);
  int getAITeamRoundVisits(int round);
  string getAITeamAlias(unsigned int index1, unsigned int index2);
  int getAITeamAliasID(unsigned int index1, unsigned int index2);
  double getAITeamAverageWins(int id);
  double getAITeamAverageWins();
  void Learn();

 private:
  AICompute *compute;
  void addVisits();
};

#endif
