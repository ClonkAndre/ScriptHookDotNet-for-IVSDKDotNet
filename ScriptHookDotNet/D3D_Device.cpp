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

#include "D3D_Device.h"

#include "Font.h"
#include "RemoteScriptDomain.h"
#include "Texture.h"
#include "VertexFormats.h"
#include "Viewport.h"

#pragma managed

namespace GTA
{

	GTA::Viewport Direct3D::Viewport::get()
	{
		GTA::Viewport viewport;
		HRESULT hr = cDevice->GetViewport( reinterpret_cast<D3DVIEWPORT9*>( &viewport ) );
		if (hr < 0) return GTA::Viewport();
		return viewport;
	}

	Matrix Direct3D::GetTransform(TransformState state)
	{
		Matrix result;
		HRESULT hr = cDevice->GetTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<D3DMATRIX*>( &result ) );
		return result;
	}
	void Direct3D::SetTransform(TransformState state, Matrix value)
	{
		HRESULT hr = cDevice->SetTransform( static_cast<D3DTRANSFORMSTATETYPE>( state ), reinterpret_cast<const D3DMATRIX*>( &value ) );
	}

	void Direct3D::Release(GTA::base::iD3DObject^ D3DObject)
	{
		if isNULL(D3DObject)
			return;
		//int index = ObjectList->IndexOf(D3DObject); //D3DObject->GetD3DObjectID(false); //ObjectList->IndexOf(D3DObject);
		//if (index >= 0) ObjectList[index] = nullptr; //ObjectList->RemoveAt(index); // DO NOT remove it from the list, or the indices of all other objects will go nuts
		try
		{
			if (D3DObject->GetType() == GTA::Font::typeid)
			{
				ReleaseFont((GTA::Font^)D3DObject);
			}
			else if (D3DObject->GetType() == GTA::Texture::typeid)
			{
				ReleaseTexture((GTA::Texture^)D3DObject);
			}
			else
			{
				NetHook::Log("Direct3D.Release: Don't know how to release '" + D3DObject->GetType()->FullName + "'!");
			}
		} catchErrors("Error on Direct3D.Release",)
	}
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

	generic<typename vType, typename iType> where vType: VertexFormats::iVertexFormat
	void Direct3D::DrawPolygons(array<vType>^ vertices, array<iType>^ indices, int TextureID)
	{
		if (isNULL(vertices) || (vertices->Length == 0))
			return;
		if (isNULL(indices)  || (indices->Length == 0))
			return;
		if (cDevice == NULL)
			return;

		if (TextureID >= 0)
		{
			IDirect3DTexture9* tex = (IDirect3DTexture9*)( ((GTA::Texture^)ObjectList[TextureID])->GetInternalPointer(true) ); //FontPtr
			cDevice->SetTexture(0, tex);
		}

		cDevice->SetFVF(vertices[0]->Format);

		int stride = vertices[0]->StrideSize;
		int vCount = vertices->Length;
		int primCount = indices->Length/3;
		
		pin_ptr<vType> pinnedVertices = &vertices[0];
		pin_ptr<iType> pinnedIndices = &indices[0];
		
		cDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, vCount, primCount, pinnedIndices, D3DFMT_INDEX32, pinnedVertices, stride);

		if (TextureID >= 0)
			cDevice->SetTexture(0, NULL);
	}

	void Direct3D::DrawLine(GTA::Vector3 pos1, GTA::Vector3 pos2, float width1, float width2, int color1, int color2)
	{
		array<VertexFormats::TransformedColored>^ vertices = gcnew array<VertexFormats::TransformedColored>(4);
		array<int>^ indices = gcnew array<int>(6);

		GTA::Vector3 vDir = (pos1 - pos2);
		vDir = GTA::Vector3(-vDir.Y, vDir.X, 0.0F);
		vDir.Normalize();
		width1 *= 0.5F;
		width2 *= 0.5F;
		GTA::Vector3 vTopLeft		= pos1 + (-width1 * vDir);
		GTA::Vector3 vTopRight		= pos1 + ( width1 * vDir);
		GTA::Vector3 vBottomLeft	= pos2 + (-width2 * vDir);
		GTA::Vector3 vBottomRight	= pos2 + ( width2 * vDir);

		vertices[0] = VertexFormats::TransformedColored(vTopLeft.X, vTopLeft.Y, vTopLeft.Z, 1.0F, color1);
		vertices[1] = VertexFormats::TransformedColored(vBottomLeft.X, vBottomLeft.Y, vBottomLeft.Z, 1.0F, color2);
		vertices[2] = VertexFormats::TransformedColored(vBottomRight.X, vBottomRight.Y, vBottomRight.Z, 1.0F, color2);
		vertices[3] = VertexFormats::TransformedColored(vTopRight.X, vTopRight.Y, vTopRight.Z, 1.0F, color1);

		indices[0] = 0; indices[1] = 2; indices[2] = 1;
		indices[3] = 2; indices[4] = 0; indices[5] = 3;

		DrawPolygons(vertices, indices, -1);
	}
	void Direct3D::DrawLine(float x1, float y1, float x2, float y2, float width, int color)
	{
		DrawLine(GTA::Vector3(x1,y1,0.0f), GTA::Vector3(x2,y2,0.0f), width, width, color, color);
	}

	void Direct3D::DrawBoxFilled(Vector3 CornerTL, Vector3 CornerTR, Vector3 CornerBL, Vector3 CornerBR, int ColorTL, int ColorTR, int ColorBL, int ColorBR)
	{
		array<VertexFormats::TransformedColored>^ vertices = gcnew array<VertexFormats::TransformedColored>(4);
		array<int>^ indices = gcnew array<int>(6);
		
		vertices[0].X = CornerTL.X; vertices[0].Y = CornerTL.Y; vertices[0].Z = CornerTL.Z; vertices[0].Rhw = 1.0F; vertices[0].Color = ColorTL;
		vertices[1].X = CornerBL.X; vertices[1].Y = CornerBL.Y; vertices[1].Z = CornerBL.Z; vertices[1].Rhw = 1.0F; vertices[1].Color = ColorBL;
		vertices[2].X = CornerBR.X; vertices[2].Y = CornerBR.Y; vertices[2].Z = CornerBR.Z; vertices[2].Rhw = 1.0F; vertices[2].Color = ColorBR;
		vertices[3].X = CornerTR.X; vertices[3].Y = CornerTR.Y; vertices[3].Z = CornerTR.Z; vertices[3].Rhw = 1.0F; vertices[3].Color = ColorTR;

		indices[0] = 0; indices[1] = 2; indices[2] = 1;
		indices[3] = 2; indices[4] = 0; indices[5] = 3;

		DrawPolygons(vertices, indices, -1);
	}
	void Direct3D::DrawBoxFilled(Drawing::RectangleF rect, int color)
	{
		DrawBoxFilled(rect.X, rect.Y, rect.Width, rect.Height, color);
	}
	void Direct3D::DrawBoxFilled(float x, float y, float width, float height, int color)
	{
		DrawBoxFilled(Vector3(x, y, 0.0F), Vector3(x+width, y, 0.0F),
		              Vector3(x, y+height, 0.0F), Vector3(x+width, y+height, 0.0F), 
					     color, color, color, color);
	}

	void Direct3D::DrawSprite(GTA::Texture^ Texture, Vector3 CornerTL, Vector3 CornerTR, Vector3 CornerBL, Vector3 CornerBR, int ColorTL, int ColorTR, int ColorBL, int ColorBR)
	{
		int texid = Texture->GetD3DObjectID(true);
		
		array<VertexFormats::TransformedColoredTextured>^ vertices = gcnew array<VertexFormats::TransformedColoredTextured>(4);
		array<int>^ indices = gcnew array<int>(6);
		
		vertices[0].X = CornerTL.X; vertices[0].Y = CornerTL.Y; vertices[0].Z = CornerTL.Z; vertices[0].Rhw = 1.0F; vertices[0].Color = ColorTL; vertices[0].U = 0.0f; vertices[0].V = 0.0f;
		vertices[1].X = CornerBL.X; vertices[1].Y = CornerBL.Y; vertices[1].Z = CornerBL.Z; vertices[1].Rhw = 1.0F; vertices[1].Color = ColorBL; vertices[1].U = 0.0f; vertices[1].V = 1.0f;
		vertices[2].X = CornerBR.X; vertices[2].Y = CornerBR.Y; vertices[2].Z = CornerBR.Z; vertices[2].Rhw = 1.0F; vertices[2].Color = ColorBR; vertices[2].U = 1.0f; vertices[2].V = 1.0f;
		vertices[3].X = CornerTR.X; vertices[3].Y = CornerTR.Y; vertices[3].Z = CornerTR.Z; vertices[3].Rhw = 1.0F; vertices[3].Color = ColorTR; vertices[3].U = 1.0f; vertices[3].V = 0.0f;

		indices[0] = 0; indices[1] = 2; indices[2] = 1;
		indices[3] = 2; indices[4] = 0; indices[5] = 3;

		DrawPolygons(vertices, indices, texid);
	}
	void Direct3D::DrawSprite(GTA::Texture^ Texture, Drawing::RectangleF rect, int color)
	{
		DrawSprite(Texture, Vector3(rect.Left, rect.Top, 0.0F), Vector3(rect.Right, rect.Top, 0.0F),
		              Vector3(rect.Left, rect.Bottom, 0.0F), Vector3(rect.Right, rect.Bottom, 0.0F), 
					     color, color, color, color);
	}

	void Direct3D::DrawString(String^ Text, Drawing::Rectangle area, TextAlignment alignment, Drawing::Color color, int FontID)
	{
		if (isNULL(Text) || (Text->Length == 0))
			return;
		if (FontID < 0)
			return;
		if (cDevice == NULL)
			return;

		ID3DXFont* font = (ID3DXFont*)( ((GTA::Font^)ObjectList[FontID])->GetInternalPointer(true) ); //FontPtr

		RECT rect;
		rect.left = area.Left;
		rect.top = area.Top;
		rect.right = area.Right;
		rect.bottom = area.Bottom;
		
		WCHAR* ptr = PinStringU(Text);
		try
		{
			font->DrawTextW(NULL, reinterpret_cast<LPCWSTR>(ptr), Text->Length, &rect, (DWORD)alignment, D3DCOLOR_ARGB(color.A, color.R, color.G, color.B));
		}
		finally
		{
			FreeString(ptr);
		}
	}

	int Direct3D::AddNewObject(GTA::base::iD3DObject^ object)
	{
		if isNULL(object)
			return -1;

		try
		{
			System::Threading::Monitor::Enter(ObjectList);
			int ID = ObjectList->Count;
			ObjectList->Add(object);
			LogCount(ObjectList, "Direct3D ObjectCache", 100);
			System::Threading::Monitor::Exit(ObjectList);

			if (VERBOSE)
				NetHook::Log("New Direct3D object added! (ID " + ID + ")");

			return ID;

		} catchErrors("Direct3D.AddNewObject: Error while adding new Direct3D object", return -1; )
	}

	int Direct3D::NewFontInternal(int height, int width, int weight, int mipLevels, bool italic, int charSet, int outputPrecision, int quality, int pitchAndFamily, String^ faceName )
	{
		if ( isNULL(faceName) || (faceName->Length == 0) )
			return 0;

		try
		{
			if (cDevice == NULL)
				return 0;

			ID3DXFont* font = NULL;

			WCHAR* pinned_name = PinStringU(faceName);
			try
			{
				D3DXCreateFont( cDevice, height, width, (UINT)weight, mipLevels, italic, static_cast<DWORD>(charSet), static_cast<DWORD>(outputPrecision), static_cast<DWORD>(quality), static_cast<DWORD>(pitchAndFamily), reinterpret_cast<LPCWSTR>( pinned_name ), &font );
			}
			finally
			{
				FreeString(pinned_name);
			}

			if (VERBOSE)
				NetHook::Log("Font created! (PTR " + force_cast<int>(font).ToString() + ")");

			return force_cast<int>(font);
		} catchErrors("Direct3D.NewFontInternal: Error while creating new font", return 0; )
	}
	int Direct3D::NewTextureInternal(array<Byte>^ data, [Out] ImageInformation% imageInformation)
	{
		try
		{
			if (cDevice == NULL)
				return 0;

			UINT DEFAULT = 0xFFFFFFFF; //static_cast<int>( D3DX_DEFAULT );
			UINT width = DEFAULT;
			UINT height = DEFAULT;
			UINT numLevels = 0;
			int usage = 0;
			int pool = D3DPOOL_MANAGED;
			Format format = Format::A8R8G8B8; //Format::Unknown;
			DWORD filter = DEFAULT;
			DWORD mipFilter = DEFAULT;
			int colorKey = 0;

			IDirect3DTexture9* texture;
			pin_ptr<unsigned char> pinnedMemory = &data[0];
			imageInformation = ImageInformation();
			pin_ptr<ImageInformation> pinnedImageInfo = &imageInformation;

			HRESULT hr = D3DXCreateTextureFromFileInMemoryEx( cDevice, pinnedMemory, data->Length, width,
				height, numLevels, static_cast<DWORD>( usage ), static_cast<D3DFORMAT>( format ), static_cast<D3DPOOL>( pool ), static_cast<DWORD>( filter ), static_cast<DWORD>( mipFilter ),
				static_cast<D3DCOLOR>( colorKey ), reinterpret_cast<D3DXIMAGE_INFO*>( pinnedImageInfo ), 
				NULL, &texture );

			if (hr < 0)
			{
				NetHook::Log("Unable to create Texture!");
				return 0;
			}

			if (VERBOSE)
				NetHook::Log("Texture created! (PTR " + force_cast<int>(texture).ToString() + ")");

			return force_cast<int>(texture);
		} catchErrors("Direct3D.NewTextureInternal: Error while creating new texture", return 0; )
	}

}