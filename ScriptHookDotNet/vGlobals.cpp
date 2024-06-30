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

#include "vGlobals.h"

#pragma managed

namespace GTA
{
	namespace value
	{

		// - - - Properties, Methods and Functions - - -
		bool Globals::AreGlobalsSupported::get()
		{
			return IVSDKDotNet::IVTheScripts::GetGlobalAddress(0) != 0;
		}

		int Globals::ReadInteger(int index)
		{
			return IVSDKDotNet::IVTheScripts::GetGlobalInteger(index);
		}
		float Globals::ReadFloat(int index)
		{
			return IVSDKDotNet::IVTheScripts::GetGlobalFloat(index);
		}
		String^ Globals::ReadString(int index)
		{
			return IVSDKDotNet::IVTheScripts::GetGlobalString(index);
		}

		void Globals::Write(int index, int value)
		{
			IVSDKDotNet::IVTheScripts::SetGlobal(index, value);
		}
		void Globals::Write(int index, float value)
		{
			IVSDKDotNet::IVTheScripts::SetGlobal(index, value);
		}
		void Globals::Write(int index, String^ value, int MaxLength)
		{
			if (MaxLength <= 0)
				value = String::Empty;
			else if (value->Length > MaxLength)
				value = value->Substring(0, MaxLength);

			IVSDKDotNet::IVTheScripts::SetGlobal(index, value);
		}
	}
}