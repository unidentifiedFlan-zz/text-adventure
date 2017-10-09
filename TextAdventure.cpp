// Adventure.cpp 
// Main program

#include "stdafx.h"
#include "scene.h"
#include "saveGame.h"
#include "loadGame.h"
#include "adventure1.h"

int main(){

	std::vector<scene> sceneList;
	std::vector<std::vector<std::vector<bool>>> actionTracker;
	
	//Initialise using stored scene values in game-specific file and header (e.g adventure1.cpp, adventure1.h)
	setScenes(sceneList, actionTracker);
	
	sceneVersion *sceneCurrent;
	sceneCurrent = &sceneList[0].version[0];
	
	std::string action;
	
	do {

	beginLoop:
		
		
		//Check scene has been updated to account for previous actions taken
		sceneCurrent = &sceneList[sceneCurrent->getPosition()].version[sceneCurrent->updateScene(actionTracker)];
		
		sceneCurrent->sceneOutput();
		
		if (sceneCurrent->numOptions() > 0) {
			std::cin >> action;

			// Save / load option
			if (action == "save" || action == "Save") {
				saveGame(*sceneCurrent, actionTracker);
				goto beginLoop;
			}

			else if (action == "load" || action == "Load") {

				int loadPos, loadVersion;
				loadGame(loadPos, loadVersion, actionTracker);

				sceneCurrent = &sceneList[loadPos].version[loadVersion];

				goto beginLoop;
			}
		}

		//Set next scene
		sceneCurrent = &sceneList[sceneCurrent->nextScene(action, actionTracker)].version[0];
		

	} while (sceneCurrent->getPosition() != sceneList.size() - 1);

	std::cout << "Congratulations you completed the game!" << std::endl;

	return 0;
}

