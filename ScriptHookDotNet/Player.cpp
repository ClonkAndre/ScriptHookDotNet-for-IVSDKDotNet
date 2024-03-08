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

#include "Player.h"

#include "ContentCache.h"
#include "Group.h"
#include "Object.h"
#include "Ped.h"
#include "Team.h"
#include "World.h"
#include "vPedSkin.h"
#include "vWeaponCollection.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Player::Player(int ID)
	{
		this->pID = ID;
	}

	// - - - Properties, Methods and Functions - - -
	int Player::ID::get()
	{
		return pID;
	}
	int Player::Index::get()
	{
		return IVSDKDotNet::Native::Natives::CONVERT_INT_TO_PLAYERINDEX(pID);
	}
	int Player::PedHandle::get()
	{
		int c;
		IVSDKDotNet::Native::Natives::GET_PLAYER_CHAR(Index, c);
		return c;
	}

	Ped^ Player::Character::get()
	{
		int c = PedHandle;

		if (c == 0)
			return nullptr;

		if (!Object::ReferenceEquals(pPed, nullptr))
		{
			if (c == pPed->Handle)
				return pPed;

			pPed->SetHandle(c);
		}
		else
		{
			pPed = ContentCache::GetPed(c);
		}

		return pPed;
	}

	GTA::Group^ Player::Group::get()
	{
		int c;
		IVSDKDotNet::Native::Natives::GET_PLAYER_GROUP(Index, c);

		if (c == 0)
			return nullptr;

		if (!Object::ReferenceEquals(pGroup, nullptr))
		{
			if (c == pGroup->Handle)
				return pGroup;

			pGroup->SetHandle(c, false);
		}
		else
		{
			pGroup = ContentCache::GetGroup(c, false);
		}

		return pGroup;
	}

	String^ Player::Name::get()
	{
		return IVSDKDotNet::Native::Natives::GET_PLAYER_NAME(Index);
	}

	GTA::Model Player::Model::get()
	{
		int model;
		IVSDKDotNet::Native::Natives::GET_CHAR_MODEL(PedHandle, model);
		return GTA::Model(model);
	}
	void Player::Model::set(GTA::Model value)
	{
		if (!Model.isPed)
			return;
		if (value == Model)
			return;

		Room r = Character->CurrentRoom;
		float heading = Character->Heading;
		int health = Character->Health;
		int armor = Character->Armor;
		int wanted = WantedLevel;
		array<int>^ ammo = Character->Weapons->GetAmmoArray();
		GTA::Weapon weap = Character->Weapons->CurrentType;

		if (!value.LoadToMemoryNow(10000))
			return;
		IVSDKDotNet::Native::Natives::CHANGE_PLAYER_MODEL(Index, (u32)value.Hash);
		value.AllowDisposeFromMemory();

		Character->SetDefaultVoice();

		Character->CurrentRoom = r;
		Character->Heading = heading;
		Character->Health = health;
		Character->Armor = armor;
		WantedLevel = wanted;
		Character->Weapons->SetAmmoArray(ammo);
		Character->Weapons->Select(weap);
	}

	GTA::value::PlayerSkin^ Player::Skin::get()
	{
		if isNULL(pSkin)
			pSkin = gcnew value::PlayerSkin(this);

		return pSkin;
	}

	System::Drawing::Color Player::Color::get()
	{
		int R = 0; int G = 0; int B = 0;
		IVSDKDotNet::Native::Natives::GET_PLAYER_RGB_COLOUR(Index, R, G, B);
		return System::Drawing::Color::FromArgb(R, G, B);
	}

	GTA::Multiplayer::Team^ Player::Team::get()
	{
		int t = force_cast<int>(IVSDKDotNet::Native::Natives::GET_PLAYER_TEAM(Index));

		if (t < 0)
			return nullptr;

		return gcnew GTA::Multiplayer::Team(t);
	}
	void Player::Team::set(GTA::Multiplayer::Team^ value)
	{
		if (isNULL(value) || (value->ID < 0) || (value->ID > 16))
			IVSDKDotNet::Native::Natives::SET_PLAYER_TEAM(Index, -1);
		else
			IVSDKDotNet::Native::Natives::SET_PLAYER_TEAM(Index, value->ID);
	}

	bool Player::isActive::get()
	{
		if (isLocalPlayer)
			return isNotNULL(Character);

		return IVSDKDotNet::Native::Natives::IS_NETWORK_PLAYER_ACTIVE(ID);
	}

	bool Player::CanControlCharacter::get()
	{
		return IVSDKDotNet::Native::Natives::IS_PLAYER_CONTROL_ON(Index);
	}
	void Player::CanControlCharacter::set(bool value)
	{
		IVSDKDotNet::Native::Natives::SET_PLAYER_CONTROL(Index, value);
	}

	int Player::WantedLevel::get()
	{
		u32 wl;
		IVSDKDotNet::Native::Natives::STORE_WANTED_LEVEL(Index, wl);
		return wl;
	}
	void Player::WantedLevel::set(int value)
	{
		if (value > 0)
			IVSDKDotNet::Native::Natives::ALTER_WANTED_LEVEL(Index, (u32)value);
		else
			IVSDKDotNet::Native::Natives::CLEAR_WANTED_LEVEL(Index);

		IVSDKDotNet::Native::Natives::APPLY_WANTED_LEVEL_CHANGE_NOW(Index);
	}

	int Player::Money::get()
	{
		u32 s;
		IVSDKDotNet::Native::Natives::STORE_SCORE(Index, s);
		return (int)s;
	}
	void Player::Money::set(int value)
	{
		u32 s;
		IVSDKDotNet::Native::Natives::STORE_SCORE(Index, s);

		if (value < 0)
			value = 0;

		IVSDKDotNet::Native::Natives::ADD_SCORE(Index, value - s);
	}

	void Player::MaxHealth::set(int value)
	{
		IVSDKDotNet::Native::Natives::INCREASE_PLAYER_MAX_HEALTH(Index, value + 100);
	}
	void Player::MaxArmor::set(int value)
	{
		IVSDKDotNet::Native::Natives::INCREASE_PLAYER_MAX_ARMOUR(Index, value);
	}

	GTA::Vehicle^ Player::LastVehicle::get()
	{
		if (!isLocalPlayer)
		{
			throw gcnew InvalidOperationException("Player.LastVehicle can only be used on the local player!");
			return nullptr;
		}

		int car;
		IVSDKDotNet::Native::Natives::GET_PLAYERS_LAST_CAR_NO_SAVE(car);

		if (car == 0)
			return nullptr;

		return ContentCache::GetVehicle(car);
	}

	bool Player::isLocalPlayer::get()
	{
		return pID == IVSDKDotNet::Native::Natives::GET_PLAYER_ID();
	}
	bool Player::isOnMission::get()
	{
		return !IVSDKDotNet::Native::Natives::CAN_PLAYER_START_MISSION(Index);
	}
	bool Player::isPlaying::get()
	{
		return IVSDKDotNet::Native::Natives::IS_PLAYER_PLAYING(Index);
	}
	bool Player::isPressingHorn::get()
	{
		return IVSDKDotNet::Native::Natives::IS_PLAYER_PRESSING_HORN(Index);
	}

	void Player::IgnoredByEveryone::set(bool value)
	{
		IVSDKDotNet::Native::Natives::SET_EVERYONE_IGNORE_PLAYER(Index, value);
	}
	void Player::CanControlRagdoll::set(bool value)
	{
		IVSDKDotNet::Native::Natives::GIVE_PLAYER_RAGDOLL_CONTROL(Index, value);
	}
	void Player::NeverGetsTired::set(bool value)
	{
		IVSDKDotNet::Native::Natives::SET_PLAYER_NEVER_GETS_TIRED(Index, value);
	}

	bool Player::isTargetting(Ped^ ped)
	{
		return IVSDKDotNet::Native::Natives::IS_PLAYER_FREE_AIMING_AT_CHAR(Index, ped->Handle);
	}
	bool Player::isTargetting(GTA::Object^ object)
	{
		return IVSDKDotNet::Native::Natives::IS_PLAYER_TARGETTING_OBJECT(Index, object->Handle);
	}

	[System::Runtime::ExceptionServices::HandleProcessCorruptedStateExceptions]
		Ped^ Player::GetTargetedPed()
	{
		array<int>^ list = World::GetValidPedHandles(GTA::Model::Null);

		for (int i = 0; i < list->Length; i++)
		{
			if (IVSDKDotNet::Native::Natives::IS_PLAYER_FREE_AIMING_AT_CHAR(Index, list[i]))
				return ContentCache::GetPed(list[i]);
		}

		return nullptr;
	}

	void Player::SetComponentVisibility(PedComponent Component, bool Visible)
	{
		if (!isLocalPlayer)
		{
			throw gcnew InvalidOperationException("Player.SetComponentVisibility can only be used on the local player!");
			return;
		}

		IVSDKDotNet::Native::Natives::SET_DRAW_PLAYER_COMPONENT((int)Component, Visible);
	}

	void Player::ActivateMultiplayerSkin()
	{
		if (!isLocalPlayer)
		{
			throw gcnew InvalidOperationException("Player.ActivateMultiplayerSkin can only be used on the local player!");
			return;
		}

		Model = GTA::Model(IVSDKDotNet::Native::Natives::GET_PLAYERSETTINGS_MODEL_CHOICE());
		IVSDKDotNet::Native::Natives::SET_PLAYERSETTINGS_MODEL_VARIATIONS_CHOICE(Index);
		Character->SetDefaultVoice();
	}

	void Player::TeleportTo(Vector3 Position)
	{
		if (!isLocalPlayer)
		{
			throw gcnew InvalidOperationException("Player.TeleportTo can only be used on the local player!");
			return;
		}

		GTA::Ped^ p = Character;
		p->Position = Position;
		GTA::World::LoadEnvironmentNow(Position);

		if (Position.Z == 0.0f)
			p->Position = GTA::World::GetGroundPosition(Position, GroundType::Highest);
	}
	void Player::TeleportTo(float X, float Y)
	{
		TeleportTo(Vector3(X, Y, 0.0f));
	}

	bool Player::operator == (Player^ left, Player^ right)
	{
		if (Object::ReferenceEquals(left, nullptr))
			return Object::ReferenceEquals(right, nullptr);
		if (Object::ReferenceEquals(right, nullptr))
			return false;

		return (left->ID == right->ID);
	}
	bool Player::operator != (Player^ left, Player^ right)
	{
		return !(left == right);
	}

	bool Player::operator == (Player^ left, Ped^ right)
	{
		if (Object::ReferenceEquals(left, nullptr))
			return Object::ReferenceEquals(right, nullptr);
		if (Object::ReferenceEquals(right, nullptr))
			return false;

		return (left->PedHandle == right->Handle);
	}
	bool Player::operator != (Player^ left, Ped^ right)
	{
		return !(left == right);
	}
	bool Player::operator == (Ped^ left, Player^ right)
	{
		if (Object::ReferenceEquals(left, nullptr))
			return Object::ReferenceEquals(right, nullptr);
		if (Object::ReferenceEquals(right, nullptr))
			return false;

		return (left->Handle == right->PedHandle);
	}
	bool Player::operator != (Ped^ left, Player^ right)
	{
		return !(left == right);
	}

}