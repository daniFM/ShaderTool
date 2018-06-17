/*

Author: Daniel Fern�ndez (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <string>
#include <memory>
#include <vector>
#include <Path.hpp>

#include <Shader.hpp>

using namespace std;

namespace st
{
	/// Manages the shaders files.
	class DocumentManager
	{
	private:

		Shader shader;

		vector < shared_ptr <Shader > > default_shaders;

		string text_editor;

	public:

		const string shaders_path;

	public:

		/// Inits the DocumentManager and copies a template shader into the shadrers folder.
		/// The template is copied to make sure the templates are never overwritten.
		DocumentManager(string path, string editor, vector < shared_ptr <Shader > > shaders)
			:
			shaders_path	(path + "\\Shaders"),
			text_editor     (editor),
			default_shaders (shaders)
		{
			createFromTemplate("newShader.glsl");
		}

		/// Reloads the current set shader.
		/// @param open Wether or not open the shader with the text editor.
		bool loadShader(bool open=false);

		/// Loads a new shader.
		/// If the shader file is not found, creates a new one in the provided path from the template.
		/// @param open Wether or not open the shader with the text editor.
		bool loadShader(string path, bool open=false);

		/// Creates a new shader file from the configured template.
		bool createFromTemplate(string name);

		/// Renames the current shader.
		/// This prevents the shader from being overwritten if it is the "newShader".
		/// @param name Name of the new shader. Must not have extension.
		bool saveShader(string name);

		/// Opens the current shader with the configured text editor.
		void openShader();

		shared_ptr<Shader> getShader()
		{
			return make_shared<Shader>(shader);
		}

	};
}
