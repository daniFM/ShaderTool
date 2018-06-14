/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

//#include <nanogui/opengl.h>
#include <nanogui/glutil.h>
#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/checkbox.h>
#include <nanogui/button.h>
#include <nanogui/toolbutton.h>
#include <nanogui/popupbutton.h>
#include <nanogui/combobox.h>
#include <nanogui/progressbar.h>
#include <nanogui/entypo.h>
#include <nanogui/messagedialog.h>
#include <nanogui/textbox.h>
#include <nanogui/slider.h>
#include <nanogui/imagepanel.h>
#include <nanogui/imageview.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/colorwheel.h>
#include <nanogui/graph.h>
#include <nanogui/tabwidget.h>
#include <nanogui/glcanvas.h>
#include <iostream>
#include <string>

// Includes for the GLTexture class.
#include <cstdint>
#include <memory>
#include <utility>

#include <ShaderProgram.hpp>
#include <Color_Buffer_Rgba8888.hpp>

namespace st_front
{
	typedef st::Color_Buffer_Rgba8888 Texture;

	class Canvas : public nanogui::GLCanvas
	{

	private:

		nanogui::GLShader mShader;

		std::shared_ptr < st::ShaderProgram > shader_program;

		/// The resolution in wich the scene is going to be rendered in the framebuffer.
		static const GLsizei framebuffer_width = 2048;
		static const GLsizei framebuffer_height = 2048;

		GLuint framebuffer_id;
		GLuint depthbuffer_id;
		GLuint out_texture_id;

		GLuint triangle_vbo0;
		GLuint triangle_vbo1;

	public:

		 Canvas(Widget *parent, std::shared_ptr < st::ShaderProgram > shader);
		~Canvas()
		{
			//mShader.free();
			shader_program->disable();
		}

		virtual void drawGL() override;

		void setShader();
		void setShader(shared_ptr<st::Shader> shader);

		nanogui::Vector2i loadTexture(string path);
		//auto_ptr< Texture > loadTexture(string path);

	};

}