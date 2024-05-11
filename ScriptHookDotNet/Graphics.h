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
	public ref class Graphics sealed
	{
	private:
		float pFrameTime;
		static Font^ pDefaultFont;
		FontScaling pScaling;
		IVSDKDotNet::ImGuiIV_DrawingContext pImGuiDrawingContext;

	internal:
		Graphics(IVSDKDotNet::ImGuiIV_DrawingContext ctx);

		void InitFrame();
		void InitScript();

	public:
		property float FrameTime
		{
			float get() { return pFrameTime; }
		}
		property FontScaling Scaling
		{
			FontScaling get() { return pScaling; }
			void set(FontScaling value) { pScaling = value; }
		}

		void DrawText(String^ Text, float X, float Y, Drawing::Color Color, GTA::Font^ Font);
		void DrawText(String^ Text, float X, float Y, GTA::Font^ Font);
		void DrawText(String^ Text, float X, float Y, Drawing::Color Color);
		void DrawText(String^ Text, float X, float Y);

		void DrawText(String^ Text, Drawing::RectangleF Area, TextAlignment Alignment, Drawing::Color Color, GTA::Font^ Font);
		void DrawText(String^ Text, Drawing::RectangleF Area, TextAlignment Alignment, GTA::Font^ Font);
		void DrawText(String^ Text, Drawing::RectangleF Area, TextAlignment Alignment, Drawing::Color Color);
		void DrawText(String^ Text, Drawing::RectangleF Area, TextAlignment Alignment);
		void DrawText(String^ Text, Drawing::RectangleF Area);

		/// <summary>
		/// Draws a colored Rectangle.
		/// </summary>
		void DrawRectangle(Drawing::RectangleF rect, Drawing::Color Color); 
		/// <summary>
		/// Draws a colored Rectangle.
		/// </summary>
		void DrawRectangle(float CenterX, float CenterY, float Width, float Height, Drawing::Color Color); 

		/// <summary>
		/// Draws a colored line.
		/// </summary>
		void DrawLine(float X1, float Y1, float X2, float Y2, float Width, Drawing::Color Color);
		/// <summary>
		/// Draws a colored line.
		/// </summary>
		void DrawLine(Drawing::PointF Point1, Drawing::PointF Point2, float Width, Drawing::Color Color);

		void DrawSprite(GTA::Texture^ Texture, GTA::Matrix Matrix, Drawing::Color Color);
		void DrawSprite(GTA::Texture^ Texture, GTA::Matrix Matrix);
		void DrawSprite(GTA::Texture^ Texture, float CenterX, float CenterY, float Width, float Height, float Rotation, Drawing::Color Color);
		void DrawSprite(GTA::Texture^ Texture, float CenterX, float CenterY, float Width, float Height, float Rotation);
		void DrawSprite(GTA::Texture^ Texture, Drawing::RectangleF Rectangle, Drawing::Color Color);
		void DrawSprite(GTA::Texture^ Texture, Drawing::RectangleF Rectangle);

		Drawing::RectangleF GetRadarRectangle(FontScaling Scaling);

	internal:
		static float ConvertUnitsToPixelX(float UnitsX);
		static float ConvertUnitsToPixelY(float UnitsY);

		static float ConvertPixelToUnitsX(float PixelX);
		static float ConvertPixelToUnitsY(float PixelY);

		static float ConvertFontToUnits(float FontSize);
		static float ConvertFontToPixelX(float FontSize);
		static float ConvertFontToPixelY(float FontSize);

		static float ConvertUnitsToFont(float Units);
		static float ConvertPixelToFontX(float PixelX);
		static float ConvertPixelToFontY(float PixelY);

		Drawing::Rectangle ConvertToPixel(Drawing::RectangleF rect);
		Drawing::RectangleF ConvertToPixelF(Drawing::RectangleF rect);
		Vector3 ConvertToPixel(Vector3 pos);
		Vector2 ConvertToPixel(Vector2 pos);
		float ToPixelX(float value);
		float ToPixelY(float value);

	public:
		static float ConvertX(float value, FontScaling SourceScaling, FontScaling TargetScaling);
		static float ConvertY(float value, FontScaling SourceScaling, FontScaling TargetScaling);
		static Drawing::RectangleF Convert(Drawing::RectangleF rect, FontScaling SourceScaling, FontScaling TargetScaling);
		static Drawing::PointF Convert(Drawing::PointF pt, FontScaling SourceScaling, FontScaling TargetScaling);
		static Drawing::SizeF Convert(Drawing::SizeF sz, FontScaling SourceScaling, FontScaling TargetScaling);

	};
}