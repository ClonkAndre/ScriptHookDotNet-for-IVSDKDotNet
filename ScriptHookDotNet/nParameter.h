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
	namespace Native
	{

		private enum class vtype
		{
			var_void,
			var_int,
			var_float,
			var_bool,
			var_string,
			var_ped,
			var_vehicle,
			var_model,
			var_player,
			var_group,
			var_object,
			var_pickup,
			var_blip,
			var_camera,
			var_vector3,
			xvar_parameter,
			xvar_pointer,
		};

		CLASS_ATTRIBUTES
		[SerializableAttribute]
		public ref class Parameter
		{
		protected:
			Parameter() { }

			static String^ GetTypeName(vtype type)
			{
				switch (type)
				{
					case vtype::var_void:			return "NULL";
					case vtype::var_int:			return "Integer";
					case vtype::var_float:			return "Float";
					case vtype::var_bool:			return "Boolean";
					case vtype::var_string:			return "String";
					case vtype::var_ped:			return "Ped";
					case vtype::var_vehicle:		return "Vehicle";
					case vtype::var_model:			return "Model";
					case vtype::var_player:			return "Player";
					case vtype::var_group:			return "Group";
					case vtype::var_object:			return "Object";
					case vtype::var_pickup:			return "Pickup";
					case vtype::var_blip:			return "Blip";
					case vtype::var_camera:			return "Camera";
					case vtype::var_vector3:		return "Vector3";
					case vtype::xvar_parameter:		return "Parameter";
					case vtype::xvar_pointer:		return "Pointer";
				}
				return "UNKNOWN";
			}

		internal:
			Parameter(System::Type^ type) { }

			static vtype GetType(System::Type^ type);

			virtual property bool isPointer
			{
				bool get();
			}

		public:
			~Parameter() { }

			Parameter(vtype type, System::Object^ value);
			Parameter(System::Object^ value);
			Parameter(Parameter^ value);
			Parameter(GTA::Camera^ value);
			Parameter(GTA::Blip^ value);
			Parameter(GTA::Pickup^ value);
			Parameter(GTA::Object^ value);
			Parameter(GTA::Group^ value);
			Parameter(GTA::Player^ value);
			Parameter(GTA::Model value);
			Parameter(GTA::Vehicle^ value);
			Parameter(GTA::Ped^ value);
			Parameter(String^ value);
			Parameter(bool value);
			Parameter(float value);
			Parameter(int value);

			void Set(vtype type, Object^ value);
			void SetTargetType(vtype type);
			void SetTargetValue(Object^ value);

			void SetValue(System::Object^ value);
			void SetValue(Parameter^ value);
			void SetValue(GTA::Camera^ value);
			void SetValue(GTA::Blip^ value);
			void SetValue(GTA::Pickup^ value);
			void SetValue(GTA::Object^ value);
			void SetValue(GTA::Group^ value);
			void SetValue(GTA::Player^ value);
			void SetValue(GTA::Model value);
			void SetValue(GTA::Vehicle^ value);
			void SetValue(GTA::Ped^ value);
			void SetValue(String^ value);
			void SetValue(bool value);
			void SetValue(float value);
			void SetValue(int value);

			property vtype TargetType
			{
				vtype get()
				{
					return m_eType;
				}
				void set(vtype value)
				{
					m_eType = value;
				}
			}
			property System::Object^ Value
			{
				System::Object^ get();
				void set(System::Object^ value);
			}

			static operator Parameter ^ (int source);
			static operator Parameter ^ (float source);
			static operator Parameter ^ (double source);
			static operator Parameter ^ (bool source);
			static operator Parameter ^ (String^ source);
			static operator Parameter ^ (GTA::Ped^ source);
			static operator Parameter ^ (GTA::Vehicle^ source);
			static operator Parameter ^ (GTA::Model source);
			static operator Parameter ^ (GTA::Player^ source);
			static operator Parameter ^ (GTA::Group^ source);
			static operator Parameter ^ (GTA::Object^ source);
			static operator Parameter ^ (GTA::Pickup^ source);
			static operator Parameter ^ (GTA::Blip^ source);
			static operator Parameter ^ (GTA::Camera^ source);

			virtual String^ ToString() override;

		private:
			Object^ m_pValue;
			vtype m_eType;

		};

		CLASS_ATTRIBUTES
		[SerializableAttribute]
		public ref class Pointer sealed : public Parameter
		{
		internal:
			Pointer()
			{
			}

			virtual property bool isPointer
			{
				bool get() override;
			}

		public:
			Pointer(System::Type^ type);

			static operator Pointer ^ (int source);
			static operator Pointer ^ (float source);
			static operator Pointer ^ (double source);
			static operator Pointer ^ (bool source);
			static operator Pointer ^ (String^ source);
			static operator Pointer ^ (GTA::Ped^ source);
			static operator Pointer ^ (GTA::Vehicle^ source);
			static operator Pointer ^ (GTA::Model source);
			static operator Pointer ^ (GTA::Player^ source);
			static operator Pointer ^ (GTA::Group^ source);
			static operator Pointer ^ (GTA::Object^ source);
			static operator Pointer ^ (GTA::Pickup^ source);
			static operator Pointer ^ (GTA::Blip^ source);
			static operator Pointer ^ (GTA::Camera^ source);
			static operator Pointer ^ (GTA::Vector3 source);
			static operator Pointer ^ (System::Type^ type);

			static operator int(Pointer^ source);
			static operator float(Pointer^ source);
			static operator double(Pointer^ source);
			static operator bool(Pointer^ source);
			static operator String ^ (Pointer^ source);
			static operator GTA::Ped ^ (Pointer^ source);
			static operator GTA::Vehicle ^ (Pointer^ source);
			static operator GTA::Model(Pointer^ source);
			static operator GTA::Group ^ (Pointer^ source);
			static operator GTA::Object ^ (Pointer^ source);
			static operator GTA::Pickup ^ (Pointer^ source);
			static operator GTA::Blip ^ (Pointer^ source);
			static operator GTA::Camera ^ (Pointer^ source);
			static operator GTA::Vector3(Pointer^ source);

			/// <summary>
			/// Unpoints the pointer and returns it as a usual parameter that is NOT a poitner anymore.
			/// </summary>
			Parameter^ ToInputParameter();

		};

	}
}