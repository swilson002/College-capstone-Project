#include "AIcomp.h"

AICompute::AICompute()
{
  Seed = new SeedStorage();
  SeedDif = new SeedDifStorage();
}

AICompute::AICompute(SeedStorage *newSeed, SeedDifStorage *newSeedDif)
{
  if(newSeed)
  {
    Seed = newSeed;
  }
  else
  {
    Seed = new SeedStorage();
  }

  if(newSeedDif)
  {
    SeedDif = newSeedDif;
  }
  else
  {
    SeedDif = new SeedDifStorage();
  }
}

AICompute::~AICompute()
{
  Seed->~SeedStorage();
  SeedDif->~SeedDifStorage();
}

void AICompute::addGame(Team *winner, Team *loser)
{
  int winSeed = winner->returnSeed();
  int loseSeed = loser->returnSeed();
  if(winSeed < 0 || loseSeed < 0)
  {
    return;
  }
  else
  {
    SeedDif->addGame(winSeed, loseSeed);
    Seed->addGame(winSeed, loseSeed);
  }
}

int AICompute::getWinsDif(int difference)
{
  return SeedDif->getWins(difference);
}

int AICompute::getGamesDif(int difference)
{
  return SeedDif->getGames(difference);
}

int AICompute::getWins(int seed1, int seed2)
{
  return Seed->getWins(seed1, seed2);
}

int AICompute::getGames(int seed1, int seed2)
{
  return Seed->getGames(seed1, seed2);
}

double AICompute::computeProbDif(Team *team1, Team *team2)
{
  if(team1->returnBlank() || team2 -> returnBlank())
  {
    return 0;
  }

  int difference = team1->returnSeed() - team2->returnSeed();

  bool neg = difference < 0;

  if(neg)
  {
    difference *= -1;
  }

  double prob = .5;
  if(difference)
  {
    int games = SeedDif->getGames(difference);
    if(games != 0)
    {
      int wins = SeedDif->getWins(difference);
   
      if(neg)
      {
        wins = games - wins;
      }
      prob = (double)wins / games;
    }
    else
    {
      int teams = SeedDif->getMaxSize();
      int rounds = 0;
      for(int count = teams; count >0; count /=2)
      {
        rounds++;
      }
    
      rounds /= 2;

      int counter = 0;
      for(int check = difference - rounds; check <= difference + rounds; 
	  check++)
      {
        if(((check > 0) && (difference >= 0)) || 
	   ((check <0) && (difference < 0)))
        {
	  int games = SeedDif->getGames(difference);
	  if(games > 0)
	  {
	    int wins = SeedDif->getWins(difference);

	    prob += (double)wins/(double)games;
	    counter++;
	  }
        }
      }
    
      if(counter)
      {
        prob /= counter;
      }
      else
      {
        prob = .5;
      }
    }
  }

  return prob;
}

double AICompute::computeProb(Team *team1, Team *team2)
{
  if(team1->returnBlank() || team2 -> returnBlank())
  {
    return 0;
  }

  int seed1 = team1->returnSeed();
  int seed2 = team2->returnSeed();

  double prob = .5;
  if(seed1 != seed2)
  {
    int games = Seed->getGames(seed1, seed2);
    if(games != 0)
    {
      int wins = Seed->getWins(seed1, seed2);
   
      prob = (double)wins / games;
    }
    else
    {

      int check = 0;
      for(int i = Seed->getMaxSize(); i > 0; i /= 2)
      {
        check++;
      }

      check /= 2;

      double prob1 = calcAreaProb(seed1, seed2, check);
      double prob2 = calcAreaProb(seed2, seed1, check);

      if(prob1 >= 0)
      {
        if(prob2 >= 0)
        {
	  prob = (prob1 + (1-prob2))/2;
        }
        else
        {
	  prob = prob1;
        }
      }
      else if(prob2 >= 0)
      {
        prob = 1 - prob2;
      }
      else
      {
        prob = computeProbDif(team1, team2);
      }
    }
  }

  return prob;
}

int AICompute::getMaxSize()
{
  return Seed->getMaxSize();
}

int AICompute::getDifMaxSize()
{
  return SeedDif->getMaxSize();
}

//Private

double AICompute::calcAreaProb(int seed1, int seed2, int range)
{
  int counter = 0;

  double prob = 0;
  for(int i = seed2 - range; i <= seed2 + range; i++)
  {
    int games = Seed->getGames(seed1, i);

    if(games >0)
    {
      int wins = Seed->getWins(seed1, i);

      prob += (double)wins / games;
      counter++;
    }
  }

  if(counter != 0)
  {
    prob /= counter;
  }
  else
  {
    prob = -1;
  }

  return prob;
}
