#ifndef DATAUNIT
#define DATAUNIT

class DataUnit
{
 public:
  DataUnit();
  DataUnit(int wins, int games);
  void addWin();
  void addLoss();
  int getWins();
  int getGames();

 private:
  int winRecord;
  int gameTotal;
};
#endif
