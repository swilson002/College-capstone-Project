#ifndef cout
#include<iostream>
using namespace std;
#endif

#include "TestTeamData.h"
#include "FullBracket.h"
#include "Player.h"

#define TESTPLAYER 3

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

  FullTest *test = new FullTest(DIV, divis, "Finals");

  TeamData sample;

  int noDiv = test->getNoDiv();

  for(int i = 0; i < noDiv; i++)
  {
    for(int j = 0; j < TEAMTEST; j++)
    {
      if(!(test->newTeam(sample.teamTest[i][j], i)))
      {
	cerr << "Team NOT in.\n";
      }
    }
  }

  int rounds = test->getMaxRounds();

  int check = 1<< rounds;

  test->teamsIn();

  for(int i = 0; i < noDiv; i++)
  {
    test->teamWin(i, 8,rounds, 10, 0, true);
    test->teamWin(i, 6, rounds, 20, 19, false);

    test->teamWin(i,0,3,50, 20, true);
    test->teamWin(i,4,3,70, 50, true);
    test->teamWin(i,6,3,99, 0, true);
    test->teamWin(i, 2,3,20, 15, false);

    test->teamWin(i,0,2,43, 40, true);
    test->teamWin(i,1,2,20, 33, false);

    test->teamWin(i,1,1,99, 98, true);
  }

  test->FinalStart();

  test->teamWin(-1,0,2,20,10,true);

  test->teamWin(-1,1,2,30,10,false);
  test->teamWin(-1,0,1,40,39,true);


  Player *pTest[TESTPLAYER];

  for(int i = 0; i < TESTPLAYER; i++)
  {
    pTest[i] = new Player(noDiv, divis, "Final", test, i, "Testing");
    for(int j = 0; j < noDiv; j++)
    {
      for(int k = 0; k < TEAMTEST; k++)
      {
        pTest[i]->newTeam(sample.teamTest[j][k], j);
      }
    }

    if(pTest[i]->makePick(0,0,3,true))
    {
      cerr << "Pick Made Prematurly.\n";
      exit(-1);
    }

    pTest[i]->teamsIn();

    if(pTest[i]->makePick(0,0,4,true))
    {
      cerr << "Nothing Advanced.\n";
      exit(-1);
    }

    cerr << "Quick Test Complete.\n";

    for(int j = 0; j < noDiv; j++)
    {
      pTest[i]->makePick(j,6,4,rand()%2);
      pTest[i]->checkTeam(j,6,3);
      pTest[i]->makePick(j,7,4,rand()%2);
      pTest[i]->checkTeam(j,7,3);

      for(int k = 0; k < 4; k++)
      {
	pTest[i]->makePick(j,k,3,rand()%2);
	pTest[i]->checkTeam(j,k,2);
      }

      for(int k = 0; k < 2; k++)
      {
	pTest[i]->makePick(j,k,2,rand()%2);
	pTest[i]->checkTeam(j,k,1);
      }

      pTest[i]->makePick(j,0,1,rand()%2);
      pTest[i]->checkTeam(j,0,0);
    }

    if(!pTest[i]->getFinalStatus())
    {
      cerr << "Final Not In.\n";
      exit(-1);
    }

    for(int k = 0; k < 2; k++)
    {
      pTest[i]->makePick(-1,k,2,rand()%2);
      pTest[i]->checkTeam(-1,k,1);
    }

    pTest[i]->makePick(-1,0,1,rand()%2);
    pTest[i]->checkTeam(-1,0,0);
  }

  int finalRnd = test->getFinalRounds();

  int numlines = 32;
  string out[numlines];
  for(int f = 0; f <= TESTPLAYER; f++)
    {  
      if(f != TESTPLAYER)
      {
	cout << "Name: " << pTest[f]->getBrName() << endl;
	cout << "AI Type: " << pTest[f]->getAIType() << endl;
	cout << "Score per Round: ";
	for(int g = rounds-1; g >= 0; g--)
	{
	  cout << pTest[f]->getPlScore(g) << ' ';
	}
	cout << endl;
	for(int g = finalRnd-1; g >= 0; g--)
	{
	  cout << pTest[f]->getFinalBrScore(g) << ' ';
	}
	cout << endl;

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
		  Team *temp;
		  if(f == TESTPLAYER)
		  {
		    temp = test->getTeamByLoc(i,l, j);
		  }
		  else
		  {
		    temp = pTest[f]->getTeamByLoc(i,l,j);
		  }
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
		      if(f != TESTPLAYER)
		      {
	                if(pTest[f]->getMarkByLoc(i,l,j))
	                {
	                  name = "*" + name;
	                }
		      }
	              if(j > 0)
	              {
			if(f == TESTPLAYER)
			{
	                  name = name + " " + 
	                    convert.convToString(test->getScoreByLoc(i,l,j));
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
  }

  for(int i = 0; i < 3; i++)
  {
    pTest[i]->~Player();
  }
}
