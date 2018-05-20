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
	class ShaderCompiler
	{

	public:

		ShaderCompiler()
		{
		}

		void compileShader(Shader shader);
	};
}
