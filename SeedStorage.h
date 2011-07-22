#ifndef SEEDSTORE
#define SEEDSTORE

#include "dataUnit.h"

#define MAXSEED 32
//#define STATIC

class SeedStorage
{
 public:
  SeedStorage();
  ~SeedStorage();
  void addGame(int winner, int loser);
  int getWins(int seed1, int seed2);
  int getGames(int seed1, int seed2);
  void addUnit(int seed1, int seed2, int wins, int games);
  int getMaxSize();

 private:
  DataUnit *units[MAXSEED][MAXSEED];
#ifndef STATIC
  void expandStorage(int newMax);
#endif
  int maxSize;
};
#endif
