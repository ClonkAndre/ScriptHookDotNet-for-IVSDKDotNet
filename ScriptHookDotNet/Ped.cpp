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

#include "Ped.h"

#include "Blip.h"
#include "ContentCache.h"
#include "Game.h"
#include "Object.h"
#include "Player.h"
#include "Vehicle.h"
#include "NmCommands.h"
#include "vEuphoria.h"
#include "vPedSkin.h"
#include "vPedAnimation.h"
#include "vTasks.h"
#include "vWeaponCollection.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Ped::Ped(int Handle)
		:HandleObject(Handle)
	{
	}

	// - - - Properties, Methods and Functions - - -
	void Ped::SetHandle(int Handle)
	{
		ContentCache::RemovePed(this);
		pHandle = Handle;
		ResetExists();
		ContentCache::AddPed(this);
	}

	int Ped::MemoryAddress::get()
	{
		IVSDKDotNet::IVPed^ ped = CCL::GTAIV::NativeWorld::GetPedInstanceFromHandle(pHandle);

		if (!ped)
			return 0;

		return (int)ped->GetUIntPtr().ToUInt32();
	}

	GTA::Model Ped::Model::get()
	{
		NON_EXISTING_CHECK(nullptr);
		u32 model = 0;
		IVSDKDotNet::Native::Natives::GET_CHAR_MODEL(pHandle, model);
		return GTA::Model(model);
	}
	GTA::value::PedSkin^ Ped::Skin::get()
	{
		NON_EXISTING_CHECK(pSkin);

		if isNULL(pSkin)
			pSkin = gcnew GTA::value::PedSkin(this);

		return pSkin;
	}

	Vector3 Ped::Position::get()
	{
		NON_EXISTING_CHECK(V3_NaN);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_CHAR_COORDINATES(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void Ped::Position::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_COORDINATES(pHandle, value.X, value.Y, value.Z);
	}

	Vector3 Ped::Velocity::get()
	{
		NON_EXISTING_CHECK(V3_NULL);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_CHAR_VELOCITY(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void Ped::Velocity::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_VELOCITY(pHandle, value.X, value.Y, value.Z);
	}

	float Ped::Heading::get()
	{
		NON_EXISTING_CHECK(0.0f);
		f32 val;
		IVSDKDotNet::Native::Natives::GET_CHAR_HEADING(pHandle, val);
		return val;
	}
	void Ped::Heading::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_HEADING(pHandle, value);
	}
	Vector3 Ped::Direction::get()
	{
		return Game::HeadingToDirection(Heading);
	}

	GTA::Gender Ped::Gender::get()
	{
		NON_EXISTING_CHECK(GTA::Gender::Male);

		if (IVSDKDotNet::Native::Natives::IS_CHAR_MALE(pHandle))
			return GTA::Gender::Male;

		return GTA::Gender::Female;
	}

	void Ped::Voice::set(String^ value)
	{
		NON_EXISTING_CHECK_NO_RETURN();

		if (isNULL(value) || (value->Length == 0) || value->Equals("default", StringComparison::InvariantCultureIgnoreCase))
		{
			SetDefaultVoice();
			return;
		}

		IVSDKDotNet::Native::Natives::SET_AMBIENT_VOICE_NAME(pHandle, value);
	}

	int Ped::Health::get()
	{
		NON_EXISTING_CHECK(-100);
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CHAR_HEALTH(pHandle, val);
		return ((int)val) - 100;
	}
	void Ped::Health::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_HEALTH(pHandle, value + 100);
	}

	void Ped::MaxHealth::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_MAX_HEALTH(pHandle, value + 100);
	}

	int Ped::Armor::get()
	{
		NON_EXISTING_CHECK(0);
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CHAR_ARMOUR(pHandle, val);
		return (int)val;
	}
	void Ped::Armor::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		int diff = value - Armor;

		if (diff == 0)
			return;

		IVSDKDotNet::Native::Natives::ADD_ARMOUR_TO_CHAR(pHandle, diff);
	}

	int Ped::Money::get()
	{
		NON_EXISTING_CHECK(0);
		return (int)IVSDKDotNet::Native::Natives::GET_CHAR_MONEY(pHandle);
	}
	void Ped::Money::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_MONEY(pHandle, value);
	}

	float Ped::HeightAboveGround::get()
	{
		NON_EXISTING_CHECK(0.0f);
		f32 value = 0.0f;
		IVSDKDotNet::Native::Natives::GET_CHAR_HEIGHT_ABOVE_GROUND(pHandle, value);
		return value;
	}
	bool Ped::isOnFire::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_ON_FIRE(pHandle);
	}
	void Ped::isOnFire::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
		{
			int fire = IVSDKDotNet::Native::Natives::START_CHAR_FIRE(pHandle);

			if (fire == 0)
				return;

			ContentCache::GetFire(fire, true);
		}
		else
		{
			IVSDKDotNet::Native::Natives::EXTINGUISH_CHAR_FIRE(pHandle);
		}
	}

	bool Ped::isRequiredForMission::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_PED_A_MISSION_PED(pHandle);
	}
	void Ped::isRequiredForMission::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
			IVSDKDotNet::Native::Natives::SET_CHAR_AS_MISSION_CHAR(pHandle);
		else
			NoLongerNeeded();
	}

	bool Ped::isAlive::get()
	{
		NON_EXISTING_CHECK(false);
		return !isDead;
	}
	bool Ped::isAliveAndWell::get()
	{
		NON_EXISTING_CHECK(false);
		return ((Exists()) && (isAlive) && (!isInjured));
	}
	bool Ped::isDead::get()
	{
		NON_EXISTING_CHECK(true);
		return IVSDKDotNet::Native::Natives::IS_CHAR_DEAD(pHandle);
	}
	bool Ped::isGettingIntoAVehicle::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_GETTING_IN_TO_A_CAR(pHandle);
	}
	bool Ped::isGettingUp::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_GETTING_UP(pHandle);
	}
	bool Ped::isIdle::get()
	{
		NON_EXISTING_CHECK(false);
		if (IVSDKDotNet::Native::Natives::IS_CHAR_INJURED(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_PED_RAGDOLL(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_CHAR_IN_AIR(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_CHAR_ON_FIRE(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_CHAR_DUCKING(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_CHAR_GESTURING(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_CHAR_GETTING_IN_TO_A_CAR(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_AMBIENT_SPEECH_PLAYING(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_SCRIPTED_SPEECH_PLAYING(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_CHAR_IN_MELEE_COMBAT(pHandle))
			return false;
		if (IVSDKDotNet::Native::Natives::IS_PED_IN_COMBAT(pHandle))
			return false;
		if ((IVSDKDotNet::Native::Natives::IS_CHAR_IN_ANY_CAR(pHandle)) && (!IVSDKDotNet::Native::Natives::IS_CHAR_SITTING_IN_ANY_CAR(pHandle)))
			return false;

		return true;
	}
	bool Ped::isInAir::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_IN_AIR(pHandle);
	}
	bool Ped::isInCombat::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_PED_IN_COMBAT(pHandle);
	}
	bool Ped::isInGroup::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_PED_IN_GROUP(pHandle);
	}
	bool Ped::isInjured::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_INJURED(pHandle);
	}
	bool Ped::isInMeleeCombat::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_IN_MELEE_COMBAT(pHandle);
	}
	bool Ped::isInWater::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_IN_WATER(pHandle);
	}
	bool Ped::isMissionCharacter::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_PED_A_MISSION_PED(pHandle);
	}

	bool Ped::isRagdoll::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_PED_RAGDOLL(pHandle);
	}
	void Ped::isRagdoll::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
		{
			PreventRagdoll = false;
			IVSDKDotNet::Native::Natives::SWITCH_PED_TO_RAGDOLL(pHandle, 10000, -1, 0, 1, 1, 0); // 10000, 10000, 0, 0, 0, 0) //10000, -1, 2, 1, 1, 0
		}
		else
		{
			IVSDKDotNet::Native::Natives::SWITCH_PED_TO_ANIMATED(pHandle, false);
		}
	}

	bool Ped::isOnScreen::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_ON_SCREEN(pHandle);
	}

	bool Ped::isShooting::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_SHOOTING(pHandle);
	}

	bool Ped::isSwimming::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_SWIMMING(pHandle);
	}

	void Ped::Invincible::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_INVINCIBLE(pHandle, value);
	}

	void Ped::Visible::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_VISIBLE(pHandle, value);
	}

	Room Ped::CurrentRoom::get()
	{
		NON_EXISTING_CHECK(Room(0, 0));
		int ii = 0;
		u32 rk;
		IVSDKDotNet::Native::Natives::GET_INTERIOR_FROM_CHAR(pHandle, ii);
		IVSDKDotNet::Native::Natives::GET_KEY_FOR_CHAR_IN_ROOM(pHandle, rk);
		return Room(force_cast<int>(rk), ii);
	}
	void Ped::CurrentRoom::set(Room value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_ROOM_FOR_CHAR_BY_KEY(pHandle, (u32)value.RoomKey);
	}

	void Ped::FreezePosition::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::FREEZE_CHAR_POSITION(pHandle, value);
	}

	GTA::Vehicle^ Ped::CurrentVehicle::get()
	{
		NON_EXISTING_CHECK(nullptr);
		int car;
		IVSDKDotNet::Native::Natives::GET_CAR_CHAR_IS_USING(pHandle, car);

		if (car == 0)
			return nullptr;

		// return gcnew GTA::Vehicle(car);
		return ContentCache::GetVehicle(car);
	}

	Blip^ Ped::AttachBlip()
	{
		NON_EXISTING_CHECK(nullptr);
		return Blip::AddBlip(this);
	}

	void Ped::AttachTo(Vehicle^ vehicle, GTA::Vector3 Offset)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);
		IVSDKDotNet::Native::Natives::ATTACH_PED_TO_CAR(pHandle, vehicle->Handle, 0, Offset.X, Offset.Y, Offset.Z, 0.0f, 0.0f, 0, 0);
	}
	void Ped::Detach()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::DETACH_PED(pHandle, true);
	}
	bool Ped::isAttachedToVehicle()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_PED_ATTACHED_TO_ANY_CAR(pHandle);
	}

	void Ped::ApplyForce(Vector3 Direction, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::APPLY_FORCE_TO_PED(pHandle, 3, Direction.X, Direction.Y, Direction.Z, Rotation.X, Rotation.Y, Rotation.Z, 0, 0, 1, 1);
	}
	void Ped::ApplyForce(Vector3 Direction)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		ApplyForce(Direction, Vector3());
	}

	void Ped::ApplyForceRelative(Vector3 Direction, Vector3 Rotation)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::APPLY_FORCE_TO_PED(pHandle, 3, Direction.X, Direction.Y, Direction.Z, Rotation.X, Rotation.Y, Rotation.Z, 0, 1, 1, 1);
	}
	void Ped::ApplyForceRelative(Vector3 Direction)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		ApplyForceRelative(Direction, Vector3());
	}

	void Ped::Accuracy::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_ACCURACY(pHandle, value);
	}
	void Ped::AlwaysDiesOnLowHealth::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_WILL_MOVE_WHEN_INJURED(pHandle, !value);
		IVSDKDotNet::Native::Natives::SET_PED_DIES_WHEN_INJURED(pHandle, value);
	}
	void Ped::BlockPermanentEvents::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(pHandle, value);
	}
	void Ped::BlockWeaponSwitching::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::BLOCK_PED_WEAPON_SWITCHING(pHandle, value);
	}
	void Ped::BlockGestures::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::BLOCK_CHAR_GESTURE_ANIMS(pHandle, value);
	}
	void Ped::CanBeDraggedOutOfVehicle::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_CANT_BE_DRAGGED_OUT(pHandle, !value);
	}
	void Ped::CanBeKnockedOffBike::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE(pHandle, value);
	}
	void Ped::CanSwitchWeapons::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::BLOCK_PED_WEAPON_SWITCHING(pHandle, !value);
	}
	void Ped::CowerInsteadOfFleeing::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING(pHandle, value);
	}
	void Ped::DuckWhenAimedAtByGroupMember::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT(pHandle, value);
	}
	void Ped::Enemy::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_AS_ENEMY(pHandle, value);
	}
	void Ped::PreventRagdoll::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::UNLOCK_RAGDOLL(pHandle, !value);
	}
	void Ped::PriorityTargetForEnemies::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_IS_TARGET_PRIORITY(pHandle, value);
	}
	void Ped::SenseRange::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_SENSE_RANGE(pHandle, value);
	}
	void Ped::WantedByPolice::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_WANTED_BY_POLICE(pHandle, value);
	}
	void Ped::WillDoDrivebys::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_WILL_DO_DRIVEBYS(pHandle, value);
	}
	void Ped::WillFlyThroughWindscreen::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(pHandle, value);
	}
	void Ped::WillUseCarsInCombat::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_WILL_USE_CARS_IN_COMBAT(pHandle, value);
	}

	GTA::PedType Ped::PedType::get()
	{
		NON_EXISTING_CHECK(GTA::PedType::CivMale);
		u32 t;
		IVSDKDotNet::Native::Natives::GET_PED_TYPE(pHandle, t);
		return (GTA::PedType)t;
	}

	GTA::RelationshipGroup Ped::RelationshipGroup::get()
	{
		NON_EXISTING_CHECK(GTA::RelationshipGroup::Civillian_Male);

		if (MemoryAddress == 0)
			return GTA::RelationshipGroup::Civillian_Male;

		return (GTA::RelationshipGroup) * (int*)(MemoryAddress + 0xBB4);
	}
	void Ped::RelationshipGroup::set(GTA::RelationshipGroup group)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_RELATIONSHIP_GROUP(pHandle, (int)group);
	}
	void Ped::ChangeRelationship(GTA::RelationshipGroup group, Relationship level)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_RELATIONSHIP(pHandle, (u32)level, (int)group);
	}
	void Ped::CantBeDamagedByRelationshipGroup(GTA::RelationshipGroup group, bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP(pHandle, (int)group, value);
	}

	void Ped::FireDamageMultiplier::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_FIRE_DAMAGE_MULTIPLIER(pHandle, value);
	}
	void Ped::GravityMultiplier::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_GRAVITY(pHandle, value);
	}

	value::PedAnimation^ Ped::Animation::get()
	{
		NON_EXISTING_CHECK(pAnimation);

		if isNULL(pAnimation)
			pAnimation = gcnew value::PedAnimation(this);

		return pAnimation;
	}
	value::PedTasks^ Ped::Task::get()
	{
		//NON_EXISTING_CHECK(pTasks); // cannot be checked due to TaskSequence's use of Ped(0)

		if isNULL(pTasks)
			pTasks = gcnew value::PedTasks(this);

		return pTasks;
	}
	value::WeaponCollection^ Ped::Weapons::get()
	{
		NON_EXISTING_CHECK(pWeapons);

		if isNULL(pWeapons)
			pWeapons = gcnew value::WeaponCollection(this);

		return pWeapons;
	}
	value::Euphoria^ Ped::Euphoria::get()
	{
		NON_EXISTING_CHECK(pEuphoria);

		if isNULL(pEuphoria)
			pEuphoria = gcnew value::Euphoria(this);

		return pEuphoria;
	}
	//value::Weapon^ Ped::Weapon() {
	//	Scripting::eWeapon w;
	//	Scripting::GetCurrentCharWeapon(pHandle,&w);
	//	return Weapon((GTA::Weapon)w);
	//}
	//value::Weapon^ Ped::Weapon(GTA::Weapon weapon) {
	//	GTA::value::Weapon^ w;
	//	if isNULL(pWeaponCache) {
	//		pWeaponCache = gcnew Dictionary<GTA::Weapon,GTA::value::Weapon^>();
	//	} else {
	//		if (pWeaponCache->TryGetValue(weapon, w)) return w;
	//	}
	//	w = gcnew GTA::value::Weapon(this, weapon);
	//	pWeaponCache->Add(weapon, w);
	//	return w;
	//}

	bool Ped::HasBeenDamagedBy(GTA::Weapon weapon)
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(pHandle, (u32)weapon);
	}
	bool Ped::HasBeenDamagedBy(Vehicle^ vehicle)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(vehicle, false);
		return IVSDKDotNet::Native::Natives::HAS_CHAR_BEEN_DAMAGED_BY_CAR(pHandle, vehicle->Handle);
	}
	bool Ped::HasBeenDamagedBy(Ped^ ped)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(ped, false);
		return IVSDKDotNet::Native::Natives::HAS_CHAR_BEEN_DAMAGED_BY_CHAR(pHandle, ped->Handle, false);
	}

	bool Ped::isInVehicle(Vehicle^ vehicle)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(vehicle, false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_IN_CAR(pHandle, vehicle->Handle);
	}
	bool Ped::isInVehicle()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_IN_ANY_CAR(pHandle);
	}

	bool Ped::isSittingInVehicle(Vehicle^ vehicle)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(vehicle, false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_SITTING_IN_CAR(pHandle, vehicle->Handle);
	}
	bool Ped::isSittingInVehicle()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_SITTING_IN_ANY_CAR(pHandle);
	}

	//bool Ped::isEnteringOrLeavingVehicle(Vehicle^ vehicle) {
	//	if (!Scripting::IsCharInCar(pHandle, vehicle->Handle)) return false;
	//	return !Scripting::IsCharSittingInCar(pHandle, vehicle->Handle);
	//}
	//bool Ped::isEnteringOrLeavingVehicle() {
	//	if (!Scripting::IsCharInAnyCar(pHandle)) return false;
	//	return !Scripting::IsCharSittingInAnyCar(pHandle);
	//}

	bool Ped::isTouching(GTA::Object^ object)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(object, false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_TOUCHING_OBJECT(pHandle, object->Handle);
	}
	bool Ped::isTouching(Vehicle^ vehicle)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(vehicle, false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_TOUCHING_VEHICLE(pHandle, vehicle->Handle);
	}
	bool Ped::isTouching(Ped^ ped)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(ped, false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_TOUCHING_CHAR(pHandle, ped->Handle);
	}

	bool Ped::isInArea(Vector3 Corner1, Vector3 Corner2, bool IgnoreHeight)
	{
		NON_EXISTING_CHECK(false);
		if (IgnoreHeight)
			return IVSDKDotNet::Native::Natives::IS_CHAR_IN_AREA_2D(pHandle, Corner1.X, Corner1.Y, Corner2.X, Corner2.Y, false);
		else
			return IVSDKDotNet::Native::Natives::IS_CHAR_IN_AREA_3D(pHandle, Corner1.X, Corner1.Y, Corner1.Z, Corner2.X, Corner2.Y, Corner2.Z, false);
	}

	GTA::Vector3 Ped::GetBonePosition(GTA::Bone Bone)
	{
		NON_EXISTING_CHECK(V3_NaN);
		System::Numerics::Vector3 vec;
		IVSDKDotNet::Native::Natives::GET_PED_BONE_POSITION(pHandle, (u32)Bone, 0.0f, 0.0f, 0.0f, vec);
		return Vector3ToGTAVector3(vec);
	}

	GTA::Vector3 Ped::GetOffsetPosition(GTA::Vector3 Offset)
	{
		NON_EXISTING_CHECK(V3_NULL);
		float x = 0.0f; float y = 0.0f; float z = 0.0f;
		IVSDKDotNet::Native::Natives::GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pHandle, Offset.X, Offset.Y, Offset.Z, x, y, z);
		return GTA::Vector3(x, y, z);
	}

	void Ped::SetPathfinding(bool AllowClimbovers, bool AllowLadders, bool AllowDropFromHeight)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_PED_PATH_MAY_USE_CLIMBOVERS(pHandle, AllowClimbovers);
		IVSDKDotNet::Native::Natives::SET_PED_PATH_MAY_USE_LADDERS(pHandle, AllowLadders);
		IVSDKDotNet::Native::Natives::SET_PED_PATH_MAY_DROP_FROM_HEIGHT(pHandle, AllowDropFromHeight);
	}

	void Ped::GiveFakeNetworkName(System::String^ Name, System::Drawing::Color Color)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::GIVE_PED_FAKE_NETWORK_NAME(pHandle, Name, (int)Color.R, (int)Color.G, (int)Color.B, (int)Color.A);
	}

	void Ped::RemoveFakeNetworkName()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::REMOVE_FAKE_NETWORK_NAME_FROM_PED(pHandle);
	}

	void Ped::FleeByVehicle(GTA::Vehicle^ Vehicle)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(Vehicle);
		IVSDKDotNet::Native::Natives::FORCE_PED_TO_FLEE_WHILST_DRIVING_VEHICLE(pHandle, Vehicle->Handle);
	}

	void Ped::ShootAt(Vector3 Position)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::FIRE_PED_WEAPON(pHandle, Position.X, Position.Y, Position.Z);
	}
	void Ped::ForceHelmet(bool enable)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (enable)
			IVSDKDotNet::Native::Natives::GIVE_PED_HELMET(pHandle);
		else
			IVSDKDotNet::Native::Natives::REMOVE_PED_HELMET(pHandle, true);
	}
	void Ped::ForceRagdoll(int duration, bool TryToStayUpright)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		PreventRagdoll = false;
		IVSDKDotNet::Native::Natives::SWITCH_PED_TO_RAGDOLL(pHandle, 10000, duration, (TryToStayUpright ? 2 : 0), 1, 1, 0);

		//Behavior:
		// 0 = Plain ragdoll, no movement
		// 1 = Stiff NULL position / NM Control
		// 2 = Try to stand
	}
	void Ped::SetDefensiveArea(Vector3 Position, float Radius)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_SPHERE_DEFENSIVE_AREA(pHandle, Position.X, Position.Y, Position.Z, Radius);
	}
	void Ped::MakeProofTo(bool Bullets, bool Fire, bool Explosions, bool FallingDamage, bool MeleeAttacks)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_PROOFS(pHandle, Bullets, Fire, Explosions, FallingDamage, MeleeAttacks);
	}

	void Ped::WarpIntoVehicle(GTA::Vehicle^ Vehicle, VehicleSeat Seat)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(Vehicle);

		if (Seat <= VehicleSeat::None)
			return;
		if (Seat == VehicleSeat::Driver)
		{
			IVSDKDotNet::Native::Natives::WARP_CHAR_INTO_CAR(pHandle, Vehicle->Handle);
		}
		else
		{
			if (isInVehicle(Vehicle))
				IVSDKDotNet::Native::Natives::WARP_CHAR_FROM_CAR_TO_CAR(pHandle, Vehicle->Handle, (u32)Seat); // change seat
			else
				IVSDKDotNet::Native::Natives::WARP_CHAR_INTO_CAR_AS_PASSENGER(pHandle, Vehicle->Handle, (u32)Seat);
		}
	}

	void Ped::DropCurrentWeapon()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::FORCE_CHAR_TO_DROP_WEAPON(pHandle);
	}
	void Ped::LeaveGroup()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::REMOVE_CHAR_FROM_GROUP(pHandle);
	}
	void Ped::LeaveVehicle()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::_TASK_LEAVE_ANY_CAR(pHandle);
	}
	void Ped::RandomizeOutfit()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_RANDOM_COMPONENT_VARIATION(pHandle);
	}
	void Ped::BecomeMissionCharacter()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CHAR_AS_MISSION_CHAR(pHandle);
	}

	void Ped::CancelAmbientSpeech()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(pHandle);
	}

	void Ped::SayAmbientSpeech(String^ PhraseID)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		CancelAmbientSpeech();
		IVSDKDotNet::Native::Natives::SAY_AMBIENT_SPEECH(pHandle, PhraseID, true, true, 0);
	}

	void Ped::StartKillingSpree(bool alsoAttackPlayer)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		//GTA::RelationshipGroup grp = GTA::RelationshipGroup::Civillian_Male; // GTA::RelationshipGroup::Criminal
		//RelationshipGroup = grp;
		//ChangeRelationship(grp, GTA::Relationship::Like);

		int i = 1;
		if (alsoAttackPlayer)
			i = 0;

		for (; i <= 22; i++)
			ChangeRelationship((GTA::RelationshipGroup)i, GTA::Relationship::Hate);
		//BlockPermanentEvents = true;
		AlwaysDiesOnLowHealth = true;
		//CowerInsteadOfFleeing = true;
		//WantedByPolice = true;
		if (isInVehicle())
		{
			WillUseCarsInCombat = true;
			WillDoDrivebys = true;
		}

		//Weapon weap = Weapons->CurrentType;

		//TaskSequence^ ts = gcnew TaskSequence();
		//ts->AddTask->SwapWeapon(weap);
		//ts->AddTask->AimAt(Position,5000);
  //    ts->AddTask->FightAgainstHatedTargets(100.0F,65000);

		Task->ClearAll();
		Task->AlwaysKeepTask = true;
		//Task->PerformSequence(ts);
		//Task->SwapWeapon(weap);
		//Task->AimAt(Position,5000);
		Task->FightAgainstHatedTargets(20.0F);
		//BlockPermanentEvents = false;
	}

	void Ped::NoLongerNeeded()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		IVSDKDotNet::Native::Natives::MARK_CHAR_AS_NO_LONGER_NEEDED(pHandle);
	}

	bool Ped::InternalCheckExists()
	{
		if (pHandle == 0)
			return false;

		// This seems to randomly return false? I guess its because its gettig called from the rendering thread instead of the proper "script" thread?
		// CONFIRMED THAT IT RANDOMLY RETURNS FALSE!
		return IVSDKDotNet::Native::Natives::DOES_CHAR_EXIST(pHandle);
	}
	void Ped::Die()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		Health = -100;
	}
	void Ped::Delete()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		SetExistsFalse();

		if (pHandle == 0)
			return;

		int ped = pHandle;
		IVSDKDotNet::Native::Natives::DELETE_CHAR(ped);
	}

	void Ped::SetDefaultVoice()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_VOICE_ID_FROM_HEAD_COMPONENT(pHandle, false, IVSDKDotNet::Native::Natives::IS_CHAR_MALE(pHandle));
	}

	Player^ Ped::GetControllingPlayer()
	{
		NON_EXISTING_CHECK(nullptr);

		array<Player^>^ players = Game::PlayerList;
		for (int i = 0; i < players->Length; i++)
		{
			Player^ player = players[i];

			if (this == player->Character)
				return player;
		}
		return nullptr;
	}

	Ped::operator Ped ^ (Player^ source)
	{
		return source->Character;
	}

}