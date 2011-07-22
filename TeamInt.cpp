#include "TeamInt.h"

// Public
Team_Interface::Team_Interface()
{
  noDiv = 0;
  manager = new AI_Manager();
}

Team_Interface::Team_Interface(AI_Manager *game)
{
  noDiv = 0;
  if(game)
  {
    manager = game;
  }
  else
  {
    manager = new AI_Manager();
  }
}

void Team_Interface::enterData()
{
  enterBracketDesc();
  enterTeams();
}

AI_Manager *Team_Interface::getManager()
{
  return manager;
}

// Private

void Team_Interface::enterBracketDesc()
{

  cout << "Enter Number of divisions: ";
  cin >> noDiv;

  cin.get();

  manager->setNumDiv(noDiv);

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

  string newFinalName = finalName;

  manager->setDivisionName(FINALS, finalName);
  string newDivName;
  for(int i = 0; i < noDiv; i++)
  {
    newDivName = divName[i];
    manager->setDivisionName(i, newDivName);
  }

}

void Team_Interface::enterTeams()
{
  for(int i = 0; i < noDiv; i++)
  {
    string name;
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

      int id;
      do
      {
	name = enterTeamName();
        id = verifyTeam(name);

      }while(id < 0);
      cout << manager->getAITeamName(id) << endl;

      cout << "Enter Team Conference: ";
      cin.getline(conf, MAXINPUT);
      cout << "Enter # of wins: ";
      cin >> wins;
      cin.get();
      cout << "Enter # of losses: ";
      cin >> losses;
      cin.get();
      manager->addTeam(i, name, id, conf, j, wins, losses);
    }
  }
  manager->teamsLoaded();

  cout << "Teams entered.\n";
}

string Team_Interface::enterTeamName()
{

  char input[MAXINPUT];

  string name;
  bool done = false;
  do
  {
    cout << "Enter Team Name: ";
    cin.getline(input, MAXINPUT);
    if(input[0] == '\0')
    {
      input[0] = ' ';
      input[1] = '\0';
    }

    name = input + '\0';
    if(name.length() < 4)
    {
      cout << "Please do not use 3 letter acronyms. ";
      do
      {
        cout << "Is this the full name of the Team (y of n)? ";

        char choice[MAXINPUT];
        cin.getline(choice, MAXINPUT);

        if(choice[1] != '\0')
        {
          cout << "Invlaid Selection.\n";
        }
        else
        {
          char select = tolower(choice[0]);
          if(select == 'y')
          {
	    done = true;
            break;
	  }
	  else if(select == 'n')
	  {
	    break;
	  }
          else
	  {
	    cout << "Innalid Selection.\n";
	  }
        }
      }while(1);
    }
    else
    {
      done = true;
    }
  }while(!done);

  return name;
}

int Team_Interface::verifyTeam(string team)
{

  int id = manager->getAITeamID(team);

  if(id < 0)
  {  
    bool done = false;
    do
    {
      cout << "Team not found in data.  Is this a new Team(y or n)? ";
      char decision[MAXINPUT];
      
      cin.getline(decision, MAXINPUT);
      
      string error = "Invalid Selection.\n";
      if(decision[1])
      {
        cout << error;
      }
      else
      {
        char choice = tolower(decision[0]);
        if(choice == 'y')
        {
          id = manager->addAITeamName(team);
	  done = true;
        }
        else if(choice == 'n')
        {
	  bool done2 = false;
	  do
	  {
	    cout << "Is " << team << " The correct team (y or n)? ";
	    
	    char decision2[MAXINPUT];

	    cin.getline(decision2, MAXINPUT);

             if(decision2[1])
             {
               cout << error;
             }
             else
             {
               char choice2 = tolower(decision2[0]);
	       if(choice2 == 'y')
               {
	       
	         string newName = enterTeamName();

	         id = verifyTeam(newName);

	         if(id > -1)
	         {
		   manager->addAITeamAlias(team, id);
	         }
		   
		 done2 = true;

	       }
               else if(choice2 == 'n')
               {
	         done2 = true; 
	       }
	       else
	       {
	         cout << error;
	       }
	     }
	  }while(!done2);
	  
	  done = true;
	}
        else
        {
          cout << error;
        }
      }
    }while(!done);
  }
      
  return id;
}

