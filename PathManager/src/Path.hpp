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

		static API string getFileName(const string & path);
		static API string getChangedName(const string & path, const string & name);

		
	};
}