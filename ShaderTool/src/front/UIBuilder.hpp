/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	15/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <map>
#include <memory>
#include <string>
#include <functional>
#include <rapidxml.hpp>
#include <nanogui/nanogui.h>
#include <Canvas.hpp>

using std::function;
using std::unique_ptr;
using std::shared_ptr;
using std::string;

namespace st
{
	/// Builds the nanogui interface from a xml.
	class UIBuilder
	{
		nanogui::Screen * screen;

		std::map< string, function< void() > > callbacks;

	public:

		Canvas * canvas;
		nanogui::TextBox * save_shader_name;
		nanogui::TextBox * open_shader_name;
		nanogui::TextBox * texture_path;

	public:

		UIBuilder() = default;
		
		/// Reads the layout xml and starts the parsing.
		nanogui::Screen * parseUI(const string & path);

		/// Adds a function callback to the callbacks map.
		/// This needs to be called before calling parseUI, as many times as methods you want to use.
		/// The name should be the same as appears in the xml.
		void add_callback(const string & name, function< void() > fun)
		{
			callbacks[name] = fun;
		}

		//st::Canvas * getCanvas() { return canvas; }

	private:

		/// Parses the Screen node.
		/// Creates a new screen and starts parsing its child nodes.
		/// We assume an Screen can only have Layouts and Widgets as children.
		nanogui::Screen * parse_screen(const rapidxml::xml_node<> * screen_node);

		/// Parses a layout.
		/// Only Screen and Widget can have a Layout.
		nanogui::Layout * parse_layout (const rapidxml::xml_node<> * layout_node);

		/// Parses and creates a pointer to a Widget.
		void parseWidget  (nanogui::Widget * parent, rapidxml::xml_node<> * widget_node);

		/// Parses and creates a pointer to a Button.
		/// Accepted parameters: name, width, height, callback.
		void parseButton  (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);

		/// Parses and creates a pointer to a Canvas.
		/// Accepted parameters: width, height.
		void parseCanvas  (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);

		/// Parses and creates a pointer to a Label.
		/// Accepted parameters: name.
		void parseLabel   (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);

		/// Parses and creates a pointer to a Textboc.
		/// Accepted parameters: name, caption, width, height, editable.
		void parseTextBox (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);

	};

}