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

namespace st
{
	UIController::UIController(shared_ptr<st::DocumentManager> dm, shared_ptr<st::ConfigurationManager> cm)
		:
		doc_manager(dm),
		conf_manager(cm)
	{
		st::UIBuilder ui_builder;

		ui_builder.add_callback("previewButton", std::bind(&UIController::previewButton, this));
		ui_builder.add_callback("editButton",    std::bind(&UIController::editButton,    this));
		ui_builder.add_callback("saveButton",    std::bind(&UIController::saveButton,    this));
		ui_builder.add_callback("openButton",    std::bind(&UIController::openButton,    this));
		ui_builder.add_callback("openTexButton", std::bind(&UIController::openTexButton, this));

		screen = ui_builder.parseUI(conf_manager->config_path + "\\ui_layout.xml");

		canvas = ui_builder.canvas;
		save_shader_name = ui_builder.save_shader_name;
		open_shader_name = ui_builder.open_shader_name;
		texture_path = ui_builder.texture_path;

		loadTexture(conf_manager->textures_path + "\\example_texture2.jpg");

		previewButton();

		screen->performLayout();

		

	}

	void UIController::run()
	{
		screen->drawAll();
		screen->setVisible(true);

		nanogui::mainloop();
	}

	void UIController::previewButton()
	{
		doc_manager->loadShader();
		canvas->setShader(doc_manager->getShader());
	}

	void UIController::editButton()
	{
		doc_manager->openShader();
	}

	void UIController::saveButton()
	{
		// file_dialog -> Not using because it changes the working directory.
		doc_manager->saveShader(save_shader_name->value());
	}

	void UIController::openButton()
	{
		doc_manager->loadShader(doc_manager->shaders_path + "\\" + open_shader_name->value() + ".glsl", true);
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

}

// HARDCODED INTERFACE

//this->setLayout(new BoxLayout(Orientation::Horizontal,
//	Alignment::Minimum, 0, 6));

//// PREVIEW WIDGET -------------------------------------------------------------------------

//Widget * preview = new Widget(this);
//preview->setLayout(new GroupLayout);

//auto * button = new nanogui::Button(preview, "Preview");
//button->setFixedWidth(512);
//button->setCallback(std::bind(&UIController::previewButton, this));

//canvas = new Canvas(preview);
////canvas = new Canvas3D(this);
//canvas->setFixedSize(nanogui::Vector2i(512, 512));

//loadTexture(conf_manager->textures_path + "\\example_texture2.jpg");

//// TOOLS WIDGET ---------------------------------------------------------------------------

//Widget * tools = new Widget(this);
//tools->setLayout(new GroupLayout);
//tools->setFixedWidth(400);

//button = new nanogui::Button(tools, "Edit shader");
//button->setCallback(std::bind(&UIController::editButton, this));

//// SAVE WIDGET ----------------------------------------------------------------------------

//new Label(tools, "Shader options");

//Widget * tools_save = new Widget(tools);
//tools_save->setLayout(new BoxLayout(Orientation::Horizontal,
//	Alignment::Middle, 0, 6));

//save_shader_name = new TextBox(tools_save);
//save_shader_name->setValue("yourShaderName");
//save_shader_name->setFixedWidth(200);
//save_shader_name->setEditable(true);

//button = new Button(tools_save, "Save");
//button->setCallback(std::bind(&UIController::saveButton, this));

////

//Widget * tools_open = new Widget(tools);
//tools_open->setLayout(new BoxLayout(Orientation::Horizontal,
//	Alignment::Fill, 0, 6));

//open_shader_name = new TextBox(tools_open);
//open_shader_name->setValue("");
//open_shader_name->setFixedWidth(200);
//open_shader_name->setEditable(true);

//button = new Button(tools_open, "Open");
//button->setCallback(std::bind(&UIController::openButton, this));

//// LOAD TEXTURE WIDGET ---------------------------------------------------------------------

//new Label(tools, "Texture options");

//Widget * tools_tex = new Widget(tools);
//tools_tex->setLayout(new BoxLayout(Orientation::Horizontal,
//	Alignment::Middle, 0, 6));

//texture_path = new TextBox(tools_tex);
//texture_path->setValue("example_texture.jpg");
//texture_path->setFixedWidth(200);
//texture_path->setEditable(true);

//button = new Button(tools_tex, "Load texture");
//button->setCallback(std::bind(&UIController::openTexButton, this));


///*text_box = new nanogui::TextBox(window);
//text_box->setEditable(true);
//text_box->setFixedSize(Vector2i(512, 600));
//text_box->setAlignment(TextBox::Alignment::Left);*/