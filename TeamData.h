#ifndef TEAMDATA
#define TEAMDATA

#include "dataUnit.h"
#include<string>
using namespace std;

#define MAXTEAM 32
#define MAXIMUMROUND 8

class TeamData
{
 public:
  TeamData();
  TeamData(string newName);
  TeamData(string newName, int newVisits, int roundVisitsCount,
	   int newRoundVisits[]);
  ~TeamData();
  string getName();
  int getWins(int curSeed, int opSeed);
  int getGames(int curSeed, int opSeed);
  bool addWin(int curSeed, int opSeed);
  bool addLoss(int curSeed, int opSeed);
  bool addUnit(int curSeed, int opSeed, int wins, int games);
  int getTotalWins();
  int getTotalGames();
  int getMaxSize();
  void addVisit();
  int getVisits();
  void addRoundVisit(int round);
  int getRoundVisits(int round);
  double getAverageWins();
  void calculateTotal();

 private:
  string name;
  DataUnit *units[MAXTEAM][MAXTEAM];
  int maxSize;
  DataUnit *total;
  int visits;
  int roundVisits[MAXIMUMROUND];  // this is for total number of rounds
  void expandData(int seed);
};

#endif
