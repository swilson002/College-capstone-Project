#ifndef cout
#include<iostream>
using namespace std;
#endif

#include "Team.h"

main()
{
  Team *team[3];
  team[0] = new Team("One", 1, "Conf1", 1, 800, 100);
  team[1] = new Team("Two", 2, "Conf2", 2, 600, 300);
  team[2] = new Team();

  team[0]->win();
  team[1]->win();
  team[2]->win();
  team[2]->eliminate();
  team[2]->win();
  team[1]->win();
  team[0]->win();
  team[0]->eliminate();

  for(int i = 0; i < 3; i++)
  {
    cout << team[i]->returnName() << ": " << team[i]->returnID() << endl;;
    cout << "Conference: " << team[i]->returnConference() << endl;;
    cout << team[i]->returnWins() << '-' << team[i]->returnLosses() << endl;
    cout << "Win count: " << team[i]->returnWinCount() << endl;
    if(team[i]->returnEliminated())
    {
      cout << "Eliminated\n";
    }
    else
    {
      cout << "Still In\n";
    }
    if(team[i]->returnBlank())
    {
      cout << "Blank Team.\n";
    }
  }
}
