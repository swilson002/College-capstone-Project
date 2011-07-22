#ifndef AICOMP
#define AICOMP

#include "SeedDifStorage.h"
#include "SeedStorage.h"
#include "Team.h"

class AICompute
{
 public:
  AICompute();
  AICompute(SeedStorage *newSeed, SeedDifStorage *newSeedDif);
  ~AICompute();
  void addGame(Team *winner, Team *loser);
  int getWinsDif(int difference);
  int getGamesDif(int difference);
  int getWins(int seed1, int seed2);
  int getGames(int seed1, int seed2);
  double computeProbDif(Team *team1, Team *team2);
  double computeProb(Team *team1, Team *team2);
  int getDifMaxSize();
  int getMaxSize();
  
 private:
  SeedStorage *Seed;
  SeedDifStorage *SeedDif;
  double calcAreaProb(int seed1, int seed2, int range);
};
#endif
