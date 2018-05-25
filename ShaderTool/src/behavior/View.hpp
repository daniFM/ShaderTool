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

#include <Window.hpp>
#include <ShaderCompiler.hpp>

using namespace std;

namespace st
{
	class View
	{
		static const GLsizei framebuffer_width = 512;
		static const GLsizei framebuffer_height = 512;

		GLint  model_view_matrix_id;
		GLint  projection_matrix_id;

		ShaderCompiler shader_compiler;

		GLuint framebuffer_id;
		GLuint depthbuffer_id;
		GLuint out_texture_id;

		GLuint shader_program_id;//effect_program_id

		GLuint triangle_vbo0;
		GLuint triangle_vbo1;

		shared_ptr<Window> window;

		int    window_width;
		int    window_height;

	public:

		View(int width, int height, shared_ptr<string> code);

		void   update();
		void   render();
		void   resize(int  width, int height);

	private:

		void   build_framebuffer();
		void   render_framebuffer();

	};
}
