/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	16/05/2018

Subject to license in LICENSE.txt

*/

#include <cassert>
#include <iostream>

#include <Path.hpp>

#include <UIController.hpp>
#include <DocumentManager.hpp>
#include <ConfigurationManager.hpp>

using namespace std;
using namespace st;

int main(int number_of_arguments, char * arguments[])
{
	pm::Path path;
	path.test();

	//Check arguments

	cout << number_of_arguments << " Arguments:" << endl;
	for (int i = 0; i < number_of_arguments; i++)
	{
		cout << arguments[i] << endl;
	}

	// Default path
	string data_path = "data";

	if (number_of_arguments > 1)
	{
		data_path = arguments[1];
	}

	//Get configuration

	shared_ptr < ConfigurationManager > config = make_shared<ConfigurationManager>(data_path);

	//Set document

	shared_ptr < DocumentManager > document_manager = make_shared<DocumentManager>
		(
			data_path,
			config->getEditor(),
			config->getDefaultShaders()
		);

	
	try
	{
		nanogui::init();
		{

			st::UIController ui(document_manager, config);

			ui.run();			

		}
		nanogui::shutdown();
	}
	catch (const std::runtime_error & error)
	{
		std::cerr << "Uncaught exception at main(): " << error.what() << std::endl;

		return -1;
	}

	return 0;

}