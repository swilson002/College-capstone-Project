#ifndef SEEDDIFSTORE
#define SEEDDIFSTORE

#include "dataUnit.h"

#define MAXDIF 32

class SeedDifStorage
{
 public:
  SeedDifStorage();
  ~SeedDifStorage();
  void addGame(int winner, int loser);
  int getWins(int difference);
  int getGames(int difference);
  void addUnit(int difference, int wins, int games);
  int getMaxSize();
 private:
  DataUnit *units[MAXDIF];
  int maxSize;
  void expandStorage(int newMax);
};
#endif
