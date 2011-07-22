#ifndef MANAGER
#define MANAGER

#include "Player.h"
#include "Master.h"

#define MAXPLAYERS 16
#define MAXTEAMS 32

class Player_Manager
{
 private:
  struct competitor
  {
    Player *bracket;
    int curScore;
    competitor()
    {
      curScore = 0;
    }
  };
  competitor *players[MAXPLAYERS];    // sorted by score
  string divName[DIV];
  string finalName;
  Master *result;
  Team *Total[DIV][MAXTEAMS];
  competitor *selectedPlayer;
  int numPlayers;
  int numTeams[DIV];
  int numDiv;
  int lowestRound;  // first complete (no byes) round
  int scoringMode; // 1 is n+1 points per game in round n.  
  //2 is 2^n points per game in round n. anything else is 1 point per game
  //reverses round numbering
  int countNegRound;  //1 is 1 point, 2 is with system, anything else is
  // not al all
  bool teamsIn;
  bool gameMode;
  bool gameDone;
  void updateScore();
  void gameComplete();

 protected:
  Team * selectedTeam;

 public:
  Player_Manager();
  Player_Manager(string bracketName[], string finalName, int noDiv);
  ~Player_Manager();
  void setNumDiv(int noDiv);
  void setDivisionName(int div, string name);
  bool addTeam(int div, string name, int ID, string conf, int seed, int wins, 
	       int losses);  // order they are added is order of seed
  void teamsLoaded();
  bool newPlayer(string playerName, int AIType);
  void deletePlayer(int index);
  void selectTeam(int div, int seed);
  void selectPlayer(int index);
  bool makePick(int div, int seed, int round, bool selected);
  void setGame();
  void setScoringMode(int mode);
  int getScoringMode();
  void setNegScoreMode(int mode);
  int getNegScoreMode();
  int getNumDiv();
  int getNumTeams(int index);
  string getDivName(int index);
  bool teamWon(int div, int seed, int score1, int score2, bool selected);
  void selectTeamInBracket(int div, int seed, int round);
  void selectOpponentInBracket(int div, int seed, int round);
  void selectTeamInBByLoc(int div, int pos, int round);
  bool getMark(int div, int seed, int round);
  bool getMarkByLoc(int div, int pos, int round);
  void selectTeamInMaster(int div, int seed, int round);
  void selectOpponentInMaster(int div, int seed, int round);
  void selectTeamInMByLoc(int div, int pos, int round);
  int getCurrentRound();
  bool getFinalStatus();
  int getMaxRounds();  // this is by division, not total rounds
  int getFinalRounds();
  int getTeamScore(int div, int seed, int round);
  int getOpponentScore(int div, int seed, int round);
  int getTeamScoreByLoc(int div, int pos, int round);
  string getBracketName();
  bool getTeamPicked(int div, int seed, int round);
  bool getManPicked(int div, int seed, int round);
  int getBracketAI();
  int getCorrectInRound(int round);
  int getCorrectFinalRound(int round);
  int getPlayerScore();
  int getNumPlayers();
  string getTeamName();
  int getTeamID();
  int getTeamSeed();
  string getTeamConf();
  int getTeamWins();
  int getTeamLosses();
  int getTeamTournWins();
  bool getTeamNullStatus(); // true if no team can exist in the selected spot
  bool getTeamBlank();
  bool getTeamTournStatus();
  bool getPickMode();
  bool getGameMode();
  bool getGameComplete();
  void sortBrackets();
};
#endif
