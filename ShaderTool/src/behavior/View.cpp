///*
//
//Author: Daniel Fernández (https://github.com/daniFM)
//Date:	16/05/2018
//
//Subject to license in LICENSE.txt
//
//*/
//
//#include <View.hpp>
//
//namespace st
//{
//	const string View::default_shader_code =
//
//		"#version 330\n"
//		""
//		"layout (location = 0) in vec3 vertex_coordinates;"
//		"layout (location = 1) in vec2 vertex_texture_uv;"
//		""
//		"out vec2 texture_uv;"
//		""
//		"void main()"
//		"{"
//		"   gl_Position = vec4(vertex_coordinates, 1.0);"
//		"   texture_uv  = vertex_texture_uv;"
//		"}"
//		""
//		"#version 330\n"
//		""
//		"uniform sampler2D sampler2d;"
//		""
//		"in  vec2 texture_uv;"
//		"out vec4 fragment_color;"
//		""
//		"void main()"
//		"{"
//		"    vec3 color = texture (sampler2d, texture_uv.st).rgb;"
//		"    float i = (color.r + color.g + color.b) * 0.3333333333;"
//		"    fragment_color = vec4(vec3(i, i, i) * vec3(1.0, 0.75, 0.5), 1.0);"
//		"}";
//
//	View::View(int width, int height, shared_ptr<Shader> shader)
//		:
//		shader_program(),
//		framebuffer(make_shared<ShaderProgram>(shader_program))
//	{
//		/*shader_program = ShaderProgram();
//		framebuffer = Framebuffer(make_shared<ShaderProgram>(shader_program));*/
//		/*shader_program = make_shared<ShaderProgram>();
//		framebuffer = Framebuffer(shader_program);*/
//
//		shader_program.compileShader(shader);
//
//		shader_program.use();
//
//		glEnable(GL_CULL_FACE);
//		glClearColor(0.f, 0.f, 0.f, 1.f);
//
//		resize(width, height);
//	}
//
//	void View::update()
//	{
//	}
//
//	void View::render()
//	{
//		framebuffer.setFramebuffer();
//		framebuffer.render(window_width, window_height);
//	}
//
//	void View::resize(int width, int height)
//	{
//		window_width = width;
//		window_height = height;
//
//		/*glm::mat4 projection_matrix = glm::perspective(60.f, GLfloat(width) / height, 1.f, 50.f);
//
//		glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));*/
//
//		glViewport(0, 0, width, height);
//	}
//
//}