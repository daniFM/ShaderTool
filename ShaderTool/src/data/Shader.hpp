/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>

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

		Shader(string title, string path, string shader_text)
			:
			title(title),
			path(path),
			shader_text(shader_text)
		{
		}

		string getTitle()
		{
			return title;
		}
		string getPath()
		{
			return path;
		}
		shared_ptr<string> getCode()
		{
			return make_shared<string>(shader_text);
		}
	};
}
