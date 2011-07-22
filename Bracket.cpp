#include "Bracket.h"

//#define debug


#ifdef debug
#include <iostream>

//#define teamDebug
//#define advanceDebug
#define searchDebug
#define searchDebug2
//#define breakPoint
#define TeamCheck
#endif

/* 
    This class uses an implied seeding system based on the order the teams
    were added.  It completely ignores the seed in the team class. The 
    third team added is seed 2 even if the seed of the team in the team 
    class is 8 This system allows for an easy search.  Each team is accessed
    through their bracket seed

    advanceTeam() advances a team in the tournament and sets the scores
    findTeam() finds the team to be used
*/


Bracket::Bracket()
{
  teams = 0;
  rounds = 0;
  twoToRound = 1;
  champ = NULL;

#ifndef NO_BRACKET_NAME
  bracketName = "";
#endif

  teamsIn = false;
  nullTeam = new Team();
  nullNode = new Node;
  nullNode -> curTeam = NULL;
  nullNode->score = 0;
}

#ifndef NO_BRACKET_NAME
Bracket::Bracket(string name)
{
  teams = 0;
  rounds = 0;
  twoToRound = 1;
  champ = NULL;
  bracketName = name;
  teamsIn = false;
  nullTeam = new Team();
  nullNode = new Node;
  nullNode -> curTeam = NULL;
}
#endif

Bracket::~Bracket()
{
  if(champ != NULL)
  {
    Node *selNode = NULL;
    for(int i = rounds; i > 0; i--)
    {
      for(int j = 0; j < twoToRound; j++)
      {
        selNode = getNode(j, i);
        if(selNode!= nullNode)
        {
	  selNode->curTeam = NULL;
	  delete selNode;
        }      
      }
      twoToRound = twoToRound / 2;
    }
    champ->curTeam = NULL;
    delete champ;
  }

  delete nullTeam;  // Note: this can cause a dangling reference
  delete nullNode;
}

bool Bracket::addTeam(Team *insTeam)
{
  if(teamsIn == true)
  {
    return false;
  }

  Node *newTeam = new Node;
  newTeam->curTeam = insTeam;

  #ifdef debug
  cerr << "Team created\n";
  #endif

  if (champ == NULL)
  { 
    champ = newTeam;
    teams = 1;
  }
  else
  {
    Node *extraSlot = new Node;
    if (twoToRound == teams)
    {
      twoToRound = twoToRound * 2;
      rounds++;
    }
   
    teams++;
    Node *match = findTeam(teams-1, rounds - 1);

    #ifdef teamDebug
    cerr << "Spot found, twoToRound: " << twoToRound;
    cerr << " Team: " << match->curTeam->returnName() << endl;
    #endif

    match->first = extraSlot;
    #ifdef teamDebug
    cerr << "Position moved\n";
    #endif

    extraSlot->curTeam = match->curTeam;
    #ifdef teamDebug
    cerr << "Team relocated";
    cerr << " Team: " << extraSlot->curTeam->returnName() << endl;
    #endif

    match->curTeam = nullTeam;
    #ifdef teamDebug
    cerr << "Old Spot cleared";
    cerr << " Team: " << extraSlot->curTeam->returnName() << endl;
    #endif

    match->second = newTeam;
  }

    #ifdef debug
    cerr << "Team moved to position";
    cerr << " Team: " << newTeam->curTeam->returnName() << endl;
    #endif

    #ifdef breakPoint
    #define FU 2
    char test[FU];
    cin.getline(test, FU);
    #endif

    #ifdef debug
    if(nullNode->first || nullNode->second)
    {
      cerr << "Error: Team placed at nullNode.\n";
    }
    #endif

    return true;
}

Team *Bracket::getTeam(int seed, int round)
{
  Node *selection = findTeam(seed, round);

  if(!selection)
  {
    return NULL;
  }
  else
  {
    return selection->curTeam;
  }
}

bool Bracket::advanceTeam(int seed, int round, int firstScore, int secondScore,
			  bool selected)
{
  if (teamsIn == false)
  {
    return false;
  }

  Node *winner = findTeam(seed, round);
  Node *nextSpot = findTeam(seed, round-1);

  if(winner == nullNode)
  {
    return false;
  }
  if(!(nextSpot->first) || !(nextSpot->second))
  {
    return false;
  }

  if((nextSpot->first->curTeam == nullTeam) || 
     (nextSpot->second->curTeam == nullTeam))
  {
    return false;
  }

  #ifdef advanceDebug
  cerr << "Teams found\n";
  #endif

  Node *other;
  if ((nextSpot -> first) != winner)
  {
    other = nextSpot -> first;
  }
  else
  {
    other = nextSpot -> second;
  }
  
  if(!selected)  //opponent won, so swap
  {
    Node *temp = winner;
    winner = other;
    other = temp;
  }

  winner -> score = firstScore;
  other -> score = secondScore;

  #ifdef advanceDebug
  cerr << "Second score added\n";
  #endif

  (nextSpot->curTeam) = (winner->curTeam);

  #ifdef advanceDebug
  cerr << "Team advanced\n";
  #endif

  return true;
}

Team *Bracket::getChamp()
{
  return champ->curTeam;
}


int Bracket::getScore(int seed, int round)
{
  Node *teamFind = findTeam(seed, round);
  return (teamFind->score);
}

int Bracket::getOpScore(int seed, int round)
{
  int pos = findLoc(seed, round);

  pos = pos ^ 1;
  Node *teamFind = getNode(pos, round);

  return (teamFind->score);
}

#ifndef NO_BRACKET_NAME
string Bracket::getBracketName()
{
  return bracketName;
}
#endif

int Bracket::getNumTeams()
{
  return teams;
}

int Bracket::getRounds()
{
  return rounds;
}

Bracket::Node *Bracket::findTeam(int seed, int round)
{
  Node *select = nullNode;
  
  if ((round >= 0) && (round <= rounds))
  {
    if((seed >= 0) && (seed < teams))
    {
      #ifdef TeamCheck
      cerr << "Check Seed: " << seed << endl;
      #endif
      int loc = findLoc(seed, round);
      select = getNode(loc, round);
    }
  }
  return select;
}

int Bracket::findLoc(int seed, int round)
{

  /* Finds path by taking seed, and calculating opponent's seed, then
     determining whether to go up or down, then selects the lower number seed
     and goes to next round, repeating the process */
  /*find path to selected Team */
  int shSeed = seed;
  int shRound = rounds;
  int pos = 0;
  int progRound = twoToRound;
  int direction = 1;

  while(shRound > round)  // Can't ignore eariler rounds, so it just doesn't
  {                      //  record the path for those rounds
       shRound--;
       if(shSeed > (progRound - 1 - shSeed))
         {
           shSeed = progRound - 1 - shSeed;
         }
       progRound /= 2;
  }
  while(progRound > 1)
  {
    if(shSeed > (progRound - 1 - shSeed))  // if seed of higher number
    {
      pos = pos + direction;
      shSeed = progRound - 1 - shSeed;
    }

    progRound >>= 1;
    direction <<= 1;
	
  } 

  #ifdef searchDebug2
  cerr << "Pos: " << pos << endl;
  #endif
  return pos;
}

Bracket::Node *Bracket::getNode(int pos, int round)
{  
  if((round > rounds) || (round < 0))
  {
    return nullNode;
  }

  int direction = 1 << round;
  direction >>= 1;  // direction != 1<< (round-1) to take care of round == 0

  /* Follow path and find selected team */
  Node *teamFind;
  teamFind = champ;
  for(int i = direction; i > 0; i >>= 1)
    {
      if(i & pos)
	{
	  teamFind = teamFind->second;
	}
      else
	{
	  teamFind = teamFind->first;
	}
      #ifdef searchDebug
      cerr << "Nextspot found\n";
      #endif
    }

  if(!teamFind)
  {
    teamFind = nullNode;
  }
  return teamFind;
}

bool Bracket::getMark(int team, int round)
{
  Node *newTeam = findTeam(team, round);

  return newTeam -> mark;
}

void Bracket::bracketDone()
{
  teamsIn = true;
}

Team *Bracket::getTeamByLoc(int pos, int round)
{
  Node *spot = getNode(pos, round);
  if( spot == NULL)
  {
    return NULL;
  }
  else
  {
    return spot->curTeam;
  }
}

Team *Bracket::getOpponent(int seed, int round)
{ 
  int pos = findLoc(seed, round);
  
  pos = pos ^ 1;

  return getNode(pos, round)->curTeam;
}

bool Bracket::markSpot(int seed, int round)
{
  Node *spot = findTeam(seed, round);
  if(spot != nullNode)
  {
    spot -> mark = true;
    return true;
  }
}

bool Bracket::getMarkByLoc(int pos, int round)
{
  Node *spot = getNode(pos, round);
  if( spot == NULL)
    {
      return false;
    }
  else
  {
    return spot->mark;
  }
}

int Bracket::getScoreByLoc(int pos, int round)
{
  Node *spot = getNode(pos, round);
  if( spot == NULL)
    {
      return 0;
    }
  else
  {
    return spot->score;
  }
}

int Bracket::getTwoToRound()
{
  return twoToRound;
}
