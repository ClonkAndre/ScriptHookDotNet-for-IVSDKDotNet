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

#include "vWeapon.h"

#include "Ped.h"

#pragma managed

namespace GTA
{
	namespace value
	{

		// - - - Constructor - - -
		Weapon::Weapon(Ped^ Owner, GTA::Weapon ID)
		{
			pOwner = Owner;
			pID = ID;
		}

		// - - - Properties, Methods and Functions - - -
		GTA::WeaponSlot Weapon::Slot::get()
		{
			if (pID <= GTA::Weapon::Unarmed)
				return GTA::WeaponSlot::Unarmed;

			int slot = 0;
			IVSDKDotNet::Native::Natives::GET_WEAPONTYPE_SLOT((int)pID, slot);
			return (GTA::WeaponSlot)slot;
		}
		bool Weapon::isPresent::get()
		{
			if (pID == GTA::Weapon::None)
				return false;
			if (pID == GTA::Weapon::Unarmed)
				return true;

			OBJECT_NON_EXISTING_CHECK(pOwner, false);
			return IVSDKDotNet::Native::Natives::HAS_CHAR_GOT_WEAPON(pOwner->Handle, (int)pID);
		}

		int Weapon::Ammo::get()
		{
			if (pID == GTA::Weapon::None)
				return 0;
			if (pID == GTA::Weapon::Unarmed)
				return 1;

			OBJECT_NON_EXISTING_CHECK(pOwner, 0);

			if (isPresent)
			{
				int ammo = 0;
				IVSDKDotNet::Native::Natives::GET_AMMO_IN_CHAR_WEAPON(pOwner->Handle, (int)pID, ammo);
				return ammo;
			}

			return 0;
		}
		void Weapon::Ammo::set(int value)
		{
			if (pID <= GTA::Weapon::Unarmed)
				return;
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(pOwner);

			if (isPresent)
				IVSDKDotNet::Native::Natives::SET_CHAR_AMMO(pOwner->Handle, (int)pID, value);
			else
				IVSDKDotNet::Native::Natives::GIVE_WEAPON_TO_CHAR(pOwner->Handle, (int)pID, value, 0);
		}
		int Weapon::AmmoInClip::get()
		{
			if (pID == GTA::Weapon::None)
				return 0;
			if (pID == GTA::Weapon::Unarmed)
				return 1;

			OBJECT_NON_EXISTING_CHECK(pOwner, 0);
			if (IVSDKDotNet::Native::Natives::HAS_CHAR_GOT_WEAPON(pOwner->Handle, (int)pID))
			{
				int ammo = 0;
				IVSDKDotNet::Native::Natives::GET_AMMO_IN_CLIP(pOwner->Handle, (int)pID, ammo);
				return ammo;
			}

			return 0;
		}
		void Weapon::AmmoInClip::set(int value)
		{
			if (pID <= GTA::Weapon::Unarmed)
				return;

			OBJECT_NON_EXISTING_CHECK_NO_RETURN(pOwner);
			if (!IVSDKDotNet::Native::Natives::HAS_CHAR_GOT_WEAPON(pOwner->Handle, (int)pID))
			{
				IVSDKDotNet::Native::Natives::GIVE_WEAPON_TO_CHAR(pOwner->Handle, (int)pID, 1, 0);
			}

			IVSDKDotNet::Native::Natives::SET_AMMO_IN_CLIP(pOwner->Handle, (int)pID, value);
		}
		int Weapon::MaxAmmo::get()
		{
			if (pID == GTA::Weapon::None)
				return 0;
			if (pID == GTA::Weapon::Unarmed)
				return 1;

			OBJECT_NON_EXISTING_CHECK(pOwner, 0);
			int ammo = 0;
			IVSDKDotNet::Native::Natives::GET_MAX_AMMO(pOwner->Handle, (int)pID, ammo);
			return ammo;
		}
		int Weapon::MaxAmmoInClip::get()
		{
			if (pID == GTA::Weapon::None)
				return 0;
			if (pID == GTA::Weapon::Unarmed)
				return 1;

			OBJECT_NON_EXISTING_CHECK(pOwner, 0);
			int ammo = 0;
			IVSDKDotNet::Native::Natives::GET_MAX_AMMO_IN_CLIP(pOwner->Handle, (int)pID, ammo);
			return ammo;
		}

		void Weapon::Select()
		{
			if (pID == GTA::Weapon::None)
				return;
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(pOwner);

			int w = (int)pID;

			if (!IVSDKDotNet::Native::Natives::HAS_CHAR_GOT_WEAPON(pOwner->Handle, w))
				IVSDKDotNet::Native::Natives::GIVE_WEAPON_TO_CHAR(pOwner->Handle, w, 1, 0);

			IVSDKDotNet::Native::Natives::SET_CURRENT_CHAR_WEAPON(pOwner->Handle, w, true);
		}
		void Weapon::Remove()
		{
			if (pID <= GTA::Weapon::Unarmed)
				return;

			OBJECT_NON_EXISTING_CHECK_NO_RETURN(pOwner);
			IVSDKDotNet::Native::Natives::REMOVE_WEAPON_FROM_CHAR(pOwner->Handle, (int)pID);
		}

		Weapon::operator GTA::Weapon(Weapon^ source)
		{
			return source->pID;
		}

		bool Weapon::operator == (Weapon^ left, Weapon^ right)
		{
			if isNULL(left) return isNULL(right);
			if isNULL(right) return false;
			return (left->pID == right->pID);
		}
		bool Weapon::operator != (Weapon^ left, Weapon^ right)
		{
			return !(left == right);
		}

		bool Weapon::operator == (GTA::Weapon left, Weapon^ right)
		{
			if isNULL(right)
				return (left == GTA::Weapon::Unarmed);

			return (left == right->pID);
		}
		bool Weapon::operator != (GTA::Weapon left, Weapon^ right)
		{
			return !(left == right);
		}

		bool Weapon::operator == (Weapon^ left, GTA::Weapon right)
		{
			if isNULL(left)
				return (right == GTA::Weapon::Unarmed);

			return (right == left->pID);
		}
		bool Weapon::operator != (Weapon^ left, GTA::Weapon right)
		{
			return !(left == right);
		}

	}
}