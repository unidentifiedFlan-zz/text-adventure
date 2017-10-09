//Adventure1: Player is trapped in a room and must use all 100% of their cunning to get out


#include "stdafx.h"
#include "adventure1.h"

void setScenes(std::vector<scene> &sceneList, std::vector<std::vector<std::vector<bool>>> &actionTracker) {

	std::vector<scene*> tempList;


	//List all scenes here:
	scene intro(tempList);
	scene door(tempList);
	scene table(tempList);
	scene end(tempList);

	//Need to add the following version to the end scene so sceneCurrent in main prgm has a sceneVersion to transition to
	//at the end of the game.
	sceneVersion endV0(end.position, end.version.size(), "", false, { {door.position,1,1} }, 1);

	end.version.push_back(endV0);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//How to: create scene content:
	//
	//Each scene contains versions of that scene representing the scene at different stages of the story. The
	//constructor takes the following form for creating a version called VER in scene SCE:
	//
	//sceneVersion VER(SCE.position, 
	//                 SCE.version.size(), 
	//                 string(description of scene),
	//                 bool(is VER the final version of SCE?), 
	//                 std::vector<std::vector<int>> (matrix of action co-ords {...{scene, version, option} ...} 
	//                       indicating which actions must be complete for VER to be updated to the next version), 
	//                 int(the version number of the next version once VER has been updated));
	//
	//Each scene version construction MUST BE followed by: SCE.version.push_back(VER);
	//

	//In each version are options that can be taken by the player. An option OPT is constructed as follows:
	//
	//option OPT(SCE.position, 
	//			 VER.getVer() - 1, 
	//           int (option number),
	//           string( option description), 
	//           string (output after option is taken), 
	//           std::vector<std::string> (list of valid actions corresponding to this option),
	//           bool (Does the scene change if OPT chosen?), 
	//           int (scene list position of next scene if scene change is true)); 
	//          
	//
	//Each option construction MUST BE followed by: SCE.version[option number].addOption(VER);



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////Intro//////////////////////////////////////////////////////////////////////////////////////////////////

	sceneVersion intro0(intro.position, intro.version.size(),
		"Welcome to ROOM ESCAPE 2017! Type 'save' to save the game, or 'load' to load a previous save.",
		false, { {0,0,0} }, 0);

	intro.version.push_back(intro0);

	option start(intro.position, intro0.getVer() - 1, 0, "Type 'start' to continue.",
		"", { "start", "1" }, true, door.position);

	intro.version[0].addOption(start);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////door V0: Initial door scene////////////////////////////////////////////////////////////////////////////////

		//Co-ords for updateTracker entries are {scene position of req. action, version num..., option num...}, 
		//all starting from 0
	std::vector<std::vector<int>> updateTr = { {table.position, 0, 0} };

	sceneVersion doorV0(door.position, door.version.size(),
		"Before you is a door. Find a way to open it. Behind you is a table. Would you like to turn toward the table?",
		false, updateTr, 1);

	door.version.push_back(doorV0);

	updateTr.clear();

	/////door: V0 OPTION 1 
	//Recognised inputs
	std::vector<std::string> valActions = { "1", "Yes", "yes" };

	option doorV0O0(door.position, doorV0.getVer() -1, 0, "Yes",
		"You move toward the table.", valActions, true, table.position);

	door.version[0].addOption(doorV0O0);

	valActions.clear();

	//////door: V0 OPTION 2
	valActions = { "2", "no", "No" };

	option doorV0O1(door.position, doorV0.getVer() - 1, 1, "No",
		"You continue to watch the door...", valActions, false, door.position);

	door.version[0].addOption(doorV0O1);

	valActions.clear();

	////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////door V1: After picking up key from table:///////////////////////////////////////////////////////////

	updateTr = { {table.position,0,0} };

	sceneVersion doorV1(door.position, door.version.size(),
		"You turn to the door. Find a way to open it. Behind you is a table.",
		true, updateTr, 1);

	door.version.push_back(doorV1);

	updateTr.clear();

	//door: version1, OPTION 1
	valActions = { "1", "unlock", "Unlock", "use key", "Use key" };

	option doorV1O0(door.position, 1, doorV1.getVer() - 1, "Unlock door with key",
		"You open the door and exit the room.",
		valActions, true, end.position);

	door.version[1].addOption(doorV1O0);

	valActions.clear();

	//door: Version1, OPTION 2
	valActions = { "2", "table", "Table" };

	option doorV1O1(door.position, doorV1.getVer() - 1, 1, "Turn toward table",
		"You turn back toward the table.", valActions, true, table.position);

	door.version[1].addOption(doorV1O1);

	valActions.clear();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////table V0///////////////////////////////////////////////////////////////////////////////////////////////

	updateTr = { {table.position,0,0} };

	sceneVersion tableV0(table.position, table.version.size(),
		"In front of you is the table. On top of the table is a key.",
		false, updateTr, 1);

	table.version.push_back(tableV0);

	updateTr.clear();

	//table: V0 OPTION 1
	valActions = { "1", "key", "Key", "pick up key", "Pick up key" };

	option tableV0O0(table.position, tableV0.getVer() - 1, 0, "Pick up key",
		"You pick up the key.", valActions, false, table.position);

	table.version[0].addOption(tableV0O0);

	valActions.clear();

	//table: V0 OPTION 2
	valActions = { "2", "door", "Door" };

	option tableV0O1(table.position, tableV0.getVer() - 1, 1, "Turn toward door",
		"You turn back towards to the door.", valActions, true, door.position);

	table.version[0].addOption(tableV0O1);

	valActions.clear();

	//////////////////////////////////////////////////////////////////////////////////////////////////////
		/////table: V1 after key has been picked up/////////////////////////////////////////////////////////////

	updateTr = { {table.position,0,0} };

	sceneVersion tableV1(table.position, table.version.size(),
		"The table is now empty. Turn toward the door?",
		true, updateTr, 1);

	table.version.push_back(tableV1);

	updateTr.clear();

	//table: V1 OPTION 1
	valActions = { "1", "y", "Y", "yes", "Yes" };

	option tableV1O0(table.position, tableV1.getVer() - 1, 0, "Yes",
		"", valActions, true, door.position);

	table.version[1].addOption(tableV1O0);

	valActions.clear();

	//table : V1 OPTION 2
	valActions = { "2", "n", "N", "No", "no" };

	option tableV1O1(table.position, tableV1.getVer() - 1, 1, "No",
		"You continue to watch the table...", valActions, false, table.position);

	table.version[1].addOption(tableV1O1);

	valActions.clear();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	for (std::vector<scene*>::iterator it = tempList.begin(); it != tempList.end(); it++) {

		sceneList.push_back(**it);
		
	}


	initialiseActionTracker(sceneList, actionTracker);
	
}



void initialiseActionTracker(std::vector<scene> &sceneList, std::vector<std::vector<std::vector<bool>>> &actionTracker) {

	std::vector<std::vector<bool>> tempMatrix;

	for (unsigned i = 0; i < sceneList.size(); i++) {

		std::vector<bool> tempVector;

		for (unsigned j = 0; j < sceneList[i].version.size(); j++) {
			bool tempAction = false;
			tempVector.clear();
			tempVector.assign(sceneList[i].version[j].getSize(), tempAction);
			tempMatrix.push_back(tempVector);


		}

		actionTracker.push_back(tempMatrix);
	}
}