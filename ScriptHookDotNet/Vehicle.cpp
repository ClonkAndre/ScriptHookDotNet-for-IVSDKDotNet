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

#include "Vehicle.h"

#include "Blip.h"
#include "ContentCache.h"
#include "Game.h"
#include "Ped.h"
#include "vTasks.h"
#include "vVehicleDoor.h"
#include "vVehicleExtra.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Vehicle::Vehicle(int handle)
		:HandleObject(handle)
	{
	}

	// - - - Properties, Methods and Functions - - -
	int Vehicle::MemoryAddress::get()
	{
		IVSDKDotNet::IVVehicle^ veh = CCL::GTAIV::NativeWorld::GetVehicleInstaceFromHandle(pHandle);

		if (!veh)
			return 0;

		return (int)veh->GetUIntPtr().ToUInt32();
	}
	Vector3 Vehicle::Position::get()
	{
		NON_EXISTING_CHECK(V3_NaN);

		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_CAR_COORDINATES(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void Vehicle::Position::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_COORDINATES(pHandle, value.X, value.Y, value.Z);
	}

	float Vehicle::Heading::get()
	{
		NON_EXISTING_CHECK(0.0f);
		f32 val;
		IVSDKDotNet::Native::Natives::GET_CAR_HEADING(pHandle, val);
		return val;
	}
	void Vehicle::Heading::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_HEADING(pHandle, value);
	}
	Vector3 Vehicle::Direction::get()
	{
		return Game::HeadingToDirection(Heading);
	}

	Vector3 Vehicle::Rotation::get()
	{
		return RotationQuaternion.ToRotation();
	}
	void Vehicle::Rotation::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		RotationQuaternion = Quaternion::FromRotation(value);
	}

	Quaternion Vehicle::RotationQuaternion::get()
	{
		NON_EXISTING_CHECK(Quaternion());
		float x, y, z, w;
		IVSDKDotNet::Native::Natives::GET_VEHICLE_QUATERNION(pHandle, x, y, z, w);
		return Quaternion(x, y, z, w);
	}
	void Vehicle::RotationQuaternion::set(Quaternion value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_VEHICLE_QUATERNION(pHandle, value.X, value.Y, value.Z, value.W);
	}

	Room Vehicle::CurrentRoom::get()
	{
		NON_EXISTING_CHECK(Room(0, 0));

		int ii = 0;
		u32 rk = 0;

		IVSDKDotNet::Native::Natives::GET_INTERIOR_FROM_CAR(pHandle, ii);
		IVSDKDotNet::Native::Natives::GET_KEY_FOR_CAR_IN_ROOM(pHandle, rk);

		return Room(force_cast<int>(rk), ii);
	}
	void Vehicle::CurrentRoom::set(Room value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_ROOM_FOR_CAR_BY_KEY(pHandle, value.InteriorID);
	}

	float Vehicle::CurrentRPM::get()
	{
		NON_EXISTING_CHECK(0.0f);

		IVSDKDotNet::IVVehicle^ veh = CCL::GTAIV::NativeWorld::GetVehicleInstaceFromHandle(pHandle);

		if (!veh)
			return 0.0f;

		return veh->EngineRPM;
	}

	void Vehicle::FreezePosition::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::FREEZE_CAR_POSITION(pHandle, value);
	}

	void Vehicle::CanBeDamaged::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_CAN_BE_DAMAGED(pHandle, value);
	}
	void Vehicle::CanBeVisiblyDamaged::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_CAN_BE_VISIBLY_DAMAGED(pHandle, value);
	}
	void Vehicle::CanTiresBurst::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAN_BURST_CAR_TYRES(pHandle, value);
	}

	float Vehicle::Dirtyness::get()
	{
		NON_EXISTING_CHECK(0.0f);
		f32 res;
		IVSDKDotNet::Native::Natives::GET_VEHICLE_DIRT_LEVEL(pHandle, res);
		return res;
	}
	void Vehicle::Dirtyness::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_VEHICLE_DIRT_LEVEL(pHandle, value);
	}

	GTA::DoorLock Vehicle::DoorLock::get()
	{
		NON_EXISTING_CHECK(GTA::DoorLock::None);

		u32 value;
		IVSDKDotNet::Native::Natives::GET_CAR_DOOR_LOCK_STATUS(pHandle, value);

		return (GTA::DoorLock)value;
	}
	void Vehicle::DoorLock::set(GTA::DoorLock value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::LOCK_CAR_DOORS(pHandle, (u32)value);
	}

	float Vehicle::EngineHealth::get()
	{
		NON_EXISTING_CHECK(0.0f);
		return IVSDKDotNet::Native::Natives::GET_ENGINE_HEALTH(pHandle);
	}
	void Vehicle::EngineHealth::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_ENGINE_HEALTH(pHandle, value);
		if (value <= 0.0F)
			IVSDKDotNet::Native::Natives::SET_CAR_ENGINE_ON(pHandle, false, true);
	}

	bool Vehicle::EngineRunning::get()
	{
		NON_EXISTING_CHECK(false);
		return (CurrentRPM > 0.0f);
	}
	void Vehicle::EngineRunning::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
			IVSDKDotNet::Native::Natives::SET_CAR_ENGINE_ON(pHandle, true, false); //true,true
		else
			IVSDKDotNet::Native::Natives::SET_CAR_ENGINE_ON(pHandle, false, false);
	}

	void Vehicle::HazardLightsOn::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_VEH_HAZARDLIGHTS(pHandle, value);
	}

	void Vehicle::InteriorLightOn::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_VEH_INTERIORLIGHT(pHandle, value);
	}

	int Vehicle::Health::get()
	{
		NON_EXISTING_CHECK(0);
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CAR_HEALTH(pHandle, val);
		return val;
	}
	void Vehicle::Health::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_HEALTH(pHandle, value);
	}

	bool Vehicle::isAlive::get()
	{
		NON_EXISTING_CHECK(false);
		return !IVSDKDotNet::Native::Natives::IS_CAR_DEAD(pHandle);
	}

	bool Vehicle::isOnAllWheels::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_VEHICLE_ON_ALL_WHEELS(pHandle);
	}

	bool Vehicle::isOnFire::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CAR_ON_FIRE(pHandle);
	}
	void Vehicle::isOnFire::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
		{
			int fire = IVSDKDotNet::Native::Natives::START_CAR_FIRE(pHandle);
			if (fire == 0)
				return;
			ContentCache::GetFire(fire, true);
		}
		else
		{
			IVSDKDotNet::Native::Natives::EXTINGUISH_CAR_FIRE(pHandle);
		}
	}

	bool Vehicle::isRequiredForMission::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CAR_A_MISSION_CAR(pHandle);
	}
	void Vehicle::isRequiredForMission::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
			IVSDKDotNet::Native::Natives::SET_CAR_AS_MISSION_CAR(pHandle);
		else
			NoLongerNeeded();
	}

	bool Vehicle::isOnScreen::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CAR_ON_SCREEN(pHandle);
	}
	bool Vehicle::isDriveable::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_VEH_DRIVEABLE(pHandle);
	}

	bool Vehicle::isUpright::get()
	{
		NON_EXISTING_CHECK(true);
		return IVSDKDotNet::Native::Natives::IS_CAR_UPRIGHT(pHandle);
	}
	bool Vehicle::isUpsideDown::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CAR_UPSIDEDOWN(pHandle);
	}

	bool Vehicle::LightsOn::get()
	{
		NON_EXISTING_CHECK(false);

		IVSDKDotNet::IVVehicle^ veh = CCL::GTAIV::NativeWorld::GetVehicleInstaceFromHandle(pHandle);

		if (!veh)
			return false;

		return veh->VehicleFlags->LightsOn;
	}

	GTA::Model Vehicle::Model::get()
	{
		NON_EXISTING_CHECK(nullptr);
		u32 model;
		IVSDKDotNet::Native::Natives::GET_CAR_MODEL(pHandle, model);
		return GTA::Model(model);
	}

	String^ Vehicle::Name::get()
	{
		NON_EXISTING_CHECK(String::Empty);
		u32 model;
		IVSDKDotNet::Native::Natives::GET_CAR_MODEL(pHandle, model);
		return IVSDKDotNet::Native::Natives::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
	}

	void Vehicle::NeedsToBeHotwired::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_NEEDS_TO_BE_HOTWIRED(pHandle, value);
	}

	int Vehicle::PassengerSeats::get()
	{
		NON_EXISTING_CHECK(0);
		u32 val;
		IVSDKDotNet::Native::Natives::GET_MAXIMUM_NUMBER_OF_PASSENGERS(pHandle, val);
		return (int)val;
	}

	float Vehicle::PetrolTankHealth::get()
	{
		NON_EXISTING_CHECK(0.0f);
		return IVSDKDotNet::Native::Natives::GET_PETROL_TANK_HEALTH(pHandle);
	}
	void Vehicle::PetrolTankHealth::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_PETROL_TANK_HEALTH(pHandle, value);
	}

	void Vehicle::PreviouslyOwnedByPlayer::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_HAS_BEEN_OWNED_BY_PLAYER(pHandle, value);
	}

	bool Vehicle::SirenActive::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CAR_SIREN_ON(pHandle);
	}
	void Vehicle::SirenActive::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SWITCH_CAR_SIREN(pHandle, value);
	}

	void Vehicle::AllowSirenWithoutDriver::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_SIREN_WITH_NO_DRIVER(pHandle, value);
	}

	float Vehicle::Speed::get()
	{
		NON_EXISTING_CHECK(0.0f);
		float s;
		IVSDKDotNet::Native::Natives::GET_CAR_SPEED(pHandle, s);
		return s;
	}
	void Vehicle::Speed::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (Model.isTrain)
		{
			IVSDKDotNet::Native::Natives::SET_TRAIN_SPEED(pHandle, value);
			IVSDKDotNet::Native::Natives::SET_TRAIN_CRUISE_SPEED(pHandle, value);
		}
		else
		{
			IVSDKDotNet::Native::Natives::SET_CAR_FORWARD_SPEED(pHandle, value);
		}
	}

	Vector3 Vehicle::Velocity::get()
	{
		NON_EXISTING_CHECK(V3_NULL);
		return Direction * Speed;
	}
	void Vehicle::Velocity::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		ApplyForce(value);
	}

	void Vehicle::Visible::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_VISIBLE(pHandle, value);
	}

	GTA::ColorIndex Vehicle::Color::get()
	{
		NON_EXISTING_CHECK(GTA::ColorIndex(0));
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_CAR_COLOURS(pHandle, c1, c2);
		return GTA::ColorIndex((int)c1);
	}
	void Vehicle::Color::set(GTA::ColorIndex value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_CAR_COLOURS(pHandle, c1, c2);
		c1 = value.Index;
		IVSDKDotNet::Native::Natives::CHANGE_CAR_COLOUR(pHandle, c1, c2);
	}

	GTA::ColorIndex Vehicle::FeatureColor1::get()
	{
		NON_EXISTING_CHECK(GTA::ColorIndex(0));
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_CAR_COLOURS(pHandle, c1, c2);
		return GTA::ColorIndex((int)c2);
	}
	void Vehicle::FeatureColor1::set(GTA::ColorIndex value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_CAR_COLOURS(pHandle, c1, c2);
		c2 = value.Index;
		IVSDKDotNet::Native::Natives::CHANGE_CAR_COLOUR(pHandle, c1, c2);
	}

	GTA::ColorIndex Vehicle::SpecularColor::get()
	{
		NON_EXISTING_CHECK(GTA::ColorIndex(0));
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_EXTRA_CAR_COLOURS(pHandle, c1, c2);
		return GTA::ColorIndex((int)c1);
	}
	void Vehicle::SpecularColor::set(GTA::ColorIndex value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_EXTRA_CAR_COLOURS(pHandle, c1, c2);
		c1 = value.Index;
		IVSDKDotNet::Native::Natives::SET_EXTRA_CAR_COLOURS(pHandle, c1, c2);
	}

	GTA::ColorIndex Vehicle::FeatureColor2::get()
	{
		NON_EXISTING_CHECK(GTA::ColorIndex(0));
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_EXTRA_CAR_COLOURS(pHandle, c1, c2);
		return GTA::ColorIndex((int)c2);
	}
	void Vehicle::FeatureColor2::set(GTA::ColorIndex value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		int c1, c2;
		IVSDKDotNet::Native::Natives::GET_EXTRA_CAR_COLOURS(pHandle, c1, c2);
		c2 = value.Index;
		IVSDKDotNet::Native::Natives::SET_EXTRA_CAR_COLOURS(pHandle, c1, c2);
	}

	value::VehicleDoor^ Vehicle::Door(GTA::VehicleDoor index)
	{
		NON_EXISTING_CHECK(nullptr);
		GTA::value::VehicleDoor^ res;
		if isNULL(pDoorCache)
		{
			pDoorCache = gcnew Dictionary<GTA::VehicleDoor, GTA::value::VehicleDoor^>();
		}
		else
		{
			if (pDoorCache->TryGetValue(index, res))
				return res;
		}
		res = gcnew GTA::value::VehicleDoor(this, index);
		pDoorCache->Add(index, res);
		return res;
	}
	value::VehicleExtra^ Vehicle::Extras(int index)
	{
		NON_EXISTING_CHECK(nullptr);
		GTA::value::VehicleExtra^ res;
		if isNULL(pExtraCache)
		{
			pExtraCache = gcnew Dictionary<int, GTA::value::VehicleExtra^>();
		}
		else
		{
			if (pExtraCache->TryGetValue(index, res))
				return res;
		}
		res = gcnew GTA::value::VehicleExtra(this, index);
		pExtraCache->Add(index, res);
		return res;
	}

	GTA::Ped^ Vehicle::CreatePedOnSeat(VehicleSeat Seat)
	{
		NON_EXISTING_CHECK(nullptr);

		if (Seat <= VehicleSeat::None)
			return nullptr;
		if (!isSeatFree(Seat))
			return nullptr;

		int ped;
		if (Seat == VehicleSeat::Driver)
			IVSDKDotNet::Native::Natives::CREATE_RANDOM_CHAR_AS_DRIVER(pHandle, ped);
		else
			IVSDKDotNet::Native::Natives::CREATE_RANDOM_CHAR_AS_PASSENGER(pHandle, (int)Seat, ped);

		if (ped == 0)
			return nullptr;

		return ContentCache::GetPed(ped);
	}
	GTA::Ped^ Vehicle::CreatePedOnSeat(VehicleSeat Seat, GTA::Model model, RelationshipGroup Type)
	{
		NON_EXISTING_CHECK(nullptr);

		if (Seat <= VehicleSeat::None)
			return nullptr;
		if (!isSeatFree(Seat))
			return nullptr;

		model.LoadToMemoryNow();

		int ped;
		if (Seat == VehicleSeat::Driver)
			IVSDKDotNet::Native::Natives::CREATE_CHAR_INSIDE_CAR(pHandle, (u32)Type, model.Hash, ped);
		else
			IVSDKDotNet::Native::Natives::CREATE_CHAR_AS_PASSENGER(pHandle, (u32)Type, model.Hash, (u32)Seat, ped);

		model.AllowDisposeFromMemory();

		if (ped == 0)
			return nullptr;

		return ContentCache::GetPed(ped);
	}
	GTA::Ped^ Vehicle::CreatePedOnSeat(VehicleSeat Seat, GTA::Model model)
	{
		NON_EXISTING_CHECK(nullptr);
		GTA::Ped^ res = CreatePedOnSeat(Seat, model, RelationshipGroup::Civillian_Male);

		if isNULL(res)
			return nullptr;

		if (res->Gender == Gender::Female)
			res->RelationshipGroup = RelationshipGroup::Civillian_Female;

		return res;
	}

	GTA::Ped^ Vehicle::GetPedOnSeat(VehicleSeat Seat)
	{
		NON_EXISTING_CHECK(nullptr);
		int ped;

		if (Seat <= VehicleSeat::None)
			return nullptr;

		if (Seat == VehicleSeat::Driver)
			IVSDKDotNet::Native::Natives::GET_DRIVER_OF_CAR(pHandle, ped);
		else if (IVSDKDotNet::Native::Natives::IS_CAR_PASSENGER_SEAT_FREE(pHandle, (u32)Seat))
			return nullptr;
		else
			IVSDKDotNet::Native::Natives::GET_CHAR_IN_CAR_PASSENGER_SEAT(pHandle, (u32)Seat, ped);

		if (ped == 0)
			return nullptr;

		return ContentCache::GetPed(ped);
	}

	bool Vehicle::isSeatFree(VehicleSeat Seat)
	{
		NON_EXISTING_CHECK(false);

		if (Seat <= VehicleSeat::None)
			return false;

		if (Seat == VehicleSeat::AnyPassengerSeat)
		{
			for (int i = 0; i < PassengerSeats; i++)
			{
				if (isSeatFree((VehicleSeat)i))
					return true;
			}
			return false;
		}
		else if (Seat == VehicleSeat::Driver)
		{
			int ped;
			IVSDKDotNet::Native::Natives::GET_DRIVER_OF_CAR(pHandle, ped);
			return (ped == 0);
		}
		else
		{
			return IVSDKDotNet::Native::Natives::IS_CAR_PASSENGER_SEAT_FREE(pHandle, (u32)Seat);
		}
	}

	bool Vehicle::isTouching(Vehicle^ vehicle)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(vehicle, false);
		return IVSDKDotNet::Native::Natives::IS_CAR_TOUCHING_CAR(pHandle, vehicle->Handle);
	}

	Blip^ Vehicle::AttachBlip()
	{
		NON_EXISTING_CHECK(nullptr);
		return Blip::AddBlip(this);
	}

	VehicleSeat Vehicle::GetFreeSeat()
	{
		NON_EXISTING_CHECK(VehicleSeat::None);
		if (isSeatFree(VehicleSeat::Driver))
			return VehicleSeat::Driver;
		return GetFreePassengerSeat();
	}
	VehicleSeat Vehicle::GetFreePassengerSeat()
	{
		NON_EXISTING_CHECK(VehicleSeat::None);
		int count = PassengerSeats;
		for (int i = 0; i < count; i++)
		{
			if (isSeatFree((VehicleSeat)i))
				return (VehicleSeat)i;
		}
		return VehicleSeat::None;
	}

	GTA::Vector3 Vehicle::GetOffsetPosition(GTA::Vector3 Offset)
	{
		NON_EXISTING_CHECK(V3_NaN);
		float x = 0.0f; float y = 0.0f; float z = 0.0f;
		IVSDKDotNet::Native::Natives::GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(pHandle, Offset.X, Offset.Y, Offset.Z, x, y, z);
		return GTA::Vector3(x, y, z);
	}
	GTA::Vector3 Vehicle::GetOffset(GTA::Vector3 Position)
	{
		NON_EXISTING_CHECK(V3_NULL);
		float x = 0.0f; float y = 0.0f; float z = 0.0f;
		IVSDKDotNet::Native::Natives::GET_OFFSET_FROM_CAR_GIVEN_WORLD_COORDS(pHandle, Position.X, Position.Y, Position.Z, x, y, z);
		return GTA::Vector3(x, y, z);
	}

	void Vehicle::ApplyForce(Vector3 Direction, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::APPLY_FORCE_TO_CAR(pHandle, 3, Direction.X, Direction.Y, Direction.Z, Rotation.X, Rotation.Y, Rotation.Z, 0, 0, 1, 1);
	}
	void Vehicle::ApplyForce(Vector3 Direction)
	{
		ApplyForce(Direction, Vector3());
	}

	void Vehicle::ApplyForceRelative(Vector3 Direction, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::APPLY_FORCE_TO_CAR(pHandle, 3, Direction.X, Direction.Y, Direction.Z, Rotation.X, Rotation.Y, Rotation.Z, 0, 1, 1, 1);
	}
	void Vehicle::ApplyForceRelative(Vector3 Direction)
	{
		ApplyForceRelative(Direction, Vector3());
	}

	bool Vehicle::IsTireBurst(GTA::VehicleWheel wheel)
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CAR_TYRE_BURST(pHandle, (u32)wheel);
	}
	void Vehicle::BurstTire(GTA::VehicleWheel wheel)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::BURST_CAR_TYRE(pHandle, (u32)wheel);
	}
	void Vehicle::FixTire(GTA::VehicleWheel wheel)
	{
		NON_EXISTING_CHECK_NO_RETURN();

		// The native call below fixes the tire but the model still remains bursted so we do this from memory to make sure the model is replaced

		u32 offset = 0;
		switch (wheel)
		{
			case GTA::VehicleWheel::FrontLeft:
				offset = 0x1680;
				break;
			case GTA::VehicleWheel::FrontRight:
				offset = 0x1960;
				break;
			case GTA::VehicleWheel::CenterLeft:
				offset = 0x1C40;
				break;
			case GTA::VehicleWheel::CenterRight:
				offset = 0x1DB0;
				break;
			case GTA::VehicleWheel::RearLeft:
				offset = 0x17F0;
				break;
			case GTA::VehicleWheel::RearRight:
				offset = 0x1AD0;
				break;
		}

		if (offset == 0)
			return;

		IVSDKDotNet::IVVehicle^ veh = CCL::GTAIV::NativeWorld::GetVehicleInstaceFromHandle(pHandle);

		if (!veh)
			return;

		*(float*)(veh->GetUIntPtr().ToUInt32() + offset) = 1000;
		IVSDKDotNet::Native::Natives::FIX_CAR_TYRE(pHandle, (u32)wheel);
	}

	void Vehicle::CloseAllDoors()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CLOSE_ALL_CAR_DOORS(pHandle);
	}
	void Vehicle::Delete()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		SetExistsFalse();

		if (pHandle == 0)
			return;

		int car = pHandle;
		IVSDKDotNet::Native::Natives::DELETE_CAR(car);
	}
	void Vehicle::EveryoneLeaveVehicle()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::_TASK_EVERYONE_LEAVE_CAR(pHandle);
	}
	void Vehicle::PassengersLeaveVehicle(bool Immediately)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		Ped^ p;
		int seats = PassengerSeats;
		for (int seat = 0; seat < seats; seat++)
		{
			p = GetPedOnSeat((VehicleSeat)seat);
			if isNotNULL(p)
			{
				if (Immediately)
					p->Task->LeaveVehicleImmediately(this);
				else
					p->Task->LeaveVehicle(this, true);
			}
		}
	}
	void Vehicle::PassengersLeaveVehicle()
	{
		PassengersLeaveVehicle(false);
	}

	[System::Runtime::ExceptionServices::HandleProcessCorruptedStateExceptions]
	bool Vehicle::InternalCheckExists()
	{
		if (pHandle == 0)
			return false;

		return IVSDKDotNet::Native::Natives::DOES_VEHICLE_EXIST(pHandle);
	}

	void Vehicle::Explode()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::EXPLODE_CAR(pHandle, true, false);
	}
	void Vehicle::NoLongerNeeded()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		IVSDKDotNet::Native::Natives::MARK_CAR_AS_NO_LONGER_NEEDED(pHandle);
	}
	void Vehicle::PlaceOnGroundProperly()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_ON_GROUND_PROPERLY(pHandle);
	}
	void Vehicle::PlaceOnNextStreetProperly()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		float tX, tY, tZ, tH;
		Vector3 p = Position;
		for (int i = 1; i < 40; i++)
		{
			IVSDKDotNet::Native::Natives::GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING(p.X, p.Y, p.Z, i, tX, tY, tZ, tH);
			if (!IVSDKDotNet::Native::Natives::IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(tX, tY, tZ, 5.0f, 5.0f, 5.0f))
			{
				Heading = tH;
				Position = Vector3(tX, tY, tZ);
				PlaceOnGroundProperly();
				return;
			}
		}
	}
	void Vehicle::Repair()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::FIX_CAR(pHandle);
	}
	void Vehicle::MakeProofTo(bool Bullets, bool Fire, bool Explosions, bool Collisions, bool MeleeAttacks)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAR_PROOFS(pHandle, Bullets, Fire, Explosions, Collisions, MeleeAttacks);
	}
	void Vehicle::SoundHorn(int duration)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SOUND_CAR_HORN(pHandle, duration);
	}
	void Vehicle::Wash()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		Dirtyness = 0.0;
		IVSDKDotNet::Native::Natives::WASH_VEHICLE_TEXTURES(pHandle, 255);
	}

}