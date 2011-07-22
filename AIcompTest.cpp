#include "AIcomp.h"
#include "stringconv.h"
#include <iostream>
using namespace std;

#define TESTCASES 5

void displayTeam(AICompute &team, Team *selTeam);

main()
{
  AICompute comp;
  conv convert;

  Team *data[TESTCASES];

  for(int i = 0; i < TESTCASES; i++)
  {
    string name = "Test " + convert.convToString(i);
    if(comp.getTeamID(name) != -1)
    {
      cerr << "Two identical Teams in data.\n";
      exit(-1);
    }

    int id = comp.addTeamName(name);
    
    data[i] = new Team(name, id, "Unknown", i, rand()%100, rand()%100);
  }

  cout << "Init.\n";
  
  comp.addGame(data[0], data[2]);
  comp.addGame(data[0], data[2]);
  comp.addGame(data[0], data[2]);
  comp.addGame(data[0], data[2]);
  comp.addGame(data[2], data[0]);

  comp.addTeamVisit(data[0]);
  comp.addTeamRoundVisit(data[0], 0);
  comp.addTeamRoundVisit(data[0], 1);
  comp.addTeamRoundVisit(data[0], 2);
  comp.addTeamRoundVisit(data[0], 3);

  comp.addGame(data[0], data[3]);
  comp.addGame(data[0], data[3]);
  comp.addGame(data[0], data[3]);
  comp.addGame(data[3], data[0]);
  comp.addGame(data[3], data[0]);

  comp.addGame(data[0], data[4]);
  comp.addGame(data[0], data[4]);
  comp.addGame(data[0], data[4]);
  comp.addGame(data[0], data[4]);
  comp.addGame(data[0], data[4]);

  comp.addTeamVisit(data[1]);

  comp.addGame(data[2], data[3]);
  comp.addGame(data[2], data[3]);
  comp.addGame(data[2], data[3]);
  comp.addGame(data[2], data[3]);
  comp.addGame(data[3], data[2]);

  comp.addTeamVisit(data[2]);
  comp.addTeamRoundVisit(data[2], 0);
  comp.addTeamRoundVisit(data[2], 1);

  comp.addGame(data[2], data[4]);
  comp.addGame(data[2], data[4]);
  comp.addGame(data[4], data[2]);
  comp.addGame(data[4], data[2]);
  comp.addGame(data[4], data[2]);

  comp.addGame(data[4], data[3]);
  comp.addGame(data[3], data[4]);
  comp.addGame(data[4], data[3]);
  comp.addGame(data[4], data[3]);
  comp.addGame(data[4], data[3]);
  
  comp.addTeamVisit(data[4]);

  cout << "Init Complete.\n";

  cout << "Seed Difference array.\n";

  for(int i = 0; i < comp.getDifMaxSize(); i++)
  {
    cout << i << '\t';
  }
  cout << endl;

  for(int i = 0; i < comp.getDifMaxSize(); i++)
  {
    cout << comp.getWinsDif(i) << '/' << comp.getGamesDif(i) << '\t';
  }
  cout << endl;

  cout << "Seed Matrix.\n";
  for(int i = 0; i < comp.getMaxSize(); i++)
  {
    cout << '\t' << i;
  }
  cout << endl;

  for(int i = 0; i < comp.getMaxSize(); i++)
  {
    cout << i;
    for(int j = 0; j <comp.getMaxSize(); j++)
    {
      cout << '\t' << comp.getWins(i,j) << '/' << comp.getGames(i,j);
    }
    cout << endl;
  }

  cout << "Team Matrices.\n";
  for(int i = 0; i < TESTCASES; i++)
  {
    displayTeam(comp, data[i]);
  }

  cout << endl;

  cout << "Probability Test.\n";

  for(int i = 0; i < TESTCASES; i++)
  {
    for(int j = i; j < TESTCASES; j++)
    {
      cout << i << " vs. " << j << ": " 
	   << comp.computeProbDif(data[i],data[j]) << ", " 
	   << comp.computeProb(data[i], data[j]) << ", "
	   << comp.computeProbTeam(data[i], data[j]) << endl << endl;
      {
	cout << j << " vs. " << i << ": " 
	     << comp.computeProbDif(data[j],data[i]) << ", " 
	     << comp.computeProb(data[j], data[i])  << ", "
	     << comp.computeProbTeam(data[j], data[i]) << endl << endl;;
      }
    }
  }

  comp.~AICompute();
}

void displayTeam(AICompute &team, Team *selTeam)
{
  int id = selTeam->returnID();

  team.calculateTotal(selTeam);

  cout << endl;
  cout << team.getTeamName(id) << endl;

  cout << "Visits: " << team.getTeamVisits(id) << endl;

  for(int i = 0; i < MAXIMUMROUND; i++)
  {
    cout << team.getTeamRoundVisits(id, i) << ' ';
  }
  cout << endl;

  cout << "Wins: " <<team.getTeamTotalWins(id) << '/';
  cout << team.getTeamTotalGames(id) << endl;

  cout << "Average: " << team.getTeamAverageWins(id) << endl;

  cout << "Matrix\n";

  for(int i = 0; i < team.getTeamMaxSize(id); i++)
  {
    cout << '\t' << i;
  }
  cout << endl;

  for(int i = 0; i < team.getTeamMaxSize(id); i++)
  {
    cout << i;

    for(int j = 0; j < team.getTeamMaxSize(id); j++)
    {
      cout << '\t' << team.getTeamWins(id,i,j) << '/' 
	   << team.getTeamGames(id,i,j);
    }
    cout << endl;
  }

  cout << endl;
}
