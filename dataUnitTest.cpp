#include "dataUnit.h"
#include <iostream>
using namespace std;

#define TESTCASES 3

main()
{
  DataUnit *test[TESTCASES];
  test[0] = new DataUnit();
  test[1] = new DataUnit(5,8);
  test[2] = new DataUnit(29, 49);

  for(int i = 0; i < TESTCASES; i++)
  {
    cout << i << ": Wins: " << test[i]->getWins() 
	 << " Games: " << test[i]->getGames() << endl;
  }
  cout << endl;

  test[0]->addWin();
  test[0]->addWin();
  test[0]->addWin();
  test[0]->addLoss();
  test[0]->addLoss();

  test[1]->addWin();
  test[1]->addLoss();
  test[1]->addWin();
  test[1]->addLoss();

  test[2]->addLoss();
  test[2]->addLoss();
  test[2]->addLoss();
  test[2]->addLoss();
  test[2]->addLoss();

  for(int i = 0; i < TESTCASES; i++)
  {
    cout << i << ": Wins: " << test[i]->getWins() 
	 << " Games: " << test[i]->getGames() << endl;
  }
}
