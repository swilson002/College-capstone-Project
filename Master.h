#ifndef MASTER
#define MASTER

#include "FullBracket.h"
class Master : public FullBracket
{
 private:
  int gamesLeft;
  int currentRound;
  void nextRound();
  void nextFinal();
  void plimNext();

 public:
  Master(int noDivisions);
#ifndef NO_BRACKET_NAME
  Master(int noDivisions, string divName[], string finalName);
#endif
  ~Master();
  bool newTeam(Team *newTeam, int div);
  bool teamWon(int div, int seed, int score1, int score2, bool selected);
  bool markSelSpot(int div, int seed, int round);
  void teamsIn();
  int getGamesLeft();
  int getCurrentRound();
};
#endif
