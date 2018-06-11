/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.hpp>
#include <Window.hpp>
#include <Framebuffer.hpp>
#include <ShaderProgram.hpp>

using namespace std;

namespace st
{
	class View
	{
		static const std::string   default_shader_code;

		GLint  model_view_matrix_id;
		GLint  projection_matrix_id;

		ShaderProgram shader_program;

		Framebuffer   framebuffer;

		int    window_width;
		int    window_height;

	public:

		View(int width, int height, shared_ptr<Shader> shader);

		void   update();
		void   render();
		void   resize(int  width, int height);

	};
}
