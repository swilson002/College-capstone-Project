#include "SeedStorage.h"
#include "SeedDifStorage.h"
#include <iostream>
using namespace std;

#define SEEDTEST
//#define DIFTEST

#ifdef SEEDTEST
#define DISPLAY

#define POINT

#define PROGRESS

#ifdef PROGRESS
//#define ADDUNIT
#define ADDGAME
#endif

#ifndef PROGRESS
//#define ADDONE

#ifndef ADDONE
//#define ADDONEUNIT
#endif

#endif

#endif
main()
{

#ifdef DIFTEST

  SeedDifStorage SeedDif;

  cout << "Init Tests:\n";

  cout << SeedDif.getWins(5) << ' ' << SeedDif.getGames(0) << endl;
  cout << SeedDif.getMaxSize() << endl;

  cout << "End Init Tests.\n";

  SeedDif.addGame(0,0);
  SeedDif.addUnit(6,3,5);

  SeedDif.addGame(3,7);
  SeedDif.addGame(1,3);
  SeedDif.addGame(3,0);
  SeedDif.addGame(7,3);
  SeedDif.addGame(6,2);
  SeedDif.addUnit(8,4,5);
  SeedDif.addUnit(1,8,19);
  SeedDif.addUnit(2,5,5);
  SeedDif.addUnit(9,0,5);
  SeedDif.addUnit(0,20,5);

  SeedDif.addGame(2,6);
  SeedDif.addGame(8,2);
  SeedDif.addGame(2,7);
  SeedDif.addGame(8,1);

  for(int i = 0; i < SeedDif.getMaxSize(); i++)
  {
    cout << "Seed: " << i << " Wins: " << SeedDif.getWins(i)
	 << " Games: " << SeedDif.getGames(i) << endl;
  }

  cout << endl << "Seed Difference Test Complete.\n\n";

  SeedDif.~SeedDifStorage();

#endif

#ifdef SEEDTEST
#ifndef POINT
  SeedStorage Seed;
#else
  SeedStorage *Seed = new SeedStorage();
#endif

  cout << "Init Tests:\n";
#ifndef POINT
  cout << Seed.getWins(5,7) << ' ' << Seed.getGames(0,0) << endl;
  cout << Seed.getMaxSize() << endl;
#else
  cout << Seed->getWins(5,7) << ' ' << Seed->getGames(0,0) << endl;
  cout << Seed->getMaxSize() << endl;
#endif

  cout << "End Init Tests.\n";

#ifndef POINT
#ifdef ADDGAME
  Seed.addGame(0,0);
#endif

#ifdef ADDUNIT
  Seed.addUnit(6,4,3,5);
#endif

#ifdef ADDGAME
  Seed.addGame(3,7);
  Seed.addGame(1,3);
  Seed.addGame(3,0);
  Seed.addGame(7,3);
  Seed.addGame(6,2);
#endif

#ifdef ADDUNIT
  Seed.addUnit(8,2,4,5);
  Seed.addUnit(1,9,8,19);
  Seed.addUnit(2,0,5,5);
  Seed.addUnit(2,9,0,5);
  Seed.addUnit(0,4,20,5);
#endif

#ifdef ADDGAME
  Seed.addGame(2,6);
  Seed.addGame(8,2);
  Seed.addGame(2,7);
  Seed.addGame(8,1);

  Seed.addGame(0,4);
  Seed.addGame(5,3);
  Seed.addGame(7,5);
  Seed.addGame(1,3);
  Seed.addGame(2,8);
  Seed.addGame(1,9);
  Seed.addGame(1,4);
#endif

#ifdef ADDONE
  Seed.addGame(0,0);
#endif

#ifdef ADDONEUNIT
  Seed.addUnit(0,0,1,1);
#endif

#else
#ifdef ADDGAME
  Seed->addGame(0,0);
#endif

#ifdef ADDUNIT
  Seed->addUnit(6,4,3,5);
#endif

#ifdef ADDGAME
  Seed->addGame(3,7);
  Seed->addGame(1,3);
  Seed->addGame(3,0);
  Seed->addGame(7,3);
  Seed->addGame(6,2);
#endif

#ifdef ADDUNIT
  Seed->addUnit(8,2,4,5);
  Seed->addUnit(1,9,8,19);
  Seed->addUnit(2,0,5,5);
  Seed->addUnit(2,9,0,5);
  Seed->addUnit(0,4,20,5);
#endif

#ifdef ADDGAME
  Seed->addGame(2,6);
  Seed->addGame(8,2);
  Seed->addGame(2,7);
  Seed->addGame(8,1);

  Seed->addGame(0,4);
  Seed->addGame(5,3);
  Seed->addGame(7,5);
  Seed->addGame(1,3);
  Seed->addGame(2,8);
  Seed->addGame(1,9);
  Seed->addGame(1,4);
#endif

#ifdef ADDONE
  Seed->addGame(0,0);
#endif

#ifdef ADDONEUNIT
  Seed->addUnit(0,0,1,1);
#endif
#endif

#ifdef DISPLAY
#ifndef POINT  
  for(int i = 0; i < Seed.getMaxSize(); i++)
  {
    for(int j = 0; j < Seed.getMaxSize(); j++)
    {
      cout << "Seed: " << i  << ',' << j << " Wins: " << Seed.getWins(i,j)
	   << " Games: " << Seed.getGames(i,j) << endl;
    }
  }
#else
  for(int i = 0; i < Seed->getMaxSize(); i++)
  {
    for(int j = 0; j < Seed->getMaxSize(); j++)
    {
      cout << "Seed: " << i  << ',' << j << " Wins: " << Seed->getWins(i,j)
	   << " Games: " << Seed->getGames(i,j) << endl;
    }
  }
#endif
#endif
  cout << "Seed Storage Test Complete.\n";

#ifndef POINT
  Seed.~SeedStorage();
#else
  delete Seed;
#endif
#endif
}
