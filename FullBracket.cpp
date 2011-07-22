#include "FullBracket.h"

#ifndef NO_BRACKET_NAME
FullBracket::FullBracket(int noDivisions, string divName[DIV], 
			 string finalName)
{
  noDiv = noDivisions;
  teamsIn = false;
  finalIn = false;
  nullTeam = new Team();

  int divTest = noDivisions;

  for (int i = 0; i < noDiv; i++)
  {
    divisions[i] = new Bracket(divName[i]);
  }

  finals = new Bracket(finalName);
}
#endif

FullBracket::FullBracket(int noDivisions)
{
  noDiv = noDivisions;
  teamsIn = false;
  finalIn = false;
  nullTeam = new Team();

  for(int i = 0; i < noDiv; i++)
  {
    divisions[i] = new Bracket();
  }

  finals = new Bracket();
}

FullBracket::~FullBracket()
{
  for(int i = 0; i < noDiv; i++)
  {
    divisions[i]->~Bracket();
  }

  finals->~Bracket();
  delete nullTeam;
}

int FullBracket::getMaxRounds()  // finds first round
{
  int max = -1;
  for(int i = 0; i < noDiv; i++)
  {
    int cur = divisions[i]->getRounds();
    if (max < cur)
    {
      max = cur;
    }
  }
  return max;
}

int FullBracket::getFinalRounds()
{
  int number = -1;
  if(finalIn)
  {
    number = finals->getRounds();
  }
  else
  {
    int teams = noDiv - 1;
    number = 0;
    while(teams > 0)
    {
      teams = teams / 2;
      number++;
    }
  }
  return number;
}

bool FullBracket::addTeam(Team *newTeam, int div)
{
  bool teamIn = false;
  if(!teamsIn)
  {
    if ((div > -1) || (div < noDiv))
    {
      teamIn = divisions[div]->addTeam(newTeam);
    }
  }
  return teamIn;
}

void FullBracket::createFinals()
{
  if ((!teamsIn) || (finalIn))
  {
    return;
  }

  Team *champs[noDiv];

  for(int i = 0; i < noDiv; i++)
  {
    champs[i] = divisions[i]->getChamp();
    if (champs[i]->returnBlank())
    {
      return;
    }
  }

  for(int j = 0; j < noDiv; j++)
  {
    finals -> addTeam(champs[j]);
  }
  finals -> bracketDone();
  finalIn = true;
}

bool FullBracket::advanceTeam(int div, int seed, int round, 
			      int score1, int score2, bool selected)
{

  bool done = false;

  if ((div == -1) && finalIn)
  {
    done = finals->advanceTeam(seed, round, score1, score2, selected);
  }
  else if ((div > -1) && (div < noDiv) && !finalIn)
  {
    done = divisions[div]->advanceTeam(seed, round, score1, score2, selected);
  }

  return done;
}

Team *FullBracket::getTeam(int div, int seed, int round)
{
  Team *curTeam = NULL;
  if (div == -1)
  {
    if(finalIn)
    { 
    curTeam = finals->getTeam(seed, round);
    }
    else
    {
      curTeam = nullTeam;
    }
  }
  else if((div > -1) && (div < noDiv))
  { 
    curTeam = divisions[div]->getTeam(seed, round);
  }

  return curTeam;
}

Team *FullBracket::getDivChamp(int div)
{

  Team *curTeam = nullTeam;
  if (div == -1)
  {
    if(finalIn)
    {
      curTeam = finals->getChamp();
    }
  }
  else if ((div >= noDiv) || (div < -1))
  {
    curTeam = NULL;
  }
  else
  {
    curTeam = divisions[div]->getChamp();
  }

  return curTeam;
}

int FullBracket::getNoDiv()
{
  return noDiv;
}

int FullBracket::getNoTeams(int div)
{
  int teams = 0;
  if (div == -1)
  {
    teams = noDiv;
  }
  else if((div > -1) && (div <= noDiv))
  {
    teams = divisions[div]->getNumTeams();
  }

  return teams;
}

void FullBracket::teamsEntered()
{
  for (int i = 0; i < noDiv; i++)
  {
    divisions[i]->bracketDone();
  }
  teamsIn = true;
}

Team *FullBracket::getOpponent(int div, int seed, int round)
{
  Team *opTeam = NULL;

  if (div == -1)
  {
    if (finalIn)
    {
      opTeam = finals->getOpponent(seed, round);
    }
  }
  else if ((div > -1) && (div < noDiv))
  {
    opTeam = divisions[div]->getOpponent(seed, round);
  }

  return opTeam;
}

int FullBracket::getScore(int div, int seed, int round)
{
  int score = 0;
  if((div == -1) && finalIn)
  {
    score = finals->getScore(seed, round);
  }
  else if ((div > -1) && (div < noDiv))
  {
    score = divisions[div]->getScore(seed, round);
  }

  return score;
}

int FullBracket::getOpScore(int div, int seed, int round)
{
  int score = 0;
  if((div == -1) && finalIn)
  {
    score = finals->getOpScore(seed, round);
  }
  else if ((div > -1) && (div < noDiv))
  {
    score = divisions[div]->getOpScore(seed, round);
  }
 
  return score;

}

Team *FullBracket::getTeamByLoc(int div, int pos, int round)
{

  Team *curTeam = NULL;
  if((div == -1) && finalIn)
  {
    curTeam = finals->getTeamByLoc(pos, round);
  }
  else if ((div > -1) && (div < noDiv))
  {
    curTeam = divisions[div]->getTeamByLoc(pos, round);
  }

  return curTeam;
}

bool FullBracket::markSpot(int div, int seed, int round)
{

  bool done = false;

  if((div == -1) && finalIn)
  {
    done = finals->markSpot(seed, round);
  }
  else if (div >=0 && div < noDiv)
  {
    done = divisions[div]->markSpot(seed, round);
  }
  return done;
}

bool FullBracket::getMark(int div, int seed, int round)
{
  bool mark = false;

  if((div == -1) && finalIn)
  {
    mark = finals->getMark(seed, round);
  }
  else if(div >-1 && div < noDiv)
  {
    mark = divisions[div]->getMark(seed, round);
  }
  return mark;
}

bool FullBracket::getMarkByLoc(int div, int pos, int round)
{
  bool mark = false;

  if((div == -1) && finalIn)
  {
    mark = finals->getMarkByLoc(pos,round);
  }
  else if((div > -1) && (div < noDiv))
  {
    mark = divisions[div]->getMarkByLoc(pos,round);
  }
  return mark;
}

int FullBracket::getScoreByLoc(int div, int pos, int round)
{
  int score = 0;

  if((div == -1) && finalIn)
  {
    score = finals->getScoreByLoc(pos,round);
  }
  else if((div > -1) && (div < noDiv))
  {
    score = divisions[div]->getScoreByLoc(pos,round);
  }
  return score;
}

int FullBracket::getMinRounds()  // finds first round with no byes
{
  int tot = -1;
    for(int i = 0; i < noDiv; i++)
    {
      int totRound = divisions[i]->getRounds();
      if(divisions[i]->getNumTeams() < divisions[i]->getTwoToRound())
      {
        totRound--;
      }

      if(tot < 0)
      {
        tot = totRound;
      }
      else if(tot > totRound)
      {
        tot = totRound;
      }
    }
  return tot;
}

bool FullBracket::getFinalStatus()
{
  return finalIn;
}

#ifndef NO_BRACKET_NAME
string FullBracket::getDivName(int div)
{
  string name;

  if(div > -1 && div < noDiv)
  {
    name = divisions[div]->getBracketName();
  }
  else if (div == -1)
  {
    name = finals->getBracketName();
  }

  return name;
}
#endif
