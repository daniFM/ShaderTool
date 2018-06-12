
#include <Canvas.hpp>
#include <GLTexture.hpp>

namespace st_front
{
	Canvas::Canvas(Widget *parent) : nanogui::GLCanvas(parent)
	{
		using namespace nanogui;

		mShader.init(
			/* An identifying name */
			"a_simple_shader",

			/* Vertex shader */
			"#version 330\n"
			"layout (location = 0) in vec3 vertex_coordinates;\n"
			"layout (location = 1) in vec2 vertex_texture_uv;\n"
			"out vec2 texture_uv;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(vertex_coordinates, 1.0);\n"
			"   texture_uv  = vertex_texture_uv;\n"
			"}",

			/* Fragment shader */
			"#version 330\n"
			"uniform sampler2D sampler2d;\n"
			"in  vec2 texture_uv;\n"
			"out vec4 fragment_color;\n"
			"void main()\n"
			"{\n"
			"    vec3 color = texture (sampler2d, texture_uv.st).rgb;\n"
			"    float i = (color.r + color.g + color.b) * 0.3333333333;\n"
			"    fragment_color = vec4(vec3(i, i, i) * vec3(1.0, 0.75, 0.5), 1.0);\n"
			"    fragment_color = vec4(1, 0, 0, 1);\n"
			"}"
		);

		// Se crea un framebuffer en el que poder renderizar:
		{
			glGenFramebuffers(1, &framebuffer_id);
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
		}

		const char* filename = "..\\assets\\example_texture.jpg";

		//out_texture_id = SOIL_load_OGL_texture
		//(
		//	filename,
		//	SOIL_LOAD_AUTO,
		//	SOIL_CREATE_NEW_ID,
		//	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		//);

		///* check for an error during the load process */
		//if (0 == out_texture_id)
		//{
		//	printf("SOIL loading error: '%s'\n", SOIL_last_result());
		//}

		st::GLTexture texture;
		out_texture_id = texture.load("..\\assets\\example_texture.jpg");

		//Se crea una textura que será el búfer de color vinculado al framebuffer:
		//{
		//	glGenTextures(1, &out_texture_id);
		//	glBindTexture(GL_TEXTURE_2D, out_texture_id);

		//	// El búfer de color tendrá formato RGB:

		//	glTexImage2D
		//	(
		//		GL_TEXTURE_2D,
		//		0,
		//		GL_RGB,
		//		framebuffer_width,
		//		framebuffer_height,
		//		0,
		//		GL_RGB,
		//		GL_UNSIGNED_BYTE,
		//		0
		//	);

		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//}

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

		static const GLfloat quad_positions[] =
		{
			+1.0f, -1.0f, 0.0f,
			+1.0f, +1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f,

			1.0f, -1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f
		};

		static const GLfloat quad_texture_uv[] =
		{
			+1.0f,  0.0f,
			+1.0f, +1.0f,
			0.0f, +1.0f,

			+1.0f,  0.0f,
			0.0f, +1.0f,
			0.0f, 0.0f
		};

		glGenBuffers(1, &triangle_vbo0);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad_positions), quad_positions, GL_STATIC_DRAW);

		glGenBuffers(1, &triangle_vbo1);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad_texture_uv), quad_texture_uv, GL_STATIC_DRAW);

		mShader.bind();
		/*mShader.uploadIndices(indices);

		mShader.uploadAttrib("position", positions);
		mShader.uploadAttrib("color", colors);*/
	}

	void Canvas::drawGL()
	{
		using namespace nanogui;

		mShader.bind();


		//glDisable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_TEST);
		//glViewport(x, y, width, height);

		// Se activa el framebuffer de la ventana:

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//shader->use();

		// Se activa la textura del framebuffer:
		glActiveTexture(1);
		glBindTexture(GL_TEXTURE_2D, out_texture_id);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//shader->disable();

		//glEnable(GL_DEPTH_TEST);

		//mShader.drawArray(GL_TRIANGLES, 0, 6);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//glEnable(GL_DEPTH_TEST);
		///* Draw 12 triangles starting at index 0 */
		////mShader.drawIndexed(GL_TRIANGLES, 0, 12);
		glDisable(GL_DEPTH_TEST);

		glBindTexture(GL_TEXTURE_2D, 0);

	}
}