#include "Loader.h"

//#define DEBUG

#ifdef DEBUG
//#define EARLYEND
#define SAVEDTEAM
#endif

// Public
Loader::Loader()
{
  teamFile = "Teams.tm";
  setFile = "Score.set";
  bracketFile = "Players.brk";
  masterFile = "Tourn.mbr";
}

Player_Manager *Loader::loadGame()
{
  Player_Manager *gameData;
  gameData = loadTeams();

  if(gameData)
  {
    loadSettings(gameData);
    loadBrackets(gameData);
    loadMaster(gameData);
  }
  return gameData;
}

void Loader::saveGame(Player_Manager *game)
{
  ofstream teamOut(teamFile, ios::trunc);
  if(!(teamOut.is_open()))
  {
    errorStatement();
    return;
  }
  ofstream brkOut(bracketFile, ios::trunc);
  if(!(brkOut.is_open()))
  {
    errorStatement();
    return;
  }
  ofstream setOut(setFile, ios::trunc);
  if(!(setOut.is_open()))
  {
    errorStatement();
    return;
  }
  ofstream masterOut(masterFile, ios::trunc);
  if(!(masterOut.is_open()))
  {
    errorStatement();
    return;
  }

  saveMaster(game, masterOut);
  saveSettings(game, setOut);
  saveBrackets(game, brkOut);
  saveTeams(game, teamOut);
}

void Loader::clean()
{
  ofstream clear;
  clear.open(teamFile, ios::trunc);
  clear.close();
  clear.open(bracketFile, ios::trunc);
  clear.close();
  clear.open(setFile, ios::trunc);
  clear.close();
  clear.open(masterFile, ios::trunc);
  clear.close();
}

// Private
Player_Manager *Loader::loadTeams()
{
  ifstream teamIn(teamFile);

  if(!(teamIn.is_open()))
  {
    return NULL;
  }

  if(teamIn.peek() == EOF)
  {
    return NULL;
  }

  int noDiv;
  teamIn >> noDiv;
  teamIn.get();

  if(!noDiv)
  {
    return NULL;
  }

  char input[MAXINPUT];
  string brName[DIV];  // DIV is a constant defined in FullBracket.h
  // MAXINPUT is defined in globalConst.h
  string final;

  for(int i = 0; i < noDiv; i++)
  {
    teamIn.getline(input, MAXINPUT);
    brName[i] = input;
  }
  teamIn.getline(input, MAXINPUT);
  final = input;

  Player_Manager *gameData = new Player_Manager(brName, final, noDiv);

  for(int j = 0; j < noDiv; j++)
  {
    string teamName;
    int id;
    string confName;
    int seed, wins, losses;

    while(teamIn.get() == '+')
    { 
      teamIn.getline(input, MAXINPUT);
      teamName = input;
      teamIn >> id;
      teamIn.get();
      teamIn.getline(input, MAXINPUT);
      confName = input;
      teamIn >> seed;
      teamIn.get();
      teamIn >> wins;
      teamIn.get();
      teamIn >> losses;
      teamIn.get();

      gameData->addTeam(j, teamName, id, confName, seed, wins, losses);
    }
  }

  gameData->teamsLoaded();

  teamIn.close();

  return gameData;
}

void Loader::loadSettings(Player_Manager *game)
{
  ifstream setIn(setFile);

  if(setIn.is_open())
  {
    if(setIn.peek() == EOF)
    {
      return;
    }
  }

  int data;
  setIn >> data;
  setIn.get();

  game -> setScoringMode(data);

  setIn >> data;
  setIn.get();

  game -> setNegScoreMode(data);

  setIn.close();
}

void Loader::loadBrackets(Player_Manager *game)
{
  ifstream brkIn(bracketFile);

  if(!(brkIn.is_open()))
  {
    return;
  }

  char test = brkIn.get();
  if((test != '+'))
  {
    return;
  }

  do
  {
    char input[MAXINPUT];
    brkIn.getline(input, MAXINPUT);
    string name = input;
    int ai;
    brkIn >> ai;
    brkIn.get();

    game->newPlayer(name, ai);

    int noDiv = game->getNumDiv();
    int rounds;

    for(int i = noDiv -1; i >= -1; i--)
    {
      if(i != -1)
      {
	rounds = game->getMaxRounds();
      }
      else
      {
	rounds = game->getFinalRounds();
      }
      for(int j = rounds; j > 0; j--)
      {
	int numGames = 1 << (j-1);

	for(int k = 0; k < numGames; k++)
	{
	  game->selectTeamInBracket(i, k, j);
	  if(!(game->getTeamNullStatus()))
	  {
	    char pick = brkIn.get();
	    if(pick == '1')
	    {
	      game->makePick(i, k, j, true);
	    }
	    else if (pick == '0')
	    {
	      game->makePick(i, k, j, false);
	    }
	    else // should never happen
	    {
	      cerr << "Error in " << bracketFile << endl;
	      exit(-1);
	    }
	  }
	}
      }
    }
    test = brkIn.get();
  }
  while(test == '+');

  brkIn.close();
}

void Loader::loadMaster(Player_Manager *game)
{
  ifstream mastIn(masterFile);

  if(!(mastIn.is_open()))
  {
    return;
  }

  char test = mastIn.get();

  if(test != '+')
  {
    return;
  }

  game->setGame();

  test = mastIn.get();

  while(test == '+')
  {
    int div, seed, winner, wScore, lScore;

    mastIn >> div >> seed >> winner >> wScore >> lScore;
    mastIn.get();

    bool selected = false;
    if(winner)
    {
      selected = true;
    }
    game->teamWon(div, seed, wScore, lScore, selected);

    test = mastIn.get();
  }

  mastIn.close();
}

void Loader::loadAI()
{
  // will be blank until AI is implemented
}

void Loader::saveTeams(Player_Manager *game, ofstream &teamOut)
{

  int noDiv = game->getNumDiv();
  teamOut << noDiv << endl;

  string brName;
  for(int i = 0; i < noDiv; i++)
  {
    brName = game->getDivName(i);
    teamOut << brName << endl;
  }
  brName = game->getDivName(-1);
  teamOut << brName << endl;

  for(int j = 0; j < noDiv; j++)
  {
    int numTeams = game->getNumTeams(j);
    for(int k = 0; k < numTeams; k++)
    {
      game->selectTeam(j,k);
      teamOut << '+';
      string outStr = game->getTeamName();
      teamOut << outStr << endl;
      int outInt = game->getTeamID();
      teamOut << outInt << ' ';
      outStr = game->getTeamConf();
      teamOut << outStr << endl;
      outInt = game->getTeamSeed();
      teamOut << outInt << ' ';
      outInt = game->getTeamWins();
      teamOut << outInt << ' ';
      outInt = game->getTeamLosses();
      teamOut << outInt << ' ';
    }
    teamOut << '-';
  }
  
  teamOut.close();
}

void Loader::saveSettings(Player_Manager *game, ofstream &setOut)
{
  int out = game->getScoringMode();
  setOut << out << endl;
  out = game->getNegScoreMode();
  setOut << out << endl;

  setOut.close();
}

void Loader::saveBrackets(Player_Manager *game, ofstream &brkOut)
{
  int numPlayers = game->getNumPlayers();

  int numRounds = game->getMaxRounds();
  int finRounds = game->getFinalRounds();
  int noDiv = game->getNumDiv();

  for(int i = 0; i < numPlayers; i++)
  {
    brkOut << '+';
    game->selectPlayer(i);
    brkOut << game->getBracketName() << endl;
    brkOut << game->getBracketAI() << ' ';
    int round = numRounds;
    for(int j = noDiv-1; j >= -1; j--)
    {
      int curDiv;
      if(j == -1)
      {
	round = finRounds;
      }
      else 
      {
	round = numRounds;
      }
      for(int k = round; k > 0; k--)
      {
	int round2 = 1 << (k-1);

	for(int l = 0; l < round2; l++)
	{
	  #ifdef DEBUG
	  cerr << "Pick to save. " << j << ',' << l << ',' << k << endl;
	  #endif

	  #ifdef EARLYEND
	  if(j == 1 && l == 0 && k == 4)
	  {
	    brkOut.close();
	    exit(0);
	  }
	  #endif

	  game->selectTeamInBracket(j, l, k);
	  #ifdef DEBUG
	  cerr << "Team Selected.\n";
	  #endif
	  if(!(game->getTeamNullStatus()))
	  {
	    #ifdef DEBUG
	    cerr << "Team not Null.\n";
	    #endif
	    if(game->getTeamPicked(j, l, k))
	    {
	      brkOut << '1';
	    }
	    else
	    {
	      brkOut << '0';
	    }
	  
	  #ifdef DEBUG
	  cerr << "Pick Saved.\n";
	  #endif
	  }
        }
      }
    }
  }

  brkOut << '-';
  brkOut.close();
}

void Loader::saveMaster(Player_Manager *game, ofstream &mastOut)
{
  if(game->getGameMode())
  {
    mastOut << '+';

    int noDiv = game->getNumDiv();
    int numRnd = game->getMaxRounds();
    int finRound = game->getFinalRounds();
    int endRnd = game->getCurrentRound();
    bool inFinal = game->getFinalStatus();

    int end;
    if(inFinal)
    {
      end = 0;
    }
    else
    {
      end = endRnd-1;
    }

    for(int j = numRnd; j > end; j--)
    {
      int numPos = 1 << (j-1);
      for(int i = 0; i < noDiv; i++)
      {
        for(int k = 0; k < numPos; k++)
        {
	  game->selectTeamInMaster(i,k,j);
	  if(!(game->getTeamNullStatus()))
	  {
            game->selectTeamInMaster(i, k, j-1);
            if(!(game->getTeamBlank()))
            {
              mastOut << '+' << i << ' ' << k << ' ';
              if(game->getManPicked(i, k, j))
              {
                mastOut << '1' << ' ' << game->getTeamScore(i, k, j)
		        << ' ' << game->getOpponentScore(i,k,j); 
	      }
	      else
	      {
	        mastOut << '0' << ' ' << game->getOpponentScore(i, k, j)
                        << ' ' << game->getTeamScore(i,k,j);
	      }
	      mastOut << ' ';
	    }
	  }
        }
      }
    }
    if(inFinal)
    {
      for(int j = finRound; j > endRnd-1; j--)
      {
	int numPos;
	if(j > 0)
	{
          numPos = 1 << (j-1);
	}
	else
	{
	  numPos = 0;
	}
        for(int k = 0; k < numPos; k++)
        {
	  int i = -1;
	  game->selectTeamInMaster(i,k,j);
	  if(!(game->getTeamNullStatus()))
	  {
            game->selectTeamInMaster(i, k, j-1);
            if(!(game->getTeamBlank()))
            {
              mastOut << '+' << i << ' ' << k << ' ';
              if(game->getManPicked(i, k, j))
              {
                mastOut << '1' << ' ' << game->getTeamScore(i, k, j)
		        << ' ' << game->getOpponentScore(i,k,j); 
	      }
	      else
	      {
	        mastOut << '0' << ' ' << game->getOpponentScore(i, k, j)
                        << ' ' << game->getTeamScore(i,k,j);
	      }
	      mastOut << ' ';
	    }
	  }
        }
      }
    
    }
  }
  
  
  mastOut << '-';
  mastOut.close();
}

void Loader::saveAI()
{
  // will be blank until AI is implemented
}

void Loader::errorStatement()
{
  cerr << "Error: save failed.\n";
}
