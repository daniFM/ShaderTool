/*

Author: Daniel Fern�ndez (https://github.com/daniFM)
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
	/// Contains the application configuration and loads it.
	class ConfigurationManager
	{
		string shader_type;

		vector < shared_ptr < Shader > > default_shaders;

		string text_editor;

	public:

		const string data_path;
		const string def_shaders_path;
		const string textures_path;
		const string config_path;

	public:

		/// Creates a configuration manager.
		/// @param path Path to the root file folder.
		ConfigurationManager(const string & path);

		/// Returns a vector with the configured shader templates.
		vector < shared_ptr < Shader > > getDefaultShaders()
		{
			return default_shaders;
		}

		/// Returns the path to the configured text editor.
		string getEditor()
		{
			return text_editor;
		}

	private:

		/// Loads the config xml and stars the parsing.
		bool load_config	(const string & config_file_path);
		/// Parses root node of the configuration.
		bool parse_config	(rapidxml::xml_node<char>* config_node);
		/// Parses template shaders.
		bool parse_shaders	(rapidxml::xml_node<char>* shaders_node);
		//bool parse_layout	(rapidxml::xml_node<char>* layout_node);

	};
}