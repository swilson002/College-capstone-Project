#include "Master.h"

//#define DEBUG
#ifdef DEBUG
#include<iostream>
using namespace std;
#endif

Master::Master(int noDivisions) : FullBracket::FullBracket(noDivisions)
{
  gamesLeft = 0;
  currentRound = 0;
}

#ifndef NO_BRACKET_NAME
Master::Master(int noDivisions, string divName[], string finalName)
  : FullBracket::FullBracket(noDivisions, divName, finalName)
{
  gamesLeft = 0;
  currentRound = 0;
}
#endif
Master::~Master()
{
  ;
}

bool Master::newTeam(Team *newTeam, int div)
{
  return addTeam(newTeam, div);
}

bool Master::teamWon(int div, int seed, int score1, int score2, bool selected)
{
  bool complete = false;
  Team *nextSpot = getTeam(div, seed, currentRound-1);
  if (nextSpot)
  {
    if(nextSpot->returnBlank())
    {

      #ifdef DEBUG
      cerr << "Team to advance.\n";
      #endif
      complete = advanceTeam(div, seed, currentRound, score1, score2,
			      selected);

      if(complete)
      {
	Team *selTeam = getTeam(div, seed, currentRound);
	Team *opp = getOpponent(div, seed, currentRound);
       
	if(selected)
	  {
	    selTeam->win();
	    opp->eliminate();
	  }
	else
	  {
	    selTeam->eliminate();
	    opp->win();
	  }

        gamesLeft--;
        if(!gamesLeft)
        {
          nextRound();
        }
      }
    }
  }
  return complete;
}

bool Master::markSelSpot(int div, int seed, int round)
{
  return markSpot(div, seed, round);
}

void Master::teamsIn()
{
  teamsEntered();
  currentRound = getMaxRounds() + 1;
  nextRound();
}

int Master::getGamesLeft()
{
  return gamesLeft;
}

int Master::getCurrentRound()
{
  return currentRound;
}

void Master::nextRound()
{
  if(gamesLeft == 0)
  {
    currentRound--;
    if(!getFinalStatus())
    {
      if(currentRound > 0)
      {
	plimNext();
      }
      else
      {
	createFinals();
	currentRound = getFinalRounds();
	nextFinal();
      }
    }
    else
    {
      nextFinal();
    }
  }
}

void Master::plimNext()
{
  int div = getNoDiv();
  for(int i = 0; i < div; i++)
  {
    bool found = false;
    int roundSize = 1 << currentRound;
    for(int j = 0; j < roundSize; j++)
    {
      Team *select = getTeamByLoc(i,j,currentRound);
#ifdef DEBUG
      if(select->returnBlank())
      {
        cerr << "Blank in Bracket.\n";
	exit(-1);
      }
#endif
      if(select)
      {
        gamesLeft++;
      }
    }
  }
  gamesLeft /= 2;
}

void Master::nextFinal()
{
  if(getFinalStatus())
  {
    if(currentRound > 0)
    {
      int roundSize = 1 << currentRound;
      for(int i = 0; i < roundSize; i++)
      {
        Team *curSel = getTeam(-1,i,currentRound);
#ifdef DEBUG
        if(curSel->returnBlank())
        {
	  cerr << "Error: Blank in Final.\n";
	  exit(-1);
        }
#endif  
	if(curSel)
	{
          gamesLeft++;
        }
      }
    }
  }
  gamesLeft /= 2;
}
