/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	14/06/2018

Subject to license in LICENSE.txt

*/

#pragma once



using namespace std;

namespace rapidxml
{
	template<class Ch>
	class xml_node;
}

namespace st
{
	class ConfigurationManager
	{


	public:

		ConfigurationManager(const string & path);

		bool load_config(const string & scene_file_path);

		bool parse_config(rapidxml::xml_node<char>* scene_node);

		//bool parse_entities(rapidxml::xml_node<char>* entities_node);
	};
}