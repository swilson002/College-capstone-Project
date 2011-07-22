#include "TeamInt.h"

// Public
Team_Interface::Team_Interface()
{
  noDiv = 0;
  manager = NULL;
}

void Team_Interface::enterData()
{
  enterBracketDesc();
  enterTeams();
}

Player_Manager *Team_Interface::getManager()
{
  return manager;
}

// Private

void Team_Interface::enterBracketDesc()
{

  cout << "Enter Number of divisions: ";
  cin >> noDiv;

  cin.get();

  if(noDiv > DIV)
  {
    cerr << "Program Error: Too many divisions.\n";
    exit(-1);
  }

  for(int i = 0; i < noDiv; i++)
  {
    cout << "Enter division " << i + 1 << ": ";
    cin.getline(divName[i], MAXINPUT);
  }

  cout << "Enter name of Finals: ";
  cin.getline(finalName, MAXINPUT);

  string newDivName[DIV];
  for(int i = 0; i < noDiv; i++)
  {
    newDivName[i] = divName[i];
  }

  string newFinalName = finalName;

  manager = new Player_Manager(newDivName, newFinalName, noDiv);
}

void Team_Interface::enterTeams()
{
  for(int i = 0; i < noDiv; i++)
  {
    char name[MAXINPUT];
    char conf[MAXINPUT];
    int wins = 0;
    int losses = 0;

    int teams = 0;

    cout << "Enter Number of Teams in " << divName[i] << ": ";
    cin >> teams;
    cin.get();

    for (int j = 1; j <= teams; j++)
    {
      cout << endl;

      cout << "Team " << j << ":\n";
     
      cout << "Enter Team Name: ";
      cin.getline(name, MAXINPUT);
      if(name[0] == '\0')
      {
	name[0] = ' ';
	name[1] = '\0';
      }
      cout << "Enter Team Conference: ";
      cin.getline(conf, MAXINPUT);
      if(conf[0] = '\0')
      {
	conf[0] = ' ';
	conf[1] = '\0';
      }
      cout << "Enter # of wins: ";
      cin >> wins;
      cin.get();
      cout << "Enter # of losses: ";
      cin >> losses;
      cin.get();
      manager->addTeam(i, name, 0, conf, j, wins, losses);
    }
  }
  manager->teamsLoaded();

  cout << "Teams entered.\n";
}
