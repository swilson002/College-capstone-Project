#include "TeamData.h"

// public

TeamData::TeamData()
{
  name = "";
  maxSize = 0;
  total = NULL;
  visits = 0;
  for(int i = 0; i < MAXIMUMROUND; i++)
  {
    roundVisits[i] = 0;
  }
}

TeamData::TeamData(string newName)
{
  name = newName;
  maxSize = 0;
  total = NULL;
  visits = 0;
  for(int i = 0; i < MAXIMUMROUND; i++)
  {
    roundVisits[i] = 0;
  }
}

TeamData::TeamData(string newName, int newVisits, 
	   int roundVisitsCount, int newRoundVisits[])
{
  name = newName;
  maxSize = 0;
  total = NULL;
  visits = newVisits;
  for(int i = 0; i < roundVisitsCount; i++)
  {
    roundVisits[i] = newRoundVisits[i];
  }
  for(int i = roundVisitsCount; i < MAXIMUMROUND; i++)
  {
    roundVisits[i] = 0;
  }
}

TeamData::~TeamData()
{
  delete total;
  
  for(int i = 0; i < maxSize; i++)
  {
    for(int j = 0; j < maxSize; j++)
    {
      delete units[i][j];
    }
  }

  if(total)
  {
    delete total;
  }
}

string TeamData::getName()
{
  return name;
}

int TeamData::getWins(int curSeed, int opSeed)
{
  int wins = 0;
  if(curSeed >= 0 && curSeed <= maxSize)
  {
    if(opSeed >= 0 && opSeed <= maxSize)
    {
      if(units[curSeed][opSeed])
      {
        wins = units[curSeed][opSeed]->getWins();
      }
    }
  }
  return wins;
}

int TeamData::getGames(int curSeed, int opSeed)
{
  int games = 0;
  if(curSeed >= 0 && curSeed <= maxSize)
  {
    if(opSeed >= 0 && opSeed <= maxSize)
    {
      if(units[curSeed][opSeed])
      {
        games = units[curSeed][opSeed]->getGames();
      }
    }
  }
  return games;
}

bool TeamData::addWin(int curSeed, int opSeed)
{
  int higher = curSeed;
  if(opSeed > curSeed)
  {
    higher = opSeed;
  }

  if(higher >= maxSize)
  {
    expandData(higher+1);
  }

  if(higher >= maxSize) // exceeded limit
  {
    return false;
  }

  units[curSeed][opSeed]->addWin();

  return true;
}

bool TeamData::addLoss(int curSeed, int opSeed)
{
  int higher = curSeed;
  if(opSeed > curSeed)
  {
    higher = opSeed;
  }

  if(higher >= maxSize)
  {
    expandData(higher+1);
  }

  if(higher >= maxSize) // exceeded limit
  {
    return false;
  }

  units[curSeed][opSeed]->addLoss();

  return true; 
}

bool TeamData::addUnit(int curSeed, int opSeed, int wins, int games)
{
  int higher = curSeed;
  if(opSeed > curSeed)
  {
    higher = opSeed;
  }

  if(higher >= maxSize)
  {
    expandData(higher+1);
  }

  if(higher >= maxSize) // exceeded limit
  {
    return false;
  }

  delete units[curSeed][opSeed];
  units[curSeed][opSeed] = new DataUnit(wins, games);

  return true;
}

int TeamData::getTotalWins()
{
  int wins = 0;
  if(total)
  {
    wins = total->getWins();
  }
  return wins;
}

int TeamData::getTotalGames()
{
  int games = 0;
  if(total)
  {
    games = total->getGames();
  }
  return games;
}

int TeamData::getMaxSize()
{
  return maxSize;
}

void TeamData::addVisit()
{
  visits++;
}

int TeamData::getVisits()
{
  return visits;
}

void TeamData::addRoundVisit(int round)
{
  if(round < MAXIMUMROUND && round >= 0)
  {
    roundVisits[round]++;
  }
}

int TeamData::getRoundVisits(int round)
{
  int vis = 0;
  if(round < MAXIMUMROUND && round >= 0)
  {
    vis = roundVisits[round];
  }
  return vis;
}

double TeamData::getAverageWins()
{
  int wins = getTotalWins();

  double average = 0;
  if(visits)
  {
    average = (double)wins/visits;
  }
  return average;
}

void TeamData::calculateTotal()
{
  if(total)
  {
    delete total;
  }

  int wins = 0;
  int games = 0;

  for(int i = 0; i < maxSize; i++)
  {
    for(int j = 0; j < maxSize; j++)
    {
      wins += units[i][j]->getWins();
      games += units[i][j]->getGames();
    }
  }
  
  total = new DataUnit(wins, games);
}

// Private
void TeamData::expandData(int newMax)
{
  if(newMax <= MAXTEAM)
  {
    for(int i = maxSize; i < newMax; i++)
    {
      for(int j = 0; j < maxSize; j++)
      {
        units[i][j] = new DataUnit();
      }
    }

    for(int i = 0; i < newMax; i++)
    {
      for(int j = maxSize; j < newMax; j++)
      {
        units[i][j] = new DataUnit();
      }
    }
    maxSize = newMax;
  }
}
