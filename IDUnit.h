#ifndef IDUNIT
#define IDUNIT

#include <string>
using namespace std;

class IDUnit
{
 public:
  IDUnit(string newName, int ID);
  string getName();
  int getID();

 private:
  string name;
  int id;
};

#endif
