#include "ManagerAI.h"

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
    compute = new AICompute(NULL, NULL);
  }
}

AI_Manager::AI_Manager(string divName[], string finalName, int noDivisions) :
            Player_Manager(divName, finalName, noDivisions)
{
  compute = new AICompute(NULL, NULL);
}

AI_Manager::~AI_Manager()
{

#ifndef KEEPDATA
  compute->~AICompute();
#else
  compute = NULL;
#endif

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
	    if(AIType == 1)
	    {
	      prob = compute->computeProbDif(team1, team2);
	    }
	    else if(AIType == 2)
	    {
	      prob = compute->computeProb(team1, team2);
	    }
	    else
	    {
	      prob = .5;
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

int AI_Manager::getAIGames(int seed1, int seed2)
{
  return compute->getGames(seed1, seed2);
}

int AI_Manager::getAIDifGames(int difference)
{
  return compute->getGamesDif(difference);
}

int AI_Manager::getAIWins(int seed1, int seed2)
{
  return compute->getWins(seed1, seed2);
}

int AI_Manager::getAIDifWins(int difference)
{
  return compute->getWinsDif(difference);
}

void AI_Manager::Learn()
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
		}
		else
		{
		  compute -> addGame(team2, team1);
		}
	      }
	    }
	  }
	}
      }
    }
  }

  selectedTeam = NULL;
}
