/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#include <iostream>
#include <fstream>

#include "DocumentManager.hpp"

namespace st
{
	bool DocumentManager::loadShader(string path)
	{
		//path += "\\newShader.glsl";

		cout << "Openning file: " << path << endl;

		bool success = true;

		ifstream infile(path);
		string shader_str(
			(istreambuf_iterator<char>(infile)),
			istreambuf_iterator<char>()
		);

		if (infile.good())
		{
			while (!infile.eof()) // To get you all the lines.
			{
				getline(infile, shader_str); // Saves the line in STRING.
				cout << shader_str; // Prints our STRING.
			}
		}
		else
		{
			cout << "File not found, creating new file" << endl;

			//Get default template

			ifstream t("..\\Shaders\\defaultShader.glsl");
			string new_shader_str(
				(istreambuf_iterator<char>(t)),
				 istreambuf_iterator<char>()
			);

			//Create new shader file

			path = path.substr(0, path.find_last_of("/\\"));
			path += "\\Shaders\\newShader.glsl";
			cout << "Creating new file in " << path << endl;
			//cout << "With template " << new_shader_str << endl;
			ofstream file(path);
			file << new_shader_str;

			shader_str = new_shader_str;
		}

		if(success)
		{
			shader = Shader(path, path, shader_str);

			string command = "start notepad.exe " + path;
			system(command.c_str());
		}

		return success;
	}
}
