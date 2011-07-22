#include "dataUnit.h"

DataUnit::DataUnit()
{
  winRecord = 0;
  gameTotal = 0;
}

DataUnit::DataUnit(int wins, int games)
{
  winRecord = wins;
  gameTotal = games;
}

void DataUnit::addWin()
{
  winRecord++;
  gameTotal++;
}

void DataUnit::addLoss()
{
  gameTotal++;
}

int DataUnit::getWins()
{
  return winRecord;
}

int DataUnit::getGames()
{
  return gameTotal;
}
