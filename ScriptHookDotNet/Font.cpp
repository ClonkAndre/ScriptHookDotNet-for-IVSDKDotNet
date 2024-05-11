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

#include "Font.h"

#include "Graphics.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Font::Font(Font^ inheritedFont)
	{
		InitValues();
		inherited = inheritedFont;

		RegisterFont();
	}

	Font::Font(String^ FontFamily, float Height, FontScaling Scaling, bool Bold, bool Italic) 
	{
		InitValues();
		pFontFamilyName = FontFamily;
		pHeight = Height;
		pScaling = Scaling;
		bBold = Bold;
		bItalic = Italic;

		RegisterFont();
	}
	Font::Font(String^ FontFamily, float Height, FontScaling Scaling)
	{
		InitValues();
		pFontFamilyName = FontFamily;
		pHeight = Height;
		pScaling = Scaling;

		RegisterFont();
	}
	Font::Font(float Height, FontScaling Scaling, bool Bold, bool Italic)
	{
		InitValues();
		pHeight = Height;
		pScaling = Scaling;
		bBold = Bold;
		bItalic = Italic;

		RegisterFont();
	}
	Font::Font(float Height, FontScaling Scaling)
	{
		InitValues();
		pHeight = Height;
		pScaling = Scaling;

		RegisterFont();
	}
	Font::Font(Drawing::Font^ WindowsFont)
	{
		Font::Font(WindowsFont->FontFamily->Name, (float)WindowsFont->Height, FontScaling::Pixel, WindowsFont->Bold, WindowsFont->Italic);
	}
	Font::Font(Font^ BaseFont, float NewHeight, FontScaling NewScaling)
	{
		InitValues();
		pFontFamilyName = BaseFont->FontFamily;
		bBold = BaseFont->Bold;
		bItalic = BaseFont->Italic;
		pColor = BaseFont->Color;
		pEffect = BaseFont->Effect;
		pEffectSize = BaseFont->EffectSize;
		pEffectColor = BaseFont->EffectColor;
		pHeight = NewHeight;
		pScaling = NewScaling;

		RegisterFont();
	}

	Font::Font()
	{
		InitValues();
		RegisterFont();
	}
	Font::~Font()
	{ // Dispose
		this->!Font();
	}
	Font::!Font()
	{ // Finalize

	}

	// - - - Properties, Methods and Functions - - -
	void Font::InitValues()
	{
		pFontFamilyName = "Arial";
		pHeight = 0.5f; //14
		bBold = true;
		bItalic = false;
		pColor = Drawing::Color::White;
		pEffect = FontEffect::Edge;
		pEffectSize = 1;
		pEffectColor = Drawing::Color::Black;
		pScaling = FontScaling::FontSize;

		inherited = nullptr;
		pInternalPointer = IntPtr::Zero;
	}

	void Font::RegisterFont()
	{
		// Register font for creation
		IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_AddFont(this);
	}

	Drawing::Font^ Font::WindowsFont::get()
	{
		return gcnew Drawing::Font(FontFamily, Graphics::ConvertY(Height,pScaling,FontScaling::Pixel), (Bold ? Drawing::FontStyle::Bold : Drawing::FontStyle::Regular) | (Italic ? Drawing::FontStyle::Italic : Drawing::FontStyle::Regular), Drawing::GraphicsUnit::Pixel);
	}

	float Font::GetLineHeight(FontScaling Scaling)
	{
		float val = Height * 1.1f;
		return Graphics::ConvertY(val,this->Scaling,Scaling);
	}

	void Font::Unload(bool permanent)
	{

	}
	void Font::Reload()
	{
		if (String::IsNullOrWhiteSpace(pFontFamilyName))
			return;

		// Try find font file with this name in the Windows Fonts folder
		array<String^>^ foundFiles = Directory::GetFiles(Environment::GetFolderPath(Environment::SpecialFolder::Fonts), pFontFamilyName + ".*", SearchOption::TopDirectoryOnly);

		if (foundFiles->Length != 0)
			pFullPath = foundFiles[0]; // Just use the first path in the array

		// Try find font file with this name in GTA IV root folder if above search failed
		if (String::IsNullOrEmpty(pFullPath))
		{
			foundFiles = Directory::GetFiles(IVSDKDotNet::IVGame::GameStartupPath, pFontFamilyName + ".*", SearchOption::TopDirectoryOnly);

			if (foundFiles->Length != 0)
				pFullPath = foundFiles[0]; // Just use the first path in the array
		}

		// Try find font file with this name in GTA IV script folder if above search failed
		if (String::IsNullOrEmpty(pFullPath))
		{
			foundFiles = Directory::GetFiles(IVSDKDotNet::IVGame::GameStartupPath + "\\scripts", pFontFamilyName + ".*", SearchOption::AllDirectories);

			if (foundFiles->Length != 0)
				pFullPath = foundFiles[0]; // Just use the first path in the array
		}

		bool usingFallbackFont = false;

		// If pFullPath is null or empty file was not found and we use the default IV-SDK .NET font
		if (String::IsNullOrEmpty(pFullPath))
		{
			NetHook::VerboseLog(String::Format("Was trying to create font {0} but it was not found. Using default font public-sans.regular.", pFontFamilyName));
			pFullPath = CLR::CLRBridge::IVSDKDotNetDataPath + "\\public-sans.regular.ttf";
			usingFallbackFont = true;
		}

		float height = Graphics::ConvertY(pHeight, pScaling, FontScaling::Pixel);
		if (IVSDKDotNet::ImGuiIV::AddFontFromFile(pFullPath, height, pInternalPointer))
			NetHook::VerboseLog(String::Format("Successfully added font {0} with height {1}!", usingFallbackFont ? "public-sans.regular" : pFontFamilyName, height));
		else
			WRITE_TO_DEBUG_OUTPUT(String::Format("Could not add font file {0}! Font might already be added or an unknown error occured.", pFontFamilyName));
	}

	int Font::GetInternalPointer(bool retrieveNew)
	{
		if (pInternalPointer == IntPtr::Zero && retrieveNew)
			Reload();

		return pInternalPointer.ToInt32();
	}
	int Font::GetD3DObjectID(bool retrieveNew)
	{
		return -1;
	}

	void Font::DestroyInheritance()
	{
		if isNULL(inherited)
			return;

		pFontFamilyName = inherited->FontFamily;
		pHeight = inherited->Height;
		pScaling = inherited->Scaling;
		bBold = inherited->Bold;
		bItalic = inherited->Italic;
		pColor = inherited->Color;
		pEffect = inherited->Effect;
		pEffectSize = inherited->EffectSize;
		pEffectColor = inherited->EffectColor;
		inherited = nullptr;

		NetHook::Log("Inheritance destroyed");
	}

}