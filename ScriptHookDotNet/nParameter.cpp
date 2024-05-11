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

#include "nParameter.h"

#include "Blip.h"
#include "Camera.h"
#include "ContentCache.h"
#include "Group.h"
#include "Object.h"
#include "Ped.h"
#include "Pickup.h"
#include "Player.h"
#include "Vehicle.h"

#pragma managed


namespace GTA
{
	namespace Native
	{

		// ===============================================
		// ================== PARAMETER ==================
		// ===============================================
		vtype Parameter::GetType(System::Type^ type)
		{
			if (type == int::typeid)
				return vtype::var_int;
			else if (type == float::typeid)
				return vtype::var_float;
			else if (type == bool::typeid)
				return vtype::var_bool;
			else if (type == String::typeid)
				return vtype::var_string;
			else if (type == GTA::Ped::typeid)
				return vtype::var_ped;
			else if (type == GTA::Vehicle::typeid)
				return vtype::var_vehicle;
			else if (type == GTA::Model::typeid)
				return vtype::var_model;
			else if (type == GTA::Player::typeid)
				return vtype::var_player;
			else if (type == GTA::Group::typeid)
				return vtype::var_group;
			else if (type == GTA::Object::typeid)
				return vtype::var_object;
			else if (type == GTA::Pickup::typeid)
				return vtype::var_pickup;
			else if (type == GTA::Blip::typeid)
				return vtype::var_blip;
			else if (type == GTA::Camera::typeid)
				return vtype::var_camera;
			else if (type == GTA::Vector3::typeid)
				return vtype::var_vector3;

			else if (type == Parameter::typeid)
				return vtype::xvar_parameter;
			else if (type == Pointer::typeid)
				return vtype::xvar_pointer;

			else
				return vtype::var_void;
		}

		// internal:
		bool Parameter::isPointer::get()
		{
			return false;
		}

		// public:
		Parameter::Parameter(vtype type, System::Object^ value)
		{
			TargetType = type;
			Value = value;
		}
		Parameter::Parameter(int value)
		{
			SetValue(value);
		}
		Parameter::Parameter(float value)
		{
			SetValue(value);
		}
		Parameter::Parameter(bool value)
		{
			SetValue(value);
		}
		Parameter::Parameter(String^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Ped^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Vehicle^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Model value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Player^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Group^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Object^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Pickup^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Blip^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(GTA::Camera^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(Parameter^ value)
		{
			SetValue(value);
		}
		Parameter::Parameter(System::Object^ value)
		{
			SetValue(value);
		}

		void Parameter::Set(vtype type, Object^ value)
		{
			m_eType = type;
			m_pValue = value;
		}
		void Parameter::SetTargetType(vtype type)
		{
			m_eType = type;
		}
		void Parameter::SetTargetValue(Object^ value)
		{
			m_pValue = value;
		}

		void Parameter::SetValue(int value)
		{
			Set(vtype::var_int, value);
		}
		void Parameter::SetValue(float value)
		{
			Set(vtype::var_float, value);
		}
		void Parameter::SetValue(bool value)
		{
			Set(vtype::var_bool, value);
		}
		void Parameter::SetValue(String^ value)
		{
			Set(vtype::var_string, value);
		}
		void Parameter::SetValue(GTA::Ped^ value)
		{
			Set(vtype::var_ped, value);
		}
		void Parameter::SetValue(GTA::Vehicle^ value)
		{
			Set(vtype::var_vehicle, value);
		}
		void Parameter::SetValue(GTA::Model value)
		{
			Set(vtype::var_model, value);
		}
		void Parameter::SetValue(GTA::Player^ value)
		{
			Set(vtype::var_player, value);
		}
		void Parameter::SetValue(GTA::Group^ value)
		{
			Set(vtype::var_group, value);
		}
		void Parameter::SetValue(GTA::Object^ value)
		{
			Set(vtype::var_object, value);
		}
		void Parameter::SetValue(GTA::Pickup^ value)
		{
			Set(vtype::var_pickup, value);
		}
		void Parameter::SetValue(GTA::Blip^ value)
		{
			Set(vtype::var_blip, value);
		}
		void Parameter::SetValue(GTA::Camera^ value)
		{
			Set(vtype::var_camera, value);
		}
		void Parameter::SetValue(Parameter^ value)
		{
			Set(value->TargetType, value->Value);
		}
		void Parameter::SetValue(System::Object^ value)
		{
			Set(vtype::xvar_pointer, value);
		}

		System::Object^ Parameter::Value::get()
		{
			return m_pValue;
		}
		void Parameter::Value::set(System::Object^ value)
		{
			m_pValue = value;
		}

		Parameter::operator Parameter ^ (int source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (float source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (double source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue((float)source);
			return p;
		}
		Parameter::operator Parameter ^ (bool source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (String^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Ped^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Vehicle^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Model source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Player^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Group^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Object^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Pickup^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Blip^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}
		Parameter::operator Parameter ^ (GTA::Camera^ source)
		{
			Parameter^ p = gcnew Parameter();
			p->SetValue(source);
			return p;
		}

		String^ Parameter::ToString()
		{
			if (Value == nullptr)
				return String::Empty;

			return Value->ToString();
		}


		// =============================================
		// ================== POINTER ==================
		// =============================================

		// internal:
		bool Pointer::isPointer::get()
		{
			return true;
		}

		// public:
		Pointer::Pointer(System::Type^ type)
		{
			SetTargetType(Parameter::GetType(type));
		}

		Pointer::operator Pointer ^ (int source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (float source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (double source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue((float)source);
			return p;
		}
		Pointer::operator Pointer ^ (bool source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (String^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Ped^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Vehicle^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Model source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Player^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Group^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Object^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Pickup^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Blip^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Camera^ source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (GTA::Vector3 source)
		{
			Pointer^ p = gcnew Pointer();
			p->SetValue(source);
			return p;
		}
		Pointer::operator Pointer ^ (System::Type^ type)
		{
			Pointer^ p = gcnew Pointer();
			p->SetTargetType(Parameter::GetType(type));
			return p;
		}

		Pointer::operator int(Pointer^ source)
		{
			if (source->TargetType == vtype::var_int)
				return Convert::ToInt32(source->Value);
			if (source->TargetType == vtype::var_float)
				return (int)Convert::ToSingle(source->Value);
			if (source->TargetType == vtype::var_bool)
				return Convert::ToBoolean(source->Value) ? 1 : 0;

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to integer");
			return 0;
		}
		Pointer::operator float(Pointer^ source)
		{
			if (source->TargetType == vtype::var_float)
				return Convert::ToSingle(source->Value);
			if (source->TargetType == vtype::var_int)
				return (float)Convert::ToInt32(source->Value);

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to float");
			return 0.0f;
		}
		Pointer::operator double(Pointer^ source)
		{
			if (source->TargetType == vtype::var_float)
				return (double)Convert::ToSingle(source->Value);
			if (source->TargetType == vtype::var_int)
				return (double)Convert::ToInt32(source->Value);

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to float");
			return 0.0;
		}
		Pointer::operator bool(Pointer^ source)
		{
			if (source->TargetType == vtype::var_bool)
				return Convert::ToBoolean(source->Value);
			if (source->TargetType == vtype::var_int)
				return Convert::ToInt32(source->Value) != 0;

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to bool");
			return 0;
		}
		Pointer::operator String ^ (Pointer^ source)
		{
			Object^ o = source->Value;

			if (o == nullptr)
				return String::Empty;

			return o->ToString();
		}
		Pointer::operator GTA::Ped ^ (Pointer^ source)
		{
			//if (source->TargetType == vtype::var_ped)
			//	return safe_cast<GTA::Ped^>(source->Value);

			if (source->TargetType == vtype::var_ped)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return gcnew GTA::Ped(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Ped");
			return nullptr;
		}
		Pointer::operator GTA::Vehicle ^ (Pointer^ source)
		{
			//if (source->TargetType == vtype::var_vehicle)
			//	return safe_cast<GTA::Vehicle^>(source->Value);

			if (source->TargetType == vtype::var_vehicle)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return gcnew GTA::Vehicle(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Vehicle");
			return nullptr;
		}
		Pointer::operator GTA::Model(Pointer^ source)
		{
			//if (source->TargetType == vtype::var_model)
			//	return safe_cast<GTA::Model>(source->Value);

			if (source->TargetType == vtype::var_model)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return GTA::Model(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Model");
			return nullptr;
		}
		Pointer::operator GTA::Group ^ (Pointer^ source)
		{
			//if (source->TargetType == vtype::var_group)
			//	return safe_cast<GTA::Group^>(source->Value);

			if (source->TargetType == vtype::var_group)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return gcnew GTA::Group(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Group");
			return nullptr;
		}
		Pointer::operator GTA::Object ^ (Pointer^ source)
		{
			//if (source->TargetType == vtype::var_object)
			//	return safe_cast<GTA::Object^>(source->Value);

			if (source->TargetType == vtype::var_object)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return gcnew GTA::Object(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Object");
			return nullptr;
		}
		Pointer::operator GTA::Pickup ^ (Pointer^ source)
		{
			//if (source->TargetType == vtype::var_pickup)
			//	return safe_cast<GTA::Pickup^>(source->Value);

			if (source->TargetType == vtype::var_pickup)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return gcnew GTA::Pickup(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Pickup");
			return nullptr;
		}
		Pointer::operator GTA::Blip ^ (Pointer^ source)
		{
			//if (source->TargetType == vtype::var_blip)
			//	return safe_cast<GTA::Blip^>(source->Value);

			if (source->TargetType == vtype::var_blip)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return gcnew GTA::Blip(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Blip");
			return nullptr;
		}
		Pointer::operator GTA::Camera ^ (Pointer^ source)
		{
			//if (source->TargetType == vtype::var_camera)
			//	return safe_cast<GTA::Camera^>(source->Value);

			if (source->TargetType == vtype::var_camera)
			{
				if (!source->Value)
					return nullptr;

				if (source->Value->GetType() == System::Int32::typeid)
					return gcnew GTA::Camera(Convert::ToInt32(source->Value));
			}

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Camera");
			return nullptr;
		}
		Pointer::operator GTA::Vector3(Pointer^ source)
		{
			if (source->TargetType == vtype::var_vector3)
				return safe_cast<GTA::Vector3>(source->Value);

			throw gcnew InvalidCastException("Invalid cast from Native.Pointer of type " + GetTypeName(source->TargetType) + " to Vector3");
			return Vector3();
		}

		Parameter^ Pointer::ToInputParameter()
		{
			return gcnew Parameter(TargetType, Value);
		}

	}
}