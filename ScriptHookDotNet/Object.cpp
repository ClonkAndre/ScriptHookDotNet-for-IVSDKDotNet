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

#include "Object.h"

#include "ContentCache.h"
#include "Blip.h"
#include "Game.h"
#include "Ped.h"
#include "Vehicle.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	GTA::Object::Object(int Handle)
		:HandleObject(Handle)
	{
	}

	// - - - Properties, Methods and Functions - - -
	int GTA::Object::MemoryAddress::get()
	{
		IVSDKDotNet::IVObject^ obj = CCL::GTAIV::NativeWorld::GetObjectInstaceFromHandle(pHandle);

		if (!obj)
			return 0;

		return (int)obj->GetUIntPtr().ToUInt32();
	}

	GTA::Model GTA::Object::Model::get()
	{
		NON_EXISTING_CHECK(nullptr);
		u32 model;
		IVSDKDotNet::Native::Natives::GET_OBJECT_MODEL(pHandle, model);
		return GTA::Model(model);
	}

	Vector3 GTA::Object::Position::get()
	{
		NON_EXISTING_CHECK(V3_NaN);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_OBJECT_COORDINATES(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void GTA::Object::Position::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_COORDINATES(pHandle, value.X, value.Y, value.Z);
	}

	Vector3 GTA::Object::Rotation::get()
	{
		NON_EXISTING_CHECK(V3_NULL);
		return RotationQuaternion.ToRotation();
	}
	void GTA::Object::Rotation::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_ROTATION(pHandle, value.X, value.Y, value.Z);
	}

	Quaternion GTA::Object::RotationQuaternion::get()
	{
		NON_EXISTING_CHECK(Quaternion());
		float x, y, z, w;
		IVSDKDotNet::Native::Natives::GET_OBJECT_QUATERNION(pHandle, x, y, z, w);
		return Quaternion(x, y, z, w);
	}
	void GTA::Object::RotationQuaternion::set(Quaternion value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_QUATERNION(pHandle, value.X, value.Y, value.Z, value.W);
	}

	Room GTA::Object::CurrentRoom::get()
	{
		NON_EXISTING_CHECK(Room(0, 0));
		u32 rk;
		IVSDKDotNet::Native::Natives::GET_ROOM_KEY_FROM_OBJECT(pHandle, rk);
		return Room(force_cast<int>(rk), 0);
	}
	void GTA::Object::CurrentRoom::set(Room value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::ADD_OBJECT_TO_INTERIOR_ROOM_BY_KEY(pHandle, (u32)value.RoomKey);
	}

	float GTA::Object::Heading::get()
	{
		NON_EXISTING_CHECK(0.0f);
		f32 val;
		IVSDKDotNet::Native::Natives::GET_OBJECT_HEADING(pHandle, val);
		return val;
	}
	void GTA::Object::Heading::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_HEADING(pHandle, value);
	}
	Vector3 GTA::Object::Direction::get()
	{
		return Game::HeadingToDirection(Heading);
	}

	Vector3 GTA::Object::Velocity::get()
	{
		NON_EXISTING_CHECK(V3_NULL);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_OBJECT_VELOCITY(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void GTA::Object::Velocity::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		ApplyForce(value, Velocity);
	}

	bool GTA::Object::isAttachedSomewhere::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_OBJECT_ATTACHED(pHandle);
	}

	bool GTA::Object::isOnFire::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_OBJECT_ON_FIRE(pHandle);
	}
	void GTA::Object::isOnFire::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
		{
			int fire = IVSDKDotNet::Native::Natives::START_OBJECT_FIRE(pHandle);

			if (fire == 0)
				return;

			ContentCache::GetFire(fire, true);
		}
		else
		{
			IVSDKDotNet::Native::Natives::EXTINGUISH_OBJECT_FIRE(pHandle);
		}
	}

	void GTA::Object::Visible::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_VISIBLE(pHandle, value);
	}

	void GTA::Object::Collision::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_COLLISION(pHandle, value);
	}
	void GTA::Object::RecordCollisions::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_RECORDS_COLLISIONS(pHandle, value);
	}
	void GTA::Object::Dynamic::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_OBJECT_DYNAMIC(pHandle, value);
	}

	void GTA::Object::FreezePosition::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::FREEZE_OBJECT_POSITION(pHandle, value);
	}

	GTA::Vector3 GTA::Object::GetOffsetPosition(GTA::Vector3 Offset)
	{
		NON_EXISTING_CHECK(V3_NULL);
		float x = 0.0f; float y = 0.0f; float z = 0.0f;
		IVSDKDotNet::Native::Natives::GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(pHandle, Offset.X, Offset.Y, Offset.Z, x, y, z);
		return GTA::Vector3(x, y, z);
	}

	Blip^ GTA::Object::AttachBlip()
	{
		NON_EXISTING_CHECK(nullptr);
		return Blip::AddBlip(this);
	}

	void GTA::Object::AttachToPed(Ped^ ped, Bone bone, Vector3 PositionOffset, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);

		CurrentRoom = ped->CurrentRoom;
		if (isAttachedSomewhere)
			Detach();

		IVSDKDotNet::Native::Natives::ATTACH_OBJECT_TO_PED(pHandle, ped->Handle, (u32)bone, PositionOffset.X, PositionOffset.Y, PositionOffset.Z, Rotation.X, Rotation.Y, Rotation.Z, 0);
	}
	void GTA::Object::AttachToVehicle(Vehicle^ vehicle, Vector3 PositionOffset, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);

		if (isAttachedSomewhere)
			Detach();

		IVSDKDotNet::Native::Natives::ATTACH_OBJECT_TO_CAR(pHandle, vehicle->Handle, 0, PositionOffset.X, PositionOffset.Y, PositionOffset.Z, Rotation.X, Rotation.Y, Rotation.Z);
	}

	void GTA::Object::ApplyForce(Vector3 Direction, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::APPLY_FORCE_TO_OBJECT(pHandle, 3, Direction.X, Direction.Y, Direction.Z, Rotation.X, Rotation.Y, Rotation.Z, 0, 0, 1, 1);
	}
	void GTA::Object::ApplyForce(Vector3 Direction)
	{
		ApplyForce(Direction, Vector3());
	}

	void GTA::Object::ApplyForceRelative(Vector3 Direction, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::APPLY_FORCE_TO_OBJECT(pHandle, 3, Direction.X, Direction.Y, Direction.Z, Rotation.X, Rotation.Y, Rotation.Z, 0, 1, 1, 1);
	}
	void GTA::Object::ApplyForceRelative(Vector3 Direction)
	{
		ApplyForceRelative(Direction, Vector3());
	}

	void GTA::Object::Delete()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		SetExistsFalse();

		if (pHandle == 0)
			return;

		int obj = pHandle;
		IVSDKDotNet::Native::Natives::DELETE_OBJECT(obj);
	}
	void GTA::Object::Detach()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::DETACH_OBJECT(pHandle, true);
	}

	bool GTA::Object::InternalCheckExists()
	{
		if (pHandle == 0)
			return false;

		return IVSDKDotNet::Native::Natives::DOES_OBJECT_EXIST(pHandle);
	}
	void GTA::Object::NoLongerNeeded()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		IVSDKDotNet::Native::Natives::MARK_OBJECT_AS_NO_LONGER_NEEDED(pHandle);
	}

}