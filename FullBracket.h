#ifndef FULLBRACKET
#define FULLBRACKET

#include "Bracket.h"
#define DIV 4
#define FINALS -1

class FullBracket
{
 private:
  Bracket *divisions[DIV];
  Bracket *finals;
  Team *nullTeam;
  int noDiv;
  bool teamsIn;
  bool finalIn;

 protected:
  bool advanceTeam(int div, int seed, int round, int score1, int score2,
		   bool selected);
  bool markSpot(int div, int seed, int round);
  bool addTeam(Team *newTeam, int div);
  void teamsEntered();
  void createFinals();

 public:
  bool getMark(int div, int seed, int round);

#ifndef NO_BRACKET_NAME
  FullBracket(int noDivisions, string divName[DIV], string finalName);
#endif

  FullBracket(int noDivisions);
  /* if div = -1, bracket is finals*/
  Team *getTeam(int div, int seed, int round);
  Team *getDivChamp(int div);
  Team *getOpponent(int div, int seed, int round);
  int getScore(int div, int seed, int round);
  int getOpScore(int div, int seed, int round);
  int getNoDiv();
  int getNoTeams(int div);
  Team *getTeamByLoc(int div, int pos, int round);
  bool getMarkByLoc(int div, int pos, int round);
  int getScoreByLoc(int div, int pos, int round);
  int getMaxRounds();
  int getMinRounds();
  int getFinalRounds();
  bool getFinalStatus();
#ifndef NO_BRACKET_NAME
  string getDivName(int div);
#endif
  ~FullBracket();
};
#endif
