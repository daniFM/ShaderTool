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
	class Shader
	{
		string title;
		string path;
		string shader_text;

	public:

		Shader()
		{
		}

		///Loads a shader from a file
		Shader(string path);
	};
}
