/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#include <UIController.hpp>

#include <nanogui/glcanvas.h>
#include <nanogui/button.h>
#include <nanogui/label.h>
#include <nanogui/layout.h>

#include <GLFW/glfw3.h>

#include <string>
#include <sstream>
#include <iostream>
#include <functional>

using namespace std;

namespace st
{
	UIController::UIController() : Screen(Eigen::Vector2i(1024, 768), "NanoGUI Test", true)
	{
		this->setLayout(new nanogui::GroupLayout);

		auto * button = new nanogui::Button(this, "Click me!");

		button->setCallback(std::bind(&UIController::buttonClicked, this));

		label = new nanogui::Label(this, "");
		canvas = new nanogui::GLCanvas(this);

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

		label->setCaption(caption.str());

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