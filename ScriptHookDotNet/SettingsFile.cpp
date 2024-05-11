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

#include "SettingsFile.h"

#include "ContentCache.h"

#pragma managed

namespace GTA
{
	//namespace value {

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
		return ContentCache::GetINI(Filename);
	}

	// - - - Properties, Methods and Functions - - -
	void SettingsFile::Clear()
	{
		// TODO: Implement
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
		// TODO: Implement
		NotImplementedYet("SettingsFile::GetCategoryNames");
		return nullptr;
	}
	array<String^>^ SettingsFile::GetValueNames(String^ Category)
	{
		// TODO: Implement
		NotImplementedYet("SettingsFile::GetValueNames");
		return nullptr;
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

	int SettingsFile::GetValueInteger(String^ OptionName, String^ Category, int DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToInteger(val, DefaultValue);
	}
	float SettingsFile::GetValueFloat(String^ OptionName, String^ Category, float DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToFloat(val, DefaultValue);
	}
	bool SettingsFile::GetValueBool(String^ OptionName, String^ Category, bool DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToBoolean(val, DefaultValue);
	}
	Vector3 SettingsFile::GetValueVector3(String^ OptionName, String^ Category, Vector3 DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToVector3(val, DefaultValue);
	}
	Windows::Forms::Keys SettingsFile::GetValueKey(String^ OptionName, String^ Category, Windows::Forms::Keys DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToKey(val, DefaultValue);
	}
	GTA::Model SettingsFile::GetValueModel(String^ OptionName, String^ Category, GTA::Model DefaultValue)
	{
		String^ val = GetValueString(OptionName, Category, String::Empty);
		return Helper::StringToModel(val, DefaultValue);
	}

	void SettingsFile::SetValue(String^ OptionName, String^ Category, String^ Value)
	{
		instance->SetValue(Category, OptionName, Value);
	}
	void SettingsFile::SetValue(String^ OptionName, String^ Category, Vector3 Value)
	{
		SetValue(OptionName, Category, Value.ToString(", ", 4));
	}
	void SettingsFile::SetValue(String^ OptionName, String^ Category, bool Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}
	void SettingsFile::SetValue(String^ OptionName, String^ Category, float Value)
	{
		SetValue(OptionName, Category, Helper::FloatToString(Value, 4));
	}
	void SettingsFile::SetValue(String^ OptionName, String^ Category, int Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}
	void SettingsFile::SetValue(String^ OptionName, String^ Category, Windows::Forms::Keys Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}
	void SettingsFile::SetValue(String^ OptionName, String^ Category, GTA::Model Value)
	{
		SetValue(OptionName, Category, Value.ToString());
	}

	//}
}