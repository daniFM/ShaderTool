/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	14/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>
#include <vector>

#include <Shader.hpp>

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
		string shader_type;

		vector < shared_ptr < Shader > > default_shaders;

	public:

		const string data_path;
		const string def_shaders_path;
		const string textures_path;
		const string config_path;

	public:

		ConfigurationManager(const string & path);

		vector < shared_ptr < Shader > > getDefaultShaders()
		{
			return default_shaders;
		}

	private:

		bool load_config	(const string & config_file_path);
		bool parse_config	(rapidxml::xml_node<char>* config_node);
		bool parse_shaders	(rapidxml::xml_node<char>* shaders_node);
		//bool parse_layout	(rapidxml::xml_node<char>* layout_node);

	};
}