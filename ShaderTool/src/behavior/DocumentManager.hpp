/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>

#include <Shader.hpp>

using namespace std;

namespace st
{
	class DocumentManager
	{
	private:

		Shader shader;

	public:

		const string data_path;
		const string shaders_path;
		const string textures_path;

	public:

		DocumentManager(string path)
			:
			data_path(path),
			shaders_path(path + "\\Shaders"),
			textures_path(path + "\\Textures")
		{
		}

		bool loadShader();
		bool loadShader(string path);

		bool saveShader(string name);

		void openShader();

		shared_ptr<Shader> getShader()
		{
			return make_shared<Shader>(shader);
		}

	};
}
