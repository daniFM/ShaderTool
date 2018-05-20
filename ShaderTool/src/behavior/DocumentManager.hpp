/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>

#include "data\Shader.hpp"

using namespace std;

namespace st
{
	class DocumentManager
	{
		Shader shader;

	public:

		DocumentManager()
		{
		}

		bool loadShader(string path);
		bool saveShader(string path);
	};
}
