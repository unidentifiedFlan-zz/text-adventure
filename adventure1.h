//Header file for Adventure1. setScenes is where the adventure itself is specified
#pragma once

#include "stdafx.h"
#include "scene.h"

void setScenes(std::vector<scene> &sceneList, std::vector<std::vector<std::vector<bool>>> &actionTracker);

void initialiseActionTracker(std::vector<scene> &sceneList, std::vector<std::vector<std::vector<bool>>> &actionTracker);