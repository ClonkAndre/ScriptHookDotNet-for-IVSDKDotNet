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

#include "Script.h"

#include "Game.h"
#include "RemoteScriptDomain.h"
#include "Player.h"
#include "SettingsFile.h"
#include "fFormHost.h"
#include "vResources.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Script::Script()
	{
		// Set the current script to this script
		IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_SetCurrentScript(this);

		BlockWait = true;
		bWaiting = false;
		bRunning = true;

		// Information
		pInterval = 0;
		NextTick = System::DateTime::MinValue;
		pGUID = Guid::NewGuid();
		pGeneralInfo = String::Empty;

		// Get full path without file extension
		pFullPath = System::IO::Path::GetFullPath(String::Format(".\\scripts\\{0}", Name->Split(gcnew array<String^> { "." }, StringSplitOptions::None)[0]));

		// Get filename with extension
		pFilename = System::IO::Path::GetFileName(pFullPath) + ".net.dll";

		// Get filename without extension
		pFilenameWithoutExtension = System::IO::Path::GetFileName(pFullPath);

		// Lists
		BoundKeys = gcnew List<BoundKeyItem>();
		ScriptCommands = gcnew List<BoundScriptCommandItem>();
		ConsoleCommands = gcnew List<BoundCommandItem>();

		// Settings
		pSettings = gcnew SettingsFile(pFullPath + ".ini");
		pSettings->Load();

		// Other
		FormHost = gcnew GTA::Forms::FormHost(this);

		BlockWait = false;
	}

	// - - - Properties, Methods and Functions - - -
	GTA::SettingsFile^ Script::Settings::get()
	{
		if isNULL(pSettings)
		{
			pSettings = GTA::SettingsFile::Open(pFilenameWithoutExtension + ".ini");
			pSettings->Load();
		}

		return pSettings;
	}

	int Script::RenderID::get()
	{
		i32 id = -1;
		IVSDKDotNet::Native::Natives::GET_SCRIPT_RENDERTARGET_RENDER_ID(id);
		return id;
	}

	int Script::Interval::get()
	{
		return pInterval;
	}
	void Script::Interval::set(int value)
	{
		if (value > 0)
		{
			pInterval = value;
			NextTick = DateTime::Now + TimeSpan(0, 0, 0, 0, value);
		}
		else
		{
			pInterval = 0;
			NextTick = DateTime::MinValue;
		}
	}

	bool Script::isKeyPressed(System::Windows::Forms::Keys Key)
	{
		if (Game::Console->isActive)
			return false;

		return IVSDKDotNet::Helper::IsKeyPressedAsync(Key);
	}

	GTA::Player^ Script::Player::get()
	{
		return Game::LocalPlayer;
	}

	GTA::value::Resources^ Script::Resources::get()
	{
		if isNULL(pResources)
			pResources = gcnew GTA::value::Resources(this);

		return pResources;
	}

	bool Script::Exists(System::Object^ Object)
	{
		if isNULL(Object)
			return false;

		if (Object->GetType()->IsSubclassOf(GTA::base::Object::typeid))
			return ((GTA::base::Object^)Object)->Exists();

		return true;
	}
	bool Script::Exists(GTA::base::Object^ GtaObject)
	{
		if (Object::ReferenceEquals(GtaObject, nullptr))
			return false;

		return GtaObject->Exists();
	}

	bool Script::CanWaitNow::get()
	{
		if (BlockWait)
			return false;

		return true;
	}

	void Script::Wait(int ms)
	{
		if (BlockWait)
		{
			throw gcnew System::InvalidOperationException("Illegal call to Wait()!");
			return;
		}

		bWaiting = true;
		BlockWait = true;

		// TODO: Call wait here

		bWaiting = false;
		BlockWait = false;
	}

	void Script::Abort()
	{
		BlockWait = true;
		bRunning = false;
	}

	void Script::SendScriptCommand(GTA::Script^ Script, String^ Command, ... array<System::Object^>^ Parameter)
	{

	}
	void Script::SendScriptCommand(Guid ScriptGUID, String^ Command, ... array<System::Object^>^ Parameter)
	{

	}
	void Script::SendScriptCommand(String^ ScriptGUID, String^ Command, ... array<System::Object^>^ Parameter)
	{
		SendScriptCommand(Guid(ScriptGUID), Command, Parameter);
	}
	bool Script::isScriptRunning(Guid GUID)
	{
		return false;
	}
	bool Script::isScriptRunning(String^ GUID)
	{
		return isScriptRunning(Guid(GUID));
	}

	void Script::BindKey(WinForms::Keys Key, KeyPressDelegate^ MethodToBindTo)
	{
		BoundKeys->Add(BoundKeyItem(Key, MethodToBindTo));
	}
	void Script::BindKey(WinForms::Keys Key, bool Shift, bool Ctrl, bool Alt, KeyPressDelegate^ MethodToBindTo)
	{
		Key = Key & WinForms::Keys::KeyCode;
		if (Shift) Key = Key | WinForms::Keys::Shift;
		if (Ctrl) Key = Key | WinForms::Keys::Control;
		if (Alt) Key = Key | WinForms::Keys::Alt;

		BindKey(Key, MethodToBindTo);
	}
	void Script::BindConsoleCommand(String^ Command, ConsoleCommandDelegate^ MethodToBindTo)
	{
		ConsoleCommands->Add(BoundCommandItem(Command, MethodToBindTo));
	}
	void Script::BindConsoleCommand(String^ Command, ConsoleCommandDelegate^ MethodToBindTo, String^ HelpText)
	{
		BindConsoleCommand(Command, MethodToBindTo);
	}
	void Script::BindScriptCommand(String^ Command, ScriptCommandDelegate^ MethodToBindTo)
	{
		ScriptCommands->Add(BoundScriptCommandItem(Command, MethodToBindTo));
	}
	void Script::BindPhoneNumber(String^ PhoneNumber, PhoneDialDelegate^ MethodToBindTo)
	{

	}

	void Script::UnbindKey(WinForms::Keys Key)
	{
		for (int i = BoundKeys->Count-1; i >= 0; i--)
		{
			if (BoundKeys[i].Key == Key)
				BoundKeys->RemoveAt(i);
		}
	}
	void Script::UnbindKey(WinForms::Keys Key, bool Shift, bool Ctrl, bool Alt)
	{
		Key = Key & WinForms::Keys::KeyCode;

		if (Shift) Key = Key | WinForms::Keys::Shift;
		if (Ctrl) Key = Key | WinForms::Keys::Control;
		if (Alt) Key = Key | WinForms::Keys::Alt;

		UnbindKey(Key);
	}
	void Script::UnbindConsoleCommand(String^ Command)
	{
		String^ cmd = Command->ToLower();

		for (int i = ConsoleCommands->Count - 1; i >= 0; i--)
		{
			if (ConsoleCommands[i].Command == cmd)
				ConsoleCommands->RemoveAt(i);
		}
	}
	void Script::UnbindScriptCommand(String^ Command)
	{
		String^ cmd = Command->ToLower();

		for (int i = ScriptCommands->Count-1; i >= 0; i--)
		{
			if (ScriptCommands[i].Command == cmd)
				ScriptCommands->RemoveAt(i);
		}
	}
	void Script::UnbindPhoneNumber(String^ PhoneNumber)
	{

	}

	void Script::ProcessBoundKeys(WinForms::Keys Key)
	{
		for (int i = 0; i < BoundKeys->Count; i++)
		{
			if (BoundKeys[i].Key == Key)
			{
				BoundKeys[i].Delegate->Invoke();
				return;
			}
		}
	}
	//void Script::ProcessBoundConsoleCommands(ScriptCommandEventArgs^ sceva)
	//{
	//	String^ cmd = sceva->Command->ToLower();

	//	for (int i = 0; i < ScriptCommands->Count; i++)
	//	{
	//		if (ScriptCommands[i].Command == cmd)
	//		{
	//			ScriptCommands[i].Delegate->Invoke(sceva->sender, sceva->Parameters);
	//			return;
	//		}
	//	}
	//}
	void Script::ProcessBoundScriptCommand(ScriptCommandEventArgs^ sceva)
	{
		String^ cmd = sceva->Command->ToLower();

		for (int i = 0; i < ScriptCommands->Count; i++)
		{
			if (ScriptCommands[i].Command == cmd)
			{
				ScriptCommands[i].Delegate->Invoke(sceva->sender, sceva->Parameters);
				return;
			}
		}
	}

	void Script::DoTick()
	{
		if (!bRunning)
			return;

		BlockWait = false;

		// Always tick
		EachTick(this, EventArgs::Empty);

		// Tick with interval
		if (Interval > 0)
		{
			if (NextTick > System::DateTime::Now)
				return;

			NextTick = System::DateTime::Now + System::TimeSpan(0, 0, 0, 0, Interval);
			Tick(this, EventArgs::Empty);
		}
		else
		{
			Tick(this, EventArgs::Empty);
		}

		BlockWait = true;
	}
	void Script::DoPerFrameDrawing(GTA::GraphicsEventArgs^ e)
	{
		if (!bRunning)
			return;

		bool bw = BlockWait;
		BlockWait = true;
		
		PerFrameDrawing(this, e);
		FormHost->TriggerDragging();

		BlockWait = bw;
	}
	void Script::DoPerFrameScriptDrawing()
	{
		if (!bRunning)
			return;

		bool bw = BlockWait;
		BlockWait = true;
		
		PerFrameScriptDrawing(this, EventArgs::Empty);

		BlockWait = bw;
	}
	void Script::DoKeyDown(GTA::KeyEventArgs^ args)
	{
		if (!bRunning)
			return;

		KeyDown(this, args);
	}
	void Script::DoKeyUp(GTA::KeyEventArgs^ args)
	{
		if (!bRunning)
			return;

		KeyUp(this, args);
	}

	String^ Script::ToString()
	{
		return Name;
	}

}