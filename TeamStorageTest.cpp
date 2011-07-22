#include "TeamStorage.h"
#include "stringconv.h"

#include<cstdlib>
#include <iostream>
using namespace std;

#define TESTCASES 10
#define ROUNDS 8

void DisplayTeam(TeamData *team);

main()
{
  TeamStorage *StoreTest = new TeamStorage();

  conv convert;
  for(int i = 0; i < TESTCASES; i++)
  {
    StoreTest->addName("Test " + convert.convToString(i));
  } 


  int roundTest[ROUNDS] = {0,0,0,3,5,2,3,4};
  StoreTest->addUnit("Unit 1", rand()%10, ROUNDS, roundTest);

  int roundTest2[ROUNDS] = {3,4,5,6,2,3,4,5};
  StoreTest->addUnit("Unit 2", rand()%10, ROUNDS, roundTest2);
  StoreTest->addAlias("Evil", 7);
  StoreTest->addAlias("9384", 9);
  StoreTest->addAlias("Me", 2);
  StoreTest->addAlias("Bob", 4);
  StoreTest->addAlias("tap", 0);

  if(TESTCASES != StoreTest->getMaxSize() - 2)
  {
    cerr << "Incorrect size.\n";
    exit(1);
  }

  cout << "Alias Test\n";

  string name;
 
  name = "EVIL ";
  int id;
  id = StoreTest->getID(name);
  if(id != 7)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  name = "test4 ";
  id = StoreTest->getID(name);

  if(id != 4)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  name = "nndi";
  id = StoreTest->getID(name);
  if(id != -1)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  name = "9384";
  id = StoreTest->getID(name);
  if(id != 9)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  name = "bob ";
  id = StoreTest->getID(name);
  if(id != 4)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  name = "Test   \t 7 ";
  id = StoreTest->getID(name);
  if(id != 7)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  name = "Unit 1";
  id = StoreTest->getID(name);
  if(id != 10)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  name = "TAP";
  id = StoreTest->getID(name);
  if(id != 0)
  {
    cerr << "Incorrect team " << name << ',' << id << endl;
  }

  cout << "Test Complete.\n";

  cout << "TeamData Test.\n";

  TeamData *dataTest[4];

  dataTest[0] = StoreTest->getTeam(0);
  dataTest[1] = StoreTest->getTeam(2);
  dataTest[2] = StoreTest->getTeam(7);
  dataTest[3] = StoreTest->getTeam(TESTCASES);

  TeamData *nullTest = StoreTest->getTeam(-1);

  if(nullTest)
  {
    cerr << "Team not NULL.\n";

  }

  for(int i = 0; i < 4; i++)
  {
    if(!dataTest[i])
    {
      cerr << "Team NULL.\n";
      exit(-1);
    }
  }

  for(int i = 0; i < 4; i++)
  {
    DisplayTeam(dataTest[i]);
  }

  dataTest[3]->addUnit(1,5,9,10);
  dataTest[3]->addUnit(4,3,8,10);
  dataTest[3]->addUnit(2,4,10,20);
  dataTest[2]->addUnit(2,5,6,7);
  dataTest[1]->addUnit(3,1,9,9);

  for(int i = 0; i < 4; i++)
  {
    int games = rand()%30;

    for(int j = 0; j < games; j++)
    {
      if(rand()%2)
      {
	dataTest[i]->addWin(rand()%5 + 1,rand()%5 + 1 );
	dataTest[i]->addRoundVisit(j%MAXIMUMROUND);
      }
      else
      {
	dataTest[i]->addLoss(rand()%5 + 1,rand()%5 + 1 );
      }
    }

    int visits = rand()%8;
    for(int k = 0; k < visits; k++)
    {
      dataTest[i]->addVisit();
      
    }
  }

  for(int i = 0; i < 4; i++)
  {
    DisplayTeam(dataTest[i]);
  }

  StoreTest->~TeamStorage();
}

void DisplayTeam(TeamData *team)
{

  team->calculateTotal();

  cout << endl;
  cout << team->getName() << endl;

  cout << "Visits: " << team->getVisits() << endl;

  for(int i = 0; i < MAXIMUMROUND; i++)
  {
    cout << team->getRoundVisits(i) << ' ';
  }
  cout << endl;

  cout << "Wins: " <<team->getTotalWins() << '/';
  cout << team->getTotalGames() << endl;

  cout << "Average: " << team->getAverageWins() << endl;

  cout << "Matrix\n";

  for(int i = 0; i < team->getMaxSize(); i++)
  {
    cout << '\t' << i;
  }
  cout << endl;

  for(int i = 0; i < team->getMaxSize(); i++)
  {
    cout << i;

    for(int j = 0; j < team->getMaxSize(); j++)
    {
      cout << '\t' << team->getWins(i,j) << '/' << team->getGames(i,j);
    }
    cout << endl;
  }

  cout << endl;
}
