/*
* Copyright (c) 2009-2011 Hazard (hazard_x@gmx.net / twitter.com/HazardX)
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "stdafx.h"

#include "fListbox.h"

#include "Font.h"
#include "Graphics.h"
#include "fScrollbar.h"

#pragma managed

using namespace IVSDKDotNet;

namespace GTA
{
namespace Forms
{

	Listbox::Listbox()
	{
		BackColor = Drawing::Color::FromArgb(50, 255, 255, 255);
		pSelectionColor = Drawing::Color::FromArgb(127, 48, 64, 192);
		pBorder = true;
		pSelectedIndex = -1;
		pScrollbarSize = 16;

		scr = gcnew Scrollbar();
		ResizeScrollbar();
		scr->MinValue = 0;
		scr->Value = 0;
		this->Controls->Add(scr);
	}

	void Listbox::ResizeScrollbar()
	{
		scr->Size = Drawing::Size(pScrollbarSize, Size.Height);
		scr->Location = Point(Size.Width - pScrollbarSize, 0);
	}

	void Listbox::OnPaint()
	{
		if (ImGuiIV::BeginListBox(Text))
		{

			for (int i = 0; i < Items->Count; i++)
			{
				ListboxItem^ item = Items[i];

				if (ImGuiIV::Selectable(item->DisplayText, i == pSelectedIndex))
					pSelectedIndex = i;
			}

			ImGuiIV::EndListBox();
		}
	}

	void Listbox::OnMouseDown(GTA::MouseEventArgs^ e)
	{
		int pos = this->PointToClient(e->PixelLocation).Y - 2;
		int id = -1;
		if (pos >= 0) {
			id = scr->Value + pos / int(Font->GetLineHeight(FontScaling::Pixel));
			if (id >= Items->Count) id = -1;
			if (id >= 0) SelectedIndex = id;
		}
		Control::OnMouseDown(e);
	}

}
}