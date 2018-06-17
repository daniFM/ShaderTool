/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>

using namespace std;

namespace st
{
	/// Represents an uniform used by a shader. WIP.
	class UniformVariable
	{
		string name;
		float value;	//Variant
		string type;
	};
}
