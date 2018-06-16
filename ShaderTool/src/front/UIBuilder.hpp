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
		
		nanogui::Screen * parseUI(const string & path);

		void add_callback(const string & name, function< void() > fun)
		{
			callbacks[name] = fun;
		}

		//st::Canvas * getCanvas() { return canvas; }

	private:

		nanogui::Screen * parse_screen(const rapidxml::xml_node<> * screen_node);

		nanogui::Layout * parse_layout (const rapidxml::xml_node<> * layout_node);

		void parseWidget  (nanogui::Widget * parent, rapidxml::xml_node<> * widget_node);
		void parseButton  (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);
		void parseCanvas  (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);
		void parseLabel   (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);
		void parseTextBox (nanogui::Widget * parent, rapidxml::xml_node<> * button_node);

	};

}