/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#include <UIController.hpp>
#include <iostream>
#include <cassert>

#include <DocumentManager.hpp>

using namespace std;
using namespace st;
using namespace st_front;

int main(int number_of_arguments, char * arguments[])
{
	//Check arguments

	cout << number_of_arguments << " Arguments:" << endl;
	for (int i = 0; i < number_of_arguments; i++)
	{
		cout << arguments[i] << endl;
	}

	// Están mal
	string shader_path = "\\Shaders";
	string texture_path = "\\Textures";

	if (number_of_arguments > 1)
	{
		shader_path = arguments[1];
	}
	if (number_of_arguments > 2)
	{
		texture_path = arguments[2];
	}

	//Set document

	shared_ptr < DocumentManager > document_manager = make_shared<DocumentManager>();
	document_manager->loadShader(shader_path);	//"..\\assets\\example_texture.tga"
	
	try
	{
		nanogui::init();
		{

			st_front::UIController ui(document_manager);

			ui.drawAll();
			ui.setVisible(true);

			nanogui::mainloop();

		}
		nanogui::shutdown();
	}
	catch (const std::runtime_error & error)
	{
		std::cerr << "Uncaught exception at main(): " << error.what() << std::endl;

		return -1;
	}

	return 0;

}