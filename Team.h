/* This class keeps track of individual teams and seedings
   Functions:
   Team(string, int): adds a new team of seed n (the seeding is permanent)
   editTeam(string) changes the name of a team
   returnName() returns name
   returnSeed() returns seed
   returnWins() returns the wins on a team
   rentunLosses() reurns the number of losses
   New atributes can be added in the code
*/
#ifndef TEAM
#define TEAM

#include<string>
using namespace std;

class Team
{
  public:
  Team();
  Team(string newTeam, int TeamId, string conf, int newSeed, 
       int newWins, int newLosses);
  string returnName();
  int returnSeed();
  int returnWins();
  int returnLosses();
  int returnWinCount();
  bool returnEliminated();
  string returnConference();
  void win();
  void eliminate();
  int returnID();
  bool returnBlank();

  private: 
  int id;
  int seed;
  string teamName;
  int wins;
  string conference;
  int losses;
  int winCount;
  bool eliminated;
  bool blank;
};
#endif
