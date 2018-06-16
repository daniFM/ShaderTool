/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <nanogui/screen.h>
#include <Canvas.hpp>

#include <DocumentManager.hpp>
#include <ConfigurationManager.hpp>
#include <UIBuilder.hpp>

namespace st
{
	class UIController
	{
	private:

		nanogui::Screen * screen;

	public:

		Canvas * canvas;
		//Canvas3D * canvas;

		nanogui::TextBox * save_shader_name;
		nanogui::TextBox * open_shader_name;
		nanogui::TextBox * texture_path;

	private:

		shared_ptr < st::DocumentManager >      doc_manager;
		shared_ptr < st::ConfigurationManager > conf_manager;

	public:

		UIController(shared_ptr<st::DocumentManager> dm, shared_ptr<st::ConfigurationManager> cm);

		void run();

	private:

		void previewButton();
		void editButton();
		void saveButton();
		void openButton();

		void openTexButton();
		void loadTexture(string path);

		/*bool keyboardEvent(int key, int scancode, int action, int modifiers) override;
		void draw(NVGcontext * context) override;*/
	};
}