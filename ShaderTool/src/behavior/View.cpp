/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#include <View.hpp>

namespace st
{
	View::View(int width, int height, shared_ptr<string> code)
	{
		build_framebuffer();

		shader_compiler = ShaderCompiler();
		shader_program_id = shader_compiler.compileShader(code);

		glUseProgram(shader_program_id);

		glEnable(GL_CULL_FACE);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		resize(width, height);
	}

	void View::update()
	{
	}

	void View::render()
	{
		//glViewport(0, 0, framebuffer_width, framebuffer_height);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);     // Se activa el framebuffer de la textura

		//glUseProgram(cube_program_id);

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glm::mat4 model_view_matrix;

		//// Se rota el cubo y se empuja hacia el fondo a la izquierda:

		//model_view_matrix = glm::mat4();
		//model_view_matrix = glm::translate(model_view_matrix, glm::vec3(0.f, 0.f, -4.f));
		//model_view_matrix = glm::rotate(model_view_matrix, angle, glm::vec3(1.f, 2.f, 1.f));

		//glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

		//// Se renderiza el cubo en el framebuffer:

		//cube.render();

		render_framebuffer();
	}

	void View::resize(int width, int height)
	{
		window_width = width;
		window_height = height;

		glm::mat4 projection_matrix = glm::perspective(60.f, GLfloat(width) / height, 1.f, 50.f);

		glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

		glViewport(0, 0, width, height);
	}

	void View::build_framebuffer()
	{
		// Se crea un framebuffer en el que poder renderizar:
		{
			glGenFramebuffers(1, &framebuffer_id);
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
		}

		// Se crea una textura que será el búfer de color vinculado al framebuffer:
		{
			glGenTextures(1, &out_texture_id);
			glBindTexture(GL_TEXTURE_2D, out_texture_id);

			// El búfer de color tendrá formato RGB:

			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_RGB,
				framebuffer_width,
				framebuffer_height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				0
			);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		// Se crea un Z-Buffer para usarlo en combinación con el framebuffer:
		{
			glGenRenderbuffers(1, &depthbuffer_id);
			glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer_id);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, framebuffer_width, framebuffer_height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer_id);
		}

		// Se configura el framebuffer:
		{
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, out_texture_id, 0);

			const GLenum draw_buffer = GL_COLOR_ATTACHMENT0;

			glDrawBuffers(1, &draw_buffer);
		}

		// Se comprueba que el framebuffer está listo:

		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

		// Se desvincula el framebuffer:

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Se crea el quad para hacer el render del framebuffer:

		static const GLfloat triangle_positions[] =
		{
			+1.0f, -1.0f, 0.0f,
			+1.0f, +1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f
		};

		static const GLfloat triangle_texture_uv[] =
		{
			+1.0f,  0.0f,
			+1.0f, +1.0f,
			0.0f, +1.0f
		};

		glGenBuffers(1, &triangle_vbo0);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_positions), triangle_positions, GL_STATIC_DRAW);

		glGenBuffers(1, &triangle_vbo1);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_texture_uv), triangle_texture_uv, GL_STATIC_DRAW);

	}

	void View::render_framebuffer()
	{
		glViewport(0, 0, window_width, window_height);

		// Se activa el framebuffer de la ventana:

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glUseProgram(shader_program_id);

		// Se activa la textura del framebuffer:

		glBindTexture(GL_TEXTURE_2D, out_texture_id);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}