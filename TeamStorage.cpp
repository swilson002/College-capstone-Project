#include "TeamStorage.h"

// Public

TeamStorage::TeamStorage()
{
  numTeams = 0;
  for(int i = 0; i < LETTERS; i++)
  {
    IDHash[i][0] = NULL;
  }
}

TeamStorage::~TeamStorage()
{
  for(int i = 0; i < numTeams; i++)
  {
    teams[i]->~TeamData();
  }

  for(int i = 0; i < LETTERS; i++)
  {
    int j = 0;
    while(IDHash[i][j])
    {
      delete IDHash[i][j];
      j++;
    }
  }
}

int TeamStorage::addUnit(string newName, int newVisits, int roundVisitsCount,
			  int newRoundVisits[])
{

  int id = -1;
  if(numTeams < TEAMTOTAL)
  {
  
    id = numTeams;
    teams[numTeams] = new TeamData(newName, newVisits, roundVisitsCount, 
			     newRoundVisits);

    addAlias(newName, numTeams);

    numTeams++;
  }

  return id;
}

int TeamStorage::addName(string newName)
{
  if(numTeams < TEAMTOTAL)
  {

    int id = numTeams;
    teams[id] = new TeamData(newName);
  
    addAlias(newName, id);

    numTeams++;
    return id;
  }
  else
  {
    return -1;
  }
}

void TeamStorage::addAlias(string newName, int id)
{
  string entry = toCompareMode(newName);

  int index;
  if(isalpha(entry[0]))
  {
    index = entry[0] - 'A';
  }
  else
  {
    index = LETTERS -1;
  }

  int count = 0;

  bool done = false;
  do
  {
    if(count >= MAXALIAS)
    {
      done = true;
    }
    else if(IDHash[index][count] == NULL)
    {
      IDHash[index][count] = new IDUnit(entry, id);
      if(count < MAXALIAS -1)
      {
	IDHash[index][count+1] = NULL;
      }
      
      done = true;
    }
    else if(entry.compare(IDHash[index][count]->getName()) > 0)
    {
      int count2 = count +1;
      while(IDHash[index][count2] && (count2 < MAXALIAS))
      {
	count2++;
      }
      
      if(count2 != MAXALIAS)
      {
	IDHash[index][count2+1] = NULL;

	for(int i = count2; i > count; i--)
	{
	  IDHash[index][i] = IDHash[index][i-1];
	}
	
	IDHash[index][count] = new IDUnit(entry, id);
      }
      done = true;
    }
    else if(!(entry.compare(IDHash[index][count]->getName())))
    {
      done = true;
    }
    else
    {
      count++;
    }
  }while(!done);

}

TeamData *TeamStorage::getTeam(int id)
{
  TeamData *data = NULL;

  if(id >= 0 && id < numTeams)
  {
    data = teams[id];
  }

  return data;
}

int TeamStorage::getID(string name)
{
  string check = toCompareMode(name);

  int index;
  if(isalpha(check[0]))
  {
    index = check[0] - 'A';
  }
  else
  {
    index = LETTERS-1;
  }

  int id;
  int count = 0;

  bool done = false;
  do
  { 
    if(count >= MAXALIAS)
    {
      id = -1;
      done = true;
    }
    else if(IDHash[index][count] == NULL)
    {
      id = -1;
      done = true;
    }
    else if(!check.compare(IDHash[index][count]->getName()))
    {
      id = IDHash[index][count]->getID();
      done = true;
    }
    else
    {
      count++;
    }
  }while(!done);

  return id;
}

string TeamStorage::getAlias(unsigned int index1, unsigned int index2)
{
  string name = "";
  if(index1 < LETTERS)
  {
    if(index2 < MAXALIAS)
    {
      if(IDHash[index1][index2])
      {
	name = IDHash[index1][index2]->getName();
      }
    }
  }

  return name;
}

int TeamStorage::getAliasID(unsigned int index1, unsigned int index2)
{
  int id = -1;

  if(index1 < LETTERS)
  {
    if(index2 < MAXALIAS)
    {
      if(IDHash[index1][index2])
      {
	id = IDHash[index1][index2]->getID();
      }
    }
  }

  return id;
}

// Private

string TeamStorage::toCompareMode(string conv)
{
  int length = conv.length();

  string result = "";
  for(int i = 0; i < length; i++)
  {
    if(isalnum(conv[i]))
    {      
      result += toupper(conv[i]);
    }
  }

  result += '\0';

  return result;
}

int TeamStorage::getMaxSize()
{
  return numTeams;
}
