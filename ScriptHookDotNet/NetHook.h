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
#pragma managed

namespace GTA
{

	CLASS_ATTRIBUTES
	private ref class NetHook sealed
	{
	public:
		static NetHook();

	private:
		NetHook() { }

		static bool bPrimary = false;

		static GTA::Forms::FormHost^ pFormHost;
		static GTA::base::Mouse^ pMouse;

	public:
		static property GTA::Forms::FormHost^ FormHost {
			GTA::Forms::FormHost^ get() {
				return pFormHost;
			}
		}
		static property GTA::base::Mouse^ Mouse {
			GTA::base::Mouse^ get() {
				return pMouse;
			}
		}
		static property bool isPrimary {
			bool get() {
				return bPrimary;
			}
		}
		static property bool isScriptDomain {
			bool get() {
				return !bPrimary;
			}
		}

		static void Log(String^ Text);
		static void Log(String^ Text, Exception^ ex);
		static void Log(Exception^ ex);
		static void Log(String^ Text, bool InsertEmptyLine, bool Truncate);

	private:
		static void LogInner(Exception^ ex);
		
	};

}