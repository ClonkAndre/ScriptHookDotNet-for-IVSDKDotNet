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

namespace GTA {
//namespace Direct3D {

	//namespace base {
	//	interface class iD3DObject;
	//}
	//namespace VertexFormat {
	//	interface class iVertexFormat;
	//}
	//enum class TransformState;
	value class ImageInformation;
	value class Viewport;

	using namespace System;

	private ref class Direct3D sealed
	{
	private:
		static property IDirect3DDevice9* cDevice
		{
			IDirect3DDevice9* get()
			{
				return (IDirect3DDevice9*)IVSDKDotNet::RAGE::GetDirect3DDevice9().ToPointer();
			}
		}
		static bool bDrawing = false;
		static bool bResettedOnce = false;

		static System::Collections::Generic::List<GTA::base::iD3DObject^>^ ObjectList = gcnew System::Collections::Generic::List<GTA::base::iD3DObject^>();

	private:
		static void ReleaseFont(GTA::Font^ Font);
		static void ReleaseTexture(GTA::Texture^ Texture);

	internal:
		static void Release(GTA::base::iD3DObject^ D3DObject);

	public:
		static property bool isDrawing
		{
			bool get() { return bDrawing; }
		}
		static property GTA::Viewport Viewport
		{
			GTA::Viewport get();
		}

		static Matrix GetTransform(TransformState state);
		static void SetTransform(TransformState state, Matrix value);

		//static Vector3 TransformFromObjectToScreen(Vector3 PositionInObject, Matrix ObjectMatrix);

		generic<typename vType, typename iType> where vType: VertexFormats::iVertexFormat
		static void DrawPolygons(array<vType>^ vertices, array<iType>^ indices, int TextureID);

		//static void DrawLine(GTA::Vector3 pos1, GTA::Vector3 pos2, float width1, float width2, int color1, int color2);
		//static void DrawLine(float x1, float y1, float x2, float y2, float width, int color);
		static void DrawLine(GTA::Vector3 pos1, GTA::Vector3 pos2, float width1, float width2, int color1, int color2);
		static void DrawLine(float x1, float y1, float x2, float y2, float width, int color);

		static void DrawBoxFilled(Vector3 CornerTL, Vector3 CornerTR, Vector3 CornerBL, Vector3 CornerBR, int ColorTL, int ColorTR, int ColorBL, int ColorBR);
		static void DrawBoxFilled(Drawing::RectangleF rect, int color);
		static void DrawBoxFilled(float x, float y, float width, float height, int color);

		static void DrawSprite(GTA::Texture^ Texture, Vector3 CornerTL, Vector3 CornerTR, Vector3 CornerBL, Vector3 CornerBR, int ColorTL, int ColorTR, int ColorBL, int ColorBR);
		static void DrawSprite(GTA::Texture^ Texture, Drawing::RectangleF rect, int Color);

		static void DrawString(String^ Text, Drawing::Rectangle area, TextAlignment alignment, Drawing::Color color, int FontID);

		/// <summary>
		/// Adds a new Direct3D object to the ObjectCache and returns the ID.
		/// </summary>
		static int AddNewObject(GTA::base::iD3DObject^ object);

		/// <summary>
		/// Creates a new Direct3D Font and returns the pointer. LOCAL ONLY!
		/// </summary>
		static int NewFontInternal(int height, int width, int weight, int mipLevels, bool italic, int charSet, int outputPrecision, int quality, int pitchAndFamily, String^ faceName );

		/// <summary>
		/// Creates a new Direct3D Font and returns the pointer. LOCAL ONLY!
		/// </summary>
		static int NewTextureInternal(array<Byte>^ data, [Out] ImageInformation% imageInformatio);

	};

}