// Scenes.cpp : consequences of player choosing a particular option 
// Big issue is what is accepted as an input action. Find a way to expand possible input
// options using vector<vector<string>> possibleAction


#include "stdafx.h"
#include "scene.h"

scene::scene(std::vector<scene*> &sceneList) {

	position = sceneList.size();
	sceneList.push_back(this);

}

sceneVersion::sceneVersion(int pos, int vNum, std::string Descrip, bool fnalV, 
	std::vector<std::vector<int>> trackr, int NxtV) {

	position = pos;
	versionNumber = vNum;

	description = Descrip;
	finalVersion = fnalV;
	updateTracker = trackr;
	nextVersion = NxtV;
};



int sceneVersion::nextScene(std::string action, std::vector<std::vector<std::vector<bool>>> &actionTracker) {

	bool actionCheck = false;
	
	//Looping through all possible options for given scene to find match with input option chosen by player
	for (unsigned i = 0; i < options.size(); i++) {

		bool optionCheck = options[i].actionValid(action, i);

		if (optionCheck == true) {
			
			int newScenePos = options[i].consequence(position, versionNumber, i, actionTracker);
			
			return newScenePos;

		}

	}
	
	//After looping through all other options, if there is no progress assume input invalid
	std::cout << "Invalid input." << std::endl;

	return position;
};



void sceneVersion::sceneOutput() {

	int k = options.size();

	std::cout << description << std::endl;

	for (int i = 0; i < k; i++) {
		std::cout << options[i].getDescription() << std::endl;
	}
}



//Function to check whether the scene being entered should be updated given actions previously
//taken in this or other scenes
int sceneVersion::updateScene(std::vector<std::vector<std::vector<bool>>> &actionTracker) {


	//Check whether scene can be updated
	if (finalVersion == true)
		return versionNumber;


	//updateTracker is a vector of co-ordinates representing point in row of actionTracker tensor. It represents
	//a particular version of that scene. FOR iterates through all versions of current scene to find which version to 
	//update to
	for (unsigned int n = 0; n < updateTracker.size(); n++) {
		
		if (actionTracker[updateTracker[n][0]][
			updateTracker[n][1]][updateTracker[n][2]] == false)
			
			return versionNumber;

	}

	return nextVersion;

};



option::option(int pos, int ver, int num, std::string descrip, std::string out, std::vector<std::string> valActs,
	bool chnge, int Nxt) {

	position = pos;
	version = ver;
	number = num;

	description = "(";
	description += std::to_string(num+1);
	description += ") ";
	description += descrip;

	output = out;
	possibleAction = valActs;
	sceneChange = chnge;
	nextScene = Nxt;

};



int option::consequence( int positionNow, int versionNow, int i, std::vector<std::vector<std::vector<bool>>> &actionTracker) {

	std::cout << output << std::endl;
	
	//Update complete to signal that this action has been taken. Later
	//scenes may react to this action having been taken 
	actionTracker[positionNow][versionNow][i] = true;
	
	if (sceneChange == true) {

		return nextScene;
	}

	return positionNow;
};



//Check input action matches one of the valid pre-determined actions
bool option::actionValid(std::string action, int i) {

	bool check = false;

	for (unsigned j = 0; j < possibleAction.size(); j++) {
		if (action == possibleAction[j])
		{
			check = true;
			return check;
		}
	}

	return check;
};