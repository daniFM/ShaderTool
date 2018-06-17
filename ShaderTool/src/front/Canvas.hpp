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

//#include <ShaderProgram.hpp>
#include <Shader.hpp>
#include <Color_Buffer_Rgba8888.hpp>

namespace st
{
	typedef st::Color_Buffer_Rgba8888 Texture;

	/// Customized GLCanvas class to act as a customizable framebuffer.
	class Canvas : public nanogui::GLCanvas
	{

	private:

		nanogui::GLShader mShader;

		//std::shared_ptr < st::ShaderProgram > shader;

		/// The resolution in wich the scene is going to be rendered in the framebuffer.
		static const GLsizei framebuffer_width = 2048;
		static const GLsizei framebuffer_height = 2048;

		GLuint framebuffer_id;
		GLuint depthbuffer_id;
		GLuint out_texture_id;

		GLuint triangle_vbo0;
		GLuint triangle_vbo1;

	public:

		/// Creates the canvas framebuffer.
		 Canvas(Widget *parent);
		~Canvas()
		{
			mShader.free();
		}

		/// Draws the framebuffer.
		virtual void drawGL() override;

		/// Relaces the shader used to render the framebuffer.
		/// @param shader Replacement shader.
		void setShader(shared_ptr<st::Shader> shader);

		/// Loads a texture and binds it to the shader.
		/// @param path Path to the texture.
		nanogui::Vector2i loadTexture(string path);

		//auto_ptr< Texture > loadTexture(string path);

	};

}