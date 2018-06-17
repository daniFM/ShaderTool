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

#include <Shader.hpp>

namespace st
{
	/// Customizable GLCanvas implementation. WIP.
	class Canvas3D : public nanogui::GLCanvas
	{

	private:

		nanogui::GLShader mShader;

		Eigen::Vector3f mRotation;

	public:

		Canvas3D(Widget *parent);
		~Canvas3D()
		{
			mShader.free();
		}

		virtual void drawGL() override;

		void setShader();
		void setShader(shared_ptr<st::Shader> shader);

		void setRotation(nanogui::Vector3f vRotation) {
			mRotation = vRotation;
		}

	};

}