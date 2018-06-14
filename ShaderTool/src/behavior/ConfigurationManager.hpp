/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	14/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>

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

		Shader default_shader;

	public:

		const string data_path;
		const string shaders_path;
		const string textures_path;
		const string config_path;

	public:

		ConfigurationManager(const string & path);

		shared_ptr < Shader > getDefaultShader()
		{
			return make_shared<Shader>(default_shader);
		}

	private:

		bool load_config(const string & config_file_path);
		bool parse_config(rapidxml::xml_node<char>* config_node);
		bool parse_shaders(rapidxml::xml_node<char>* shaders_node);

	};
}