#include "TestTeamData.h"

#ifndef cerr
#include<iostream>
using namespace std;
#endif

//#define TESTDEBUG

// anything that includes this file MUST include Team.h
TeamData::TeamData()
{
  conv fu;
  for(int i = 0; i < DIVTEST; i++)
  {
    for(int j = 0; j < TEAMTEST; j++)
    {
      string num;
      string name = "Team ";
      num = fu.convToString(i);
      name = name + num + ' ';
      num = fu.convToString(j);
      name = name + num;

      #ifdef TESTDEBUG
      cerr << "Team: " << name << endl;
      #endif

      int id = rand();

      #ifdef TESTDEBUG
      cerr << "id: " << id<< endl;
      #endif

      int numb = rand() % 100;
      num = fu.convToString(numb);
      string conf = num;

      #ifdef TESTDEBUG
      cerr << "Conference: " << conf << endl;
      #endif
      int seed = j;
 
      #ifdef TESTDEBUG
      cerr << "Seed: " << seed << endl;
      #endif
      int wins = rand();

      #ifdef TESTDEBUG
      cerr << "wins: " << wins<< endl;
      #endif

      int losses = rand();

      #ifdef TESTDEBUG
      cerr << "Losses: " << losses<< endl;
      #endif

      teamTest[i][j] = new Team(name, id, conf, seed, wins, losses);

      #ifdef TESTDEBUG
      cerr << "Team: " << teamTest[i][j]->returnName() << endl;
      cerr << "id: " << teamTest[i][j]->returnID() << endl;
      cerr << "Conf: " << teamTest[i][j]->returnConference() << endl;
      cerr << "seed: " << teamTest[i][j]->returnSeed() << endl;
      cerr << teamTest[i][j]->returnWins() << '-' << 
	teamTest[i][j]->returnLosses() << endl;
      cerr << "Created.\n";
      #endif
    } 
  }
  blankTeam = new Team();
}

