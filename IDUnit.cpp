#include "IDUnit.h"

IDUnit::IDUnit(string newName, int ID)
{
  name = newName;
  id = ID;
}

string IDUnit::getName()
{
  return name;
}

int IDUnit::getID()
{
  return id;
}
