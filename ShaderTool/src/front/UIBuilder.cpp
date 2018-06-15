
//  comentario de cabecera

#include <UIBuilder.hpp>
#include <iostream>
#include <fstream>

using namespace rapidxml;
using namespace nanogui;

namespace st
{
	nanogui::Screen *  UIBuilder::parseUI(const string & path)
	{
		// Read file content

		fstream xml_file(path, fstream::in);

		if (xml_file.good())
		{
			vector< char > xml_content;

			bool finished = false;

			do
			{
				int character = xml_file.get();

				if (character != -1)
				{
					xml_content.push_back((char)character);
				} else
					finished = true;
			} while (!finished);

			// Add a 0 at the end

			xml_content.push_back(0);

			// Create document model (DOM):

			xml_document< > document;

			document.parse< 0 >(xml_content.data());

			// Check if previous step worked

			xml_node< > * root = document.first_node();

			if (root && string(root->name()) == "Screen")
			{
				parse_screen(root);
			}
		}
		
		return screen;
	}

	nanogui::Screen * UIBuilder::parse_screen (const rapidxml::xml_node<> * screen_node)
	{
		string name;
		string width;
		string height;
		string fullscreen;
		string resizable;

		for (xml_attribute<> * attribute = screen_node->first_attribute (); attribute; attribute = attribute->next_attribute ())
		{
			if (string(attribute->name()) == "name"      ) name       = attribute->value(); else
			if (string(attribute->name()) == "width"     ) width	  = attribute->value(); else
			if (string(attribute->name()) == "height"    ) height	  = attribute->value(); else
			if (string(attribute->name()) == "fullscreen") fullscreen = attribute->value();	else
			if (string(attribute->name()) == "resizable" ) resizable  = attribute->value();
		}

		int  screen_width     = std::stoi (width );
		int  screen_height    = std::stoi (height);
		bool screen_full      = fullscreen == "true";
		bool screen_resizable = resizable  == "true";

		screen = new nanogui::Screen(nanogui::Vector2i(screen_width, screen_height), name, screen_resizable, screen_full);

		for (xml_node<> * child_node = screen_node->first_node(); child_node; child_node = child_node->next_sibling())
		{
			if (child_node->type() == node_element)
			{
				if (string(child_node->name()) == "layout")
				{
					nanogui::Layout * layout = parse_layout(child_node);

					if (layout)
					{
						screen->setLayout(layout);
					}
				}
				else if (string(child_node->name()) == "Widget")
				{
					parseWidget(screen, child_node);
				}
				// Solo se contempla que Screen tenga Layout y Widgets
				/*else if (string(child_node->name()) == "Button")
				{
					parseButton(screen.get(), child_node);
				}*/
			}
		}

		return screen;
	}

	nanogui::Layout * UIBuilder::parse_layout (const rapidxml::xml_node<> * layout_node)
	{
		nanogui::Layout * layout;

		if (string(layout_node->first_attribute()->value()) == "GroupLayout")
		{
			layout = new nanogui::GroupLayout;
		}
		else if (string(layout_node->first_attribute()->value()) == "BoxLayout")
		{
			rapidxml::xml_node<> * params_node = layout_node->first_node();

			string str_orientation;
			string str_alignment;
			string str_margin;
			string str_spacing;

			for (xml_attribute<> * attribute = params_node->first_attribute(); attribute; attribute = attribute->next_attribute())
			{

				if (string(attribute->name()) == "Orientation") str_orientation = attribute->value(); else
				if (string(attribute->name()) == "Alignment")   str_alignment = attribute->value(); else
				if (string(attribute->name()) == "margin")      str_margin = attribute->value(); else
				if (string(attribute->name()) == "spacing")     str_spacing = attribute->value();
				
			}

			Orientation orientation;
			Alignment alignment;
				
			if (str_orientation == "Horizontal") orientation = Orientation::Horizontal;
			else if (str_orientation == "Vertical")   orientation = Orientation::Vertical;

			if (str_alignment == "Fill")		alignment = Alignment::Fill;
			else if (str_alignment == "Maximum")	alignment = Alignment::Maximum;
			else if (str_alignment == "Middle")		alignment = Alignment::Middle;
			else if (str_alignment == "Minimum")	alignment = Alignment::Minimum;

			int margin = std::stoi(str_margin);
			int spacing = std::stoi(str_spacing);

			layout = new BoxLayout(orientation, alignment, margin, spacing);
		
		}

		return layout;
	}

	void UIBuilder::parseWidget (nanogui::Widget * parent, rapidxml::xml_node<> * widget_node)
	{
		Widget * widget = new Widget(parent);

		for (xml_node<> * child_node = widget_node->first_node(); child_node; child_node = child_node->next_sibling())
		{
			if (child_node->type() == node_element)
			{
				if (string(child_node->name()) == "layout")
				{
					nanogui::Layout * layout = parse_layout(child_node);

					if (layout)
					{
						widget->setLayout(layout);
					}
				}
				else if (string(child_node->name()) == "Widget")
				{
					parseWidget(widget, child_node);
				}
				else if (string(child_node->name()) == "Button")
				{
					parseButton(widget, child_node);
				}
				else if (string(child_node->name()) == "Canvas")
				{
					parseCanvas(widget, child_node);
				}
				else if (string(child_node->name()) == "Label")
				{
					parseLabel(widget, child_node);
				}
				else if (string(child_node->name()) == "TextBox")
				{
					parseTextBox(widget, child_node);
				}
			}
		}
	}

	void UIBuilder::parseButton (nanogui::Widget * parent, rapidxml::xml_node<> * button_node)
	{
		string str_name;
		string str_width;
		string str_height;
		string str_callbac;

		for (xml_attribute<> * attribute = button_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{
			if (string(attribute->name()) == "name")		str_name = attribute->value(); else
			if (string(attribute->name()) == "width")		str_width = attribute->value(); else
			if (string(attribute->name()) == "height")      str_height = attribute->value(); else
			if (string(attribute->name()) == "callback")	str_callbac = attribute->value();
		}

		Button * button = new Button(parent, str_name);

		if (str_width != "")  button->setFixedWidth(std::stoi(str_width));
		if (str_height != "") button->setFixedHeight(std::stoi(str_height));

		button->setCallback(callbacks[str_callbac]);

	}

	void UIBuilder::parseCanvas(nanogui::Widget * parent, rapidxml::xml_node<> * canvas_node)
	{
		string str_width;
		string str_height;

		for (xml_attribute<> * attribute = canvas_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{
			if (string(attribute->name()) == "width")	str_width  = attribute->value(); else
			if (string(attribute->name()) == "height")	str_height = attribute->value();
		}

		int width = std::stoi(str_width);
		int height = std::stoi(str_height);

		st::Canvas * mycanvas = new st::Canvas(parent);
		mycanvas->setFixedSize(nanogui::Vector2i(width, height));

		canvas = mycanvas;
	}

	void UIBuilder::parseLabel(nanogui::Widget * parent, rapidxml::xml_node<> * label_node)
	{
		string str_name;

		for (xml_attribute<> * attribute = label_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{
			if (string(attribute->name()) == "name")		str_name = attribute->value();
		}

		Label * label = new Label(parent, str_name);
	}

	void UIBuilder::parseTextBox(nanogui::Widget * parent, rapidxml::xml_node<> * textbox_node)
	{
		/*save_shader_name = new TextBox(tools_save);
		save_shader_name->setValue("yourShaderName");
		save_shader_name->setFixedWidth(200);
		save_shader_name->setEditable(true);*/

		string str_name;
		string str_width;
		string str_height;
		string str_editable;

		for (xml_attribute<> * attribute = textbox_node->first_attribute(); attribute; attribute = attribute->next_attribute())
		{
			if (string(attribute->name()) == "caption")		str_name = attribute->value(); else
			if (string(attribute->name()) == "width")		str_width = attribute->value(); else
			if (string(attribute->name()) == "height")      str_height = attribute->value(); else
			if (string(attribute->name()) == "editable")	str_editable = attribute->value();
		}

		bool editable = str_editable == "true";

		TextBox * tb = new TextBox(parent);

		tb->setValue(str_name);

		if (str_width != "")  tb->setFixedWidth(std::stoi(str_width));
		if (str_height != "") tb->setFixedHeight(std::stoi(str_height));

		tb->setEditable(editable);
	}

}
