#include "PickInt.h"

Picks_Interface::Picks_Interface()
{
  manager = NULL;
  scoringMode[0] = "1 point per game";
  scoringMode[1] = "Add 1 for each Round";
  scoringMode[2] = "Double for each Round";
  negRound[0] = "not including extra game";
  negRound[1] = "1 point for the extra game";
  negRound[2] = "extra game is the first round";
}

void Picks_Interface::addManager(Player_Manager *game)
{
  manager = game;
}

int Picks_Interface::makePicks()
{
  if(!manager)
  {
    cout << "Error: No Game Data.\n";
    return 0;
  }

  if(!(manager->getPickMode()))
  {
    cout << "Error: Teams not entered.\n";
    return 0;
  }

  if(manager->getGameMode())
  {
    return 0;
  }

  int selection;
  while(1)
  {
    cout << "\n\n\n";
    cout << "Make a selection from the choices below.\n";
    cout << "1. Create a new bracket.\n";
    cout << "2. Delete an existing bracket.\n";
    cout << "3. View a bracket.\n";
    cout << "4. View Teams.\n";
    cout << "5. Show Settings.\n";
    cout << "6. Adjust Settings.\n";
    cout << "7. Save Progress.\n";
    cout << "8. Move on to the tournament.\n";
    cout << "9. Quit.\n";
    cout << "Selection: ";
    cin >> selection;
    cin.get();

    switch(selection)
    {
      case 1: newBracket(); break;
      case 2: deleteBracket(); break;
      case 3: showBracket(); break;
      case 4: showTeams(); break;
      case 5: showSet(); break;
      case 6: setSettings(); break;
      case 7: return 2; break;
      case 8: manager->setGame(); return 0; break;
      case 9: return quitMenu(); break;
      default: cout << "Invalid Selection.\n";
    }
  }
}

Player_Manager *Picks_Interface::getManager()
{
  return manager;
}

//Private

void Picks_Interface::newBracket()
{
  char input[MAXINPUT];  // MAXINPUT is a constant defined in TeamInt.h

  cout << "Enter name of the bracket: ";
  cin.getline(input, MAXINPUT);
 
  string brIn = input;
  manager->newPlayer(brIn, 0);

  int numRounds = manager->getMaxRounds();
  int numDiv = manager->getNumDiv();

  for(int i = numRounds ;i > 0; i--)
  {
    int numGames = 1 << (i-1);  // get 2^curRound, and halve it

    for(int j = 0; j < numDiv; j++)
    {
      for(int f = 0; f < numGames; f++)
      {
	pickTeamMenu(j,f,i);
      }
    }
  }

  numRounds = manager->getFinalRounds();
  for(int k = numRounds; k > 0; k--)
  {
    int numFinal = 1 << k-1;
    
    for(int l = 0; l < numFinal; l++)
    {
      pickTeamMenu(-1,l,k);
    }
  }
}

void Picks_Interface::pickTeamMenu(int div, int seed, int round)
{
  manager->selectTeamInBracket(div, seed, round);
  if(!(manager->getTeamNullStatus()))
  {
    if(manager->getTeamBlank()) // should never happen
    {
      cerr << "Program Error: Blank Spot in Bracket.\n";
      exit(-1);
    }

    bool done = false;
    do
    {
      cout << "\n\n";
      cout << "Which Team will advance:\n";
      manager->selectTeamInBracket(div, seed, round);
      cout << "1. " << manager->getTeamName() << endl;
      manager->selectOpponentInBracket(div, seed, round);
      cout << "2. " << manager->getTeamName() << endl;
      cout << "3. Team Information.\n";
            
      int selection;
      cout << "Selection: ";
      cin >> selection;
      cin.get();

      switch(selection)
      {
        case 1: manager->makePick(div, seed, round, true); done = true; break;
        case 2: manager->makePick(div, seed, round, false); done = true; break;
        case 3: {
	          manager->selectTeamInBracket(div, seed, round);
	          displaySelectedTeam();
	          manager->selectOpponentInBracket(div, seed, round);
	          displaySelectedTeam();
                } break;
        default: cout << "Invalid selection.\n";
      }
    }while(!done);
  }
}
int Picks_Interface::selectBracket()
{
  int selection = 0;
  int max = manager->getNumPlayers();
  bool done = false;

  if(!max)
  {
    cout << "No players.\n";
    return -1;
  }
  do
    {
      cout << "\n\n\n";
      cout << "Select Bracket:\n";

      for(int i = 0; i < max; i++)
	{
	  manager->selectPlayer(i);
	  cout << i+1 << ". " << manager->getBracketName() << endl;
	}
      cout << "Selection (0 to cancel): ";
      cin >> selection;
      cin.get();

      if(selection == 0)
	{
	  done = true;
	}
      else if (selection < 0 || selection > max)
	{
	  cout << "Invalid Selection.\n";
	}
      else
	{	  
	  done = true;
	}
    }while(!done);

    return selection - 1;
}

void Picks_Interface::deleteBracket()
{
  int selection = selectBracket();
  if(selection == -1)
  {
    return;
  }
  manager->selectPlayer(selection);

  string decision;

  do
  {
  cout << manager->getBracketName() << " will be deleted.  Are you Sure?";
  cout << "(y or n) ";
  cin >> decision;
  cin.get();

  if(!(decision[1]))
  {
    if(decision[0] == 'y' || decision[0] == 'Y')
    {
      manager->deletePlayer(selection);
      cout << "Player Deleted.\n";
      break;
    }
    else if(decision[0] == 'n' || decision[0] == 'N')
    {
      break;
    }
  }
  cout << "Invalid choice. Choose y or n.\n\n";

  }while(true);
}

void Picks_Interface::showBracket()
{
  int selection = selectBracket();

  if(selection == -1)
  {
    return;
  }

  manager->selectPlayer(selection);

  cout << "Bracket: " << manager->getBracketName() << endl;
  int div = manager->getNumDiv();

  for(int i = 0; i < div; i++)
  {
    displayDivision(i, selection);
  }

  displayDivision(-1, selection);
}

#define MAXLINES 64
void Picks_Interface::displayDivision(int div, int selection)
{
  manager->selectPlayer(selection);
  if(div > manager->getNumDiv() || div < -1)
  {
    return;
  }

  int rounds;

  if(div == -1)
  {
    rounds = manager->getFinalRounds();
  }
  else
  {
    rounds = manager->getMaxRounds();
  }

  string lines[MAXLINES];

  int numlines = 1 << rounds;
  numlines = 2 * numlines - 1;  //one line per team, one line per game

  if(numlines > MAXLINES)
  {
    cerr << "Program error: Too many teams.\n";
    exit(-1);
  }

  for(int j = rounds; j >= 0; j--)
  {
    bool free = true;
    int l = 0;
    for(int k = 0; k < numlines; k++)
    {
      if(!(lines[k][0]))
      {
	if(free)
	{
	  manager->selectTeamInBByLoc(div, l, j);
	  if(manager->getTeamNullStatus())
	  {
	    lines[k] = " ";
	  }
	  else
	  {
	    string name = manager->getTeamName();
	    if(!(name[0]))
	    {
	      lines[k] = " ";
	    }
	    else
	    {
	      string disp = "";
	      for(int i = rounds; i > j; i--)
	      {
		disp = disp + "\t";
	      }
	      lines[k] = disp + name;
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

  cout << endl << manager->getDivName(div);
  if(div != -1)
  {
    cout << " division";
  }
  cout << endl << endl;

  for(int z = 0; z < numlines; z++)
  {
    cout << lines[z] << endl;
  }
}

void Picks_Interface::showTeams()
{
  bool done = false;
  int max = manager->getNumDiv();
  int selection;
  do
  {
    cout << "\n\n\n";
    cout << "Select Division:\n";

    for(int i = 0; i < max; i++)
    {
      cout << i+1 << ". " << manager->getDivName(i) << endl;
    }

    cout << "Selection(0 to return to menu): ";
    cin >> selection;
    cin.get();

    if(!selection)
    {
      return;
    }
    if(selection < 0 || selection > max)
    {
      cout << "Invalid Selection.\n";
    }
    else
    {
      done = true;
    }
  }while(!done);

  int index = selection - 1;

  max = manager->getNumTeams(index);
  
  do
  {
    cout << "\n\n\n";
    cout << "Select Team:\n";

    for(int i = 0; i < max; i++)
    {
      manager->selectTeam(index, i);
      cout << i+1 << ". " << manager->getTeamName() << endl;
    }

    cout << "Selection(0 to return to menu): ";
    cin >> selection;
    cin.get();

    if(!selection)
    {
      return;
    }

    if(selection < 0 || selection > max)
    {
      cout << "Invalid Selection.\n";
    }
    else
    {
      done = true;
    }
  }while(!done);

  manager->selectTeam(index, selection-1);
  displaySelectedTeam();
}

void Picks_Interface::displaySelectedTeam()  // assumes team is selected
{
  if(manager->getTeamNullStatus() || manager->getTeamBlank())
  {
    return;
  }
                                                                        
  cout << "Team: " << manager->getTeamName() << endl;
  cout << "Conference: " << manager->getTeamConf() << endl;
  cout << "Seed: " << manager->getTeamSeed() << endl;
  cout << "Record: " << manager->getTeamWins() << '-' <<
    manager->getTeamLosses() << endl;
}

void Picks_Interface::showSet()
{
  cout << "Scoring mode is ";
  int mode = manager ->getScoringMode();
  cout << scoringMode[mode] << " and ";
  int negMode = manager ->getNegScoreMode();
  cout << negRound[negMode] << ".\n";
}

void Picks_Interface::setSettings()
{
  int selection;
  do
    {
      cout << "Select scoring mode.\n";
      cout << "1. " << scoringMode[0] << ".\n";
      cout << "2. " << scoringMode[1] << ".\n";
      cout << "3. " << scoringMode[2] << ".\n";
      cout << "Selection: ";
      cin >> selection;
      cin.get();

      if(selection > 0 && selection < 4)
	{
	  manager->setScoringMode(selection - 1);
	}
      else
	{
	  cout << "Invalid selection.\n";
	}
    }while(!(selection > 0 && selection < 4));

  do
    {
      cout << "Include extra game?\n";
      cout << "1. Yes.\n";
      cout << "2. No.\n";
      cout << "Selection: ";
      cin >> selection;
      cin.get();

      if (selection == 1)
	{
	  manager->setNegScoreMode(1);
	}
      else if(selection == 2)
	{
	  manager->setNegScoreMode(0);
	}
      else
	{
	  cout << "Invalid selection.\n";
	}
   }while(selection < 1 || selection > 2);

}

int Picks_Interface::quitMenu()
{
  string input;
  bool done = false;
  int save = 0;
  do
  {
    cout << "Save Progress? (y or n): ";
    cin >> input;
    cin.get();

    if(input[1] == '\0')
    {
      if(input[0] == 'y' || input[0] == 'Y')
      {
        save = 1;
        done = true;
      }
      else if(input[0] == 'n' || input[0] == 'N')
      {
        save = 0;
        done = true;
      }
    }
    if(!done)
    {
      cout << "Invalid selection.\n";
    }
  }while(!done);

  return save;
}
