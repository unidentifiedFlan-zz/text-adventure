#include <sys/stat.h>
#include "stdafx.h"
#include"fileExists.h"

// Function: fileExists
/**
Check if a file exists
@param[in] filename - the name of the file to check

@return    true if the file exists, else false

*/
bool fileExists(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}