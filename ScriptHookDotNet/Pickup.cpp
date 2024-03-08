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

#include "Pickup.h"

#include "ContentCache.h"
#include "Blip.h"
#include "Ped.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Pickup::Pickup(int Handle)
		:HandleObject(Handle)
	{
	}

	// - - - Properties, Methods and Functions - - -
	Vector3 Pickup::Position::get()
	{
		NON_EXISTING_CHECK(V3_NaN);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_PICKUP_COORDINATES(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void Pickup::Position::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		//Scripting::SetPickupCoordinates(pHandle,value.X,value.Y,value.Z);
		throw gcnew NotImplementedException("It is not possible to change a pickup position");
	}

	Room Pickup::CurrentRoom::get()
	{
		NON_EXISTING_CHECK(Room(0, 0));
		u32 rk;
		IVSDKDotNet::Native::Natives::GET_ROOM_KEY_FROM_PICKUP(pHandle, rk);
		return Room(force_cast<int>(rk), 0);
	}
	void Pickup::CurrentRoom::set(Room value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::ADD_PICKUP_TO_INTERIOR_ROOM_BY_KEY(pHandle, force_cast<u32>(value.RoomKey));
	}

	void Pickup::CollectableByCar::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_PICKUP_COLLECTABLE_BY_CAR(pHandle, value);
	}

	bool Pickup::HasBeenCollected::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::HAS_PICKUP_BEEN_COLLECTED(pHandle);
	}

	void Pickup::GiveToPed(Ped^ ped)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
		IVSDKDotNet::Native::Natives::GIVE_PED_PICKUP_OBJECT(ped->Handle, pHandle, true);
	}

	Blip^ Pickup::AttachBlip()
	{
		NON_EXISTING_CHECK(nullptr);
		return Blip::AddBlip(this);
	}

	bool Pickup::InternalCheckExists()
	{
		if (pHandle == 0)
			return false;

		return IVSDKDotNet::Native::Natives::DOES_PICKUP_EXIST(pHandle);
	}

	void Pickup::Delete()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		SetExistsFalse();

		if (pHandle == 0)
			return;

		IVSDKDotNet::Native::Natives::REMOVE_PICKUP(pHandle);
	}

	// STATIC
	GTA::Pickup^ Pickup::CreatePickup(Vector3 Position, GTA::Model Model, PickupType Type, Vector3 Rotation)
	{
		if (!Model.LoadToMemoryNow())
			return nullptr;

		int res = 0;
		IVSDKDotNet::Native::Natives::CREATE_PICKUP_ROTATE(Model.Hash, (int)Type, 0, Position.X, Position.Y, Position.Z, Rotation.X, Rotation.Y, Rotation.Z, res);
		Model.AllowDisposeFromMemory();

		if (res == 0)
			return nullptr;

		return ContentCache::GetPickup(res);
	}
	GTA::Pickup^ Pickup::CreatePickup(Vector3 Position, GTA::Model Model, PickupType Type)
	{
		if (!Model.LoadToMemoryNow())
			return nullptr;

		int res = 0;
		IVSDKDotNet::Native::Natives::CREATE_PICKUP(Model.Hash, (int)Type, Position.X, Position.Y, Position.Z, res, false);
		Model.AllowDisposeFromMemory();

		if (res == 0)
			return nullptr;

		return ContentCache::GetPickup(res);
	}

	GTA::Pickup^ Pickup::CreateWeaponPickup(Vector3 Position, GTA::Weapon Weapon, int Ammo, Vector3 Rotation)
	{
		GTA::Model model = Model::GetWeaponModel(Weapon);

		if (!model.LoadToMemoryNow())
			return nullptr;

		int res = 0;
		IVSDKDotNet::Native::Natives::CREATE_PICKUP_ROTATE(model.Hash, (int)PickupType::Weapon, Ammo, Position.X, Position.Y, Position.Z, Rotation.X, Rotation.Y, Rotation.Z, res);
		model.AllowDisposeFromMemory();

		if (res == 0)
			return nullptr;

		return ContentCache::GetPickup(res);
	}
	GTA::Pickup^ Pickup::CreateWeaponPickup(Vector3 Position, GTA::Weapon Weapon, int Ammo)
	{
		GTA::Model model = Model::GetWeaponModel(Weapon);

		if (!model.LoadToMemoryNow())
			return nullptr;

		int res = 0;
		IVSDKDotNet::Native::Natives::CREATE_PICKUP_WITH_AMMO(model.Hash, (int)PickupType::Weapon, Ammo, Position.X, Position.Y, Position.Z, res);
		model.AllowDisposeFromMemory();

		if (res == 0)
			return nullptr;

		return ContentCache::GetPickup(res);
	}

	GTA::Pickup^ Pickup::CreateMoneyPickup(Vector3 Position, int MoneyAmount)
	{
		int res = 0;
		IVSDKDotNet::Native::Natives::CREATE_MONEY_PICKUP(Position.X, Position.Y, Position.Z, MoneyAmount, true, res);

		if (res == 0)
			return nullptr;

		return ContentCache::GetPickup(res);
	}

}