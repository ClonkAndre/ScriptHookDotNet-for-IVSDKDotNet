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

#pragma once
#pragma managed

namespace GTA
{
namespace Forms
{
	CLASS_ATTRIBUTES
	private ref class Mouse : base::Mouse
	{
	private:
		Drawing::PointF GetMovement();

	internal:
		Mouse(){}

	public:
		property bool Enabled
		{
			virtual bool get() override
			{
				return IVSDKDotNet::ImGuiIV::ForceCursor;
			}
			virtual void set(bool value) override;
		}
		property Drawing::PointF Position
		{
			virtual Drawing::PointF get() override
			{
				System::Numerics::Vector2 mPos = IVSDKDotNet::ImGuiIV::GetMousePos();
				return Drawing::PointF(mPos.X, mPos.Y);
			}
		}
		property Drawing::PointF Movement
		{
			virtual Drawing::PointF get() override
			{
				return GetMovement();
			}
		}
		property System::Windows::Forms::MouseButtons PressedButtons
		{
			virtual System::Windows::Forms::MouseButtons get() override
			{
				bool lD = IVSDKDotNet::ImGuiIV::IsMouseDown(IVSDKDotNet::Enums::eImGuiMouseButton::Left);
				bool rD = IVSDKDotNet::ImGuiIV::IsMouseDown(IVSDKDotNet::Enums::eImGuiMouseButton::Right);
				bool mD = IVSDKDotNet::ImGuiIV::IsMouseDown(IVSDKDotNet::Enums::eImGuiMouseButton::Middle);

				if (!lD && !rD && !mD)
					return System::Windows::Forms::MouseButtons::None;

				System::Windows::Forms::MouseButtons pressedButtons;

				if (lD)
					pressedButtons = pressedButtons | System::Windows::Forms::MouseButtons::Left;
				if (rD)
					pressedButtons = pressedButtons | System::Windows::Forms::MouseButtons::Right;
				if (mD)
					pressedButtons = pressedButtons | System::Windows::Forms::MouseButtons::Middle;

				return pressedButtons;
			}
		}

		virtual bool isButtonDown(System::Windows::Forms::MouseButtons Button) override
		{
			// TODO: Add support for XButton1 and XButton2 in the future (If needed)
			switch (Button)
			{
				case System::Windows::Forms::MouseButtons::Left:
					return IVSDKDotNet::ImGuiIV::IsMouseDown(IVSDKDotNet::Enums::eImGuiMouseButton::Left);
				case System::Windows::Forms::MouseButtons::Right:
					return IVSDKDotNet::ImGuiIV::IsMouseDown(IVSDKDotNet::Enums::eImGuiMouseButton::Right);
				case System::Windows::Forms::MouseButtons::Middle:
					return IVSDKDotNet::ImGuiIV::IsMouseDown(IVSDKDotNet::Enums::eImGuiMouseButton::Middle);
				default:
					return false;
			}
		}

	};
}
}