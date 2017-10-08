//scene.h

#pragma once

#include "stdafx.h"

#include <string>
#include <vector>
#include <iostream>

class option {
	int position;
	int version;
	int number;

	std::string description;
	std::string output;
	std::vector<std::string> possibleAction;
	bool sceneChange;
	int nextScene;

public:
	option(int pos, int ver, int num, std::string descrip, std::string out, std::vector<std::string> valActs,
		bool chnge, int Nxt, std::vector<std::vector<std::vector<bool>>> &actionTracker);

	int consequence(int positionNow, int versionNow, int i, std::vector<std::vector<std::vector<bool>>> &actionTracker);

	bool actionValid(std::string action, int i);

	std::string getDescription() {

		return description;
	}

};



class sceneVersion {
	int position;
	int versionNumber;
	bool finalVersion = false;
	std::string description;
	std::vector<std::vector<int>> updateTracker;
	int nextVersion;
	std::vector<option> options;

public:
	sceneVersion(int pos, int vNum, std::string Descrip, bool fnalV, std::vector<std::vector<int>> trackr, int NxtV);

	int sceneVersion::updateScene(std::vector<std::vector<std::vector<bool>>> &actionTracker);

	int nextScene(std::string action, std::vector<std::vector<std::vector<bool>>> &actionTracker);

	void sceneOutput();

	friend int saveGame(sceneVersion &sceneCurrent, std::vector<std::vector<std::vector<bool>>> &actionTracker);

	int getPosition() {

		return position;
	}
	int getVer() {
		return versionNumber;
	}

	void addOption(option &newOption) {

		options.push_back(newOption);
	}

	int getSize() {
		return options.size();
	}
};



struct scene {
	std::string description;
	int position;
	std::vector<sceneVersion> version;

	scene(std::vector<scene*> &sceneList);
};

