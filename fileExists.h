#pragma once

#include <sys/stat.h>
#include "stdafx.h"
#include <string>
// Function: fileExists
/**
Check if a file exists
@param[in] filename - the name of the file to check

@return    true if the file exists, else false

*/

bool fileExists(const std::string &filename);