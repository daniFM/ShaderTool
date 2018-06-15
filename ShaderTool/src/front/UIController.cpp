/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#include <UIController.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <functional>

using namespace std;
using namespace nanogui;

namespace st_front
{
	UIController::UIController(shared_ptr<st::DocumentManager> dm, shared_ptr<st::ConfigurationManager> cm)
		:
		Screen(Eigen::Vector2i(960, 600), "ShaderTool", true),
		doc_manager(dm),
		conf_manager(cm)
	{
		this->setLayout(new BoxLayout(Orientation::Horizontal,
			Alignment::Minimum, 0, 6));

		// PREVIEW WIDGET -------------------------------------------------------------------------

		preview = new Widget(this);
		preview->setLayout(new GroupLayout);

		auto * button = new nanogui::Button(preview, "Preview");
		button->setFixedWidth(512);
		button->setCallback(std::bind(&UIController::previewButton, this));

		//canvas = new Canvas2D(preview);
		////canvas = new Canvas3D(this);
		//canvas->setFixedSize(nanogui::Vector2i(512, 512));
		changeButton();

		loadTexture(conf_manager->textures_path + "\\example_texture2.jpg");

		button = new nanogui::Button(preview, "Change mode");
		button->setFixedWidth(512);
		button->setCallback(std::bind(&UIController::changeButton, this));

		// TOOLS WIDGET ---------------------------------------------------------------------------

		Widget * tools = new Widget(this);
		tools->setLayout(new GroupLayout);
		tools->setFixedWidth(400);

		button = new nanogui::Button(tools, "Edit shader");
		button->setCallback(std::bind(&UIController::editButton, this));

		// SAVE WIDGET ----------------------------------------------------------------------------

		new Label(tools, "Shader options");

		Widget * tools_save = new Widget(tools);
		tools_save->setLayout(new BoxLayout(Orientation::Horizontal,
			Alignment::Middle, 0, 6));

		save_shader_name = new TextBox(tools_save);
		save_shader_name->setValue("yourShaderName");
		save_shader_name->setFixedWidth(200);
		save_shader_name->setEditable(true);

		button = new Button(tools_save, "Save");
		button->setCallback(std::bind(&UIController::saveButton, this));

		//

		Widget * tools_open = new Widget(tools);
		tools_open->setLayout(new BoxLayout(Orientation::Horizontal,
			Alignment::Fill, 0, 6));

		open_shader_name = new TextBox(tools_open);
		open_shader_name->setValue("");
		open_shader_name->setFixedWidth(200);
		open_shader_name->setEditable(true);

		button = new Button(tools_open, "Open");
		button->setCallback(std::bind(&UIController::openButton, this));

		// LOAD TEXTURE WIDGET ---------------------------------------------------------------------

		new Label(tools, "Texture options");

		Widget * tools_tex = new Widget(tools);
		tools_tex->setLayout(new BoxLayout(Orientation::Horizontal,
			Alignment::Middle, 0, 6));

		texture_path = new TextBox(tools_tex);
		texture_path->setValue("example_texture.jpg");
		texture_path->setFixedWidth(200);
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

	void UIController::changeButton()
	{
		string newMode = conf_manager->swapMode();
		doc_manager->loadShader(doc_manager->shaders_path + "\\newShader.glsl");

		changeMode(newMode);

	}

	void UIController::editButton()
	{
		doc_manager->openShader();
	}

	void UIController::saveButton()
	{
		doc_manager->saveShader(save_shader_name->value());
	}

	void UIController::openButton()
	{
		doc_manager->loadShader(doc_manager->shaders_path + "\\" + open_shader_name->value() + ".glsl");
		canvas->setShader(doc_manager->getShader());
	}

	void UIController::openTexButton()
	{
		loadTexture(conf_manager->textures_path + "\\" + texture_path->value());
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

	void UIController::changeMode(string newMode)
	{
		if (newMode == "postprocessing")
			canvas = new Canvas2D(preview);
		else// (newMode == "default3d")
			canvas = new Canvas3D(preview);

		canvas->setShader(doc_manager->getShader());
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