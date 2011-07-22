#ifndef BRACKET
#define BRACKET

#include "Team.h"
/* 
    This class uses an implied seeding system based on the order the teams
    were added.  It completely ignores the seed in the team class. The 
    third team added is seed 2 even if the seed of the team in the team 
    class is 8 This system allows for an easy search.  Each team is accessed
    through their bracket seed

    addTeam() adds the team and set stats
    advanceTeam() advances a team in the tournament and sets the scores
    findTeam() finds the team to be used
*/


#define NO_BRACKET_NAME
class Bracket
{
  public:
  Bracket();

#ifndef NO_BRACKET_NAME
  Bracket(string name);
#endif

  /* Functions that return a team value return null if team isn't there,
   returns nuttTeam is parameters are outside bounds */

  ~Bracket();

  Team *getChamp();
#ifndef NO_BRACKET_NAME
  string getBracketName();
#endif

  int getNumTeams();

  int getRounds();

  bool advanceTeam(int seed, int round, int firstScore, int SecondScore,
		   bool selected);  // false means opponent won
  // firstScore is that of the winner

  bool addTeam(Team *insTeam);

  int getScore(int seed, int round);

  int getOpScore(int seed, int round);
  Team *getTeam(int seed, int round);

  bool getMark(int seed, int round);
  bool markSpot(int seed, int round);

  void bracketDone();

  Team *getTeamByLoc(int pos, int round);
  bool getMarkByLoc(int pos, int round);
  int getScoreByLoc(int pos, int round);
  Team *getOpponent(int pos, int round);
  int getTwoToRound();

  private:
class Node
  {
  public:
    Team *curTeam;
    int score;
    Node *first;
    Node *second;
    bool  mark;     /* true if pick is correct */
    Node()
    {
      first = NULL;
      second = NULL;
      score = 0;
      mark = false;
    }
  };


  Node *champ;
  Team *nullTeam;  /* if a procedure returns this, it selected an empty spot*/
  Node *nullNode;
  int teams;
  int rounds;
  int twoToRound;
  string bracketName;
  Node *findTeam(int seed, int round);  // will never return NULL
  int findLoc(int seed, int round);
  Node *getNode(int pos, int round);  // will never return NULL
  bool teamsIn;
};
#endif
