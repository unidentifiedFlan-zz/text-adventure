//Program for saving text adventure

#include "saveGame.h"
#include "stdafx.h"
#include "scene.h"
#include "fileExists.h"
#include <fstream>

int saveGame(sceneVersion &sceneCurrent, std::vector<std::vector<std::vector<bool>>> &actionTracker) {


	std::string filename;
	bool fileCheck;
	
startSave:

	filename.clear();

	std::cout << "Please enter a save file name or type 'exit' to exit:" << std::endl;

	std::cin >> filename;

	if (filename == "exit") {
		std::cout << std::endl;
		return 0;
	}
		

	filename.append(".txt");

	fileCheck = fileExists(filename);

	if (fileCheck == true) {

		std::string confirm;

		std::cout << filename << 
			" already exists. Would you like to overwrite it? (Y/N)" << std::endl;

		std::cin >> confirm;

		if (confirm == "n" || confirm == "N")
			goto startSave;
		if (confirm == "y" || confirm == "Y")
			goto saving;
		else
			return 0;
	}

	saving: 
	std::fstream save;
	save.open(filename, std::fstream::out | std::fstream::trunc);

	if (save.good() == false) {
		save.close();
		std::cout << "Save file no good.";
		goto startSave;
	}

	save << sceneCurrent.position << "\t" << sceneCurrent.versionNumber << std::endl;

	for (unsigned int i = 0; i < actionTracker.size(); i++) {

		for (unsigned int j = 0; j < actionTracker[i].size(); j ++) {

			for (unsigned int k = 0; k < actionTracker[i][j].size(); k++) {

				save << actionTracker[i][j][k] << "\t";

				if (k == actionTracker[i][j].size() - 1)
				save << std::endl;

			}

		}


	}

	save.close();

	std::cout << "The game has saved successfully." << std::endl << std::endl;

		return 0;

}