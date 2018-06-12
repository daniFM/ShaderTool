
#include <Canvas.hpp>


extern "C"
{
#include <targa.h>
}

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
			"    //fragment_color = vec4(1, 0, 0, 1);\n"
			"}"
		);

		mShader.bind();

		const char* filename = "..\\assets\\example_texture.tga";

		//st::GLTexture texture;
		std::auto_ptr< Texture > texture = loadTexture(filename);

		bool has_texture = texture.get() != 0;

		if (has_texture)
		{
			// Se habilitan las texturas, se genera un id para un b�fer de textura,
			// se selecciona el b�fer de textura creado y se configuran algunos de
			// sus par�metros:

			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &out_texture_id);
			glBindTexture(GL_TEXTURE_2D, out_texture_id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			// Se suben los colores de la textura a la memoria de v�deo:

			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,
				texture->get_width(),
				texture->get_height(),
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				texture->colors()
			);
		}

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

	auto_ptr< Texture > Canvas::loadTexture(string path)
	{
		std::auto_ptr< Texture > texture;
		tga_image                loaded_image;

		if (tga_read(&loaded_image, path.c_str()) == TGA_NOERR)
		{
			// Si se ha podido cargar la imagen desde el archivo, se crea un b�fer para una textura:

			texture.reset(new Texture(loaded_image.width, loaded_image.height));

			// Se convierte el formato de p�xel de la imagen cargada a RGBA8888:

			tga_convert_depth(&loaded_image, texture->bits_per_color());
			tga_swap_red_blue(&loaded_image);

			// Se copian los pixels del b�fer de la imagen cargada al b�fer de la textura:

			Texture::Color * loaded_image_pixels = reinterpret_cast< Texture::Color * >(loaded_image.image_data);
			Texture::Color * loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
			Texture::Color * image_buffer_pixels = texture->colors();

			while (loaded_image_pixels <  loaded_image_pixels_end)
			{
				*image_buffer_pixels++ = *loaded_image_pixels++;
			}

			tga_free_buffers(&loaded_image);
		}

		return (texture);
	}
}