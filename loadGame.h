//Program for loading progress in text adventure
#pragma once

#include "stdafx.h"
#include "scene.h"
#include "fileExists.h"
#include <fstream>

int loadGame(int &loadPos, int &loadVersion, std::vector<std::vector<std::vector<bool>>> &actionTracker);