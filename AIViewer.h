#ifndef AIVIEWER
#define AIVIEWER

#include "AIcomp.h"
#include <iostream>
using namespace std;

#define MAXIN 255

class AIViewer
{
 private:
  AICompute *data;
  string roundName[MAXIMUMROUND];
  void viewSeedDifMatrix();
  void viewSeedMatrix();
  void viewTeamMatrix();
  void getProbability();
  void getProbabilityDif();
  void getProbabilitySeed();
  void getProbabilityTeam();
  int selectTeam();

 public:
  AIViewer(AICompute *newData);
  ~AIViewer();
  void viewData();
};

#endif
