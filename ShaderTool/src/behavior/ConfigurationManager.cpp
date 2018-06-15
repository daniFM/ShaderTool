/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	14/06/2018

Subject to license in LICENSE.txt

*/

#include <ConfigurationManager.hpp>

#include <iostream>
#include <fstream>
#include <rapidxml.hpp>

using namespace rapidxml;
using namespace std;

namespace st
{
	ConfigurationManager::ConfigurationManager(const string & path)
		:
		data_path		(path),
		def_shaders_path(path + "\\config"),
		textures_path	(path + "\\Textures"),
		config_path		(path + "\\config")
	{
		load_config(config_path + "\\config.xml");
	}

	bool ConfigurationManager::load_config(const string & config_file_path)
	{
		// Read file content

		fstream xml_file(config_file_path, fstream::in);

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

			if (root && string(root->name()) == "config")
			{
				parse_config(root);
			}
		}

		return true;
	}

	bool ConfigurationManager::parse_config(xml_node<> * config_node)
	{
		for (xml_node<> * child = config_node->first_node(); child; child = child->next_sibling())
		{
			if (child->type() == node_element)
			{
				if (string(child->name()) == "shader_type")
				{
					shader_type = child->contents();
				}
				else if (string(child->name()) == "default_shaders")
				{
					parse_shaders(child);
				}
				/*else if (string(child->name()) == "Layout")
				{
					parse_layout(child);
				}*/
			}
		}

		return true;
	}

	bool ConfigurationManager::parse_shaders(xml_node<> * shaders_node)
	{
		cout << "Parsing default shaders" << endl;


		for (xml_node<> * shader_tag = shaders_node->first_node(); shader_tag; shader_tag = shader_tag->next_sibling())
		{
			if (shader_tag->type() == node_element)
			{
				
				string s_name = shader_tag->first_attribute()->value();
				string code = string(shader_tag->contents());

				if (string(shader_tag->name()) == shader_type)
					default_shaders.insert(default_shaders.begin(), make_shared<Shader>(s_name, def_shaders_path + "\\" + s_name + ".glsl", code));
				else
					default_shaders.push_back(make_shared<Shader>(s_name, def_shaders_path + "\\" + s_name + ".glsl", code));
			}
		}

		return true;
	}

	/*
	bool ConfigurationManager::parse_layout(xml_node<> * layout_node)
	{
		cout << "Parsing application layout" << endl;

		for (xml_node<> * layout_tag = layout_node->first_node(); layout_tag; layout_tag = layout_tag->next_sibling())
		{
			if (layout_tag->type() == node_element)
			{
				if (layout_tag->name() == "layout")
				{

				}
				else if (layout_tag->name() == "Screen")
				{
					xml_attribute<> * attr = layout_tag->first_attribute();
					root = make_shared<CScreen>
						(
							attr->value(),
							attr->next_attribute()->value(),
							attr->next_attribute()->value(),
							attr->next_attribute()->value()
						);

				}

				parse_layout(layout_tag);
			}
		}
	}
	*/
}