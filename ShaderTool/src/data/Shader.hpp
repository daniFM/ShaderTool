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
	/// Data class that contains the code of a shader.
	class Shader
	{
		string title;
		string path;
		string shader_text;

	public:

		Shader() = default;

		/// Creates a new shader.
		/// @param tile Shader name.
		/// @param path Path to the shader file.
		/// @param shader_text Code of the shader.
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

		void setPath(string _path)
		{
			path = _path;
		}
	};
}
