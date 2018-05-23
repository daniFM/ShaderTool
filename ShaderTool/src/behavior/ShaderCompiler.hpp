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
		static const std::string   vertex_shader_code;
		static const std::string fragment_shader_code;

	public:

		ShaderCompiler(shared_ptr<string> code);

		GLuint compileShader();

	private:

		void   show_compilation_error(GLuint  shader_id);
		void   show_linkage_error(GLuint program_id);
	};
}
