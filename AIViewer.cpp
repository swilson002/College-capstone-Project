#include "AIViewer.h"

//Public

#define MATRIXSIZE 8

AIViewer::AIViewer(AICompute *newData)
{
  data = newData;

  roundName[0] = "Tournaments Won: ";
  roundName[1] = "Championship Visits: ";
  roundName[2] = "Final Four Visits: ";
  roundName[3] = "Elite 8 Visits: ";
  roundName[4] = "Sweet Sixteen Visits: ";
  roundName[5] = "Second round Visits: ";
  roundName[6] = "";

  data->addTeamName("000Newcomer000");
}

AIViewer::~AIViewer()
{
  data = NULL;
}

void AIViewer::viewData()
{
  if(data)
  {
    bool done = false;
    do
    {
      cout << endl;
      cout << "Select Option.\n";
      cout << "1. View Array of difference of seeds.\n";
      cout << "2. View Seed Matrix.\n";
      cout << "3. View Team Matrix.\n";
      cout << "4. Show Probability of Match.\n";
      cout << "5. Quit.\n";
      cout << "Selection: ";

      int selection;

      cin >> selection;
      cin.get();

      cout << endl;

      switch(selection)
      {
        case 1: viewSeedDifMatrix(); break;
        case 2: viewSeedMatrix(); break;
        case 3: viewTeamMatrix(); break;
        case 4: getProbability(); break;
        case 5: done = true; break;
        default: cout << "Invalid Selection.\n\n";
      }

    }while(!done);
  }
}

//Private

void AIViewer::viewSeedDifMatrix()
{
  int size = data->getDifMaxSize();

  int final = 0;

  while(final <= size)
  {
    int start = final;

    int count = size - final;
    final += MATRIXSIZE;

    if(count > MATRIXSIZE)
    {
      count = MATRIXSIZE;
    }

    int pos = start;
    for(int i = 0; i < count; i++)
    {
      cout << pos << '\t';
      pos ++;
    }
    cout << endl;
    pos = start;

    for(int i = 0; i < count; i++)
    {
      cout << data->getWinsDif(pos) << '/' << data->getGamesDif(pos) << '\t';
      pos++;
    }
    cout << endl << endl;
  }
}

void AIViewer::viewSeedMatrix()
{
  int size = data->getMaxSize();

  int final = 1;

  while(final < size)
  {
    int start = final;
    int count = size - final;

    final += MATRIXSIZE;
 
    if(count > MATRIXSIZE)
    {
      count = MATRIXSIZE;
    }

    int pos = start;
    for(int i = 0; i < count; i++)
    {
      cout << '\t' << pos;
      pos ++;
    }
    cout << endl;
    pos = start;

    for(int j = 1; j < size; j++)
    {
      cout << j;

      pos = start;
      for(int i = 0; i < count; i++)
      {
        cout << '\t' << data->getWins(j, pos) << '/' << data->getGames(j, pos);
        pos++;
      }
      cout << endl;
    }
    cout << endl;
  }
}

void AIViewer::viewTeamMatrix()
{
  int id = selectTeam();

  if(id < 0)
  {
    cout << "No such team exists in data.\n";
  }
  else
  {
    cout << data->getTeamName(id) << endl;

    cout << "Record in Tournament: ";

    int wins = data->getTeamTotalWins(id);
    int losses = data->getTeamTotalGames(id) - wins;

    cout << wins << '-' << losses << endl;
    cout << "Tournament visits: " << data->getTeamVisits(id) << endl;

    cout << "Average Wins: " << (int)(data->getTeamAverageWins(id) + .5) << endl;

    int i = 0;

    while(roundName[i][0] != '\0')
    {
      cout << roundName[i] << data->getTeamRoundVisits(id, i) << endl;
      i++;
    }

    int size = data->getTeamMaxSize(id);

    int final = 1;

    while(final < size)
    {
      int start = final;

      int count = size - final;

      final += MATRIXSIZE;

      if(count > MATRIXSIZE)
      {
        count = MATRIXSIZE;
      }

      int pos = start;
      for(int i = 0; i < count; i++)
      {
        cout << '\t' << pos;
        pos ++;
      }
      cout << endl;
      pos = start;

      for(int j = 1; j < size; j++)
      {
        cout << j;

	pos = start;
        for(int i = 0; i < count; i++)
        {
          cout << '\t' << data->getTeamWins(id, j, pos) << '/' 
	       << data->getTeamGames(id, j, pos);
          pos++;
        }
        cout << endl;
      }
      cout << endl;
    }
  }
}

void AIViewer::getProbability()
{
  bool done;
  do
  {
    done = true;
    cout << "Pick Method of calculating Probability.\n";
    cout << "1. By Difference of seeds.\n";
    cout << "2. By Seeds.\n";
    cout << "3. By Team.\n";
    cout << "Selection (0 to cancel): ";

    int selection;
    cin >> selection;
    cin.get();

    cout << endl;

    switch(selection)
    {
      case 0: break;
      case 1: getProbabilityDif(); break;
      case 2: getProbabilitySeed(); break;
      case 3: getProbabilityTeam(); break;
      default: done = false;  cout << "Invalid Selection.\n\n"; break;
    }
  }while(!done);
}

void AIViewer::getProbabilityDif()
{
  int seed1, seed2;

  do
  {
    cout << "Select Seed of First Team: ";
    cin >> seed1;
    cin.get();

    if(seed1 <=0)
    {
      cout << "Invalid Seed.\n";
    }
  }while(seed1 <=  0);

  do
  {
    cout << "Select Seed of Second Team: ";
    cin >> seed2;
    cin.get();

    if(seed2 <= 0)
    {
      cout << "Invalid Seed.\n";
    }
  }while(seed2 <= 0);

  Team *team1 = new Team("", 0, "", seed1, 0, 0);
  Team *team2 = new Team("", 0, "", seed2, 0, 0);

  double prob = data-> computeProbDif(team1, team2);

  prob  *= 100;

  cout << "The probability of the the Team with seed " << seed1 
       << " winning ";
  cout << "is: " << prob << "%.\n";
}

void AIViewer::getProbabilitySeed()
{
  int seed1, seed2;

  do
  {
    cout << "Select Seed of First Team: ";
    cin >> seed1;
    cin.get();

    if(seed1 <=0)
    {
      cout << "Invalid Seed.\n";
    }
  }while(seed1 <= 0);

  do
  {
    cout << "Select Seed of Second Team: ";
    cin >> seed2;
    cin.get();

    if(seed2 <= 0)
    {
      cout << "Invalid Seed.\n";
    }
  }while(seed2 <= 0);

  Team *team1 = new Team("", 0, "", seed1, 0, 0);
  Team *team2 = new Team("", 0, "", seed2, 0, 0);

  double prob = data->computeProb(team1, team2);

  prob *= 100;

  cout << "The probability of the the Team with seed " << seed1 
       << " winning ";
  cout << "is: " << prob << "%.\n";
}

void AIViewer::getProbabilityTeam()
{
  int seed1, seed2;
  int id1, id2;

  id1 = selectTeam();

  if(id1 < 0)
  {
    cout << "Team does not exist in data.\n";
    return;
  }

  do
  {
    cout << "Select Seed of " << data->getTeamName(id1) << ": ";
    cin >> seed1;
    cin.get();

    if(seed1 <=0)
    {
      cout << "Invalid Seed.\n";
    }
  }while(seed1 <= 0);

  id2 = selectTeam();

  if(id2 < 0)
  {
    cout << "Team does not exist in data.\n";
    return;
  }

  do
  {
    cout << "Select Seed of " << data->getTeamName(id2) << ": ";
    cin >> seed2;
    cin.get();

    if(seed2 <= 0)
    {
      cout << "Invalid Seed.\n";
    }
  }while(seed2 <= 0);

  Team *team1 = new Team("", id1, "", seed1, 0, 0);
  Team *team2 = new Team("", id2, "", seed2, 0, 0);

  double prob = data->computeProbTeam(team1, team2);

  prob *= 100;

  cout << "The probability of " << data->getTeamName(id1) << " winning ";
  cout << "is: " << prob << "%.\n";
}

int AIViewer::selectTeam()
{
  cout << "Insert Name of Team: ";

  char input[MAXIN];

  cin.getline(input, MAXIN);

  return data->getTeamID(input);
  
}
