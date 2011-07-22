#include "Team.h"

Team::Team()
{
  teamName = "\0";
  seed = -1;
  wins = -1;
  losses = -1;
  eliminated = false;
  winCount = 0;
  id = -1;
  conference = "\0";
  blank = true;
}

Team::Team(string newTeam, int TeamId, string conf, int newSeed, 
	   int newWins, int newLosses)
{
  teamName = newTeam;
  seed = newSeed;
  wins = newWins;
  losses = newLosses;
  winCount = 0;
  eliminated = false;
  id = TeamId;
  conference = conf;
  blank = false;
}

string Team::returnName()
{
  return teamName;
}

int Team::returnSeed()
{
  return seed;
}

int Team::returnWins()
{
  return wins;
}

int Team::returnLosses()
{
  return losses;
}

bool Team::returnEliminated()
{
  return eliminated;
}

int Team::returnWinCount()
{
  return winCount;
}

int Team::returnID()
{
  return id;
}

void Team::win()
{
  if(!eliminated)
  {
    winCount++;
  }
}

void Team::eliminate()
{
  eliminated = true;
}

string Team::returnConference()
{
  return conference;
}

bool Team::returnBlank()
{
  return blank;
}
