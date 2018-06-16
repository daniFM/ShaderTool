/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/06/2018

Subject to license in LICENSE.txt

*/

#include <iostream>
#include "Path.hpp"

namespace pm
{
	void Path::test()
	{
		std::cout << "Hello from DLL!" << std::endl;
	}

	string Path::getFileName(const string & path)
	{
		return path.substr(path.find_last_of("/\\") + 1, path.length() - 1);
	}

	string Path::getChangedName(const string & path, const string & name)
	{
		string extension = path.substr(path.find_last_of("."), path.length());
		return path.substr(0, path.find_last_of("/\\") + 1) + name + extension;
	}
}