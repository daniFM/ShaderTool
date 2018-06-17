/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>

#include "Config.hpp"

using namespace std;

namespace pm
{
	class Path
	{
	public:

		void API test();

		/// Gets a path and returns the file name with the extension.
		/// @param path Path to extract the name from.
		static API string getFileName(const string & path);
		/// Gets a path and a file name and returns a new path with the new name.
		/// @param path Path with a filename and extension to be changed.
		/// @param name Name of the new file. Must not contain the file extension.
		static API string getChangedName(const string & path, const string & name);

		
	};
}