/*

Author: Daniel Fernández (https://github.com/daniFM)
Date:	14/06/2018

Subject to license in LICENSE.txt

*/

#pragma once

#include <map>
#include <memory>
#include <string>

#include <nanogui/widget.h>

using namespace std;

namespace st
{
	enum NType
	{
		Screen,
		Widget,
		Button
	};

	class CNode
	{
		map < string, shared_ptr < CNode > > children;

		nanogui::Widget * widget;

	public:

		CNode() = default;

		CNode(string name, NType type)

	};
}