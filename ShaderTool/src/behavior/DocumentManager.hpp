/*

Author: Daniel Fern�ndez (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <Path.hpp>

#include <Shader.hpp>

using namespace std;

namespace st
{
	class DocumentManager
	{
	private:

		Shader shader;

		vector < shared_ptr <Shader > > default_shaders;

		string text_editor;

	public:

		const string shaders_path;

	public:

		DocumentManager(string path, string editor, vector < shared_ptr <Shader > > shaders)
			:
			shaders_path	(path + "\\Shaders"),
			text_editor     (editor),
			default_shaders (shaders)
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
