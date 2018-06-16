/*

Author: Daniel Fern�ndez (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#include <iostream>
#include <fstream>
#include <cstdio>

#include "DocumentManager.hpp"

namespace st
{
	bool DocumentManager::loadShader()
	{
		return loadShader(shader.getPath());
	}

	bool DocumentManager::loadShader(string path)
	{
		cout << "Openning file: " << path << endl;

		bool success = true;

		ifstream infile(path);
		string shader_str(
			(istreambuf_iterator<char>(infile)),
			istreambuf_iterator<char>()
		);

		if (infile.good())
		{
			shader = Shader(path, path, shader_str);
		}
		else
		{
			//cout << "File not found, creating new file" << endl;

			//path = shaders_path + "\\newShader.glsl";
			////path = default_shaders[0]->getPath();
			//cout << "Creating new file in " << path << endl;

			//string new_shader_str = *default_shaders[0]->getCode().get();

			//ofstream file(path);
			//file << new_shader_str;

			//shader_str = new_shader_str;

			//Get default template

			string name = path.substr(path.find_last_of("/\\") + 1, path.length() - 1);

			createFromTemplate(name);
		}

		return success;
	}

	bool DocumentManager::createFromTemplate(string name)
	{
		bool success = true;

		ifstream t(default_shaders[0]->getPath());
		string new_shader_str(
			(istreambuf_iterator<char>(t)),
			istreambuf_iterator<char>()
		);

		if (!t.good())
		{
			cout << "ERROR: Could not find shader template" << endl;
			success = false;
		}
		else
		{
			//Create new shader file

			/*path = path.substr(0, path.find_last_of("/\\"));
			path += shaders_path + "\\newShader.glsl";*/
			string path = shaders_path + "\\" + name;
			cout << "Creating new file in " << path << endl;
			ofstream file(path);
			file << new_shader_str;

			shader = Shader(name, path, new_shader_str);
		}

		return success;
	}

	bool DocumentManager::saveShader(string name)
	{
		bool success = true;

		int result;
		string oldname = shader.getPath();
		string newname = oldname.substr(0, oldname.find_last_of("/\\") + 1) + name + ".glsl";
		result = rename(oldname.c_str(), newname.c_str());

		if (result == 0)
		{
			success = true;
			puts("File successfully renamed");

			shader.setPath(newname);

			openShader();
		}
		else
		{
			success = false;
			perror("Error renaming file");
		}

		return success;
	}

	void DocumentManager::openShader()
	{
		string command = "start notepad.exe " + shader.getPath();
		string command;
		if (text_editor == "notepad.exe")
			command = "start " + text_editor + " " + shader.getPath();
		else
			command = "\"\"" + text_editor + "\" \"" + shader.getPath() + "\"\"";

		cout << command << endl;
		system(command.c_str());
	}

}
