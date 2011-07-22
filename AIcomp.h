#ifndef AICOMP
#define AICOMP

#include "SeedDifStorage.h"
#include "SeedStorage.h"
#include "TeamStorage.h"
#include "Team.h"

class AICompute
{
 public:
  AICompute();
  AICompute(SeedStorage *newSeed, SeedDifStorage *newSeedDif, 
	    TeamStorage *newTeam);
  ~AICompute();
  void addGame(Team *winner, Team *loser);
  int addTeamName(string newName);  // returns the id assigned to that name
  void addTeamAlias(string newName, int id);
  int getTeamID(string name);
  string getTeamName(int id);
  int getWinsDif(int difference);
  int getGamesDif(int difference);
  int getWins(int seed1, int seed2);
  int getGames(int seed1, int seed2);
  int getTeamWins(int id, int seed1, int seed2);
  int getTeamWins(Team *selTeam, int seed1, int seed2);
  int getTeamGames(int id, int seed1, int seed2);
  int getTeamGames(Team *selTeam, int seed1, int seed2);
  int getTeamTotalWins(int id);
  int getTeamTotalWins(Team *selTeam);
  int getTeamTotalGames(int id);
  int getTeamTotalGames(Team *selTeam);
  double computeProbDif(Team *team1, Team *team2);
  double computeProb(Team *team1, Team *team2);
  double computeProbTeam(Team *team1, Team *team2);
  void addTeamVisit(Team *selTeam);
  void addTeamRoundVisit(Team *selTeam, int round);
  int getDifMaxSize();
  int getMaxSize();
  int getTeamTotalMaxSize();
  int getTeamMaxSize(int id);
  int getTeamMaxSize(Team *selTeam);
  int getTeamVisits(int id);
  int getTeamVisits(Team *selTeam);
  int getTeamRoundVisits(int id, int round);
  int getTeamRoundVisits(Team *selTeam, int round);
  string getTeamAlias(unsigned int index1, unsigned int index2);
  int getTeamAliasID(unsigned int index1, unsigned int index2);
  double getTeamAverageWins(int id);
  double getTeamAverageWins(Team *selTeam);
  void calculateTotal(Team *selTeam);


 private:
  SeedStorage *Seed;
  SeedDifStorage *SeedDif;
  TeamStorage *TeamStore;
  double calcAreaProb(int seed1, int seed2, int range);  // returns -1 if
  double calcProbOfTeam(Team *team1, Team *team2); // no data is found
  double calcAreaProbOfTeam(TeamData *team1, int seed1, int seed2, int range);
  double calcAreaProbOfTeamOp(TeamData *team1, int seed1, int seed2, 
			      int range);
};
#endif
