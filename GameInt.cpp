#include "GameInt.h"

#define MAXAI 4
// public

Game_Interface::Game_Interface()
{
  manager = NULL;
  scoringMode[0] = "1 point per game";
  scoringMode[1] = "Add 1 for each Round";
  scoringMode[2] = "Double for each Round";
  negRound[0] = "not including extra game";
  negRound[1] = "1 point for the extra game";
  negRound[2] = "extra game is the first round";

  AIType[0] = "Human";
  AIType[1] = "Difference of Seeds";
  AIType[2] = "Seeds";
  AIType[3] = "Team";

  Round[0] = "Final Four";
  Round[1] = "Elite Eight";
  Round[2] = "Sweet Sixteen";
  Round[3] = "2nd Round";
  Round[4] = "1st Round";
  Round[5] = "Play in Game";

  Final[0] = "Champion";
  Final[1] = "Championship";
  Final[2] = Round[0];

}

void Game_Interface::addManager(AI_Manager *game)
{
  manager = game;
}

int Game_Interface::playGame()
{
  if(!manager)
  {
    cerr << "Program Error, No data.\n";
    return 0;
  }

  if(!(manager->getGameMode()))
  {
    cerr << "Program Error, Picks not complete.\n";
    return 0;
  }

  manager->sortBrackets();

  while(true)
  {
    int selection;
    cout << "\n\n";
    cout << "Select one of the options listed.\n";
    cout << "1. Select team to advance.\n";
    cout << "2. Show Brackets.\n";
    cout << "3. Show Tournament Results.\n";
    cout << "4. Show Scores.\n";
    cout << "5. Show Scores under a different scoring mode.\n";
    cout << "6. Show Teams.\n";
    cout << "7. Show settings.\n";
    cout << "8. Save Game.\n";
    cout << "9. Clear current game and start a new game.\n";
    cout << "10. Quit.\n";
    cout << "Selection: ";
    cin >> selection;
    cin.get();

    switch(selection)
    {
      case 1: selectGame(); break;
      case 2: displayBracket(); break;
      case 3: displayTourn(); break;
      case 4: displayPlayers(); break;
      case 5: displayPlayersAltScore(); break;
      case 6: displayTeams(); break;
      case 7: showScoringMode(); break;
      case 8: return 2; break;
      case 9: if(clearMenu()){return 3;} break;
      case 10: return quitMenu(); break;
      default: cout << "Invalid selection.\n";
    }
  }
}

// private
int Game_Interface::selectBracket()
{
  int selection = 0;
  int max = manager->getNumPlayers();
  bool done = false;

  if(max == 0)
  {
    cout << "No Players.\n";
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

void Game_Interface::displayTeams()
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
  displayTeam(index, selection-1);

}

#define TEAMS 64  // will allow for 128 teams
void Game_Interface::selectGame()
{
  if(manager->getGameComplete())
  {
    cout << "Tournament is complete.\n";
    return;
  }

  int round = manager->getCurrentRound();
  int choices[TEAMS][2];
  int numChoices = 0;
  int div = manager->getNumDiv();
  int posGames = 1 << (round -1);

  if((posGames * div) > TEAMS)
  {
    cerr << "Program Error: Too Many Teams.\n";
  }  
  bool done = false;

  int start = 0;
  int end = div;
  if(manager->getFinalStatus())
  {
    start = -1;
    end = 0;
  }

  do
  {
    numChoices = 0;
 
    cout << "\n\nSelect Game.\n";
    for(int i = start; i < end; i++)
    {
      for(int j = 0; j < posGames; j++)
      {
        manager->selectTeamInMaster(i,j,round-1);
        if(manager->getTeamBlank())
        {
	  manager->selectTeamInMaster(i, j, round);

	  if(!manager->getTeamNullStatus())
	  {
	    cout << numChoices+1 << ". " << manager->getTeamName();
	    manager->selectOpponentInMaster(i,j,round);
	    cout << " VS. " << manager->getTeamName() << endl;
	    choices[numChoices][0] = i;
	    choices[numChoices][1] = j;
	    numChoices++;
	  }
        }
      }
    }
    if(numChoices == 0) // shouldn't happen
    {
      cerr << "Program Error: Round Complete, didn't update.\n";
      exit(-1);
    }

    cout << "Selection(0 to return to main menu): ";
    int selection;
    cin >> selection;
    cin.get();

    if(!selection)
    {
      done = true;
    }
    else if(selection > 0 && selection <= numChoices)
    {
      selection--;
      advanceTeam(choices[selection][0], choices[selection][1]);
      done = true;
    }
    else
    {
      cout << "Invalid Selection.\n";
    }
  }while(!done);
}

void Game_Interface::advanceTeam(int div, int seed)
{
  int round = manager->getCurrentRound();

  bool done = false;
  bool win = true;
  string team[2];

  manager->selectTeamInMaster(div,seed,round);
  team[0] = manager->getTeamName();
  manager->selectOpponentInMaster(div,seed,round);
  team[1] = manager->getTeamName();

  do
  {
    cout << "Pick Winning Team:\n";
    cout << "1. " << team[0] << endl;
    cout << "2. " << team[1] << endl;
    cout << "Selection(0 to cancel): ";
    int selection;
    cin >> selection;
    cin.get();

    switch(selection)
    {
      case 0: return; break;
      case 1: win = true; done = true; break;
      case 2: win = false; done = true; break;
      default: cout << "Invalid selection.\n";
    }
  }while(!done);
 
  int scoreWin;
  int scoreLose;

  cout << "Enter score for ";
  if(win)
  {
    cout << team[0];
  }
  else
  {
    cout << team[1];
  }
  cout << ": ";

  cin >> scoreWin;
  cin.get();
  cout << "Enter score for ";
  if(win)
  {
    cout << team[1];
  }
  else
  {
    cout << team[0];
  }
  cout << ": ";
  cin >> scoreLose;
  cin.get();

  manager->teamWon(div, seed, scoreWin, scoreLose, win);
  manager->sortBrackets();
}

void Game_Interface::displayTeam(int div, int seed)
{
  manager->selectTeam(div, seed);
  if(manager->getTeamNullStatus() || manager->getTeamBlank())
  {
    return;
  }

  cout << "Team: " << manager->getTeamName() << endl;
  cout << "Conference: " << manager->getTeamConf() << endl;
  cout << "Seed: " << manager->getTeamSeed() << endl;
  cout << "Record: " << manager->getTeamWins() << '-' <<
    manager->getTeamLosses() << endl;
  if(manager->getTeamTournStatus())
  {
    cout << "Eliminated.\n";
  }
}

void Game_Interface::displayBracket()
{
  int selection = selectBracket();

  if(selection == -1)
  {
    return;
  }
  manager->selectPlayer(selection);

  cout << "Bracket: " << manager->getBracketName() << endl;
  int div = manager->getNumDiv();

  int AI = manager->getBracketAI();

  if(AI > 0 && AI < MAXAI)
  {
    cout << "Computer Generated Bracket by " << AIType[AI] << endl;
  }

  cout << "Score: " << manager->getPlayerScore() << endl;
  cout << "Score by Round:\n";

  for(int i = manager->getMaxRounds()-1; i >= 0; i--)
  {
    cout << Round[i] << ": " << manager->getCorrectInRound(i) << endl;
  }

  for(int i = manager->getFinalRounds()-1; i >= 0; i--)
  {
    cout << Final[i] << ": " << manager->getCorrectFinalRound(i) << endl;
  }

  for(int i = 0; i < div; i++)
  {
    cout << endl;
    displaySelectedDivision(i, selection);
  }

  cout << endl;
  displaySelectedDivision(-1, selection);

}

#define MAXLINES 64

void Game_Interface::displaySelectedDivision(int div, int selection)
 // selection == -1 is result
{
  // Algorithm explained in PickInt.h

  if(selection != -1)
  {
    manager->selectPlayer(selection);
  }
  else
  {
    manager->selectPlayer(-1);  // deselect the player so that the mark is
                                // always false. Also detects bugs.
  }

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
 
  if(numlines > MAXLINES)  // did not allocate enough memory
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
	  if(selection != -1)
	  {
       	    manager->selectTeamInBByLoc(div, l, j);
	  }
	  else
	  {
	    manager->selectTeamInMByLoc(div, l, j);
	  }
	  conv toConv;
	  bool empty = manager->getTeamBlank();
	  if(empty)
       	  {
            lines[k] = " ";
       	  }
	  else
       	  {
            string name = manager->getTeamName();
	    int seed = manager->getTeamSeed();

	    name = toConv.convToString(seed) + ". " + name;
	    if(selection != -1)
	    {
              if(manager->getMarkByLoc(div, l, j))
	      {
	        name = name + "*";
	      }
	    }
	    else
	    {
	      if(!empty)
	      {
		if(j != 0)
		{

		  string temp;
		  manager->selectTeamInMByLoc(div, l/2, j-1);
		  if(!manager->getTeamBlank())
		  {
		    temp = toConv.convToString(manager->getTeamScoreByLoc(div, 
			  					      l, j));
	            name = name + " " + temp;
		  }
		}
	      }
	    }
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

  cout << manager->getDivName(div);
  if(div != -1)
  {
    cout << " division";
  }
  cout << endl << endl;

  for(int z = 0; z < numlines; z++)
  {
    cout << lines[z] << endl;
  }
  cout << endl;
}

void Game_Interface::displayTourn()
{
  cout << "\n\nTournament Results.\n\n";

  int div = manager->getNumDiv();
  for(int i = 0; i < div; i++)
  {
    displaySelectedDivision(i, -1);
  }

  if(manager->getFinalStatus())
  {
    displaySelectedDivision(-1, -1);
  }
}

#define NAMELIMIT 30
#define SCORESPOT 35
void Game_Interface::displayPlayers()
{
  int players = manager->getNumPlayers();

  string out;
  out = "Bracket";
  for(int j = out.length(); j < SCORESPOT; j++)
  {
    out = out + " ";
  }
  out = out + "Score";

  cout << out << endl;

  for(int i = 0; i < players; i++)
  {
    manager->selectPlayer(i);
    out = manager->getBracketName();
    if(out.length() > NAMELIMIT)
    {
      out = out.substr(0, NAMELIMIT);
    }
    for(int i = out.length(); i < SCORESPOT; i++)
    {
      out = out + " ";
    }
    char temp[8];
    sprintf(temp, "%d", manager->getPlayerScore());
    out = out + temp;
    cout << out << endl;
  }
}

void Game_Interface::displayPlayersAltScore()
{
  int score = manager->getScoringMode();
  int neg = manager->getNegScoreMode();

  bool sameSc = false;
  bool sameNeg = false;
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
      if(selection != score)
      {
        manager->setScoringMode(selection - 1);
      }
      else
      {
	sameSc = true;
      }
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
      if(neg != 1)
      {
        manager->setNegScoreMode(1);
      }
      else
      {
	sameNeg = true;
      }
    }
    else if(selection == 2)
    {
      if(neg != 0)
      {
        manager->setNegScoreMode(0);
      }
      else
      {
	sameNeg = true;
      }
    }
    else
    {
      cout << "Invalid selection.\n";
    }
  }while(selection < 1 || selection > 2);

  if(!(sameSc && sameNeg))
  {
    manager->sortBrackets();
  }
  displayPlayers();

  if(!(sameSc && sameNeg))
  {
    manager->setScoringMode(score);
    manager->setNegScoreMode(neg);
    manager->sortBrackets();
  }
}

void Game_Interface::showScoringMode()
{
  cout << "Scoring mode is ";
  int mode = manager ->getScoringMode();
  cout << scoringMode[mode] << " and ";
  int negMode = manager ->getNegScoreMode();
  cout << negRound[negMode] << ".\n";
}

int Game_Interface::quitMenu()
{
  string input;
  bool done = false;
  int save = 0;
  do
  {
    cout << "Save Tournament? (y or n): ";
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

bool Game_Interface::clearMenu()
{
  string input;
  bool done = false;
  do
  {
    cout << endl;
    cout << "Erase everything and start again. Are you sure(y or n): ";
    cin >> input;
    cin.get();

    if(input[1] == '\0')
    {
      if((input[0] == 'y') || (input[0] == 'Y'))
      {
	if(manager->getGameComplete())
	{
	  manager->Learn();
	}

	return true;
      }
      else if((input[0] == 'n') || (input[0] == 'N'))
      {
	return false;
      }
    }

    cout << "\nInvalid selectiion.\n";
  }while(true);
}
