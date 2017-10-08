//Program for saving progress in text adventure
#pragma once

#include "stdafx.h"
#include "scene.h"
#include "fileExists.h"
#include <fstream>

int saveGame(sceneVersion &sceneCurrent, std::vector<std::vector<std::vector<bool>>> &actionTracker);