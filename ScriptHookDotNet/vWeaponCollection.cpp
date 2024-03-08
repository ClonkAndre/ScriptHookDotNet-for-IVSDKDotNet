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

#include "vWeaponCollection.h"

#include "Ped.h"
#include "vWeapon.h"

#pragma managed

namespace GTA
{
	namespace value
	{

		// - - - Constructor - - -
		WeaponCollection::WeaponCollection(Ped^ ped)
		{
			this->ped = ped;
		}

		// - - - Properties, Methods and Functions - - -
		value::Weapon^ WeaponCollection::default::get(GTA::Weapon weapon)
		{
			return FromType(weapon);
		}

		array<int>^ WeaponCollection::GetAmmoArray()
		{
			OBJECT_NON_EXISTING_CHECK(ped, gcnew array<int>(0));
			array<int>^ ammo = gcnew array<int>(19);
			u32 amount;
			ammo[0] = 0;
			for (int i = 1; i < 19; i++)
			{
				if (IVSDKDotNet::Native::Natives::HAS_CHAR_GOT_WEAPON(ped->Handle, i))
				{
					amount = 0;

					if (i > 3)
						IVSDKDotNet::Native::Natives::GET_AMMO_IN_CHAR_WEAPON(ped->Handle, i, amount);

					ammo[i] = (int)amount;
				}
				else
				{
					ammo[i] = -1;
				}
			}
			return ammo;
		}
		void WeaponCollection::SetAmmoArray(array<int>^ ammo)
		{
			if (isNULL(ammo) || (ammo->Length < 19))
				return;

			OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
			for (int i = 1; i < 19; i++)
			{
				if (ammo[i] >= 0)
					IVSDKDotNet::Native::Natives::GIVE_WEAPON_TO_CHAR(ped->Handle, i, ammo[i], 0);
			}
		}

		value::Weapon^ WeaponCollection::Current::get()
		{
			return FromType(CurrentType);
		}
		GTA::Weapon WeaponCollection::CurrentType::get()
		{
			OBJECT_NON_EXISTING_CHECK(ped, GTA::Weapon::None);
			u32 w;
			IVSDKDotNet::Native::Natives::GET_CURRENT_CHAR_WEAPON(ped->Handle, w);
			return (GTA::Weapon)w;
		}

		value::Weapon^ WeaponCollection::FromType(GTA::Weapon weapon)
		{
			GTA::value::Weapon^ w;
			if isNULL(pWeaponCache)
			{
				pWeaponCache = gcnew Dictionary<GTA::Weapon, GTA::value::Weapon^>();
			}
			else
			{
				if (pWeaponCache->TryGetValue(weapon, w))
					return w;
			}
			w = gcnew GTA::value::Weapon(ped, weapon);
			pWeaponCache->Add(weapon, w);
			return w;
		}
		value::Weapon^ WeaponCollection::inSlot(GTA::WeaponSlot WeaponSlot)
		{
			if (WeaponSlot == GTA::WeaponSlot::Unarmed)
				return Unarmed;

			OBJECT_NON_EXISTING_CHECK(ped, Unarmed);
			u32 w;
			u32 p4, p5;
			IVSDKDotNet::Native::Natives::GET_CHAR_WEAPON_IN_SLOT(ped->Handle, (u32)WeaponSlot, w, p4, p5);

			if (int(w) <= 0)
				return FromType(GTA::Weapon::None);

			return FromType((GTA::Weapon)w);
		}

		void WeaponCollection::Select(GTA::Weapon weapon)
		{
			FromType(weapon)->Select();
		}
		void WeaponCollection::RemoveAll()
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::REMOVE_ALL_CHAR_WEAPONS(ped->Handle);
		}

		// CONVERSION
		WeaponCollection::operator GTA::Weapon(WeaponCollection^ source)
		{
			OBJECT_NON_EXISTING_CHECK(source->ped, GTA::Weapon::None);
			u32 w;
			IVSDKDotNet::Native::Natives::GET_CURRENT_CHAR_WEAPON(source->ped->Handle, w);
			return (GTA::Weapon)w;
		}
		WeaponCollection::operator GTA::value::Weapon ^ (WeaponCollection^ source)
		{
			return source->Current;
		}

	}
}