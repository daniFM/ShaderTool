/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <GL/glew.h>

#include <string>
#include <memory>
#include <iostream>
#include <cassert>
#include <Windows.h>

//#include "..\data\Shader.hpp"
#include <Shader.hpp>

using namespace std;

namespace st
{
	class ShaderProgram
	{
		GLint shader_program_id;

		std::string   vertex_shader_code;
		std::string fragment_shader_code;

	public:

		ShaderProgram();

		GLuint compileShader(shared_ptr<Shader> shader);

		void use()
		{
			glUseProgram(shader_program_id);
		}

		void disable()
		{
			glUseProgram(0);
		}

	private:

		void   show_compilation_error(GLuint  shader_id);
		void   show_linkage_error(GLuint program_id);
	};
}
