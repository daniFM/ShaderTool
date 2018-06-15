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
#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/checkbox.h>
#include <nanogui/button.h>
#include <nanogui/toolbutton.h>
#include <nanogui/popupbutton.h>
#include <nanogui/combobox.h>
#include <nanogui/progressbar.h>
#include <nanogui/entypo.h>
#include <nanogui/messagedialog.h>
#include <nanogui/textbox.h>
#include <nanogui/slider.h>
#include <nanogui/imagepanel.h>
#include <nanogui/imageview.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/colorwheel.h>
#include <nanogui/graph.h>
#include <nanogui/tabwidget.h>

#include <Canvas.hpp>

using namespace std;
using namespace nanogui;
using namespace st;

namespace st
{
	/*enum NType
	{
		Screen,
		Widget,
		Button
	};*/

	class CNode
	{
		map < string, shared_ptr < CNode > > children;

	protected:

		Widget * widget;

		shared_ptr < CNode > parent;

		map < string, void(*)() > callbacks;

	public:

		CNode() = default;
		//CNode(string name, string type);

		Widget * get()
		{
			return widget;
		}

		void addChild(string name, shared_ptr < CNode > child)
		{
			children[name] = child;
			widget->addChild(child->get());
		}

		void addCallback(string name, void(*function)())
		{
			callbacks[name] = function;
		}
		
		void setGroupLayout()
		{
			widget->setLayout(new GroupLayout);
		}

		void setBoxLayout(string str_orientation, string str_alignment, int margin, int spacing)
		{
			Orientation orientation;
			Alignment alignment;

			if      (str_orientation == "Horizontal") orientation = Orientation::Horizontal;
			else if (str_orientation == "Vertical")   orientation = Orientation::Vertical;

			if		(str_alignment == "Fill")		alignment = Alignment::Fill;
			else if (str_alignment == "Maximum")	alignment = Alignment::Maximum;
			else if (str_alignment == "Middle")		alignment = Alignment::Middle;
			else if (str_alignment == "Minimum")	alignment = Alignment::Minimum;

			widget->setLayout(new BoxLayout(orientation, alignment, margin, spacing));
		}

	};

	class CScreen : public CNode
	{

	public:

		CScreen(string name, int width, int height, bool fullscreen)
			/*:
			widget(nanogui::Screen(Eigen::Vector2i(width, height), name, fullscreen))*/
		{
			widget = new Screen(Eigen::Vector2i(width, height), name, fullscreen);
		}
	};

	class CLabel : public CNode
	{

	public:

		CLabel(string caption)
		{
			widget = new Label(parent->get(), caption);
		}
	};

	class CButton : public CNode
	{

	public:

		CButton(string name, int width = 0, int height = 0, string callback = "")
		{
			//widget = static_cast<Button * >(widget);
			Button * button = new Button(parent->get(), name);
			widget = button;

			if (width != 0)
				widget->setFixedWidth(width);
			if (height != 0)
				widget->setFixedWidth(height);

			if (callback != "")
				button->setCallback(callbacks[callback]);	//(std::bind(callbacks[callback], parent->get())
		}
	};

	class CTextBox : public CNode
	{

	public:

		CTextBox(string caption, int width = 0, int height = 0)
		{
			//widget = new TextBox(parent->get());
			TextBox * textbox = new TextBox(parent->get());
			widget = textbox;

			if (width != 0)
				widget->setFixedWidth(width);
			if (height != 0)
				widget->setFixedWidth(height);

			textbox->setEditable(true);
			textbox->setValue(caption);
		}
	};

	class CCanvas : public CNode
	{

	public:

		CCanvas(int width = 0, int height = 0)
		{
			widget = new Canvas(parent->get());

			if (width != 0)
				widget->setFixedWidth(width);
			if (height != 0)
				widget->setFixedWidth(height);
		}
	};
}