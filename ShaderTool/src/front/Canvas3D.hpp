///*
//
//Author: Daniel Fernández (https://github.com/daniFM)
//Date:	12/06/2018
//
//Subject to license in LICENSE.txt
//
//*/
//
//#pragma once
//
//#include <nanogui/opengl.h>
//#include <nanogui/glutil.h>
//#include <nanogui/screen.h>
//#include <nanogui/window.h>
//#include <nanogui/layout.h>
//#include <nanogui/label.h>
//#include <nanogui/checkbox.h>
//#include <nanogui/button.h>
//#include <nanogui/toolbutton.h>
//#include <nanogui/popupbutton.h>
//#include <nanogui/combobox.h>
//#include <nanogui/progressbar.h>
//#include <nanogui/entypo.h>
//#include <nanogui/messagedialog.h>
//#include <nanogui/textbox.h>
//#include <nanogui/slider.h>
//#include <nanogui/imagepanel.h>
//#include <nanogui/imageview.h>
//#include <nanogui/vscrollpanel.h>
//#include <nanogui/colorwheel.h>
//#include <nanogui/graph.h>
//#include <nanogui/tabwidget.h>
//#include <nanogui/glcanvas.h>
//#include <iostream>
//#include <string>
//
//// Includes for the GLTexture class.
//#include <cstdint>
//#include <memory>
//#include <utility>
//
//#include <Shader.hpp>
//
//namespace st_front
//{
//
//	class Canvas3D : public nanogui::GLCanvas
//	{
//
//	private:
//
//		nanogui::GLShader mShader;
//
//		Eigen::Vector3f mRotation;
//
//	public:
//
//		Canvas3D(Widget *parent);
//		~Canvas3D()
//		{
//			mShader.free();
//		}
//
//		virtual void drawGL() override;
//
//		void setShader();
//		void setShader(shared_ptr<st::Shader> shader);
//
//		void setRotation(nanogui::Vector3f vRotation) {
//			mRotation = vRotation;
//		}
//
//	};
//
//}