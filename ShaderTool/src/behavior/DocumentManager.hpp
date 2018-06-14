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
		Shader default_shader;

		const string shaders_path;

	public:

		DocumentManager(string path, shared_ptr<Shader> _shader)
			:
			//data_path		(path),
			shaders_path	(path + "\\Shaders"),
			default_shader(*_shader.get())
		{
			//shader = default_shader;
			loadShader(default_shader.getPath());
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
