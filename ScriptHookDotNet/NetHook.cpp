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

#include "NetHook.h"

#include "Console.h"
#include "D3D_Device.h"
#include "Game.h"
#include "Graphics.h"
#include "KeyboardLayout.h"
#include "KeyWatchDog.h"
#include "Player.h"
#include "RemoteScriptDomain.h"
#include "fFormHost.h"
#include "fMouse.h"

#pragma managed

namespace GTA
{

	void NetHook::VerboseLog(String^ Text)
	{
		if (VERBOSE)
			IVSDKDotNet::IVGame::Console::PrintWarning(String::Format("[SHDN: NetHook Verbose Log] {0}", Text));
	}
	void NetHook::VerboseLog(String^ Text, Exception^ ex)
	{
		if (VERBOSE)
			IVSDKDotNet::IVGame::Console::PrintWarning(String::Format("[SHDN: NetHook Exception Verbose] {0} - Exception: {1}", Text, ex));
	}
	void NetHook::VerboseLog(Exception^ ex)
	{
		if (VERBOSE)
			IVSDKDotNet::IVGame::Console::PrintWarning(String::Format("[SHDN: NetHook Exception Verbose] {0}", ex));
	}

	void NetHook::Log(String^ Text)
	{
		Log(Text, false, false);
	}
	void NetHook::Log(String^ Text, Exception^ ex)
	{
		IVSDKDotNet::IVGame::Console::PrintWarning(String::Format("[SHDN: NetHook Exception] {0} - Exception: {1}", Text, ex));
	}
	void NetHook::Log(Exception^ ex)
	{
		IVSDKDotNet::IVGame::Console::PrintWarning(String::Format("[SHDN: NetHook Exception] {0}", ex));
	}
	void NetHook::Log(String^ Text, bool InsertEmptyLine, bool Truncate)
	{
		IVSDKDotNet::IVGame::Console::PrintWarning(String::Format("[SHDN: NetHook Log] {0}", Text));
	}
	void NetHook::LogInner(Exception^ ex)
	{
		IVSDKDotNet::IVGame::Console::PrintWarning(String::Format("[SHDN: NetHook LogInner Exception] {0}", ex));
	}

}