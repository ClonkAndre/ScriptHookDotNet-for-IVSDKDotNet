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

// IV-SDK .NET translation layer by ItsClonkAndre

#include "stdafx.h"

#include "fMouse.h"

#include "Game.h"
#include "Player.h"

#pragma managed

namespace GTA
{
	namespace Forms
	{

		// - - - Properties, Methods and Functions - - -
		void Mouse::Enabled::set(bool value)
		{
			if (value)
				Game::LocalPlayer->CanControlCharacter = false;
			else
				Game::LocalPlayer->CanControlCharacter = true;

			IVSDKDotNet::ImGuiIV::ForceCursor = value;
		}

		Drawing::PointF Mouse::GetMovement()
		{
			float s = IVSDKDotNet::Native::Natives::GET_MOUSE_SENSITIVITY() * 0.0025f;
			float ratio = float(GTA::Game::Resolution.Width) / float(GTA::Game::Resolution.Height); // Y axis has to be faster
			int x = 0; int y = 0;
			IVSDKDotNet::Native::Natives::GET_MOUSE_INPUT(x, y);
			return Drawing::PointF(float(x) * s, float(y) * s * ratio);
		}

	}
}