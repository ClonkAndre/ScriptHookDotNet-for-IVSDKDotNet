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

#include "d3d9Includes.h"
#include "stdafx.h"

#include "D3D_Device.h"

#include "Font.h"
#include "Texture.h"

#include "Script.h"

#pragma managed

namespace GTA
{

	void Direct3D::ReleaseFont(GTA::Font^ item)
	{
		if isNULL(item)
			return;

		ID3DXFont* ptr = (ID3DXFont*)( item->GetInternalPointer(false) );
		if (ptr == NULL)
			return;

		ptr->Release();
	}
	void Direct3D::ReleaseTexture(GTA::Texture^ item)
	{
		if isNULL(item)
			return;

		IDirect3DTexture9* ptr = (IDirect3DTexture9*)( item->GetInternalPointer(false) );

		if (ptr == NULL)
			return;

		ptr->Release();
	}

	IntPtr Direct3D::NewTextureInternal(System::Object^ callingScript, array<Byte>^ data, [Out] int% textureWidth, [Out] int% textureHeight)
	{
		pin_ptr<System::Byte> pinnedData = &data[0];
		unsigned char* pby = pinnedData;
		void* dataPtr = reinterpret_cast<void*>(pby);

		msclr::interop::marshal_context ctx;
		PDIRECT3DTEXTURE9 texture;

		// Get device
		IDirect3DDevice9* device = (IDirect3DDevice9*)IVSDKDotNet::RAGE::GetDirect3DDevice9().ToPointer();

		// Try create texture
		HRESULT hr = D3DXCreateTextureFromFileInMemoryEx(device, dataPtr, data->Length, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &texture);

		if (hr != S_OK)
		{
			NetHook::Log(String::Format("[ImGuiIV] Failed to create texture from memory. HResult: {0}", hr));

			textureWidth = 0;
			textureHeight = 0;
			return IntPtr::Zero;
		}

		// Get the texture surface description
		D3DSURFACE_DESC imageDesc;
		texture->GetLevelDesc(0, &imageDesc);

		// Set stuff
		IntPtr ptr = IntPtr(texture);
		textureWidth = imageDesc.Width;
		textureHeight = imageDesc.Height;

		// Try assign texture to calling script
		if (callingScript)
		{
			GTA::Script^ script = (GTA::Script^)callingScript;
			VLOG(String::Format("[Direct3D::NewTextureInternal] Successfully got calling script {0}!", script->Name));
			script->Textures->Add(ptr);
			NetHook::VerboseLog(String::Format("Assigned texture {0} to current script!", ptr));
		}
		else
		{
			WRITE_TO_DEBUG_OUTPUT("[Direct3D::NewTextureInternal] Failed to get calling script! Trying out with legacy method.");

			// Try get calling script via legacy method
			GTA::Script^ script = GetCurrentScript(ScriptEvent::PerFrameDrawing);

			if (script)
			{
				VLOG(String::Format("[Direct3D::NewTextureInternal] Successfully got calling script {0} via legacy method!", script->Name));
				script->Textures->Add(ptr);
				NetHook::VerboseLog(String::Format("Assigned texture {0} to current script!", ptr));
			}
			else
				WRITE_TO_DEBUG_OUTPUT("[Direct3D::NewTextureInternal] Failed to get calling script via legacy method! Not in an ideal state right now...");
		}

		return ptr;
	}

}