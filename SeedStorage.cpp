#include "SeedStorage.h"

//#define DEBUG
#ifdef DEBUG
#include <iostream>
using namespace std;
#define NOELIMINATE
#define EXCEPTION
#endif

SeedStorage::SeedStorage()
{
  maxSize = 0;
#ifdef STATIC
  for(int i = 0; i < MAXSEED; i++)
  {
    for(int j = 0; j < MAXSEED; j++)
    {
      units[i][j] = new DataUnit();
    }
  }

#endif

}

SeedStorage::~SeedStorage()
{
#ifndef STATIC
  for(int i = 0; i < maxSize; i++)
#else
  for(int i = 0; i < MAXSEED; i++)
#endif
  {
#ifndef STATIC
    for(int j = 0; j < maxSize; j++)
#else
    for(int j = 0; j < MAXSEED; j++)
#endif
    {
      delete units[i][j];
    }
  }
}

void SeedStorage::addGame(int winner, int loser)
{

  if(winner < 0 || loser < 0)
  {
    return;
  }

  int higher;
  if(winner > loser)
  {
    higher = winner;
  }
  else
  {
    higher = loser;
  }


  if(higher >= maxSize)
#ifndef STATIC
  {
    expandStorage(higher+1);
  }
#else
  {
    maxSize = higher+1;
  }
#endif

#ifndef STATIC  
  if(higher >= maxSize) // exceeds limit
#else
    if(maxSize > MAXSEED)
#endif
  {
#ifdef EXCEPTION
    cerr << "Failed expansion: " << higher << ',' << MAXSEED;
#endif
    return;
  }

  units[winner][loser]->addWin();

  units[loser][winner]->addLoss();

}

int SeedStorage::getWins(int seed1, int seed2)
{
  int wins = 0;
  if((seed1 >= 0) && (seed1 < maxSize) && (seed2 >= 0) && (seed2 < maxSize))
  {
    wins = units[seed1][seed2]->getWins();
  }
  return wins;
}

int SeedStorage::getGames(int seed1, int seed2)
{
  int games = 0;
  if((seed1 >= 0) && (seed1 < maxSize) && (seed2 >= 0) && (seed2 < maxSize))
  {
    games = units[seed1][seed2]->getGames();
  }
  return games;
}

void SeedStorage::addUnit(int seed1, int seed2, int wins, int games)
{
  if(seed1 < 0 || seed2 < 0)
  {
    return;
  }

  int higher;
  if(seed1 > seed2)
  {
    higher = seed1;
  }
  else
  {
    higher = seed2;
  }

  if(higher >= maxSize)
#ifndef STATIC
  {
    expandStorage(higher + 1);
  }
#else
  {
    maxSize = higher+1;
  }
#endif

#ifndef STATIC
  if(higher >= maxSize) // exceeds limit
#else
  if(maxSize > MAXSEED)
#endif
  {

#ifdef EXCEPTION
    cerr << "Failed expansion: " << higher << ',' << MAXSEED;
#endif
    return;
  }

#ifndef NOELIMINATE
  if(units[seed1][seed2])
  {
    delete units[seed1][seed2];
  }
#endif
    units[seed1][seed2] = new DataUnit(wins, games);
}

int SeedStorage::getMaxSize()
{
  return maxSize;
}

// Private
#ifndef STATIC
void SeedStorage::expandStorage(int newMax)
{
  if(newMax <= MAXSEED)
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
#endif
