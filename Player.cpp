#include "Player.h"

Player::Player(int noDivisions, FullBracket *theMaster, int AI, string name)
  : FullBracket::FullBracket(noDivisions)
{
  master = theMaster;
  finalRound = 0;
  AIType = AI;
  BrName = name;
  for(int i = 0; i < MAXROUND; i++)
  {
    score[i] = 0;
  }
  for(int i = 0; i < DIV; i++)
  {
    finalScore[i] = 0;
  }
}

#ifndef NO_BRACKET_NAME
Player::Player(int noDivisions, string divName[], string finalName,
	       FullBracket *theMaster, int AI, string name)
  : FullBracket::FullBracket(noDivisions, divName, finalName)
{
  master = theMaster;
  finalRound = 0;
  AIType = AI;
  BrName = name;
  for(int i = 0; i < MAXROUND; i++)
  {
    score[i] = 0;
  }
  for(int i = 0; i < DIV; i++)
  {
    finalScore[i] = 0;
  }
}
#endif

Player::~Player()
{
  master = NULL;
}

bool Player::newTeam(Team *insTeam, int div)
{
  return addTeam(insTeam, div);
}

bool Player::makePick(int div, int seed, int round, bool selected)
{
  bool in = advanceTeam(div, seed, round, 0, 0, selected);
  if(in)
  {
    if(round == 1 && div != -1)
    {
      bool complete = true;
      for(int i = 0; i < getNoDiv(); i++)
      {
        if(getDivChamp(i)->returnBlank())
        {
          complete = false;
        }
      }

      if(complete)
      {
        createFinals();
        finalRound = getFinalRounds();
      }
    }    
  }

  return in;
}

void Player::teamsIn()
{
  teamsEntered();
}

void Player::checkTeam(int div, int seed, int round)
{
  if(master->getTeam(div,seed,round+1))
  {
    Team *check = master->getTeam(div, seed, round);
    if(check)
    {
      if(!check->returnBlank())
      {
        if(check == getTeam(div, seed, round))
        {
	  if(!getMark(div, seed, round))
	  {
            markSpot(div, seed, round);
            if(div != -1)
	    {
	      score[round]++;
	    }
	    else
	    {
	      finalScore[round]++;
	    }
	  }
        }
      }
    }
  }  
}

void Player::checkFinals()
{
  if(master->getFinalStatus())
  {
    for(int i = 0; i < getNoDiv(); i++)
    {
      if(getTeam(FINALS, i, getFinalRounds()) == 
	 master->getTeam(FINALS, i, getFinalRounds()))
      {
	markSpot(FINALS, i, getFinalRounds());
      }
    }
  }
}

int Player::getPlScore(int round)
{
  if ((round > -1) && (round < MAXROUND))
  {
    return score[round];
  }
  else
  {
    return 0;
  }
}

int Player::getFinalBrScore(int round)
{
  if((round > -1) && (round < getFinalRounds()))
  {
    return finalScore[round];
  }
  else
  {
    return 0;
  }
}

int Player::getAIType()
{
  return AIType;
}

string Player::getBrName()
{
  return BrName;
}
