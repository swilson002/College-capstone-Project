#ifndef cout
#include<iostream>
using namespace std;
#endif

#include "TestTeamData.h"
#include "FullBracket.h"

#define INSERTTEST
#define STABILITY
#define PROGRESSION
#define FINAL

//#define INTENTSCREWUP

#ifdef INSERTTEST
#define MUCKUP1
#define MUCKUP2
#define MUCKUP3
#define GETTEAMTEST
//#define GETLOCTEST
//#define GETOPTEST
#endif
class FullTest : public FullBracket
{
 public:
  FullTest(int noDiv, string divName[DIV], string finalName) : 
    FullBracket(noDiv,divName, finalName)
  {
    ;
  }

  bool teamWin(int div, int seed, int round, int score1, int score2,
	       bool selected)
  {
    return advanceTeam(div, seed, round, score1, score2, selected);
  }

  bool mark(int div, int seed, int round)
  {
    return markSpot(div, seed, round);
  }

  bool newTeam(Team *newTeam, int selected)
  {
    return addTeam(newTeam, selected);
  }

  void teamsIn()
  {
    teamsEntered();
  }

  void FinalStart()
  {
    createFinals();
  }

  ~FullTest()
  {
    ;
  }
};

main()
{
  conv convert;
  int teams = TEAMTEST;

  string divis[DIV];

  for(int i = 0; i < DIV; i++)
  {
    divis[i] = "Division " + convert.convToString(i);
    cerr << divis[i] << endl;
  }

#ifdef INTENTSCREWUP

  FullTest *screwup;

  {
  string halp[2];
  halp[0] = "Test1";
  halp[1] = "Test2";

  screwup = new FullTest(2,halp, "Ha Ha");

  }

  cerr << screwup->getDivName(0) << ' ' << screwup->getDivName(1) << endl;
#endif

#ifdef INSERTTEST
  FullTest test(DIV, divis, "Finals");

  cerr << "Bracket defined.\n";

  TeamData sample;

#ifdef MUCKUP1
  cerr << "Muckup 1\n";

  int noDiv = test.getNoDiv();

  for(int i = 0; i < noDiv; i++)
  {
    for(int j = 0; j < TEAMTEST; j++)
    {
      if(!(test.newTeam(sample.teamTest[i][j], i)))
      {
	cerr << "Team NOT in.\n";
      }
    }
  }

  int rounds = test.getMaxRounds();
  int minRound = test.getMinRounds();

  cout << "Divisions sent: " << DIV << "   Divisions: " << noDiv << endl;

  cout << "No. Rounds: " << rounds << endl;
  cout << "First Full Round: " << minRound << endl;

#ifdef MUCKUP2
  cerr << "muckup 2\n";

  for(int i = 0; i < noDiv; i++)
  {
    cout << "Division: " << test.getDivName(i) << " ";
    cout << "# of teams: " << test.getNoTeams(i) << endl;
  }
#endif
#ifdef MUCKUP3
  cerr << "Muckup 3\n";

#ifdef GETTEAMTEST
  for(int i = 0; i < noDiv + 2; i++)
  {
    for(int j = 0; j < teams + 2; j++)
    {
      Team *curTeam = test.getTeam(i,j, rounds);
      if(curTeam)
      {
        cout << "Call: " << i << ',' << j << ',' << rounds << endl;
        cout << "Team: " << curTeam->returnName() << endl;
        cout << "Conference: " << curTeam->returnConference() << endl;
        cout << "Seed: " << curTeam->returnSeed() << endl;
        cout << "Record: " << curTeam->returnWins() << '-' << 
	  curTeam->returnLosses() << endl;
      }
    }
  }

  cout << endl;
  for(int i = 0; i < noDiv + 2; i++)
  {
    for(int j = 0; j < teams + 2; j++)
    {
      Team *curTeam = test.getTeam(i, j, rounds - 1);
      if(curTeam)
	{
	  cout << "Call: " << i << ',' << j << ',' << rounds - 1 << endl;
	  cout << "Team: " << curTeam->returnName() << endl;
	  cout << "Conference: " << curTeam->returnConference() << endl;
	  cout << "Seed: " << curTeam->returnSeed() << endl;
	  cout << "Record: " << curTeam->returnWins() << '-' <<
	    curTeam->returnLosses() << endl << endl;
	}
      }
  }


  {
    Team *curTeam = test.getTeam(-1, 1, rounds);
    cout << "Final Team: " << curTeam->returnName() << endl;

    cerr << "Empty Finals Check complete.\n";
  }

#endif
  int check = 1 << rounds;
  check += 2;

#ifdef GETLOCTEST
  for(int i = 0; i < noDiv + 2; i++)
  {
    for(int j = 0; j < check; j++)
    {
      Team *curTeam = test.getTeamByLoc(i, j, rounds);
      if(curTeam)
      {
	cout << "Call by Loc: " << i << ',' << j << ',' << rounds << endl;
	cout << "Team: " << curTeam->returnName() << " Seed: "
	     << curTeam->returnSeed() << endl;
      }
    }
  }

  cout << endl;

  for(int i = 0; i < noDiv + 2; i++)
  {
    for(int j = 0; j < check; j++)
    {
      Team *curTeam = test.getTeamByLoc(i, j, rounds-1);
      if(curTeam)
      {
        cout << "Call by Loc: " << i << ',' << j << ',' << rounds-1 << endl;
        cout << "Team: " << curTeam->returnName() << " Seed: "
             << curTeam->returnSeed() << endl;
      }
    }
  }
  cout << endl << endl;

#endif

#ifdef GETOPTEST
  for(int i = 0; i < noDiv + 2; i++)
  {
    for(int j = 0; j < teams + 2; j++)
    {
      Team *curTeam = test.getTeam(i, j, rounds);
      if(curTeam)
      {
        Team *opp = test.getOpponent(i, j, rounds);
        cout << "Call: " << i << ',' << j << ',' << rounds << endl;
        cout << "Team: " << curTeam->returnName() << " Seed: "
	     << curTeam->returnSeed() << endl;
        cout << "Opp: " << opp->returnName() << " Seed: "
	     << opp->returnSeed() << endl;
      }
    }
  }

  cout << endl;
  for(int i = 0; i < noDiv + 2; i++)
  {
    for(int j = 0; j < teams + 2; j++)
    {
      Team *curTeam = test.getTeam(i, j, rounds-1);
      if(curTeam)
	{
	  Team *opp = test.getOpponent(i,j, rounds-1);
	  cout << "Call: " << i << ',' << j << ',' << rounds-1 << endl;
	  cout << "Team: " << curTeam->returnName() << " Seed: "
	       << curTeam->returnSeed() << endl;
	  cout << "Opp: " << opp->returnName() << " Seed: "
	       << opp->returnSeed() << endl;
        }
    }
  }
  cout << endl;

#endif
#ifdef STABILITY
  if(test.teamWin(0, 8, rounds, 10, 0, true))
  {
    cerr << "Team advanced when not set.\n";
  }

  if(!(test.getTeam(0, 8, rounds -1)->returnBlank()))
    {
      cerr << "Team advanced when not set.\n";
    }

  test.teamsIn();

  cout << "Teams Set.\n";

  if(test.getFinalStatus())
  {
    cout << "Finals set prematurely.\n";
  }

  if(test.newTeam(sample.teamTest[1][1],0))
  {
    cerr << "Team added when set.\n";
  }

  if(test.getTeam(0,11, rounds))
  {
    cerr << "Team added when set.\n";
  }

  cout << "Add extra Team test complete.\n";
  if(test.teamWin(0,1, rounds-1, 0, 0, true))
  {
    cerr << "Team Won without Opponent.\n";
  }

  cerr << "No Opponent test complete.\n";
  if(test.teamWin(0,7, 1, 0, 0, true))
  {
    cerr << "NullTeam advanced.\n";
  }

  cerr << "NullTeam test Complete.\n";
  if(test.teamWin(0,1,rounds, 0, 0, true))
  {
    cerr << "Nothing advanced.  Seg fault didn't occur.\n";
  }

  if(test.teamWin(-1,1,2,0,0,true))
  {
    cerr << "Final Team advanced.  Seg fault didn't occur.\n";
  }

  cerr << "advanceTeam errors Complete.\n";

#endif

#ifdef PROGRESSION
  for(int i = 0; i < noDiv + 2; i++)
  {
    test.teamWin(i, 8,rounds, 10, 0, true);
    test.mark(i, 8,rounds);

    test.teamWin(i, 6, rounds, 20, 19, false);
    test.mark(i, 9, rounds);
  }

  cerr << "Bye Round Complete.\n";

  for(int j = 0; j < noDiv; j++)
  {
    for(int i = 6; i < 8; i++)
    {
      Team *curTeam = test.getTeam(j, i, rounds);
      Team *opp = test.getOpponent(j, i, rounds);
      cout << "Seed: " << curTeam->returnSeed() << ' ';
      cout << "Score: " << test.getScore(j, i, rounds) << ' ';
      if(test.getMark(j, i, rounds))
      {
        cout << "marked.";
      }

      cout << endl;
      cout << "Seed: " << opp->returnSeed() << ' ';
      cout << "Score: " << test.getOpScore(j, i, rounds) << ' ';
      if(test.getMark(j, 15-i, rounds))
      {
	cout << "marked.";
      }

      cout << endl;
    }
  }

  for(int i = 0; i < noDiv; i++)
  {
    for(int j = 0; j < check; j++)
    {
      Team *curTeam = test.getTeamByLoc(i, j, rounds-1);
      if(curTeam)
      {
        cout << "Call: " << i << ',' << j << ',' << rounds-1 << endl;
        cout << "Team: " << curTeam->returnName() << " Seed: "
             << curTeam->returnSeed() << endl;
      }
    }
  }

  for(int i = 0; i < noDiv; i++)
  {
    test.teamWin(i,0,3,50, 20, true);
    test.mark(i,0,3);
    test.teamWin(i,4,3,70, 50, true);
    test.mark(i,4,3);
    test.teamWin(i,6,3,99, 0, true);
    test.mark(i,6,3);
    test.teamWin(i, 2,3,20, 15, false);
    test.mark(i,5,3);

    test.teamWin(i,0,2,43, 40, true);
    test.mark(i,0,2);
    test.teamWin(i,1,2,20, 33, false);
    test.mark(i,2,2);

    test.teamWin(i,1,1,99, 98, true);
    test.mark(i,1,1);

    cout << "Champ of: " << i << ", " << test.getDivChamp(i)->returnName() 
	 << endl;

  }

  test.FinalStart();

  if(!test.getFinalStatus())
    {
      cerr << "Finals not in.\n";
    }

  if(!test.teamWin(-1,0,2,20,10,true))
  {
    cerr << "advance 1,2 failed.\n";
  }
  test.mark(-1,0,2);
  if(!test.teamWin(-1,1,2,30,10,false))
  {
    cerr << "advance 2,2 failed.\n";
  }

  test.mark(-1,2,2);

  if(!test.teamWin(-1,0,1,40,39,true))
    {
      cerr << "advance 1,1 failed.\n";
    }
  test.mark(-1,0,1);

  cout << "Champ: " << test.getDivChamp(-1)->returnName() << endl;


#ifdef FINAL
  string out[32];

  int numlines = 32;
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
		  Team *temp = test.getTeamByLoc(i,l, j);
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
	              if(test.getMarkByLoc(i,l,j))
	              {
	                name = "*" + name;
	              }
	              if(j > 0)
	              {
	                name = name + " " + 
	                  convert.convToString(test.getScoreByLoc(i,l,j));
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
  test.~FullTest();


#endif
#endif
#endif
#endif
#endif
}
