/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

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

#include <Canvas.hpp>
#include <Canvas3D.hpp>
#include <DocumentManager.hpp>
#include <ConfigurationManager.hpp>

namespace st_front
{
	class UIController : public nanogui::Screen
	{
	private:

		Canvas * canvas;
		//Canvas3D * canvas;

		nanogui::TextBox * save_shader_name;
		nanogui::TextBox * open_shader_name;
		nanogui::TextBox * texture_path;

		shared_ptr < st::DocumentManager >      doc_manager;
		shared_ptr < st::ConfigurationManager > conf_manager;

	public:

		UIController(shared_ptr<st::DocumentManager> dm, shared_ptr<st::ConfigurationManager> cm);

	private:

		void previewButton();
		void editButton();
		void saveButton();
		void openButton();

		void openTexButton();
		void loadTexture(string path);

		bool keyboardEvent(int key, int scancode, int action, int modifiers) override;

		void draw(NVGcontext * context) override;
	};
}