#include "Bracket.h"
#include "TestTeamData.h"
#include "stringconv.h"
#include <iostream>

#include<string>
using namespace std;
//#define addteamtest
//#define advanceteamtest

// need to redo to consider changes to Bracket
main()
{

  conv convert;
  int teams = TEAMTEST;

  Bracket testBracket("Test");

  cerr << "Bracket Defined. \n";

  // enter teams
  TeamData sample;

  cerr << "Sample teams created.\n";

  for(int i = 0; i < teams; i++)
  {
    testBracket.addTeam(sample.teamTest[0][i]);
  }
  
  cerr << "\nTeams added.\n\n";

  int rounds = testBracket.getRounds();

  cout << "Bracket: " << testBracket.getBracketName() << " ";
  cout << "# of teams: " << testBracket.getNumTeams() << " ";
  cout << "# of Rounds: " << rounds;
  cout << " 2^rounds: " << testBracket.getTwoToRound() << endl << endl;
  for(int j = 0; j < teams + 2; j++)
  {
    Team *curTeam = testBracket.getTeam(j, rounds);
    if(curTeam)
    {
      cerr << "Call: " << j << ',' << rounds << endl;
      cout << "Team: " << curTeam->returnName() << endl;
      cout << "Conference: " << curTeam->returnConference() << endl;
      cout << "Seed: " << curTeam->returnSeed() << endl;
      cout << "Record: " << curTeam->returnWins() << '-' <<
        curTeam->returnLosses() << endl << endl;
    }
  }

  cerr << "Teams check.\n";
  for(int j = 0; j < teams + 2; j++)
    {
      Team *curTeam = testBracket.getTeam(j, rounds - 1);
      if(curTeam)
	{
	  cout << "Call: " << j << ',' << rounds - 1 << endl;
	  cout << "Team: " << curTeam->returnName() << endl;
	  cout << "Conference: " << curTeam->returnConference() << endl;
	  cout << "Seed: " << curTeam->returnSeed() << endl;
	  cout << "Record: " << curTeam->returnWins() << '-' <<
	    curTeam->returnLosses() << endl << endl;
	}
    }

  int check = testBracket.getTwoToRound();
  check += 2;

  for(int j = 0; j < check; j++)
    {
      Team *curTeam = testBracket.getTeamByLoc(j, rounds);
      if(curTeam)
      {
	cout << "Call: " << j << ',' << rounds << endl;
	cout << "Team: " << curTeam->returnName() << " Seed: "
	     << curTeam->returnSeed() << endl;
      }
    }

  cout << endl;

  for(int j = 0; j < check; j++)
    {
      Team *curTeam = testBracket.getTeamByLoc(j, rounds-1);
      if(curTeam)
	{
	  cout << "Call: " << j << ',' << rounds-1 << endl;
	  cout << "Team: " << curTeam->returnName() << " Seed: "
	       << curTeam->returnSeed() << endl;
	}
    }

  cout << endl << endl;

  for(int j = 0; j < teams + 2; j++)
  {
    Team *curTeam = testBracket.getTeam(j, rounds);
    if(curTeam)
    {
      Team *opp = testBracket.getOpponent(j, rounds);
      cout << "Call: " << j << ',' << rounds << endl;
      cout << "Team: " << curTeam->returnName() << " Seed: "
	   << curTeam->returnSeed() << endl;
      cout << "Opp: " << opp->returnName() << " Seed: "
	   << opp->returnSeed() << endl;
    }
  }

  cout << endl;

  for(int j = 0; j < teams + 2; j++)
    {
      Team *curTeam = testBracket.getTeam(j, rounds-1);
      if(curTeam)
	{
	  Team *opp = testBracket.getOpponent(j, rounds-1);
	  cout << "Call: " << j << ',' << rounds << endl;
	  cout << "Team: " << curTeam->returnName() << " Seed: "
	       << curTeam->returnSeed() << endl;
	  cout << "Opp: " << opp->returnName() << " Seed: "
	       << opp->returnSeed() << endl;
        }
    }

  cout << endl;
  if(testBracket.advanceTeam(8, rounds, 10, 0, true))
  {
    cerr << "Team advanced when not set.\n";
  }

  if(!(testBracket.getTeam(8, rounds -1)->returnBlank()))
    {
      cerr << "Team advanced when not set.\n";
    }

  testBracket.bracketDone();

  cout << "Teams Set.\n";

  if(testBracket.addTeam(sample.teamTest[1][1]))
  {
    cerr << "Team added when set.\n";
  }

  if(testBracket.getTeam(11, rounds))
  {
    cerr << "Team added when set.\n";
  }

  cout << "Add extra Team test complete.\n";
  if(testBracket.advanceTeam(1, rounds-1, 0, 0, true))
  {
    cerr << "Team Won without Opponent.\n";
  }

  cerr << "No Opponent test complete.\n";
  if(testBracket.advanceTeam(7, 1, 0, 0, true))
  {
    cerr << "NullTeam advanced.\n";
  }

  cerr << "NullTeam test Complete.\n";
  if(testBracket.advanceTeam(1,rounds, 0, 0, true))
  {
    cerr << "Nothing advanced.  Seg fault didn't occur.\n";
  }

  cerr << "advanceTeam errors Complete.\n";

  testBracket.advanceTeam(8,rounds, 10, 0, true);
  testBracket.markSpot(8,rounds);

  testBracket.advanceTeam(6, rounds, 20, 19, false);
  testBracket.markSpot(9, rounds);

  for(int i = 6; i < 8; i++)
  {
    Team *curTeam = testBracket.getTeam(i, rounds);
    Team *opp = testBracket.getOpponent(i, rounds);
    cout << "Seed: " << curTeam->returnSeed() << ' ';
    cout << "Score: " << testBracket.getScore(i, rounds) << ' ';
    if(testBracket.getMark(i, rounds))
    {
      cout << "marked.";
    }

    cout << endl;
    cout << "Seed: " << opp->returnSeed() << ' ';
    cout << "Score: " << testBracket.getOpScore(i, rounds) << ' ';
    if(testBracket.getMark(15-i, rounds))
      {
	cout << "marked.";
      }


    cout << endl;
  }

  for(int j = 0; j < check; j++)
    {
      Team *curTeam = testBracket.getTeamByLoc(j, rounds-1);
      if(curTeam)
        {
          cout << "Call: " << j << ',' << rounds-1 << endl;
          cout << "Team: " << curTeam->returnName() << " Seed: "
               << curTeam->returnSeed() << endl;
        }
    }

  testBracket.advanceTeam(0,3,50, 20, true);
  testBracket.markSpot(0,3);
  testBracket.advanceTeam(4,3,70, 50, true);
  testBracket.markSpot(4,3);
  testBracket.advanceTeam(6,3,99, 0, true);
  testBracket.markSpot(6,3);
  testBracket.advanceTeam(2,3,20, 15, false);
  testBracket.markSpot(5,3);

  testBracket.advanceTeam(0,2,43, 40, true);
  testBracket.markSpot(0,2);
  testBracket.advanceTeam(1,2,20, 33, false);
  testBracket.markSpot(2,2);

  testBracket.advanceTeam(1,1,99, 98, true);
  testBracket.markSpot(1,1);

  cout << "Champ: " << testBracket.getChamp()->returnName() << endl;

  string out[32];

  int numlines = 32;
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
		  Team *temp = testBracket.getTeamByLoc(l, j);
		  if(!temp)
		    {
		      out[k] = " ";
		    }
		  else
		  {
		    string name = temp->returnName();
	            if(!(name[0]))
	      	    {
	       	      out[k] = " ";
		    }
		    else
		    {
	              if(testBracket.getMarkByLoc(l,j))
	              {
	                name = "*" + name;
	              }
	              if(j > 0)
	              {
	                name = name + " " + 
	                  convert.convToString(testBracket.getScoreByLoc(l,j));
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
  }

  testBracket.~Bracket();
}
