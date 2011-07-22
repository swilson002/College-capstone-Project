#include "Loader.h"
#include "GameInt.h"
#include "PickInt.h"
#include "TeamInt.h"

main()
{
  Player_Manager *gameData;
  Loader data;

  gameData = data.loadGame();
  bool clean;
  do
  {
    clean = false;
    if(!gameData)
    {
      Team_Interface teamsIn;
      teamsIn.enterData();
      gameData = teamsIn.getManager();
    }

    if(!(gameData->getGameMode()))
    {
      Picks_Interface pickIn;
      pickIn.addManager(gameData);

      int saveStatus;
      do
      {
        saveStatus = pickIn.makePicks();

	switch(saveStatus)
	{
	  case 1: saveStatus--;
	  case 2: data.saveGame(gameData); break;
	  default: ;
	}
      }while(saveStatus);
    }

    if(gameData->getGameMode())
    {
      Game_Interface gameIn;
      gameIn.addManager(gameData);
    
      int toSave;
      do
      {
        toSave = gameIn.playGame();
      
	switch(toSave)
	{
          case 1: toSave--;
          case 2: data.saveGame(gameData); break;
	  case 3: data.clean(); clean = true; toSave = 0; break;
	}

      }while(toSave);
    }

    gameData->~Player_Manager();
    gameData = NULL;
  }while(clean);
}
