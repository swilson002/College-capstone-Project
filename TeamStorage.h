#ifndef TEAMSTORE
#define TEAMSTORE

#include <cctype>
#include <string>
using namespace std;

#include "TeamData.h"
#include "IDUnit.h"

#define TEAMTOTAL 512
#define LETTERS 27
#define MAXALIAS 128

class TeamStorage
{
 public:
  TeamStorage();
  ~TeamStorage();
  int addUnit(string newName, int newVisits, int roundVisitsCount,
	       int newRoundVisits[]);
  int addName(string newName);  // returns the id assigned to that name
  void addAlias(string newName, int id);
  TeamData *getTeam(int id);  // returns NULL if team doesn't exist
  int getID(string name);
  int getMaxSize();
  string getAlias(unsigned int index1, unsigned int index2);
  int getAliasID(unsigned int index1, unsigned int index2);
  
 private:
  TeamData *teams[TEAMTOTAL];
  IDUnit *IDHash[LETTERS][MAXALIAS];  // used to identify names with ID's
  int numTeams;
  string toCompareMode(string conv);  // converts to uppercase and removes
                                      //non alphanumeric characters
};

#endif
