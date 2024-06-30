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

#include "SettingsFile.h"

#include "ContentCache.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	SettingsFile::SettingsFile(IVSDKDotNet::SettingsFile^ file)
	{
		instance = file;
	}
	SettingsFile::SettingsFile(String^ Filename)
	{
		instance = gcnew IVSDKDotNet::SettingsFile(Filename);
	}
	SettingsFile::!SettingsFile()
	{

	}

	SettingsFile^ SettingsFile::Open(String^ Filename)
	{
		if (String::IsNullOrWhiteSpace(Filename))
			return nullptr;

		String^ path = Filename;

		if (!File::Exists(path))
		{
			path = String::Format("{0}\\scripts\\{1}", IVSDKDotNet::IVGame::GameStartupPath, Filename);

			if (!File::Exists(path))
			{
				WRITE_TO_DEBUG_OUTPUT(String::Format("Could not find settings file {0}!", path));
			}
		}

		SettingsFile^ settings = gcnew SettingsFile(path);
		settings->Load();
		return settings;
	}

	// - - - Properties, Methods and Functions - - -
	void SettingsFile::Clear()
	{
		instance->Clear();
	}

	void SettingsFile::Load()
	{
		instance->Load();
	}
	bool SettingsFile::Save()
	{
		return instance->Save();
	}
	bool SettingsFile::SaveCopyTo(String^ Filename)
	{
		try
		{
			System::IO::File::WriteAllText(Filename, instance->ToString());
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	array<String^>^ SettingsFile::GetCategoryNames()
	{
		return instance->GetSectionNames();
	}
	array<String^>^ SettingsFile::GetValueNames(String^ Category)
	{
		return instance->GetValueNames(Category);
	}

	String^ SettingsFile::GetValueString(String^ OptionName, String^ Category, String^ DefaultValue)
	{
		return instance->GetValue(Category, OptionName, DefaultValue);
	}
	String^ SettingsFile::GetValueString(String^ OptionName, String^ Category)
	{
		return GetValueString(OptionName, Category, String::Empty);
	}
	String^ SettingsFile::GetValueString(String^ OptionName)
	{
		return GetValueString(OptionName, String::Empty, String::Empty);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, String^ Value)
	{
		instance->SetValue(Category, OptionName, Value);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, Vector3 Value)
	{
		SetValue(OptionName, Category, Value.ToString(", ", 4));
	}
	Vector3 SettingsFile::GetValueVector3(String^ OptionName, String^ Category, Vector3 DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToVector3(val, DefaultValue);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, bool Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}
	bool SettingsFile::GetValueBool(String^ OptionName, String^ Category, bool DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToBoolean(val, DefaultValue);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, float Value)
	{
		SetValue(OptionName, Category, Helper::FloatToString(Value, 4));
	}
	float SettingsFile::GetValueFloat(String^ OptionName, String^ Category, float DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToFloat(val, DefaultValue);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, int Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}
	int SettingsFile::GetValueInteger(String^ OptionName, String^ Category, int DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToInteger(val, DefaultValue);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, Windows::Forms::Keys Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}
	Windows::Forms::Keys SettingsFile::GetValueKey(String^ OptionName, String^ Category, Windows::Forms::Keys DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToKey(val, DefaultValue);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, GTA::Model Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}
	GTA::Model SettingsFile::GetValueModel(String^ OptionName, String^ Category, GTA::Model DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToModel(val, DefaultValue);
	}

}