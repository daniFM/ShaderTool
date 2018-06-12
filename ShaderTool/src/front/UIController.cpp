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
	UIController::UIController()
		:
		Screen(Eigen::Vector2i(1024, 768), "NanoGUI Test", true)
	{
		//this->setLayout(new nanogui::GroupLayout);

		Window *window = new Window(this, "Preview");
		window->setPosition(Vector2i(15, 15));
		window->setLayout(new GroupLayout());

		auto * button = new nanogui::Button(window, "Preview");

		button->setCallback(std::bind(&UIController::buttonClicked, this));

		//label = new nanogui::Label(this, "");

		canvas = new Canvas(window);
		//canvas->setFixedSize(nanogui::Vector2i(512, 600));

		window = new Window(this, "Shader Editor");
		window->setPosition(Vector2i(512, 15));
		window->setLayout(new GroupLayout());

		text_box = new nanogui::TextBox(window);
		text_box->setEditable(true);
		text_box->setFixedSize(Vector2i(512, 600));
		text_box->setAlignment(TextBox::Alignment::Left);
		//shader_editor->setFixedSize(nanogui::Vector2i(512, 600));
		//shader_editor->setPosition(nanogui::Vector2i(512, -600));
		//shader_editor->setAlignment(nanogui::TextBox::Alignment::Right);

		performLayout();

		clickCount = 0;
	}

	void UIController::buttonClicked()
	{
		clickCount++;

		ostringstream caption;

		caption << "The button has been clicked ";

		switch (clickCount)
		{
		case 1:  caption << "once.";  break;
		case 2:  caption << "twice."; break;
		default: caption << clickCount << " times.";
		}

		//label->setCaption(caption.str());
		text_box->setValue(caption.str());

		performLayout();
	}

	bool UIController::keyboardEvent(int key, int scancode, int action, int modifiers)
	{
		return Screen::keyboardEvent(key, scancode, action, modifiers);
	}

	void UIController::draw(NVGcontext * context)
	{
		Screen::draw(context);
	}
}