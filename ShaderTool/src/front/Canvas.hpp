/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <nanogui/glcanvas.h>

#include <string>
#include <memory>

#include <Shader.hpp>

using namespace std;

namespace st_front
{
	class Canvas : nanogui::GLCanvas
	{
		         Canvas() = default;
		virtual ~Canvas() = 0;

		virtual void setShader() = 0;
		virtual void setShader(shared_ptr<st::Shader> shader) = 0;

		virtual nanogui::Vector2i loadTexture(string path) = 0;
	};
}