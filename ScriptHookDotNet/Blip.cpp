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

#include "Blip.h"

#include "ContentCache.h"
#include "Object.h"
#include "Ped.h"
#include "Pickup.h"
#include "Vehicle.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Blip::Blip(int Handle)
		:HandleObject(Handle)
	{
	}

	// - - - Properties, Methods and Functions - - -
	int Blip::MemoryAddress::get()
	{
		// TODO
		//return unmanaged::MemoryAccess::GetAddressOfBlip(pHandle);
		return 0;
	}

	GTA::Vector3 Blip::Position::get()
	{
		NON_EXISTING_CHECK(V3_NaN);

		switch (Type)
		{
			case BlipType::Vehicle:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_CAR_INDEX(pHandle);
				f32 x, y, z;

				if (!IVSDKDotNet::Native::Natives::DOES_VEHICLE_EXIST(id))
					return GTA::Vector3();

				IVSDKDotNet::Native::Natives::GET_CAR_COORDINATES(id, x, y, z);
				return GTA::Vector3(x, y, z);
			}
			case BlipType::Ped:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_PED_INDEX(pHandle);
				f32 x, y, z;

				if (!IVSDKDotNet::Native::Natives::DOES_CHAR_EXIST(id))
					return GTA::Vector3();

				IVSDKDotNet::Native::Natives::GET_CHAR_COORDINATES(id, x, y, z);
				return GTA::Vector3(x, y, z);
			}
			case BlipType::Object:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_OBJECT_INDEX(pHandle);
				f32 x, y, z;

				if (!IVSDKDotNet::Native::Natives::DOES_OBJECT_EXIST(id))
					return GTA::Vector3();

				IVSDKDotNet::Native::Natives::GET_OBJECT_COORDINATES(id, x, y, z);
				return GTA::Vector3(x, y, z);
			}
			case BlipType::Coordinate:
			case BlipType::Contact:
			{
				if (!IVSDKDotNet::Native::Natives::DOES_BLIP_EXIST(pHandle))
					return GTA::Vector3();

				System::Numerics::Vector3 pos;
				IVSDKDotNet::Native::Natives::GET_BLIP_COORDS(pHandle, pos);

				return Vector3ToGTAVector3(pos);
			}

			case BlipType::Pickup:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_PICKUP_INDEX(pHandle);
				f32 x, y, z;

				if (!IVSDKDotNet::Native::Natives::DOES_PICKUP_EXIST(id))
					return GTA::Vector3();

				IVSDKDotNet::Native::Natives::GET_PICKUP_COORDINATES(id, x, y, z);
				return GTA::Vector3(x, y, z);
			}
		}

		return GTA::Vector3();
	}
	void Blip::Position::set(GTA::Vector3 value)
	{
		throw gcnew Exception("Blip position can't be set");
	}

	base::Object^ Blip::GetAttachedItem()
	{
		NON_EXISTING_CHECK(nullptr);

		switch (Type)
		{
			case BlipType::Vehicle:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_CAR_INDEX(pHandle);

				if (!IVSDKDotNet::Native::Natives::DOES_VEHICLE_EXIST(id))
					return nullptr;

				return ContentCache::GetVehicle(id);
			}
			case BlipType::Ped:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_PED_INDEX(pHandle);

				if (!IVSDKDotNet::Native::Natives::DOES_CHAR_EXIST(id))
					return nullptr;

				return ContentCache::GetPed(id);
			}
			case BlipType::Object:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_OBJECT_INDEX(pHandle);

				if (!IVSDKDotNet::Native::Natives::DOES_OBJECT_EXIST(id))
					return nullptr;

				return ContentCache::GetObject(id);
			}
			case BlipType::Pickup:
			{
				i32 id = IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_PICKUP_INDEX(pHandle);

				if (!IVSDKDotNet::Native::Natives::DOES_PICKUP_EXIST(id))
					return nullptr;

				return ContentCache::GetPickup(id);
			}
		}

		return nullptr;
	}

	String^ Blip::Name::get()
	{
		NON_EXISTING_CHECK(String::Empty);
		NotImplementedYet("Blip::Name::get");
		//return gcnew String(Scripting::GetBlipName(pHandle));
	}
	void Blip::Name::set(String^ value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_NAME_FROM_ASCII(pHandle, value);
	}

	BlipType Blip::Type::get()
	{
		NON_EXISTING_CHECK((BlipType)0);
		return (BlipType)IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_TYPE(pHandle);
	}

	void Blip::Friendly::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_BLIP_AS_FRIENDLY(pHandle, value);
	}

	void Blip::Scale::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_SCALE(pHandle, value);
	}

	void Blip::Transparency::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_ALPHA(pHandle, value);
	}

	bool Blip::ShowOnlyWhenNear::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_BLIP_SHORT_RANGE(pHandle);
	}
	void Blip::ShowOnlyWhenNear::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_BLIP_AS_SHORT_RANGE(pHandle, value);
	}

	BlipIcon Blip::Icon::get()
	{
		NON_EXISTING_CHECK((BlipIcon)-1);
		return (BlipIcon)IVSDKDotNet::Native::Natives::GET_BLIP_SPRITE(pHandle);
	}
	void Blip::Icon::set(BlipIcon value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_SPRITE(pHandle, (u32)value);
	}

	BlipColor Blip::Color::get()
	{
		NON_EXISTING_CHECK(BlipColor::White);
		u32 c;
		IVSDKDotNet::Native::Natives::GET_BLIP_COLOUR(pHandle, c);
		return (BlipColor)c;
	}
	void Blip::Color::set(BlipColor value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_COLOUR(pHandle, (int)value);
	}

	void Blip::SetColorRGB(Drawing::Color color)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_COLOUR(pHandle, color.ToArgb());
	}

	BlipDisplay Blip::Display::get()
	{
		NON_EXISTING_CHECK(BlipDisplay::Hidden);
		return (BlipDisplay)IVSDKDotNet::Native::Natives::GET_BLIP_INFO_ID_DISPLAY(pHandle);
	}
	void Blip::Display::set(BlipDisplay value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_DISPLAY(pHandle, (u32)value);
	}

	void Blip::Priority::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CHANGE_BLIP_PRIORITY(pHandle, (u32)value);
	}

	void Blip::RouteActive::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_ROUTE(pHandle, value);
	}

	void Blip::Delete()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		SetExistsFalse();

		if (pHandle == 0)
			return;

		// Why does the blip get hidden first?
		//try {
		//	Scripting::ChangeBlipDisplay(pHandle,(Scripting::eBlipDisplay)BlipDisplay::Hidden);
		//} catch (...) {
		//}

		IVSDKDotNet::Native::Natives::REMOVE_BLIP(pHandle);
	}

	bool Blip::InternalCheckExists()
	{
		if (pHandle == 0)
			return false;

		return IVSDKDotNet::Native::Natives::DOES_BLIP_EXIST(pHandle);
	}

	// STATIC
	Blip^ Blip::AddBlip(GTA::Pickup^ Target)
	{
		OBJECT_NON_EXISTING_CHECK(Target, nullptr);
		int b;
		IVSDKDotNet::Native::Natives::ADD_BLIP_FOR_PICKUP(Target->Handle, b);

		if (b == 0)
			return nullptr;

		return ContentCache::GetBlip(b, true);
	}
	Blip^ Blip::AddBlip(GTA::Object^ Target)
	{
		OBJECT_NON_EXISTING_CHECK(Target, nullptr);
		int b;
		IVSDKDotNet::Native::Natives::ADD_BLIP_FOR_OBJECT(Target->Handle, b);

		if (b == 0)
			return nullptr;

		return ContentCache::GetBlip(b, true);
	}
	Blip^ Blip::AddBlip(GTA::Vector3 Target)
	{
		int b;
		IVSDKDotNet::Native::Natives::ADD_BLIP_FOR_COORD(Target.X, Target.Y, Target.Z, b);

		if (b == 0)
			return nullptr;

		return ContentCache::GetBlip(b, true);
	}
	Blip^ Blip::AddBlip(GTA::Vehicle^ Target)
	{
		OBJECT_NON_EXISTING_CHECK(Target, nullptr);
		int b;
		IVSDKDotNet::Native::Natives::ADD_BLIP_FOR_CAR(Target->Handle, b);

		if (b == 0)
			return nullptr;

		return ContentCache::GetBlip(b, true);
	}
	Blip^ Blip::AddBlip(GTA::Ped^ Target)
	{
		OBJECT_NON_EXISTING_CHECK(Target, nullptr);
		int b;
		IVSDKDotNet::Native::Natives::ADD_BLIP_FOR_CHAR(Target->Handle, b);

		if (b == 0)
			return nullptr;

		return ContentCache::GetBlip(b, true);
	}
	Blip^ Blip::AddBlipContact(GTA::Vector3 Target)
	{
		int b;
		IVSDKDotNet::Native::Natives::ADD_BLIP_FOR_CONTACT(Target.X, Target.Y, Target.Z, b);

		if (b == 0)
			return nullptr;

		return ContentCache::GetBlip(b, true);
	}

	array<Blip^>^ Blip::GetAllBlipsOfType(BlipType type)
	{
		int t = (int)type;

		List<Blip^>^ res = gcnew List<Blip^>();

		int b = IVSDKDotNet::Native::Natives::GET_FIRST_BLIP_INFO_ID(t);
		while (b != 0)
		{
			if (IVSDKDotNet::Native::Natives::DOES_BLIP_EXIST(b))
				res->Add(ContentCache::GetBlip(b, false));

			b = IVSDKDotNet::Native::Natives::GET_NEXT_BLIP_INFO_ID(t);
		}

		return res->ToArray();
	}

}