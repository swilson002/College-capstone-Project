#include "SeedDifStorage.h"

SeedDifStorage::SeedDifStorage()
{
  maxSize = 0;
}

SeedDifStorage::~SeedDifStorage()
{
  for(int i = 0; i < maxSize; i++)
  {
    delete units[i];
  }
}

void SeedDifStorage::addGame(int winner, int loser)
{
  int dif = winner - loser;
  bool neg = false;
  if(dif < 0)
  {
    neg = true;
    dif *= -1;
  }

  if(dif >= maxSize)
  {
    expandStorage(dif+1);
  }

  if(dif >= maxSize) // excedds limit
  {
    return;
  }

  if(!neg)
  {
    units[dif]->addWin();
  }
  else
  {
    units[dif]->addLoss();
  }
}

int SeedDifStorage::getWins(int difference)
{
  int wins = 0;
  if((difference < maxSize) && (difference > (-1*maxSize)))
  {
    bool neg = false;
    if(difference < 0)
    {
      neg = true;
      difference *= -1;
    }

    wins = units[difference]->getWins();
    if(neg)
    {
      wins = units[difference]->getGames() - wins;
    }
  }
  return wins;
}

int SeedDifStorage::getGames(int difference)
{
  int games = 0;
  if((difference < maxSize) && (difference > (-1 * maxSize)))
  {
    if(difference < 0)
    {
      difference *= -1;
    }

    games = units[difference]->getGames();
  }
  return games;
}

void SeedDifStorage::addUnit(int difference, int wins, int games)
{
  if(difference >= maxSize)
  {
    expandStorage(difference+1);
  }

  if(difference >= maxSize) // exceeds Limit
  {
    return;
  }

  if(units[difference])
  {
    delete units[difference];
  }

  units[difference] = new DataUnit(wins, games);
}

int SeedDifStorage::getMaxSize()
{
  return maxSize;
}

//Private

void SeedDifStorage::expandStorage(int newMax)
{
  if(newMax <= MAXDIF)
  {
    for(int i = maxSize; i < newMax; i++)
    {
      units[i] = new DataUnit();
    }

    maxSize = newMax;
  }
}
