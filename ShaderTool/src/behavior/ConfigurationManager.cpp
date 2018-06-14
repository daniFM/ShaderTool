/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	14/06/2018

Subject to license in LICENSE.txt

*/

#include <ConfigurationManager.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <rapidxml.hpp>

using namespace rapidxml;
using namespace std;

namespace st
{
	ConfigurationManager::ConfigurationManager(const string & path)
	{
		load_config(path);
	}

	bool ConfigurationManager::load_config(const string & scene_file_path)
	{
		// Read file content

		fstream xml_file(scene_file_path, fstream::in);

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

			if (root && string(root->name()) == "scene")
			{
				parse_config(root);
			}
		}

		return true;
	}

	bool ConfigurationManager::parse_config(xml_node<> * scene_node)
	{
		for (xml_node<> * child = scene_node->first_node(); child; child = child->next_sibling())
		{
			if (child->type() == node_element)
			{
				if (string(child->name()) == "entities")
				{
					//parse_entities(child);
				}
				//else if (string(child->name()) == "config")
				//{
				//	parse_config(child);
				//}
				//else if (string(child->name()) == "components")
				//{
				//	//parse_components(child, [CHILD ENTITY]);
				//}
				//...
			}
		}

		return true;
	}

	//bool Scene::parse_entities(xml_node<> * entities_node)
	//{
	//	char * name = "";
	//	cout << "Parseando entidades" << endl;

	//	/*for (
	//	xml_node<> * entity
	//	)*/

	//	/*for (
	//	xml_attribute<> * attribute = entities_node->first_attribute();
	//	attribute;
	//	attribute = attribute->next_attribute()
	//	)
	//	{
	//	cout << "Parseando " << string(attribute->name()) << endl;
	//	if (string(attribute->name()) == "name")
	//	{
	//	name = attribute->value();
	//	}
	//	}*/
	//	/*cout << "Name: " << name << endl;
	//	if (name == "") return false;*/

	//	for (xml_node<> * entity_tag = entities_node->first_node(); entity_tag; entity_tag = entity_tag->next_sibling())
	//	{
	//		if (entity_tag->type() == node_element)
	//		{
	//			if (string(entity_tag->name()) != "entity") return false;

	//			shared_ptr< Entity > entity(new Entity(this));
	//			name = entity_tag->first_attribute()->value();

	//			for (xml_node<> * child = entity_tag->first_node(); child; child = child->next_sibling())
	//			{
	//				if (child->type() == node_element)
	//				{
	//					if (string(child->name()) == "components")	//if (string(entity->name()) == "components")
	//					{
	//						if (!parse_components(child, *entity))
	//							return false;
	//					}
	//				}
	//			}

	//			entities[name] = entity;
	//			cout << "Parsed enity: " << name << endl;
	//		}
	//	}

	//	return true;
	//}
}