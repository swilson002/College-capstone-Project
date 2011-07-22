#include "Loader.h"
#include "GameInt.h"
#include "PickInt.h"
#include "TeamInt.h"
#include "AIViewer.h"

main(int argc, char *argv[])
{
  AI_Manager *gameData;
  Loader data;

  AICompute *AIData = data.loadAI();

  bool viewer = false;

  for(int i = 1; i < argc; i++)
  {
    if(argv[i][0] == '-')
    {
      if(argv[i][1] == 'm')
      {
	viewer = true;
      }
    }
  }
  
  if(viewer)
  {
    AIViewer view(AIData);
    view.viewData();
  }
  else
  {
    gameData = data.loadGame(AIData);
    bool clean;
    do
    {
      clean = false;
      if(!gameData)
      {
        gameData = new AI_Manager(AIData);
        Team_Interface teamsIn(gameData);
        teamsIn.enterData();
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
	    case 3: {
	              data.saveAIData(gameData);
	              data.clean(); 
	              clean = true; 
		      toSave = 0; 
	            }break;
	  }

        }while(toSave);
      }

      gameData->~AI_Manager();
      gameData = NULL;
    }while(clean);

  }

  AIData->~AICompute();
}
