/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <nanogui/screen.h>
#include <Canvas.hpp>

namespace st_front
{
	class UIController : public nanogui::Screen
	{
	private:

		nanogui::Label * label;
		Canvas * canvas;
		nanogui::TextBox * text_box;

		unsigned int     clickCount;

	public:

		UIController();

	private:

		void buttonClicked();
		bool keyboardEvent(int key, int scancode, int action, int modifiers) override;
		void draw(NVGcontext * context) override;
	};
}