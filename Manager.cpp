#include "Manager.h"

//#define DEBUG
#ifdef DEBUG
#include<iostream>
using namespace std;
#endif

//public

Player_Manager::Player_Manager()
{
  numPlayers = 0;
  numDiv = 0;
  scoringMode = 0;
  countNegRound = 0;
  teamsIn = false;
  gameMode = false;
  gameDone = false;

  for(int i = 0; i < DIV; i++)
  {
    numTeams[i] = 0;
    divName[i] = "";
  }
  finalName = "";
}

Player_Manager::Player_Manager(string bracketName[], string finals, 
			       int noDiv)
{
  numPlayers = 0;
  numDiv = noDiv;
  scoringMode = 0;
  countNegRound = 0;
  teamsIn = false;
  gameMode = false;
  gameDone = false;
  
  for(int i = 0; i < numDiv; i++)
  {
    numTeams[i] = 0;
    divName[i] = bracketName[i];
  }
  finalName = finals;

  result = new Master(numDiv);
}

Player_Manager::~Player_Manager()
{
  result ->~Master();

  for(int f = 0; f < numPlayers; f++)
  {
    players[f]->bracket->~Player();
    delete players[f];
  }

  for(int i = 0; i < numDiv; i++)
  {
    for(int j = 0; j < numTeams[i];j++)
    {
      delete Total[i][j];
    }
  }
}

void Player_Manager::setNumDiv(int noDiv)
{
  if(noDiv > 0 && noDiv <= DIV)
  {
    if(numDiv <= 0)
    {
      numDiv = noDiv;

      result = new Master(numDiv);
    }
  }
}

void Player_Manager::setDivisionName(int div, string name)
{
  if(numDiv > 0)
  {
    if(div >= 0 && div < numDiv)
    {
      divName[div] = name;
    }
    else if(div == FINALS)
    {
      finalName = name;
    }
  }
}

bool Player_Manager::addTeam(int div, string name, int ID, string conf, 
			     int seed, int wins, int losses)
{
  bool complete = false;
  if(numDiv > 0)
  {
    if(!teamsIn && (div > -1) && (div < numDiv))
    {
      Team *newTeam = new Team(name, ID, conf, seed, wins, losses);
    
      complete = result ->newTeam(newTeam, div);

      if(complete)
      {
        Total[div][numTeams[div]] = newTeam;
        numTeams[div]++;
      }
    }
  }

  return complete;
}

void Player_Manager::teamsLoaded()
{
  result->teamsIn();
  teamsIn = true;
}

bool Player_Manager::newPlayer(string playerName, int AIType)
{
  bool complete = false;

  if(teamsIn && !gameMode)
  {
    players[numPlayers] = new competitor;
    players[numPlayers] -> bracket = new Player(numDiv, result, AIType, 
						playerName);
    selectedPlayer = players[numPlayers];
    for(int i = 0; i < numDiv; i++)
    {
      for(int j = 0; j < numTeams[i]; j++)
      {
        selectedPlayer->bracket ->newTeam(Total[i][j], i);
      }
    }
  
    selectedPlayer->bracket->teamsIn();
    numPlayers++;
    complete = true;
  }
  return complete;
}

void Player_Manager::deletePlayer(int index)
{
  if(!gameMode)
  {
    if((index < numPlayers) && (index > -1))
    {
      players[index] -> bracket -> ~Player();
      numPlayers--;
      players[index] = players[numPlayers];
      players[numPlayers] = NULL;
      selectedPlayer = NULL;
    }
  }
}

void Player_Manager::selectTeam(int div, int seed)
{
  if(div > -1 && div < numDiv)
  {
    if(seed > -1 && seed < numTeams[div])
    {
      selectedTeam = Total[div][seed];
    }
    else
    {
      selectedTeam = NULL;
    }
  }
  else
  {
    selectedTeam = NULL;
  }
}

void Player_Manager::selectPlayer(int index)
{
  if((index < numPlayers) && (index > -1))
  {
    selectedPlayer = players[index];
  }
  else
  {
    selectedPlayer = NULL;
  }
}

bool Player_Manager::makePick(int div, int seed, int round, bool selected)
{
  bool complete = false;
  if(!gameMode)
  {
    if(selectedPlayer)
    {
        complete = selectedPlayer -> bracket -> makePick(div, seed, round,
							 selected);
    }
  }
  return complete;
}

void Player_Manager::setGame()
{
  gameMode = true;
}

void Player_Manager::setScoringMode(int mode)
{
  scoringMode = mode;
  updateScore();
}

int Player_Manager::getScoringMode()
{
  return scoringMode;
}

void Player_Manager::setNegScoreMode(int mode)
{
  countNegRound = mode;
  updateScore();
}

int Player_Manager::getNegScoreMode()
{
  return countNegRound;
}

int Player_Manager::getNumDiv()
{
  return numDiv;
}

int Player_Manager::getNumTeams(int index)
{
  return result->getNoTeams(index);
}

string Player_Manager::getDivName(int index)
{
  string name = "";
  if(index == -1)
  {
    name = finalName;
  }
  else if(index > -1 && index < numDiv)
  {
    name = divName[index];
  }

  return name;
}

bool Player_Manager::teamWon(int div, int seed, int score1, int score2, 
			     bool selected)
{
  bool complete = false;
  if(gameMode && !gameDone)
  {
    #ifdef DEBUG
    cerr << "Met Requirements.\n";
    #endif

    int round = result -> getCurrentRound() - 1;
    bool preFinalStatus = result->getFinalStatus();
    complete = result -> teamWon(div, seed, score1, score2, selected);

    #ifdef DEBUG
    cerr << "Team advanced.\n";
    #endif

    if(complete)
    {
      for(int i = 0; i < numPlayers; i++)
      {
	players[i] -> bracket -> checkTeam(div, seed, round);
      }
      
      if(!preFinalStatus)
      {
	if(result->getFinalStatus())
	{
	  for(int i = 0; i < numPlayers; i++)
	  {
	    players[i]->bracket->checkFinals();
	  }
	}
      }

      #ifdef DEBUG
      cerr << "Players Checked.\n";
      #endif

      updateScore();

      #ifdef DEBUG
      cerr << "Score Updated.\n";
      #endif

      if(!(result->getDivChamp(-1)->returnBlank()))
	{
	  gameComplete();
	}
    }
  }
  #ifdef DEBUG
  cerr << "Done.\n";
  #endif

  return complete;
}

void Player_Manager::selectTeamInBracket(int div, int seed, int round)
{
  if(selectedPlayer)
  {
    selectedTeam = selectedPlayer -> bracket -> getTeam(div, seed, round);
  }
}

void Player_Manager::selectOpponentInBracket(int div, int seed, int round)
{
  if(selectedPlayer)
  {
    selectedTeam = selectedPlayer -> bracket -> getOpponent(div, seed, round);
  }
}

void Player_Manager::selectTeamInBByLoc(int div, int pos, int round)
{
  if(selectedPlayer)
  {
    selectedTeam = selectedPlayer -> bracket ->getTeamByLoc(div, pos, round);
  }
}

bool Player_Manager::getMark(int div, int seed, int round)
{
  bool mark = false;
  if(selectedPlayer)
  {
    mark = selectedPlayer -> bracket -> getMark(div, seed, round);
  }
  return mark;
}

bool Player_Manager::getMarkByLoc(int div, int pos, int round)
{
  bool mark = false;
  if(selectedPlayer)
  {
    mark = selectedPlayer -> bracket -> getMarkByLoc(div, pos, round);
  }
  return mark;
}

void Player_Manager::selectTeamInMaster(int div, int seed, int round)
{
  selectedTeam = result -> getTeam(div, seed, round);
}

void Player_Manager::selectOpponentInMaster(int div, int seed, int round)
{
  selectedTeam = result -> getOpponent(div, seed, round);
}

void Player_Manager::selectTeamInMByLoc(int div, int pos, int round)
{
  selectedTeam = result -> getTeamByLoc(div, pos, round);
}

int Player_Manager::getCurrentRound()
{
  return result->getCurrentRound();
}

bool Player_Manager::getFinalStatus()
{
  return result->getFinalStatus();
}

int Player_Manager::getMaxRounds()
{
  return result->getMaxRounds();
}

int Player_Manager::getFinalRounds()
{
  return result->getFinalRounds();
}

int Player_Manager::getTeamScore(int div, int seed, int round)
{
  int  score = result -> getScore(div, seed, round);
  return score;
}

int Player_Manager::getOpponentScore(int div, int seed, int round)
{
  int score = result -> getOpScore(div, seed, round);
  return score;
}

int Player_Manager::getTeamScoreByLoc(int div, int pos, int round)
{
  int score = result -> getScoreByLoc(div, pos, round);
  return score;
}

string Player_Manager::getBracketName()
{
  string name = "\0";
  if(selectedPlayer)
  {
    name = selectedPlayer -> bracket -> getBrName();
  }
  return name;
}

bool Player_Manager::getTeamPicked(int div, int seed, int round)
{
  bool match = false;
  if(selectedPlayer)
  {
    if(div >= -1 && div < numDiv)
    {
      if(seed >= 0 && seed < getNumTeams(div))
      {
	int crRound;
	if(div != -1)
	{
	  crRound = getMaxRounds();
	}
	else
	{
	  crRound = getFinalRounds();
	}
	if(round > 0 && round <= crRound)
	{
          Team *select;
          select = selectedPlayer->bracket->getTeam(div,seed,round);
          Team *winner;
          winner = selectedPlayer->bracket->getTeam(div,seed,round-1);

          if(select == winner)
          {
            match = true;
          }
	}
      }
    }
  }
  return match;
}

bool Player_Manager::getManPicked(int div, int seed, int round)
{
  bool match = false;
  if(div >= -1 && div < numDiv)
  {
    if(seed >= 0 && seed < getNumTeams(div))
    {
      int crRound;
      if(div != -1)
      {
	crRound = getMaxRounds();
      }
      else
      {
	crRound = getFinalRounds();
      }

      if(round > 0 && round <= crRound)
      {
        Team *select;
 	select = result->getTeam(div,seed,round);
        Team *winner;
        winner = result->getTeam(div,seed,round-1);
  
        if(select == winner)
        {
          match = true;
        }
      }
    }
  }
  return match;

}

int Player_Manager::getBracketAI()
{
  int AIType = -1;
  if(selectedPlayer)
  {
    AIType = selectedPlayer-> bracket -> getAIType();
  }
  return AIType;
}

int Player_Manager::getCorrectInRound(int round)
{
  int score = -1;
  if(selectedPlayer)
  {
    score = selectedPlayer -> bracket -> getPlScore(round);
  }
  return score;
}

int Player_Manager::getCorrectFinalRound(int round)
{
  int score = -1;
  if(selectedPlayer)
  {
    score = selectedPlayer->bracket->getFinalBrScore(round);
  }
  return score;
}

int Player_Manager::getPlayerScore()
{
  int score = -1;
  if(selectedPlayer)
  {
    score = selectedPlayer -> curScore;
  }
  return score;
}

int Player_Manager::getNumPlayers()
{
  return numPlayers;
}

string Player_Manager::getTeamName()
{
  string name = "\0";
  if(selectedTeam)
  {
    name = selectedTeam->returnName();
  }
  return name;
}

int Player_Manager::getTeamID()
{
  int id = -1;
  if(selectedTeam)
  {
    id = selectedTeam->returnID();
  }
  return id;
}

int Player_Manager::getTeamSeed()
{
  int seed = -1;
  if(selectedTeam)
  {
    seed = selectedTeam->returnSeed();
  }
  return seed;
}

string Player_Manager::getTeamConf()
{
  string conf = "\0";
  if(selectedTeam)
    {
      conf = selectedTeam->returnConference();
    }
  return conf;
}

int Player_Manager::getTeamWins()
{
  int wins = -1;
  if(selectedTeam)
    {
      wins = selectedTeam->returnWins();
    }
  return wins;
}

int Player_Manager::getTeamLosses()
{
  int losses = -1;
  if(selectedTeam)
  {
    losses = selectedTeam->returnLosses();
  }
  return losses;
}

int Player_Manager::getTeamTournWins()
{
  int wins = -1;
  if(selectedTeam)
  {
    wins = selectedTeam->returnWinCount();
  }
  return wins;
}

bool Player_Manager::getTeamNullStatus()
{
  bool nullStatus = true;
  if(selectedTeam)
  {
    nullStatus = false;
  }
  return nullStatus;
}

bool Player_Manager::getTeamBlank()
{
  bool blank = true;
  if(selectedTeam)
  {
    blank = selectedTeam->returnBlank();
  }
  return blank;
}

bool Player_Manager::getTeamTournStatus()
{
  bool gone = false;
  if(selectedTeam)
  {
    gone = selectedTeam->returnEliminated();
  }
  return gone;

}

bool Player_Manager::getPickMode()
{
  return teamsIn;
}

bool Player_Manager::getGameMode()
{
  return gameMode;
}

bool Player_Manager::getGameComplete()
{
  return gameDone;
}

//Private

void Player_Manager::updateScore()
{
  int round1, round2;
  if(countNegRound >0 && countNegRound < 3)
  {
    round1 = result -> getMaxRounds()-1;
    round2 = result -> getMinRounds()-1;
  }
  else
  {
    round1 = result -> getMinRounds()-1;
  }
  
  for(int i = 0; i < numPlayers; i++)
  {
    int stRound = round1;
    players[i] ->curScore = 0;
    if(countNegRound == 1)
    {
      for(int j = round1; j > round2; j--)
      {
	players[i] -> curScore += players[i] -> bracket ->getPlScore(j);
      }
      stRound = round2;
    }

    int multiplier = 1;
    for(int k = stRound; k >= 0; k--)
    {
      int tempScore = players[i] -> bracket -> getPlScore(k);
      tempScore *= multiplier; 
      
      players[i] -> curScore += tempScore;

      if(scoringMode == 1)
      {
	multiplier++;
      }
      else if(scoringMode == 2)
      {
	multiplier *= 2;
      }
    }
    for(int k = getFinalRounds()-1; k >= 0; k--)
    {
      int tempScore = players[i] -> bracket -> getFinalBrScore(k);
      tempScore *= multiplier; 
      
      players[i] -> curScore += tempScore;

      if(scoringMode == 1)
      {
	multiplier++;
      }
      else if(scoringMode == 2)
      {
	multiplier *= 2;
      }
    }
  }
}

void Player_Manager::sortBrackets()  // public
{
  competitor *temp;

  for(int i = 1; i < numPlayers; i++)
  {
    bool notDone = true;
    int j = i;
    while(notDone)
    {
      if((players[j] -> curScore) < (players[j-1] -> curScore))
      {
	notDone = false;
      }
      else
      {
	temp = players[j-1];
	players[j-1] = players[j];
	players[j] = temp;
      }
      j--;
      if(j == 0)
      {
	notDone = false;
      }
    }
  }
}

void Player_Manager::gameComplete()
{
  gameDone = true;
}
