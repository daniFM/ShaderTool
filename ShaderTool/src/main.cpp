/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

//#include <GL/glew.h>
#include <UIController.hpp>
#include <iostream>
#include <cassert>

//#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>

//#include <DocumentManager.hpp>
//#include <Window.hpp>
//#include <View.hpp>

using namespace std;
//using namespace sf;
//using namespace st;
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

	////Window window(1024, 768, "Shader Tool", true);
	//sf::Window window(VideoMode(1024, 768), "Shader Tool", Style::Default, ContextSettings(32));
	//window.setVerticalSyncEnabled(true);

	//Init OpenGL

	/*GLenum glew_initialization = glewInit();
	assert(glew_initialization == GLEW_OK);*/

	//Set document

	//DocumentManager document_manager;
	//document_manager.loadShader(shader_path);	//"..\\assets\\example_texture.tga"
	//
	//View view(1024, 768, document_manager.getShader());

	try
	{
		nanogui::init();
		{

			st_front::UIController ui;

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

	/*bool running = true;

	do
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				running = false;
				break;
			}

			case Event::Resized:
			{
				Vector2u window_size = window.getSize();

				view.resize(window_size.x, window_size.y);

				break;
			}
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);

		view.update();
		view.render();

		window.display();

	} while (running);

	return 0;*/
}