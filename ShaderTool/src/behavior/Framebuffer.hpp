/*

Author: Daniel Fernández
Date:	10/06/2018

*/

#pragma once

#include <memory>

#include <ShaderProgram.hpp>
#include <Color_Buffer_Rgba8888.hpp>

namespace st
{
	//typedef Color_Buffer_Rgba8888 Texture;

	/// Used to render the scene to a framebuffer and apply post processig shaders to it.
	class Framebuffer
	{
	private:

		/// Post processing shader.
		std::shared_ptr < ShaderProgram > shader;

		/// The resolution in wich the scene is going to be rendered in the framebuffer.
		static const GLsizei framebuffer_width = 2048;
		static const GLsizei framebuffer_height = 2048;
		
		GLuint framebuffer_id;
		GLuint depthbuffer_id;
		GLuint out_texture_id;

		GLuint triangle_vbo0;
		GLuint triangle_vbo1;

	public:

		/// Creates a Framebuffer.
		/// Creation of the GL_FRAMEBUFFER, texture, z-buffer and the screen quad.
		/// @param post processing shader that will be used to render the framebuffer.
		Framebuffer(std::shared_ptr < ShaderProgram > shader);

		/// Renders the framebuffer in the specified screen dymensions.
		/// The framebuffer needs to be set before calling to render.
		/// To be called after rendering all other scene elements.
		/// @param width screen width.
		/// @param height screen height.
		void render(int width, int height);
		/// Inits the glViewport and the GL_FRAMEBUFFER for the scene objects to be rendered.
		/// To be called at the start of the scene rendering.
		void setFramebuffer();

	};
}