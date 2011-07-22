#include "Manager.h"

#include "stringconv.h"
#include<iostream>
using namespace std;

#define BREAK

main()
{
  Player_Manager *test;

  conv convert;

  int teams = 10;
   
  string divis[DIV];
 
  for(int i = 0; i < DIV; i++)
    {
      divis[i] = "Division " + convert.convToString(i);
      cerr << divis[i] << endl;
    }
  
  test = new Player_Manager(divis, "Finals", DIV);

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

  if(!test->getPickMode())
  {
    cerr << "Teams not secure.\n";
    exit(-1);
  }

  if(test->getGameMode())
  {
    cerr << "In Game Mode Early.\n";
    exit(-1);
  }

  if(test->getGameComplete())
  {
    cerr << "Finished Early.\n";
    exit(-1);
  }

  if(test->addTeam(0, "Test", 0, "Test", 0, 0,0))
  {
    cerr << "Teams added after set.\n";
  }

  int noDiv = test->getNumDiv();
  cerr << "Divisions Sent: " << DIV << " Divisions in: " << noDiv << endl;

  for(int i = 0; i < noDiv; i++)
  {
    cerr << "Division" << i << ": " << test->getDivName(i) << endl;
  }

  int players = 4;

  if(test->teamWon(0,9,30, 30, true))
  {
    cerr << "Team advanced early.\n";
    exit(-1);
  }

  for(int i = 0; i < players; i++)
    {
      test->newPlayer("Testing" + convert.convToString(i));
                 
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
  
      if(test->makePick(0,0,2,true))
      {
	cerr << "Pick in Division made when final was set.\n";
	exit(-1);
      }

      for(int k = 0; k < 2; k++)
	{
	  test->makePick(-1,k,2,rand()%2);
	}
   
      test->makePick(-1,0,1,rand()%2);
    }

  test->deletePlayer(1);

  test->setGame();

  if(test->newPlayer("Test"))
  {
    cerr << "Player added after set.\n";
    exit(-1);
  }

  int rounds = test->getMaxRounds();

  for(int i = 0; i < noDiv + 2; i++)
    {
      for(int j = 0; j < teams + 2; j++)
	{
	  test->selectTeamInMaster(i,j, rounds);
	  if(!test->getTeamNullStatus())
	    {
	      cout << "Call: " << i << ',' << j << ',' << rounds << endl;
	      cout << "Team: " << test->getTeamName() << endl;
	      cout << "Conference: " << test->getTeamConf() << endl;
	      cout << "Seed: " << test->getTeamSeed() << endl;
	      cout << "Record: " << test->getTeamWins() << '-' <<
		test->getTeamLosses() << endl;
	      test->selectOpponentInMaster(i,j,rounds);
	      cout << "Opp: " << test->getTeamName() << endl;
	      cout << "Seed:" << test->getTeamSeed() << endl;
	    }
	}
    }
  cout << endl;

  for(int i = 0; i < noDiv + 2; i++)
    {
      for(int j = 0; j < teams + 2; j++)
        {
          test->selectTeamInMaster(i,j, rounds-1);
          if(!test->getTeamNullStatus())
            {
              cout << "Call: " << i << ',' << j << ',' << rounds-1 << endl;
              cout << "Team: " << test->getTeamName() << endl;
              cout << "Conference: " << test->getTeamConf() << endl;
              cout << "Seed: " << test->getTeamSeed() << endl;
              cout << "Record: " << test->getTeamWins() << '-' <<
                test->getTeamLosses() << endl;
              test->selectOpponentInMaster(i,j,rounds-1);
              cout << "Opp: " << test->getTeamName() << endl;
              cout << "Seed:" << test->getTeamSeed() << endl;
            }
        }
    }

  int check = 1 << rounds;
  for(int i = 0; i < noDiv + 2; i++)
    {
      for(int j = 0; j < check; j++)
	{
	  test->selectTeamInMByLoc(i, j, rounds);
	  if(!test->getTeamNullStatus())
	  {
	    cout << "Call by Loc: " << i << ',' << j << ',' << rounds << endl;
	    cout << "Team: " << test->getTeamName() << " Seed: "
	         << test->getTeamSeed() << endl;
	  }
	}
    }

  for(int i = 0; i < noDiv + 2; i++)
    {
      for(int j = 0; j < check; j++)
      {
        test->selectTeamInMByLoc(i, j, rounds-1);
        if(!test->getTeamNullStatus())
        {
          cout << "Call by Loc: " << i << ',' << j << ',' << rounds-1 << endl;
          cout << "Team: " << test->getTeamName() << " Seed: "
               << test->getTeamSeed() << endl;
        }
      }
    }

  for(int i = 0; i < noDiv + 2; i++)
    {
      for(int j = 0; j < check; j++)
        {
          test->selectTeam(i, j);
          if(!test->getTeamNullStatus())
	    {
	      cout << "Call by Team: " << i << ',' << j << endl;
	      cout << "Team: " << test->getTeamName() << " Seed: "
		   << test->getTeamSeed() << endl;
	    }
        }
    }

  #ifdef BREAK
  {
    char breakPoint[255];
    cin.getline(breakPoint, 255);
  }
  #endif

  for(int i = 0; i < noDiv; i++)
    {
      cerr << "Round: " << test->getCurrentRound() << endl;
      test->teamWon(i, 8, 10, 0, true);
      test->teamWon(i, 6, 20, 19, false);
    }
  for(int i = 0; i < noDiv; i++)
    {
      cerr << "Round: " << test->getCurrentRound() << endl;
      test->teamWon(i,0,50, 20, true);
      test->teamWon(i,4,70, 50, true);
      test->teamWon(i,6,99, 0, true);
      test->teamWon(i, 2,20, 15, false);
    }
  for(int i = 0; i < noDiv; i++)
    {
      cerr << "Round: " << test->getCurrentRound() << endl;
      test->teamWon(i,0,43, 40, true);
      test->teamWon(i,1,20, 33, false);
    }
  for(int i = 0; i < noDiv; i++)
    {
      cerr << "Round: " << test->getCurrentRound() << endl;
      test->teamWon(i,1,99, 98, true);
    }
  
  cout << "Round: " << test->getCurrentRound() << endl;  
  test->teamWon(-1,0,20,10,true);
  test->teamWon(-1,1,30,10,false);

  cout << "Round: " << test->getCurrentRound() << endl;
  test->teamWon(-1,0,40,39,true);

  cerr << "Game progressed.\n";

  int numlines = 32;
  string out[numlines];

  test->deletePlayer(1);
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

  if(!test->getGameComplete())
  {
    cerr << "Game Not Complete.\n";
  }

  teams = test->getNumPlayers();
  
  cout << "Score Test. " << test->getNegScoreMode() << endl;
  cout << "1 point per game.\n";
  for(int i = 0; i < teams; i++)
  {
    test->selectPlayer(i);
    cout << test->getBracketName() << ' ' << test->getPlayerScore() << endl;
  }

  test->setNegScoreMode(2);
  cout << "Include Negative.\n";
  for(int i = 0; i < teams; i++)
    {
      test->selectPlayer(i);
      cout << test->getBracketName() << ' ' << test->getPlayerScore() << endl;
    }
  test->setScoringMode(2);
  test->sortBrackets();
  cout << "2^round, sorted.\n";
  for(int i = 0; i < teams; i++)
    {
      test->selectPlayer(i);
      cout << test->getBracketName() << ' ' << test->getPlayerScore() << endl;
    }

  test->setNegScoreMode(0);
  test->sortBrackets();
  cout << "No Neg Rounds, sorted.\n";
  for(int i = 0; i < teams; i++)
    {
      test->selectPlayer(i);
      cout << test->getBracketName() << ' ' << test->getPlayerScore() << endl;
    }

  test->setNegScoreMode(1);
  cout << "1 point neg round.\n";
  for(int i = 0; i < teams; i++)
    {
      test->selectPlayer(i);
      cout << test->getBracketName() << ' ' << test->getPlayerScore() << endl;
    }
  test->~Player_Manager();
}
