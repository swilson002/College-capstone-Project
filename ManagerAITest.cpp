#include "ManagerAI.h"

#include "stringconv.h"
#include<iostream>
using namespace std;

//#define BREAK
//#define DISPLAY
//#define DISPLAYMATRIX

#define TESTCASES 10

bool testSimilarFunctions(AI_Manager *game)
{
  bool pass = true;

  for(int i = 0; i < DIV; i++)
  {
    for(int j = 0; j < TESTCASES; j++)
    {
      game->selectTeam(i,j);

      int id = game->getTeamID();

      // 0 argument functions

      if(game->getAITeamMaxSize() != game->getAITeamMaxSize(id))
      {
	cerr << "Team MaxSize Error.\n";
	pass = false;
      }

      if(game->getAITeamTotalWins() != game->getAITeamTotalWins(id))
      {
	cerr << "Team Total Wins Error.\n";
	pass = false;
      }

      if(game->getAITeamTotalGames() != game->getAITeamTotalGames(id))
      {
	cerr << "Team Total Games Error.\n";
	pass = false;
      }

      if(game->getAITeamVisits() != game->getAITeamVisits(id))
      {
	cerr << "Team Visits Error.\n";
	pass = false;
      }

      if(game->getAITeamAverageWins() != game->getAITeamAverageWins(id))
      {
	cerr << "Team Average Wins Error.\n";
	pass = false;
      }

      // 1 argument

      for(int k = 0; k < MAXIMUMROUND; k++)
      {
	if(game->getAITeamRoundVisits(k) != game->getAITeamRoundVisits(id, k))
	{
	  cerr << "Team Round Visits Error.\n";
	  pass = false;
	}
      }

      // 2 argumants

      if(pass)
      {
	int size = game->getAITeamMaxSize(id);

	for(int k = 0; k < size; k++)
	{
	  for(int l = 0; l < size; l++)
	  {
	    if(game->getAITeamWins(k,l) != game->getAITeamWins(id,k,l))
	    {
	      cerr << "Team Wins Error.\n";
	      pass = false;
	    }

	    if(game->getAITeamGames(k,l) != game->getAITeamGames(id,k,l))
	    {
	      cerr << "Team Games Error.\n";
	      pass = false;
	    }
	  }
	}
      }
      
    }
  }
  return pass;
}

void selectWinner(Player_Manager *game, int div, int seed)
{
  game->selectTeamInMaster(div, seed, game->getCurrentRound());
  int seed1 = game->getTeamSeed();
  game->selectOpponentInMaster(div,seed, game->getCurrentRound());
  int seed2 = game->getTeamSeed();
  
  int dif = seed1 - seed2;
  bool neg = false;
  if(dif < 0)
  {
    neg = true;
    dif *= -1;
  }

  double prob = 0.5;
  if(dif)
  {
    prob = ((double)dif)/((double)TESTCASES);
    if(!neg)
    {
      prob = 1 - prob;
    }
  }

  int mark = (int)(prob * 10000.0);

  game->teamWon(div,seed,0,0,((rand()%10000) < mark));  
}

void displayTeam(AI_Manager *team, int id)
{

  cout << endl;
  cout << team->getAITeamName(id) << endl;

  cout << "Visits: " << team->getAITeamVisits(id) << endl;

  for(int i = 0; i < MAXIMUMROUND; i++)
  {
    cout << team->getAITeamRoundVisits(id, i) << ' ';
  }
  cout << endl;

  cout << "Wins: " <<team->getAITeamTotalWins(id) << '/';
  cout << team->getAITeamTotalGames(id) << endl;

  cout << "Average: " << team->getAITeamAverageWins(id) << endl;

  cout << "Matrix\n";

  for(int i = 0; i < team->getAITeamMaxSize(id); i++)
  {
    cout << '\t' << i;
  }
  cout << endl;

  for(int i = 0; i < team->getAITeamMaxSize(id); i++)
  {
    cout << i;

    for(int j = 0; j < team->getAITeamMaxSize(id); j++)
    {
      cout << '\t' << team->getAITeamWins(id,i,j) << '/' 
	   << team->getAITeamGames(id,i,j);
    }
    cout << endl;
  }

  cout << endl;
}

void displayMatrix(AI_Manager *comp)
{
  if(comp)
  {
    cout << "Seed Difference array.\n";

    for(int i = 0; i < comp->getAIDifMaxSize(); i++)
    {
      cout << i << '\t';
    }
    cout << endl;

    for(int i = 0; i < comp->getAIDifMaxSize(); i++)
    {
      cout << comp->getAIDifWins(i) << '/' << comp->getAIDifGames(i) << '\t';
    }
    cout << endl;

    cout << "Seed Matrix.\n";
    for(int i = 0; i < comp->getAIMaxSize(); i++)
    {
      cout << '\t' << i;
    }
    cout << endl;

    for(int i = 0; i < comp->getAIMaxSize(); i++)
    {
      cout << i;
      for(int j = 0; j <comp->getAIMaxSize(); j++)
      {
        cout << '\t' << comp->getAIWins(i,j) << '/' << comp->getAIGames(i,j);
      }
      cout << endl;
    }

    cout << endl;

    for(int i = 0; i < comp->getAITeamTotalMaxSize(); i++)
    {
      displayTeam(comp, i);
    }
  }
}

main()
{
  AI_Manager *test = NULL;
  AICompute *comp = new AICompute();
  conv convert;

  int teams = TESTCASES;
   
  string divis[DIV];

  for(int trials = 0; trials < 7; trials++)
  {
#ifdef DISPLAYMATRIX
    displayMatrix(test);
#endif

    for(int i = 0; i < DIV; i++)
    {
      divis[i] = "Division " + convert.convToString(i);  
    }
  
    test = new AI_Manager(divis, "Finals", DIV, comp);

    test->setNegScoreMode(2);

    for(int i = 0; i < DIV; i++)
    {
      for(int j = 0; j < teams; j++)
	{
	  string num;
	  string name = "Team ";
	  num = convert.convToString(i);
	  name = name + num + ' ';
	  num = convert.convToString(j);
	  name = name + num;
                                                                               
	  int id = rand();
                                                                              

	  int numb = rand() % 100;
	  num = convert.convToString(numb);
	  string conf = num;
                                                                               
	  int seed = j;
                                                                             
	  int wins = rand() %100;
      
	  int losses = rand()%100;
 
	  test->addTeam(i, name, id, conf, j, wins, losses);
	}
    }

    test->teamsLoaded();

    int players = 6;

    for(int i = 0; i < players; i++)
    {
      test->newAI("Testing " + convert.convToString(i),i % 3 + 1); 
      cerr << "AI: " << i << " created.\n";
    }
 
    test->setGame();

    test->newAI("Error",1);
    if(players < test->getNumPlayers())
    {
      cerr << "AI added after Game was set.\n";
      exit(-1);
    }

    int rounds = test->getMaxRounds();

#ifdef BREAK
    {
      char breakPoint[255];
      cin.getline(breakPoint, 255);
    }
#endif

    int noDiv = test->getNumDiv();

    for(int i = 0; i < noDiv; i++)
    {
      selectWinner(test,i, 8);
      selectWinner(test,i, 6);
    }
    for(int i = 0; i < noDiv; i++)
    {
      selectWinner(test,i, 0);
      selectWinner(test,i, 4);
      selectWinner(test,i, 6);
      selectWinner(test,i, 2);

    }
    for(int i = 0; i < noDiv; i++)
    {
      selectWinner(test,i, 0);
      selectWinner(test,i, 1);
    }
    for(int i = 0; i < noDiv; i++)
    {
      selectWinner(test,i, 1);
    }
  

    selectWinner(test,FINALS, 0);
    selectWinner(test,FINALS, 1);


    selectWinner(test,FINALS, 0);

    cerr << "Game progressed.\n";

#ifdef DISPLAY
    int numlines = 32;
    string out[numlines];

    int TESTPLAYER = test->getNumPlayers();
    int finalRnd = test->getFinalRounds();
    for(int f = 0; f <= TESTPLAYER; f++)
    {
      if(f != TESTPLAYER)
	{
	  test->selectPlayer(f);
	  cout << "Name: " << test->getBracketName() << endl;
	  cout << "AI Type: " << test->getBracketAI() << endl;
	  cout << "Score per Round: ";
	  for(int g = rounds-1; g >= 0; g--)
	    {
	      cout << test->getCorrectInRound(g) << ' ';
	    }
	  cout << endl;
	  for(int g = finalRnd-1; g >= 0; g--)
	    {
	      cout << test->getCorrectFinalRound(g) << ' ';
	    }
	  cout << endl;
	}
      else
      {
	cout << "Master Bracket.\n";
      }
      for(int i = noDiv-1; i >= -1; i--)
	{
	  for(int j = rounds; j >= 0; j--)
	    {
	      bool free = true;
	      int l = 0;
	      for(int k = 0; k < numlines; k++)
		{
		  if(!(out[k][0]))
		    {
		      if(free)
			{
			  if(f == TESTPLAYER)
			    {
			      test->selectTeamInMByLoc(i,l, j);
			    }
			  else
			    {
			      test->selectTeamInBByLoc(i,l,j);
			    }
			  if(test->getTeamNullStatus())
			    {
			      out[k] = " ";
			    }
			  else
			    {
			      string name = test->getTeamName();
			      if(!(name[0]))
				{
				  out[k] = " ";
				}
			      else
				{
				  if(f != TESTPLAYER)
				    {
				      if(test->getMarkByLoc(i,l,j))
					{
					  name = "*" + name;
					}
				    }
				  if(j > 0)
				    {
				      if(f == TESTPLAYER)
					{
                        name = name + " " +
                          convert.convToString(test->getTeamScoreByLoc(i,l,j));
					}
				    }
				  string disp = "";
				  for(int i = 0; i < j; i++)
				    {
				      disp = disp + "\t";
				    }
				  out[k] = disp + name;
				}
			    }
			  l++;
			  free = false;
			}
		      else
			{
			  free = true;
			}
		    }
		}
	    }
   
	  for(int i = 0; i < numlines; i++)
	    {
	      cout << out[i] << endl;
	      out[i] = "";
	    }
	}
          #ifdef BREAK
          {
            char breakPoint[255];
            cin.getline(breakPoint, 255);
          }
          #endif

    }

#endif

    players = test->getNumPlayers();

    test->sortBrackets();

    cout << "Score Test. " << test->getNegScoreMode() << endl;
    cout << "1 point per game.\n";
    for(int i = 0; i < players; i++)
    {
      test->selectPlayer(i);
      cout << test->getBracketName() << ':' << test->getBracketAI()
	   << ": " << test->getPlayerScore() << endl;
    }
    test->Learn();

    if(!testSimilarFunctions(test))
    {
      cerr << "Functions don't match.\n";
    }
    test->~AI_Manager();
  }
#ifdef DISPLAYMATRIX
  test = new AI_Manager(comp);
  displayMatrix(test);
  test->~AI_Manager();
#endif
  comp->~AICompute();
}
