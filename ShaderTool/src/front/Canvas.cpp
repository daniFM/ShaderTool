
#include <Canvas.hpp>

//#include <GLTexture.hpp>
#include <stb_image.h>


extern "C"
{
#include <targa.h>
}

namespace st_front
{
	Canvas::Canvas(Widget *parent, std::shared_ptr < st::ShaderProgram > shader) : nanogui::GLCanvas(parent),
		shader_program(shader)
	{
		using namespace nanogui;

		//setShader();
		shader_program->use();

		//loadTexture("..\\assets\\example_texture.jpg");
		
		static const GLfloat quad_positions[] =
		{
			+1.0f, +1.0f, 0.0f,
			+1.0f, -1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,

			+1.0f, +1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			-1.0f, +1.0f, 0.0f
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

		//mShader.bind();
		shader_program->use();

		glEnable(GL_DEPTH_TEST);

		glActiveTexture(1);
		glBindTexture(GL_TEXTURE_2D, out_texture_id);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisable(GL_DEPTH_TEST);

		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void Canvas::setShader()
	{
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
	}

	void Canvas::setShader(shared_ptr<st::Shader> shader)
	{
		/*string code = *shader->getCode().get();
		string vertex_shader_code = code.substr(0, code.find_last_of("#"));
		string fragment_shader_code = code.substr(code.find_last_of("#"));

		mShader.init(shader->getTitle(), vertex_shader_code, fragment_shader_code);

		mShader.bind();*/

		shader_program->compileShader(shader);
		shader_program->use();
	}

	nanogui::Vector2i Canvas::loadTexture(string path)
	{
		using handleType = std::unique_ptr<uint8_t[], void(*)(void*)>;

		if (out_texture_id) {
			glDeleteTextures(1, &out_texture_id);
			out_texture_id = 0;
		}
		int force_channels = 0;
		int w, h, n;
		handleType textureData(stbi_load(path.c_str(), &w, &h, &n, force_channels), stbi_image_free);
		if (!textureData)
			throw std::invalid_argument("Could not load texture data from file " + path);

		glGenTextures(1, &out_texture_id);
		glBindTexture(GL_TEXTURE_2D, out_texture_id);
		GLint internalFormat;
		GLint format;
		switch (n) {
		case 1: internalFormat = GL_R8; format = GL_RED; break;
		case 2: internalFormat = GL_RG8; format = GL_RG; break;
		case 3: internalFormat = GL_RGB8; format = GL_RGB; break;
		case 4: internalFormat = GL_RGBA8; format = GL_RGBA; break;
		default: internalFormat = 0; format = 0; break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, w, h, 0, format, GL_UNSIGNED_BYTE, textureData.get());
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		return nanogui::Vector2i(w, h);

		//std::auto_ptr< Texture > texture = loadTexture(filename);

		//bool has_texture = texture.get() != 0;

		//if (has_texture)
		//{
		//	// Se habilitan las texturas, se genera un id para un búfer de textura,
		//	// se selecciona el búfer de textura creado y se configuran algunos de
		//	// sus parámetros:

		//	glEnable(GL_TEXTURE_2D);
		//	glGenTextures(1, &out_texture_id);
		//	glBindTexture(GL_TEXTURE_2D, out_texture_id);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//	// Se suben los colores de la textura a la memoria de vídeo:

		//	glTexImage2D
		//	(
		//		GL_TEXTURE_2D,
		//		0,
		//		GL_RGBA,
		//		texture->get_width(),
		//		texture->get_height(),
		//		0,
		//		GL_RGBA,
		//		GL_UNSIGNED_BYTE,
		//		texture->colors()
		//	);
		//}


		//std::auto_ptr< Texture > texture;
		//tga_image                loaded_image;

		//if (tga_read(&loaded_image, path.c_str()) == TGA_NOERR)
		//{
		//	// Si se ha podido cargar la imagen desde el archivo, se crea un búfer para una textura:

		//	texture.reset(new Texture(loaded_image.width, loaded_image.height));

		//	// Se convierte el formato de píxel de la imagen cargada a RGBA8888:

		//	tga_convert_depth(&loaded_image, texture->bits_per_color());
		//	tga_swap_red_blue(&loaded_image);

		//	// Se copian los pixels del búfer de la imagen cargada al búfer de la textura:

		//	Texture::Color * loaded_image_pixels = reinterpret_cast< Texture::Color * >(loaded_image.image_data);
		//	Texture::Color * loaded_image_pixels_end = loaded_image_pixels + loaded_image.width * loaded_image.height;
		//	Texture::Color * image_buffer_pixels = texture->colors();

		//	while (loaded_image_pixels <  loaded_image_pixels_end)
		//	{
		//		*image_buffer_pixels++ = *loaded_image_pixels++;
		//	}

		//	tga_free_buffers(&loaded_image);
		//}

		//return (texture);
	}
}