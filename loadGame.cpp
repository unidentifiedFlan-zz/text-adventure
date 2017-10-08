//Program for loading text adventure

#include "loadGame.h"
#include "stdafx.h"
#include "scene.h"
#include "fileExists.h"
#include <fstream>

struct wear {
	bool complete;
};

int loadGame(int &loadPos, int &loadVersion, std::vector<std::vector<std::vector<bool>>> &actionTracker) {


	std::string filename;
	bool fileCheck;

startLoad:

	filename.clear();

	std::cout << "Please enter a saved file name to load or type 'exit' to exit:" << std::endl;

	std::cin >> filename;

	if (filename == "exit") {
		std::cout << std::endl;
		return 0;
	}


	filename.append(".txt");

	fileCheck = fileExists(filename);

	if (fileCheck == false) {

		std::string confirm;

		std::cout << filename << " does not exist." << std::endl;

		goto startLoad;
	}

	std::fstream load;
	load.open(filename, std::fstream::in);

	if (load.good() == false) {
		load.close();
		std::cout << "Save file corrupted.";
		goto startLoad;
	}

	load >> loadPos >> loadVersion;

	for (unsigned int i = 0; i < actionTracker.size(); i++) {
	
		for (unsigned int j = 0; j < actionTracker[i].size(); j++) {

			for (unsigned int k = 0; k < actionTracker[i][j].size(); k++) {
				bool loadVal;

				load >> loadVal;
				actionTracker[i][j][k] = loadVal;

			}

		}


	}

	load.close();

	std::cout << "The game has loaded successfully." << std::endl << std::endl;

	return 0;

}