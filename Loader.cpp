
//#define PLIMFILE

#ifdef PLIMFILE
#include "Loader_AI.h"
#else
#include "Loader.h"
#endif


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
  AIFile = "BracketData.ai";
}

AI_Manager *Loader::loadGame(AICompute *comp)
{
  AI_Manager *gameData;
  gameData = loadManager(comp);

  if(gameData)
  {
    loadSettings(gameData);
    loadBrackets(gameData);
    loadMaster(gameData);
  }
  return gameData;
}

void Loader::saveGame(AI_Manager *game)
{
  ofstream teamOut(teamFile, ios::trunc);
  if(!(teamOut.is_open()))
  {
    errorStatement();
    return;
  }

  ofstream AIOut(AIFile, ios::trunc);
  if(!(AIOut.is_open()))
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

  saveAI(game, AIOut);
  saveMaster(game, masterOut);
  saveSettings(game, setOut);
  saveBrackets(game, brkOut);
  saveTeams(game, teamOut);
}

void Loader::saveAIData(AI_Manager *game)
{

  ofstream AIOut(AIFile, ios::trunc);
  if(!(AIOut.is_open()))
  {
    errorStatement();
    return;
  }

  saveAI(game, AIOut);
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
AI_Manager *Loader::loadManager(AICompute *comp)
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

  AI_Manager *gameData = new AI_Manager(brName, final, noDiv, comp);

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

AICompute *Loader::loadAI()  // Public
{
  ifstream AIIn(AIFile);

  SeedStorage *Seed = new SeedStorage();
  
  SeedDifStorage *SeedDif = new SeedDifStorage();

  TeamStorage *newStore = new TeamStorage();

  if(AIIn.is_open())
  {
    char marker = AIIn.get();

    int i = 0;
    while(marker == '+')
    {
     
      int wins;
      int games;

      AIIn >> wins >> games;
      AIIn.get();

      SeedDif->addUnit(i, wins, games);
      i++;

      marker = AIIn.get();
    }

    marker = AIIn.get();
    
    i = 0;
    while(marker == '+')
    {
      int j = 0;
      char marker2 = AIIn.get();

      while(marker2 == '+')
      {
	int wins;
	int games;

	AIIn >> wins >> games;
	AIIn.get();

	Seed->addUnit(i,j,wins,games);

	j++;
	marker2 = AIIn.get();
      }

      i++;

      marker = AIIn.get();
    }

    marker = AIIn.get();

    while(marker == '+')
    {
      loadTeam(newStore, AIIn);

      marker = AIIn.get();
    }

    marker = AIIn.get();
    while(marker == '+')
    {
      int id;
      string name;

      AIIn >> id >> name;  // whitespace should be eliminated
      AIIn.get();

      if(newStore->getID(name) < 0)
      {
	newStore->addAlias(name, id);
      }

      marker = AIIn.get();
    }

    AIIn.close();
  }


  AICompute *comp = new AICompute(Seed, SeedDif, newStore);

  return comp;
}

void Loader::loadSettings(AI_Manager *game)
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

void Loader::loadBrackets(AI_Manager *game)
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

void Loader::loadMaster(AI_Manager *game)
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

void Loader::loadTeam(TeamStorage *curStore, ifstream &AIIn)
{
  char input[MAXINPUT];
  AIIn.getline(input, MAXINPUT);

  string name = input + '\0';

  int visits, rounds;

  AIIn >> visits >> rounds;

  int roundVisit[rounds];
  
  for(int i = 0; i < rounds; i++)
  {
    AIIn >> roundVisit[i];
  }

  AIIn.get();
  int id = curStore->addUnit(name, visits, rounds, roundVisit);

  TeamData *curTeam = curStore->getTeam(id);

  char mark = AIIn.get();

  int first = 0;
  while(mark == '+')
  {
    int second = 0;
    char mark2 = AIIn.get();

    while(mark2 == '+')
    {
      int win, game;

      AIIn >> win >> game;
      AIIn.get();

      curTeam->addUnit(first, second, win, game);

      second++;
      mark2 = AIIn.get();
    }

    first++;
    mark = AIIn.get();
  }

  curTeam->calculateTotal();
}

void Loader::saveTeams(AI_Manager *game, ofstream &teamOut)
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

void Loader::saveSettings(AI_Manager *game, ofstream &setOut)
{
  int out = game->getScoringMode();
  setOut << out << endl;
  out = game->getNegScoreMode();
  setOut << out << endl;

  setOut.close();
}

void Loader::saveBrackets(AI_Manager *game, ofstream &brkOut)
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

void Loader::saveMaster(AI_Manager *game, ofstream &mastOut)
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

void Loader::saveAI(AI_Manager *game, ofstream &AIOut)
{
  int max = game->getAIDifMaxSize();

  for(int i = 0; i < max; i++)
  {
    AIOut << "+" << game->getAIDifWins(i) << ' ';
    AIOut << game->getAIDifGames(i) << ' ';
  }

  AIOut << '-';

  max = game->getAIMaxSize();
  for(int i = 0; i < max; i++)
  {
    AIOut << '+';

    for(int j = 0; j < max; j++)
    {
      AIOut << '+';
      AIOut << game->getAIWins(i,j) << ' ';
      AIOut << game->getAIGames(i,j) << ' ';
    }
    AIOut << '-';
  }
  AIOut << '-';

  int teams = game->getAITeamTotalMaxSize();

  for(int i = 0; i < teams; i++)
  {
    AIOut << '+';

    saveAITeam(i, game, AIOut);
  }
  AIOut << '-';

  for(int i = 0; i < LETTERS; i++)
  {
    int j = 0;

    do
    {
      int id = game->getAITeamAliasID(i,j);
      if(id == -1)
      {
	break;
      }
      else
      {
	AIOut << '+';

	AIOut << id << ' ';

	string name = game->getAITeamAlias(i,j);

	AIOut << name << endl;
      }

      j++;
    }while(true);
  }
  AIOut << '-';

  AIOut.close();
}


void Loader::saveAITeam(int id, AI_Manager *game, ofstream &AIOut)
{
  AIOut << game->getAITeamName(id) << endl;

  AIOut << game->getAITeamVisits(id) << ' ';

  int rounds = MAXIMUMROUND;
  AIOut << rounds << ' ';

  for(int i = 0; i < rounds; i++)
  {
    AIOut << game->getAITeamRoundVisits(id, i) << ' ';
  }

  int maxSize = game->getAITeamMaxSize(id);

  for(int i = 0; i < maxSize; i++)
  {
    AIOut << '+';
    for(int j = 0; j < maxSize; j++)
    {
      AIOut << '+';
    
      AIOut << game->getAITeamWins(id, i, j) << ' ';
      AIOut << game->getAITeamGames(id, i, j) << ' ';
    }
    AIOut << '-';
  }
  AIOut << '-';
}

void Loader::errorStatement()
{
  cerr << "Error: save failed.\n";
}
