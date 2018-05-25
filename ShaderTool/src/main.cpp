/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#include <GL/glew.h>
#include <iostream>
#include <cassert>

#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <DocumentManager.hpp>
#include <Window.hpp>
#include <View.hpp>

using namespace std;
using namespace st;

int main(int number_of_arguments, char * arguments[])
{
	cout << number_of_arguments << " Arguments:" << endl;
	for (int i = 0; i < number_of_arguments; i++)
	{
		cout << arguments[i] << endl;
	}

	string shader_path = "\\Shaders";

	if (number_of_arguments > 1)
	{
		shader_path = arguments[1];
	}

	//Shader active_shader(shader_path)
	DocumentManager document_manager;
	document_manager.loadShader(shader_path);

	//Window window()

	View(1024, 768, document_manager.getShader()->getCode());

	getchar();

	return 0;
}