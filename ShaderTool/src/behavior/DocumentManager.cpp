/*

Author: Daniel Fernández (https://github.com/daniFM)
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
			//while (!infile.eof()) // To get you all the lines.
			//{
			//	getline(infile, shader_str); // Saves the line in STRING.
			//	cout << shader_str; // Prints our STRING.
			//}
		}
		else
		{
			cout << "File not found, creating new file" << endl;

			//Get default template

			ifstream t(shaders_path + "\\defaultShader.glsl");
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
				path = shaders_path + "\\newShader.glsl";
				cout << "Creating new file in " << path << endl;
				//cout << "With template " << new_shader_str << endl;
				ofstream file(path);
				file << new_shader_str;

				shader_str = new_shader_str;
			}
		}

		if(success)
		{
			shader = Shader(path, path, shader_str);
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
		system(command.c_str());
	}

}
