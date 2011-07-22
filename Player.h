#ifndef PLAYER
#define PLAYER

#include "Master.h"
#define MAXROUND 16
class Player : public FullBracket
{
 public:
  Player(int noDivisions, FullBracket *theMaster, int AI, string name);

#ifndef NO_BRACKET_NAME
  Player(int noDivisions, string divName[], string finalName, 
	 FullBracket *theMaster, int AI, string name);
#endif

  ~Player();
  bool newTeam(Team *insTeam, int div);
  bool makePick(int div, int seed, int round, bool selected);
  void teamsIn();
  void checkTeam(int div, int seed, int round);
  void checkFinals();
  int getPlScore(int round);
  int getFinalBrScore(int round);
  int getAIType();
  string getBrName();

 private:
  int score[MAXROUND];
  int finalScore[DIV]; // DIV is a constant in the FullBracket class
  int finalRound;
  int AIType;
  string BrName;
  FullBracket *master;
  
};
#endif
