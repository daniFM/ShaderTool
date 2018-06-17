/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	12/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <nanogui/screen.h>
#include <Canvas.hpp>

#include <DocumentManager.hpp>
#include <ConfigurationManager.hpp>
#include <UIBuilder.hpp>

namespace st
{
	/// Controls the application Front-end.
	class UIController
	{
	private:

		nanogui::Screen * screen;

	public:

		Canvas * canvas;
		//Canvas3D * canvas;

		nanogui::TextBox * save_shader_name;
		nanogui::TextBox * open_shader_name;
		nanogui::TextBox * texture_path;

	private:

		shared_ptr < st::DocumentManager >      doc_manager;
		shared_ptr < st::ConfigurationManager > conf_manager;

	public:

		/// Creates the controller and creates the UIBuilder.
		/// @param dm DocumentManager used in the application.
		/// @param cm CunfigurationManager
		UIController(shared_ptr<st::DocumentManager> dm, shared_ptr<st::ConfigurationManager> cm);

		/// Starts the drawing of nanogui and enters it's main loop.
		void run();

	private:

		/// Preview button functionality.
		/// Reads the shader from the file and sets it in the canvas.
		void previewButton();

		/// Edit button functionality.
		/// Opens the current file with the configured text editor.
		void editButton();

		/// Save button functionality.
		/// Saves the current shader with another name.
		/// By not using this, if you are editing the default "newShader" will be overwritten the next time the program is ran.
		void saveButton();

		/// Open shader functionality.
		/// Opens a new shader from the configured template.
		void openButton();

		/// Open texture functionality.
		/// Loads a new texture from the configured path.
		void openTexButton();

		/// Loads and sets the texture from the provided path.
		void loadTexture(string path);

	};
}