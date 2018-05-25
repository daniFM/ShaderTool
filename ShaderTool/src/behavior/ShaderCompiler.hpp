/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <cassert>
#include <Windows.h>

#include <GL/glew.h>

#include "..\data\Shader.hpp"

using namespace std;

namespace st
{
	class ShaderCompiler
	{
		std::string   vertex_shader_code;
		std::string fragment_shader_code;

	public:

		ShaderCompiler();

		GLuint compileShader(shared_ptr<string> code);

	private:

		void   show_compilation_error(GLuint  shader_id);
		void   show_linkage_error(GLuint program_id);
	};
}
