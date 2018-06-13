/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <nanogui/screen.h>
#include <Canvas.hpp>
//#include <Canvas3D.hpp>
#include <DocumentManager.hpp>

namespace st_front
{
	class UIController : public nanogui::Screen
	{
	private:

		Canvas * canvas;
		//Canvas3D * canvas;

		nanogui::TextBox * shader_name;
		nanogui::TextBox * texture_path;

		shared_ptr < st::DocumentManager > doc_manager;

	public:

		UIController(shared_ptr<st::DocumentManager> dm);

	private:

		void previewButton();
		void openButton();
		void saveButton();

		void openTexButton();
		void loadTexture(string path);

		bool keyboardEvent(int key, int scancode, int action, int modifiers) override;

		void draw(NVGcontext * context) override;
	};
}