/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#include <UIController.hpp>

//#include <nanogui/glcanvas.h>
//#include <nanogui/button.h>
//#include <nanogui/label.h>
//#include <nanogui/layout.h>
//
//#include <GLFW/glfw3.h>

#include <nanogui/window.h>

#include <string>
#include <sstream>
#include <iostream>
#include <functional>

using namespace std;
using namespace nanogui;

namespace st_front
{
	UIController::UIController(shared_ptr<st::DocumentManager> dm)
		:
		Screen(Eigen::Vector2i(1024, 768), "NanoGUI Test", true),
		doc_manager(dm)
	{
		this->setLayout(new nanogui::GroupLayout);

		/*Window *window = new Window(this, "Preview");
		window->setPosition(Vector2i(0, 0));
		window->setLayout(new GroupLayout());*/

		auto * button = new nanogui::Button(this, "Preview");

		button->setCallback(std::bind(&UIController::buttonClicked, this));

		//label = new nanogui::Label(this, "");

		//canvas = new Canvas(this);
		canvas = new Canvas3D(this);
		canvas->setFixedSize(nanogui::Vector2i(512, 512));

		/*window = new Window(this, "Shader Editor");
		window->setPosition(Vector2i(542, 0));
		window->setLayout(new GroupLayout());

		text_box = new nanogui::TextBox(window);
		text_box->setEditable(true);
		text_box->setFixedSize(Vector2i(512, 600));
		text_box->setAlignment(TextBox::Alignment::Left);*/

		performLayout();
	}

	void UIController::buttonClicked()
	{
		doc_manager->loadShader();
		canvas->setShader(doc_manager->getShader());

		performLayout();
	}

	bool UIController::keyboardEvent(int key, int scancode, int action, int modifiers)
	{
		return Screen::keyboardEvent(key, scancode, action, modifiers);
	}

	void UIController::draw(NVGcontext * context)
	{
		//framebuffer->setFramebuffer();

		Screen::draw(context);

		/*int width = canvas->width();
		int height = canvas->height();
		int x = canvas->position().x();
		int y = canvas->position().y() + this->height() - height;

		framebuffer->render(x, y, width, height);*/
	}
}