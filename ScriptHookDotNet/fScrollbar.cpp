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

#pragma once
#include "stdafx.h"

#include "fScrollbar.h"

#include "Graphics.h"

#pragma managed

namespace GTA {
namespace Forms {

	void Scrollbar::Value::set(int value) {
		if (value < pMinValue) value = pMinValue;
		if (value > MaxValue) value = MaxValue;
		if (pValue == value) return;
		pValue = value;
		OnValueChanged(EventArgs::Empty);
	}

	void Scrollbar::OnPaint(GTA::GraphicsEventArgs^ e) {

		
	}

	void Scrollbar::OnMouseDown(GTA::MouseEventArgs^ e) {
		if (e->Button == Windows::Forms::MouseButtons::Left) {
			Drawing::Point pos = e->PixelLocation;
			if (pButtonRectMinus.Contains(pos)) {
				pDownOn = 2; pWasDownOn = 2;
			} else if (pButtonRectPlus.Contains(pos)) {
				pDownOn = 3; pWasDownOn = 3;
			} else if (pHasGrabHandle) {
				if (pButtonRectGrabHandle.Contains(pos)) {
					pDownOn = 1; pWasDownOn = 1;
					if (bHorizontal)
						pMouseOffset = pos.X - pButtonRectGrabHandle.X;
					else
						pMouseOffset = pos.Y - pButtonRectGrabHandle.Y;
				} else if (pSpaceRectMinus.Contains(pos)) {
					Value -= LargeChange;
				} else if (pSpaceRectPlus.Contains(pos)) {
					Value += LargeChange;
				}
			}
		}
		Control::OnMouseDown(e);
	}
	void Scrollbar::OnDragRelease(GTA::MouseEventArgs^ e) {
		pDownOn = 0;
		Control::OnDragRelease(e);
	}
	void Scrollbar::OnClick(GTA::MouseEventArgs^ e) {
		if (e->Button == Windows::Forms::MouseButtons::Left) {
			Drawing::Point pos = e->PixelLocation;
			if ((pWasDownOn == 2) && pButtonRectMinus.Contains(pos)) {
				Value -= SmallChange;
			} else if ((pWasDownOn == 3) && pButtonRectPlus.Contains(pos)) {
				Value += SmallChange;
			}
		}
		Control::OnClick(e);
	}
	void Scrollbar::OnDragging(GTA::MouseEventArgs^ e) {

	}

}
}