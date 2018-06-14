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
		Screen(Eigen::Vector2i(960, 600), "ShaderTool", true),
		doc_manager(dm)
	{
		//shader_program = make_shared<st::ShaderProgram>(doc_manager->getShader());

		// INTERFACE CREATION ---------------------------------------------------------------------

		this->setLayout(new BoxLayout(Orientation::Horizontal,
			Alignment::Minimum, 0, 6));

		// PREVIEW WIDGET -------------------------------------------------------------------------

		Widget * preview = new Widget(this);
		preview->setLayout(new GroupLayout);

		auto * button = new nanogui::Button(preview, "Preview");
		button->setFixedWidth(512);
		button->setCallback(std::bind(&UIController::previewButton, this));

		canvas = new Canvas(preview, make_shared<st::ShaderProgram>(doc_manager->getShader()));
		//canvas = new Canvas3D(this);
		canvas->setFixedSize(nanogui::Vector2i(512, 512));

		loadTexture(doc_manager->textures_path + "\\example_texture2.jpg");

		// TOOLS WIDGET ---------------------------------------------------------------------------

		Widget * tools = new Widget(this);
		tools->setLayout(new GroupLayout);
		tools->setFixedWidth(400);

		button = new nanogui::Button(tools, "Open shader");
		button->setCallback(std::bind(&UIController::openButton, this));

		// SAVE WIDGET ----------------------------------------------------------------------------

		new Label(tools, "Shader options");

		Widget * tools_save = new Widget(tools);
		tools_save->setLayout(new BoxLayout(Orientation::Horizontal,
			Alignment::Middle, 0, 6));

		shader_name = new TextBox(tools_save);
		shader_name->setValue("yourShaderName");
		shader_name->setEditable(true);

		button = new Button(tools_save, "Save");
		button->setCallback(std::bind(&UIController::saveButton, this));

		// LOAD TEXTURE WIDGET ---------------------------------------------------------------------

		new Label(tools, "Texture options");

		Widget * tools_tex = new Widget(tools);
		tools_tex->setLayout(new BoxLayout(Orientation::Horizontal,
			Alignment::Middle, 0, 6));

		texture_path = new TextBox(tools_tex);
		texture_path->setValue("..\\assets\\example_texture.jpg");
		texture_path->setEditable(true);

		button = new Button(tools_tex, "Load texture");
		button->setCallback(std::bind(&UIController::openTexButton, this));


		/*text_box = new nanogui::TextBox(window);
		text_box->setEditable(true);
		text_box->setFixedSize(Vector2i(512, 600));
		text_box->setAlignment(TextBox::Alignment::Left);*/

		performLayout();
	}

	void UIController::previewButton()
	{
		doc_manager->loadShader();
		canvas->setShader(doc_manager->getShader());

		performLayout();
	}

	void UIController::openButton()
	{
		doc_manager->openShader();
	}

	void UIController::saveButton()
	{
		doc_manager->saveShader(shader_name->value());
	}

	void UIController::openTexButton()
	{
		loadTexture(texture_path->value());
	}

	void UIController::loadTexture(string path)
	{
		Vector2i newres = canvas->loadTexture(path);

		int w = newres.x();
		int h = newres.y();
		float aspect = (float)w / (float)h;

		int prevh = canvas->fixedHeight();
		canvas->setHeight((int)(prevh / aspect));
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