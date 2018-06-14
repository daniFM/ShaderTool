/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>
#include <vector>

#include <Shader.hpp>

using namespace std;

namespace st
{
	class DocumentManager
	{
	private:

		Shader shader;

		vector < shared_ptr <Shader > > default_shaders;

	public:

		const string shaders_path;

	public:

		DocumentManager(string path, vector < shared_ptr <Shader > > shaders)
			:
			//data_path		(path),
			shaders_path	(path + "\\Shaders"),
			default_shaders(shaders)
		{
			//shader = default_shader;
			//loadShader(default_shaders[0]->getPath());
			createFromTemplate("newShader.glsl");
		}

		bool loadShader();
		bool loadShader(string path);

		bool createFromTemplate(string name);

		bool saveShader(string name);

		void openShader();

		shared_ptr<Shader> getShader()
		{
			return make_shared<Shader>(shader);
		}

	};
}
