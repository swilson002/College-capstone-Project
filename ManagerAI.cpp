#include "ManagerAI.h"

AI_Manager::AI_Manager() : Player_Manager()
{
  compute = new AICompute();
}

AI_Manager::AI_Manager(AICompute *AI) : Player_Manager()
{
  if(AI)
  {
    compute = AI;
  }
  else
  {
    compute = new AICompute();
  }
}

AI_Manager::AI_Manager(string divName[], string finalName, int noDivisions, 
	     AICompute *AI) :
            Player_Manager(divName, finalName, noDivisions)
{
  if(AI)
  {
    compute = AI;
  }
  else
  {
    compute = new AICompute();
  }
}

AI_Manager::AI_Manager(string divName[], string finalName, int noDivisions) :
            Player_Manager(divName, finalName, noDivisions)
{
  compute = new AICompute();
}

AI_Manager::~AI_Manager()
{

#ifndef KEEPDATA
  compute->~AICompute();
#else
  compute = NULL;
#endif

}

int AI_Manager::addAITeamName(string newName)
{
  return compute->addTeamName(newName);
}

void AI_Manager::addAITeamAlias(string newName, int id)
{
  compute->addTeamAlias(newName, id);
}

int AI_Manager::getAITeamID(string name)
{
  return compute->getTeamID(name);
}

string AI_Manager::getAITeamName(int id)
{
  return compute->getTeamName(id);
}

void AI_Manager::newAI(string brName, int AIType)
{
  if(newPlayer(brName, AIType))
  {
    for(int i = getNumDiv(); i >= -1; i--)
    {
      int round;
      if(i != FINALS)
      {
	round = getMaxRounds();
      }
      else
      {
	round = getFinalRounds();
      }
    
      for(int j = round; j > 0; j--)
      {
	int games = 1 << (j-1);

	for(int k = 0; k < games; k++)
	{
	  selectTeamInBracket(i,k,j);
	  if(selectedTeam)
	  {
	    Team *team1 = selectedTeam;
	    selectOpponentInBracket(i,k,j);
	    Team *team2 = selectedTeam;

	    double prob;
	    switch(AIType)
	    {
	      case 1: prob = compute->computeProbDif(team1, team2); break;
	      case 2: prob = compute->computeProb(team1, team2); break;
	      case 3: prob = compute->computeProbTeam(team1, team2); break;
	      default: prob = .5;
	    }

	    int cutoff = (int)(prob * MARGIN +.5);

	    int decision = (int)((double)MARGIN*rand()/(RAND_MAX + 1.0));

	    if(decision < cutoff)
	    {
	      makePick(i,k,j,true);
	    }
	    else
	    {
	      makePick(i,k,j,false);
	    }

	  }
	}
      }
    }
  }

  selectedTeam = NULL;
}

int AI_Manager::getAIMaxSize()
{
  return compute->getMaxSize();
}

int AI_Manager::getAIDifMaxSize()
{
  return compute->getDifMaxSize();
}

int AI_Manager::getAITeamTotalMaxSize()
{
  return compute->getTeamTotalMaxSize();
}

int AI_Manager::getAITeamMaxSize(int id)
{
  return compute->getTeamMaxSize(id);
}

int AI_Manager::getAITeamMaxSize()
{
  return compute->getTeamMaxSize(selectedTeam);
}

int AI_Manager::getAIGames(int seed1, int seed2)
{
  return compute->getGames(seed1, seed2);
}

int AI_Manager::getAIDifGames(int difference)
{
  return compute->getGamesDif(difference);
}

int AI_Manager::getAITeamGames(int id, int seed1, int seed2)
{
  return compute->getTeamGames(id, seed1, seed2);
}

int AI_Manager::getAITeamGames(int seed1, int seed2)
{
  return compute->getTeamGames(selectedTeam, seed1, seed2);
}

int AI_Manager::getAIWins(int seed1, int seed2)
{
  return compute->getWins(seed1, seed2);
}

int AI_Manager::getAIDifWins(int difference)
{
  return compute->getWinsDif(difference);
}

int AI_Manager::getAITeamWins(int id, int seed1, int seed2)
{
  return compute->getTeamWins(id, seed1, seed2);
}

int AI_Manager::getAITeamWins(int seed1, int seed2)
{
  
  return compute->getTeamWins(selectedTeam, seed1, seed2);
}

int AI_Manager::getAITeamTotalWins(int id)
{
  return compute->getTeamTotalWins(id);
}

int AI_Manager::getAITeamTotalWins()
{
  return compute->getTeamTotalWins(selectedTeam);
}

int AI_Manager::getAITeamTotalGames(int id)
{
  return compute->getTeamTotalGames(id);
}

int AI_Manager::getAITeamTotalGames()
{
  return compute->getTeamTotalGames(selectedTeam);
}

int AI_Manager::getAITeamVisits(int id)
{
  return compute->getTeamVisits(id);
}

int AI_Manager::getAITeamVisits()
{
  return compute->getTeamVisits(selectedTeam);
}

int AI_Manager::getAITeamRoundVisits(int id, int round)
{
  return compute->getTeamRoundVisits(id, round);
}

int AI_Manager::getAITeamRoundVisits(int round)
{
  return compute->getTeamRoundVisits(selectedTeam, round);
}

string AI_Manager::getAITeamAlias(unsigned int index1, unsigned int index2)
{
  return compute->getTeamAlias(index1, index2);
}

int AI_Manager::getAITeamAliasID(unsigned int index1, unsigned int index2)
{
  return compute->getTeamAliasID(index1, index2);
}

double AI_Manager::getAITeamAverageWins(int id)
{
  return compute->getTeamAverageWins(id);
}

double AI_Manager::getAITeamAverageWins()
{
  return compute->getTeamAverageWins(selectedTeam);
}

void AI_Manager::Learn()  // UPDATE
{
  if(getGameComplete())
  {
    for(int i = getNumDiv(); i >= FINALS; i--)
    {
      int round;
      if(i != FINALS)
      {
       round = getMaxRounds();
      } 
      else
      {
       round = getFinalRounds();
      } 

      for(int j = round; j > 0; j--)
      {
        int games = 1 << (j-1);

        for(int k = 0; k < games; k++)
        { 
	  selectTeamInMaster(i,k,j);

	  if(selectedTeam)
	  {
	    Team *team1 = selectedTeam;

	    selectOpponentInMaster(i,k,j);
	    
	    if(selectedTeam)
	    {
	      Team *team2 = selectedTeam;

	      
	      selectTeamInMaster(i,k,j-1);
	      if(!selectedTeam->returnBlank())
	      {
		if(team1 == selectedTeam)
		{
		  compute -> addGame(team1, team2);

		  if(i != FINALS)
		  {
		    compute->addTeamRoundVisit(team1,getFinalRounds() + j - 1);
		  }
		  else
		  {
		    compute->addTeamRoundVisit(team1, j-1);
		  }
		}
		else
		{
		  compute -> addGame(team2, team1);

		  if(i != FINALS)
		  {
		    compute->addTeamRoundVisit(team2,getFinalRounds() + j - 1);
		  }
		  else
		  {
		    compute->addTeamRoundVisit(team2, j-1);
		  }
		}
	      }
	    }
	  }
	}
      }
    }

    addVisits();
  }
  selectedTeam = NULL;
}

//Private

void AI_Manager::addVisits()
{

  int noDiv = getNumDiv();
  for(int div = 0; div < noDiv; div++)
  {

    int noTeams = getNumTeams(div);
    for(int team = 0; team < noTeams; team++)
    {
      selectTeam(div,team);

      compute->addTeamVisit(selectedTeam);
      compute->calculateTotal(selectedTeam);
    }
  }
}
