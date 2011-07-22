
#define DIVTEST 4
#define TEAMTEST 10

#include "stringconv.h"
#include "Team.h"

// anything that includes this file MUST include Team.h
class TeamData
{
 public:
  Team *teamTest[DIVTEST][TEAMTEST];
  Team *blankTeam;

  TeamData();
};
