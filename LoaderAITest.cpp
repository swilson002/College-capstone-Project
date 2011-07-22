#include "Manager.h"
#include "Loader.h"

#include "stringconv.h"
#include<iostream>
using namespace std;

//#define BREAK
//#define DETAILS
//#define TESTDATA
#define FINALSCORE
#define DISPLAY
//#define SHOWMATRIX

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

bool compareTheManagers(Player_Manager *Man1, Player_Manager *Man2)
{
  bool pass = true;
  
  //variable test
  if((Man1->getCurrentRound()) != (Man2->getCurrentRound()))
  {
    cerr << "CurrentRound Error.\n";
    cerr << "Actual Round: " << Man1->getCurrentRound() << ' '
	 << "Saved Round: " << Man2->getCurrentRound() << endl;
    pass = false;
  }
  if((Man1->getNumPlayers()) != (Man2->getNumPlayers()))
    {
    cerr << "NumPlayers Error.\n";
      pass = false;
    }
  if((Man1->getFinalStatus()) != (Man2->getFinalStatus()))
    {
    cerr << "FinalStatus Error.\n";
      pass = false;
    }
#ifdef DETAILS
  cerr << "Max Rounds: " << Man1->getMaxRounds() << ',' << Man2->getMaxRounds()
       << endl;
#endif
  if((Man1->getMaxRounds()) != (Man2->getMaxRounds()))
    {
    cerr << "MaxRound Error.\n";
      pass = false;
    }
  if((Man1->getFinalRounds()) != (Man2->getFinalRounds()))
    {
    cerr << "FinalRound Error.\n";
      pass = false;
    }
  if((Man1->getPickMode()) != (Man2->getPickMode()))
    {
    cerr << "PickMode Error.\n";
      pass = false;
    }
  if((Man1->getGameMode()) != (Man2->getGameMode()))
    {
    cerr << "GameMode Error.\n";
      pass = false;
    }
  if((Man1->getGameComplete()) != (Man2->getGameComplete()))
    {
    cerr << "GameComplete Error.\n";
      pass = false;
    }
  if((Man1->getScoringMode()) != (Man2->getScoringMode()))
    {
    cerr << "ScoringMode Error.\n";
      pass = false;
    }
  if((Man1->getNegScoreMode()) != (Man2->getNegScoreMode()))
    {
    cerr << "NegMode Error.\n";
      pass = false;
    }
  int div = Man1->getNumDiv();
  if(div != Man2->getNumDiv())
  {
    cerr << "NumDiv Error.\n";
    pass = false;
  }
  //test multiple divisions
  for(int i = 0; i < div; i++)
  {
    if(pass)
    {
      int teams = Man1->getNumTeams(i);
      if(teams != (Man2->getNumTeams(i)))
      {
	cerr << "Num Teams Error. " << i << "\n";
	pass = false;
      }
      if(((Man1->getDivName(i)).compare(Man2->getDivName(i))))
      {
	#ifdef DETAILS
	cerr << Man1->getDivName(i) << ' ' << Man2->getDivName(i) << endl;
	#endif
	cerr << "DivName Error. " << i << "\n";
	pass = false;
      }
      for(int j = 0; j < teams; j++)
      {
	Man1->selectTeam(i,j);
	Man2->selectTeam(i,j);

	if(Man1->getTeamID() != Man2->getTeamID())
	{
	  cerr << "TeamID Error. " << i << ',' << j << "\n";
	  pass = false;
	}
	if(Man1->getTeamSeed() != Man2->getTeamSeed())
	  {
	  cerr << "TeamSeed Error. " << i << ',' << j << "\n";
	    pass = false;
	  }
	if(Man1->getTeamWins() != Man2->getTeamWins())
	  {
	  cerr << "TeamWins Error. " << i << ',' << j << "\n";
	    pass = false;
	  }
	if(Man1->getTeamLosses() != Man2->getTeamLosses())
	  {
	  cerr << "TeamLosses Error. " << i << ',' << j << "\n";
	    pass = false;
	  }
	if(Man1->getTeamTournWins() != Man2->getTeamTournWins())
	  {
	  cerr << "TeamTournWins Error. " << i << ',' << j << "\n";
	    pass = false;
	  }
	if(Man1->getTeamBlank() != Man2->getTeamBlank())
	  {
	  cerr << "TeamBlank Error. " << i << ',' << j << "\n";
	    pass = false;
	  }
	if(Man1->getTeamTournStatus() != Man2->getTeamTournStatus())
	  {
	  cerr << "TeamTournStatus Error. " << i << ',' << j << "\n";
	    pass = false;
	  }
	if(((Man1->getTeamName()).compare(Man2->getTeamName())))
	  {
	  cerr << "TeamName Error. " << i << ',' << j << "\n";
	    pass = false;
	  }
        if(((Man1->getTeamConf()).compare(Man2->getTeamConf())))
          {
	  cerr << "TeamConf Error. " << i << ',' << j << "\n";
            pass = false;
          }
      }
    }
  }

  //Master Test
  if(pass)
  {
    for(int i = 0; i < div; i++)
    {
      for(int j = Man1->getMaxRounds(); j > 0; j--)
      {
	int round = 1 << j;
	for(int k = 0; k < round; k++)
	{
	  if(Man1->getManPicked(i,k,j) != Man2->getManPicked(i,k,j))
	  {
	    cerr << "MasterPicks Error. " << i << ',' << k << ',' << j << "\n";
	    pass = false;
	  }
	}
      }
    }
    for(int j = Man1->getFinalRounds(); j > 0; j--)
    {
      int round = 1 << j;
      for(int k = 0; k < round; k++)
      {
	if(Man1->getManPicked(-1,k,j) != Man2->getManPicked(-1,k,j))
	{
	  cerr << "MasterPicks Error. " << "-1" << ',' << k << ',' 
	       << j << "\n";
	  pass = false;
	}
      }
    }
  }

  // Player Test
  if(pass)
  {
    for(int z = 0; z < Man1->getNumPlayers(); z++)
    {
      Man1->selectPlayer(z);
      Man2->selectPlayer(z);
      if((Man1->getBracketName().compare(Man2->getBracketName())))
      {
	cerr << "BracketName Error.\n";
	cerr << Man1->getBracketName() << ' ' 
	     << Man2->getBracketName() << endl;
	pass = false;
      }

      if(Man1->getPlayerScore() != Man2->getPlayerScore())
      {
	cerr << "PlayerScore Error.\n";
	cerr << "Actual Score: " << Man1->getPlayerScore() << ' '
	     << "Saved Score: " << Man2->getPlayerScore() << endl;
	pass = false;
      }

      if(Man1->getBracketAI() != Man2->getBracketAI())
      {
	cerr << "Player AI error.\n";
	pass = false;
      }

      for(int i = 0; i < div; i++)
	{
	  for(int j = Man1->getMaxRounds(); j > 0; j--)
	    {
	      int round = 1 << j;
	      for(int k = 0; k < round; k++)
		{
		  if(Man1->getTeamPicked(i,k,j) != Man2->getTeamPicked(i,k,j))
		  {
		    cerr << "Picks Error. " << z << ',' << i << ',' 
			 << k << ',' << j << "\n";
		    Man1->selectTeamInBracket(i,k,j-1);
		    Man2->selectTeamInBracket(i,k,j-1);
		    cerr << "Actual team: " << Man1->getTeamName() << endl;
		    cerr << "Saved team: " << Man2->getTeamName() << endl;
		    pass = false;
		  }
		}
	    }
	}
      for(int j = Man1->getFinalRounds(); j > 0; j--)
	{
	  int round = 1 << j;
	  for(int k = 0; k < round; k++)
	    {
	    if((Man1->getTeamPicked(-1,k,j)) != (Man2->getTeamPicked(-1,k,j)))
		{
		    cerr << "Picks Error. " << z << ',' << -1 << ',' 
			 << k << ',' << j << "\n";
		  pass = false;
		}
	    }
	}

    }
  }
  
  return pass;
}

bool compareAI(AI_Manager *AI1, AI_Manager *AI2)
{
  bool pass = compareTheManagers(AI1, AI2);

  if(pass)
  {
    // Seed Difference

    if(AI1->getAIDifMaxSize() != AI2->getAIDifMaxSize())
    {
      cerr << "Dif Max Size error.\n";
      pass = false;
    }

    if(pass)
    {
      for(int i = 0; i < AI1->getAIDifMaxSize(); i++)
      {
	if(AI1->getAIDifWins(i) != AI2->getAIDifWins(i))
	{
	  cerr << "Dif Wins Error: " << i << endl;
	  pass = false;
	}

	if(AI1->getAIDifGames(i) != AI2->getAIDifGames(i))
	{
	  cerr << "Dif Games Error: " << i << endl;
	  pass = false;
	}
      }
    }

    // Seed Storage

    if(AI1->getAIMaxSize() != AI2->getAIMaxSize())
    {
      cerr << "Dif Max Size error.\n";
      pass = false;
    }

    if(pass)
    {
      for(int i = 0; i < AI1->getAIMaxSize(); i++)
      {
        for(int j = 0; j < AI1->getAIMaxSize(); j++)
        {
	  if(AI1->getAIWins(i,j) != AI2->getAIWins(i,j))
	  {
	    cerr << "Wins Error: " << i  << ',' << j << endl;
	    pass = false;
	  }

	  if(AI1->getAIGames(i,j) != AI2->getAIGames(i,j))
	  {
	    cerr << "Games Error: " << i  << ',' << j << endl;
	    pass = false;
          }
	}
      }
    }

    if(pass)  // Team check
    {
      int div = AI1->getNumDiv();
      for(int i = 0; i < div; i++)
      {
	int teams = AI2->getNumTeams(i);
	for(int j = 0; j < teams; j++)
	{
	  AI1->selectTeam(i,j);
	  AI2->selectTeam(i,j);

	  if(AI1->getAITeamID(AI1->getTeamName()) != 
	     AI2->getAITeamID(AI2->getTeamName()))
	  {
	    cerr << "AI Team ID error.\n";
	    pass = false;
	  }
	}
      }

      if(pass)
      {
        int size = AI1->getAITeamTotalMaxSize();
	if(size != AI2->getAITeamTotalMaxSize())
	{
	  cerr << "AI size error.\n";
	  pass = false;
	}
	if(pass)
	{
	  for(int i = 0; i < size; i++)
	  {

	    if(AI1->getAITeamName(i).compare(AI2->getAITeamName(i)))
	    {
	      cerr << "AI Team Name Error.\n";
	      pass = false;
	    }
	    if(AI1->getAITeamTotalWins(i) != AI2->getAITeamTotalWins(i))
	    {
	      cerr << "AI Team Wins Error.\n";
	      pass = false;
	    }

	    if(AI1->getAITeamTotalGames(i) != AI2->getAITeamTotalGames(i))
	    {
	      cerr << "AI Team Games Error.\n";
	      pass = false;
	    }

	    if(AI1->getAITeamVisits(i) != AI2->getAITeamVisits(i))
	    {
	      cerr << "AI Team Visits Error.\n";
	      pass = false;
	    }

	    for(int j = 0; j < MAXIMUMROUND; j++)
	    {
	      if(AI1->getAITeamRoundVisits(i, j) != 
		 AI2->getAITeamRoundVisits(i, j))
	      {
	        cerr << "AI Team Round Visits Error.\n";
	        pass = false;
	      }
	    }

	    int teamSize = AI1->getAITeamMaxSize(i);

	    if(teamSize != AI2->getAITeamMaxSize(i))
	    {
	      cerr << "AI Team Max Size error.\n";
	      pass = false;
	    }

	    if(pass)
	    {
	      for(int m = 0; m < teamSize; m++)
	      {
		for(int n = 0; n < teamSize; n++)
		{
		  if(AI1->getAITeamWins(i,m,n) != AI2->getAITeamWins(i,m,n))
		  {
		    cerr << "AI Team Wins Error.\n";
		    pass = false;
		  }

		  if(AI1->getAITeamGames(i,m,n) != AI2->getAITeamGames(i,m,n))
		  {
		    cerr << "AI Team Games Error.\n";
		    pass = false;
		  }
		}
	      }
	    }
	  }
        }
      }

      for(int i = 0; i < LETTERS; i++)
      {
	int k = 0;
	int id;
	do
	{
	  id = AI1->getAITeamAliasID(i,k);

	  if(id != AI2->getAITeamAliasID(i,k))
	  {
	    cerr << "Alias ID Error.\n";
	    pass = false;
	  }

	  if(id != -1)
	  {
	    if((AI1->getAITeamAlias(i,k).compare(AI2->getAITeamAlias(i,k))))
	    {
	      cerr << "Alias Name Error. " << AI1->getAITeamAlias(i,k)
		   << ", " << AI2->getAITeamAlias(i,k) << "\n";
	      pass = false;
	    }
	  }

	  k++;
	}while(id != -1);
      }
    }
  }

  return pass;

}

main()
{

  Loader Load;
  AI_Manager *test;

  AICompute *comp = new AICompute();
  conv convert;


  for(int z = 0; z < 3; z++)
  {
    int teams = 10;
   
    string divis[DIV];

#ifdef TESTDATA 
    for(int i = 0; i < DIV; i++)
    {
      divis[i] = "Division " + convert.convToString(i);
      cerr << divis[i] << endl;
    }
#endif

    test = new AI_Manager(divis, "Finals", DIV, comp);

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
                                                                               
	  int id = test->getAITeamID(name);
	  if(id < 0)
	  {
	    id = test->addAITeamName(name);
	  }                                   

	  int numb = rand() % 100;
	  num = convert.convToString(numb);
	  string conf = num;
                                                                               
	  int seed = j;
                                                                             
	  int wins = rand() %100;
      
	  int losses = rand()%100;
 
	  test->addTeam(i, name, id, conf, j, wins, losses);
	}
    }

    if(z == 0)
    {
      test->addAITeamAlias("Bob", 0);
      test->addAITeamAlias("Ni",1);
      test->addAITeamAlias("Beer", 8);
    }

    test->teamsLoaded();

    Load.saveGame(test);
    if(compareAI(test, Load.loadGame(Load.loadAI())))
    {
      cout << "Teams In Test Complete.\n\n";
    }
    else
    {
      cout << "Teams In Test Failed.\n";
      exit(-1);
    }


    int noDiv = test->getNumDiv();
#ifdef TESTDATA
    cerr << "Divisions Sent: " << DIV << " Divisions in: " << noDiv << endl;
#endif

    int players = 2;

    for(int i = 0; i < players; i++)
    {
      test->newPlayer("Testing" + convert.convToString(i), 0);
                 
      if(test->makePick(-1,0,2, true))
      {
	cerr << "Final Pick Made without finals.\n";
	exit(-1);
      }

      for(int j = 0; j < noDiv; j++)
	{
	  test->makePick(j,6,4,rand()%2);
	  test->makePick(j,7,4,rand()%2);
        
	  for(int k = 0; k < 4; k++)
	    {
	      test->makePick(j,k,3,rand()%2);
	    }
      
	  for(int k = 0; k < 2; k++)
	    {
	      test->makePick(j,k,2,rand()%2);
	    }
      
	  test->makePick(j,0,1,rand()%2);

	}
  
      for(int k = 0; k < 2; k++)
	{
	  test->makePick(-1,k,2,rand()%2);
	}
   
      test->makePick(-1,0,1,rand()%2);
 
      if(i == 1)
      {
        Load.saveGame(test);
	cerr << "Saved.\n";
        if(compareAI(test, Load.loadGame(Load.loadAI())))
        {
	  cout << "Middle of picks test complete.\n";
        }
        else
        {
          cout << "Middle of picks  Test Failed.\n";
          exit(-1);
        }
      }
    }

    test->newAI("AI 1", 1);
    test->newAI("AI 2", 2);
    test->newAI("AI 3", 3);

    test->setGame();
#ifdef TESTDATA
    for(int i = 0; i < test->getNumPlayers();i++)
    {
      test->selectPlayer(i);

      cout << test->getBracketName() << ": " << test->getPlayerScore() << endl;
    }
#endif
    Load.saveGame(test);
    if(compareAI(test, Load.loadGame(Load.loadAI())))
    {
      cout << "Game set test complete.\n";
    }
    else
    {
      cout << "Game set Test Failed.\n";
      exit(-1);
    }
#ifdef TESTDATA
    for(int i = 0; i < test->getNumPlayers();i++)
    {
      test->selectPlayer(i);
      cout << test->getBracketName() << ": " << test->getPlayerScore() << endl;
    }
#endif

    int rounds = test->getMaxRounds();

    for(int i = 0; i < noDiv; i++)
    {
#ifdef TESTDATA
      cerr << "Round: " << test->getCurrentRound() << endl;
#endif

      test->teamWon(i, 8, 10, 0, true);
      test->teamWon(i, 6, 20, 19, false);
    }

#ifdef TESTDATA
  for(int i = 0; i < test->getNumPlayers();i++)
  {
    test->selectPlayer(i);
    cout << test->getBracketName() << ": " << test->getPlayerScore() << endl;
  }
#endif

  for(int i = 0; i < noDiv; i++)
    {
#ifdef TESTDATA
      cerr << "Round: " << test->getCurrentRound() << endl;
#endif

      test->teamWon(i,0,50, 20, true);
      test->teamWon(i,4,70, 50, true);
      test->teamWon(i,6,99, 0, true);
      test->teamWon(i, 2,20, 15, false);
    }
#ifdef TESTDATA
  for(int i = 0; i < test->getNumPlayers();i++)
  {
    test->selectPlayer(i);
    cout << test->getBracketName() << ": " << test->getPlayerScore() << endl;
  }
#endif

  Load.saveGame(test);
  if(compareAI(test, Load.loadGame(Load.loadAI())))
  {
    cout << "Middle of game Test Complete.\n\n";
  }
  else
  {
    cout << "Middle of game Test Failed.\n";
    exit(-1);
  }

  for(int i = 0; i < noDiv; i++)
    {
#ifdef TESTDATA
      cerr << "Round: " << test->getCurrentRound() << endl;
#endif
      test->teamWon(i,0,43, 40, true);
      test->teamWon(i,1,20, 33, false);
    }
  for(int i = 0; i < noDiv; i++)
    {
#ifdef TESTDATA
      cerr << "Round: " << test->getCurrentRound() << endl;
#endif
      test->teamWon(i,1,99, 98, true);
    }
#ifdef TESTDATA  
  cout << "Round: " << test->getCurrentRound() << endl; 
#endif 
  test->teamWon(-1,0,20,10,true);
  Load.saveGame(test);
  if(compareAI(test, Load.loadGame(Load.loadAI())))
  {
    cout << "Middle of round Test Complete.\n\n";
  }
  else
  {
    cout << "Middle of round Test Failed.\n";
    exit(-1);
  }

  test->teamWon(-1,1,30,10,false);

#ifdef TESTDATA
  cout << "Round: " << test->getCurrentRound() << endl;
#endif
  test->teamWon(-1,0,40,39,true);

  cerr << "Game progressed.\n";

  int numlines = 32;
  string out[numlines];

#ifdef DISPLAY
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

  if(!test->getGameComplete())
  {
    cerr << "Game Not Complete.\n";
  }

  test->setNegScoreMode(2);

#ifdef FINALSCORE
  for(int i = 0; i < test->getNumPlayers();i++)
  {
    test->selectPlayer(i);
    cout << test->getBracketName() << ": " << test->getPlayerScore() << endl;
  }
#endif


  Load.saveGame(test);
  if(compareAI(test, Load.loadGame(Load.loadAI())))
  {
    cout << "different game modes Test complete.\n\n";
  }
  else
  {
    cout << "different game modes Test Failed.\n";
    exit(-1);
  }

  test->Learn();
#ifdef SHOWMATRIX
  displayMatrix(test);
#endif
  test->~AI_Manager();

  }

  comp->~AICompute();
}
