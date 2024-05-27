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

#include "fControl.h"

#include "Font.h"
#include "Graphics.h"

#pragma managed

namespace GTA
{
namespace Forms
{

	Control::Control()
	{
		bVisible = true;
		pName = String::Empty;
		pControls = gcnew ControlCollection(this);
		pBackColor = Drawing::Color::FromArgb(0,200,200,200);
		pForeColor = Drawing::Color::FromArgb(255,255,255,255);
		pLocation = Drawing::Point(0,0);
		pBorderColorLight = Drawing::Color::FromArgb(100, 255, 255, 255);
		pBorderColorDark = Drawing::Color::FromArgb(100, 0, 0, 0);
		InitEarlyValues();
		pSize = DefaultSize;
	}

	void Control::Visible::set(bool value)
	{
		if (bVisible == value)
			return;

		bVisible = value;
		OnVisibleChanged(EventArgs::Empty);
	}

	void Control::Parent::set(Control^ value)
	{
		if (System::Object::ReferenceEquals(value, pParent))
			return;

		if isNotNULL(pParent)
			pParent->Controls->Remove(this);

		pParent = value;
		pParent->Controls->Add(this);
	}

	GTA::Font^ Control::DefaultFont::get()
	{
		if isNULL(pDefaultFont) pDefaultFont = gcnew GTA::Font(16.0f, FontScaling::Pixel);
		return pDefaultFont;
	}

	GTA::Font^ Control::Font::get()
	{
		if isNULL(pFont) {
			if isNotNULL(pParent) {
				pFont = gcnew GTA::Font(pParent->Font);
			} else {
				pFont = gcnew GTA::Font(DefaultFont);
			}
		}
		return pFont;
	}

	Drawing::Point Control::PointToClient(Point ScreenPoint)
	{
		if isNotNULL(Parent) ScreenPoint = Parent->PointToClient(ScreenPoint);
		return Helper::SubtractPoint(Helper::SubtractPoint(ScreenPoint, Location), ClientRectangle.Location);
	}
	Drawing::Point Control::PointToScreen(Point ClientPoint)
	{
		Drawing::Point loc = Helper::AddPoint(Helper::AddPoint(Location, ClientRectangle.Location), ClientPoint);
		if isNULL(Parent) return loc;
		return Parent->PointToScreen(loc);
	}

	bool Control::isPointInside(Point ScreenPoint, bool NotWhenInSubcontrol)
	{
		return true;
	}
	Control^ Control::GetControlAt(Point ScreenPoint)
	{
		return this;
	}

}
}