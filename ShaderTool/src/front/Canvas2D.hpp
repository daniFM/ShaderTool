/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <nanogui/glcanvas.h>
#include <iostream>
#include <string>

// Includes for the GLTexture class.
#include <cstdint>
#include <memory>
#include <utility>

#include <ShaderProgram.hpp>
#include <Color_Buffer_Rgba8888.hpp>

#include <Canvas.hpp>

namespace st_front
{
	typedef st::Color_Buffer_Rgba8888 Texture;

	class Canvas2D : public Canvas	//nanogui::GLCanvas
	{

	private:

		nanogui::GLShader mShader;

		std::shared_ptr < st::ShaderProgram > shader;

		/// The resolution in wich the scene is going to be rendered in the framebuffer.
		static const GLsizei framebuffer_width = 2048;
		static const GLsizei framebuffer_height = 2048;

		GLuint framebuffer_id;
		GLuint depthbuffer_id;
		GLuint out_texture_id;

		GLuint triangle_vbo0;
		GLuint triangle_vbo1;

	public:

		 Canvas2D(Widget *parent);
		~Canvas2D()
		{
			mShader.free();
		}

		virtual void drawGL() override;

		void setShader() override;
		void setShader(shared_ptr<st::Shader> shader) override;

		nanogui::Vector2i loadTexture(string path);
		//auto_ptr< Texture > loadTexture(string path);

	};

}