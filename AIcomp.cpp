#include "AIcomp.h"

AICompute::AICompute()
{
  Seed = new SeedStorage();
  SeedDif = new SeedDifStorage();
  TeamStore = new TeamStorage();
}

AICompute::AICompute(SeedStorage *newSeed, SeedDifStorage *newSeedDif,
		     TeamStorage *newTeam)
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

  if(newTeam)
  {
    TeamStore = newTeam;
  }
  else
  {
    TeamStore = new TeamStorage();
  }
}

AICompute::~AICompute()
{
  Seed->~SeedStorage();
  SeedDif->~SeedDifStorage();
  TeamStore->~TeamStorage();
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

  int winID = winner->returnID();
  int loseID = loser->returnID();

  TeamData *Win = TeamStore->getTeam(winID);
  TeamData *Loss = TeamStore->getTeam(loseID);

  if(Win)
  {
    Win->addWin(winSeed, loseSeed);
    Loss->addLoss(loseSeed, winSeed);
  }
}

int AICompute::addTeamName(string newName)
{
  return TeamStore->addName(newName);
}

void AICompute::addTeamAlias(string newName, int id)
{
  TeamStore->addAlias(newName, id);
}

int AICompute::getTeamID(string name)
{
  return TeamStore->getID(name);
}

string AICompute::getTeamName(int id)
{
  TeamData *curTeam = TeamStore->getTeam(id);

  string name = "";
  if(curTeam)
  {
    name = curTeam->getName();
  }

  return name;
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

int AICompute::getTeamWins(int id, int seed1, int seed2)
{
  int wins = 0;
  TeamData *curTeam = TeamStore->getTeam(id);

  if(curTeam)
  {
    wins = curTeam->getWins(seed1, seed2);
  }

  return wins;
}

int AICompute::getTeamWins(Team *selTeam, int seed1, int seed2)
{
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }

  return getTeamWins(id, seed1, seed2);
}

int AICompute::getTeamGames(int id, int seed1, int seed2)
{
  int games = 0;
  TeamData *curTeam = TeamStore->getTeam(id);
  
  if(curTeam)
  {
    games = curTeam->getGames(seed1, seed2);
  }
  
  return games;
}

int AICompute::getTeamGames(Team *selTeam, int seed1, int seed2)
{
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }

  return getTeamGames(id, seed1, seed2);
}

int AICompute::getTeamTotalWins(int id)
{
  int wins = 0;
  TeamData *curTeam = TeamStore->getTeam(id);
  
  if(curTeam)
  {
    wins = curTeam->getTotalWins();
  }
  
  return wins;
}

int AICompute::getTeamTotalWins(Team *selTeam)
{
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }
  
  return getTeamTotalWins(id);
}

int AICompute::getTeamTotalGames(int id)
{
  int games = 0;
  TeamData *curTeam = TeamStore->getTeam(id);
  
  if(curTeam)
  {
    games = curTeam->getTotalGames();
  }
  
  return games;
}

int AICompute::getTeamTotalGames(Team *selTeam)
{
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }
  return getTeamTotalGames(id);
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

double AICompute::computeProbTeam(Team *team1, Team *team2)
{
  double prob1 = calcProbOfTeam(team1, team2);
  double prob2 = calcProbOfTeam(team2, team1);

  double totalProb = .5;

  if(prob1 >= 0)
  {
    if(prob2 >= 0)
    {
      totalProb = (prob1 + (1 - prob2)) / 2;
    }
    else
    {
      totalProb = prob1;
    }
  }
  else
  {
    if(prob2 >= 0)
    {
      totalProb = 1 - prob2;
    }
    else
    {
      totalProb = computeProb(team1, team2);
    }
  }

  return totalProb;
}

void AICompute::addTeamVisit(Team *selTeam)
{
  int id = selTeam->returnID();

  TeamData *curTeam = TeamStore->getTeam(id);
  if(curTeam)
  {
    curTeam->addVisit();
  }
}

void AICompute::addTeamRoundVisit(Team *selTeam, int round)
{
  
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }
  TeamData *curTeam = TeamStore->getTeam(id);

  if(curTeam)
  {
    curTeam->addRoundVisit(round);
  }
}

int AICompute::getMaxSize()
{
  return Seed->getMaxSize();
}

int AICompute::getDifMaxSize()
{
  return SeedDif->getMaxSize();
}

int AICompute::getTeamTotalMaxSize()
{
  return TeamStore->getMaxSize();
}

int AICompute::getTeamMaxSize(int id)
{
  int size = 0;
  TeamData *curTeam = TeamStore->getTeam(id);

  if(curTeam)
  {
    size = curTeam->getMaxSize();
  }

  return size;
}

int AICompute::getTeamMaxSize(Team *selTeam)
{
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }
  return getTeamMaxSize(id);
}

int AICompute::getTeamVisits(int id)
{
  TeamData *curTeam = TeamStore->getTeam(id);

  int visits = 0;
  if(curTeam)
  {
    visits = curTeam->getVisits();
  }

  return visits;
}

int AICompute::getTeamVisits(Team *selTeam)
{
  
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }
  return getTeamVisits(id);
}

int AICompute::getTeamRoundVisits(int id, int round)
{
  TeamData *curTeam = TeamStore->getTeam(id);

  int visits = 0;
  if(curTeam)
  {
    visits = curTeam->getRoundVisits(round);
  }

  return visits;
}

int AICompute::getTeamRoundVisits(Team *selTeam, int round)
{
  
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }
  return getTeamRoundVisits(id, round);
}

string AICompute::getTeamAlias(unsigned int index1, unsigned int index2)
{
  return TeamStore->getAlias(index1, index2);
}

int AICompute::getTeamAliasID(unsigned int index1, unsigned int index2)
{
  return TeamStore->getAliasID(index1, index2);
}

double AICompute::getTeamAverageWins(int id)
{
  TeamData *curTeam = TeamStore->getTeam(id);

  double avg = 0;

  if(curTeam)
  {
   avg = curTeam->getAverageWins();
  }

  return avg;
}

double AICompute::getTeamAverageWins(Team *selTeam)
{
  
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }
  return getTeamAverageWins(id);
}

void AICompute::calculateTotal(Team *selTeam)
{
  int id = -1;
  if(selTeam)
  {
    id = selTeam->returnID();
  }

  TeamData *curTeam = TeamStore->getTeam(id);

  if(curTeam)
  {
    curTeam->calculateTotal();
  }
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

double AICompute::calcProbOfTeam(Team *team1, Team *team2)
{
  int seed1 = team1->returnSeed();
  int seed2 = team2->returnSeed();
  TeamData *data1 = TeamStore->getTeam(team1->returnID());
  
  double prob = -1;

  if(data1)
  {
    int games = data1->getGames(seed1, seed2);
    if(games)
    {
      int wins = data1->getWins(seed1, seed2);
      prob = (double)wins /(double)games;
    }
    else
    {
      int maxTeams = data1->getMaxSize();

      int count = 0;
      while(maxTeams > 1)
      {
	maxTeams /= 2;
	count++;
      }

      double prob1 = calcAreaProbOfTeamOp(data1, seed1, seed2, count);
      double prob2 = calcAreaProbOfTeam(data1, seed1, seed2, count);

      prob = (prob1 + prob2) / 2;
    }
  }
  return prob;
}

double AICompute::calcAreaProbOfTeam(TeamData *team1, int seed1, int seed2, 
				     int range)
{
  int counter = 0;

  double prob = 0;
  for(int i = seed1 - range; i <= seed1 + range; i++)
  {
    int games = team1->getGames(i, seed2);

    if(games >0)
    {
      int wins = team1->getWins(i, seed2);

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

double AICompute::calcAreaProbOfTeamOp(TeamData *team1, int seed1, int seed2, 
				       int range)
{
  int counter = 0;

  double prob = 0;
  for(int i = seed2 - range; i <= seed2 + range; i++)
  {
    int games = team1->getGames(seed1, i);

    if(games >0)
    {
      int wins = team1->getWins(seed1, i);

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
