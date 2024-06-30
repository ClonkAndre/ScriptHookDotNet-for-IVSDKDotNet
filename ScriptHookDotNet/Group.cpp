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

#include "Group.h"

#include "ContentCache.h"
#include "PedCollection.h"
#include "Ped.h"
#include "Vehicle.h"
#include "vTasks.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Group::Group(int Handle)
		: HandleObject(Handle)
	{
	}
	Group::Group(Ped^ Leader) : HandleObject(0)
	{
		int g;
		IVSDKDotNet::Native::Natives::CREATE_GROUP(false, g, true);
		pHandle = g;
		this->Leader = Leader;
		ContentCache::AddGroup(this, true);
	}

	// - - - Properties, Methods and Functions - - -
	void Group::SetHandle(int Handle, bool CreatedByMe)
	{
		ContentCache::RemoveGroup(this);
		pHandle = Handle;
		// ResetExists(); // TODO: Remove completely probably
		ContentCache::AddGroup(this, CreatedByMe);
	}

	Ped^ Group::Leader::get()
	{
		NON_EXISTING_CHECK(nullptr);

		int p;
		IVSDKDotNet::Native::Natives::GET_GROUP_LEADER(pHandle, p);

		if (p == 0)
			return nullptr;

		return ContentCache::GetPed(p);
	}
	void Group::Leader::set(Ped^ value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(value);
		IVSDKDotNet::Native::Natives::SET_GROUP_LEADER(pHandle, value->Handle);
	}

	int Group::MemberCount::get()
	{
		NON_EXISTING_CHECK(0);
		int s, c;
		IVSDKDotNet::Native::Natives::GET_GROUP_SIZE(pHandle, s, c);
		return c;
	}
	int Group::MaxMemberCount::get()
	{
		return MAX_GROUP_SIZE;
	}

	bool Group::isLeader(Ped^ ped)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(ped, false);
		return IVSDKDotNet::Native::Natives::IS_GROUP_LEADER(ped->Handle, pHandle);
	}
	bool Group::isMember(Ped^ ped)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(ped, false);
		return IVSDKDotNet::Native::Natives::IS_GROUP_MEMBER(ped->Handle, pHandle);
	}
	bool Group::AddMember(Ped^ ped, bool NeverLeave)
	{
		NON_EXISTING_CHECK(false);
		OBJECT_NON_EXISTING_CHECK(ped, false);

		if (MemberCount >= MaxMemberCount)
			return false;

		IVSDKDotNet::Native::Natives::SET_GROUP_MEMBER(pHandle, ped->Handle);

		if (NeverLeave)
			IVSDKDotNet::Native::Natives::SET_CHAR_NEVER_LEAVES_GROUP(ped->Handle, true);

		return true;
	}
	bool Group::AddMember(Ped^ ped)
	{
		return AddMember(ped, false);
	}
	Ped^ Group::GetMember(int Index)
	{
		NON_EXISTING_CHECK(nullptr);

		int p;
		IVSDKDotNet::Native::Natives::GET_GROUP_MEMBER(pHandle, Index, p);

		if (p == 0)
			return nullptr;

		return ContentCache::GetPed(p);
	}
	void Group::RemoveAllMembers()
	{
		NON_EXISTING_CHECK_NO_RETURN();

		for (int i = MemberCount - 1; i >= 0; i--)
		{
			RemoveMember(i);
		}

		//ForceNextExistsCheck(); // TODO: Remove completely probably
	}
	void Group::RemoveMember(Ped^ ped)
	{
		if (!isMember(ped))
			return;

		ped->LeaveGroup();
		//ForceNextExistsCheck(); // TODO: Remove completely probably
	}
	void Group::RemoveMember(int Index)
	{
		NON_EXISTING_CHECK_NO_RETURN();

		int p;
		IVSDKDotNet::Native::Natives::GET_GROUP_MEMBER(pHandle, Index, p);

		if (p != 0)
			IVSDKDotNet::Native::Natives::REMOVE_CHAR_FROM_GROUP(p);

		//ForceNextExistsCheck(); // TODO: Remove completely probably
	}

	array<Ped^>^ Group::ToArray(bool IncludingLeader)
	{
		return ToList(IncludingLeader)->ToArray();
	}
	PedCollection^ Group::ToList(bool IncludingLeader)
	{
		Ped^ p;
		PedCollection^ list = gcnew PedCollection();
		NON_EXISTING_CHECK(list);
		if (IncludingLeader)
		{
			p = Leader;
			if (!Object::ReferenceEquals(p, nullptr))
				list->Add(p);
		}
		for (int i = 0; i < MemberCount; i++)
		{
			p = GetMember(i);
			if (!Object::ReferenceEquals(p, nullptr))
				list->Add(p);
		}
		return list;
	}

	void Group::SeparationRange::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_GROUP_SEPARATION_RANGE(pHandle, value);
	}
	void Group::FollowStatus::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_GROUP_FOLLOW_STATUS(pHandle, value);
	}
	void Group::Formation::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_GROUP_FORMATION(pHandle, value);
	}
	void Group::FormationSpacing::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_GROUP_FORMATION_SPACING(pHandle, value);
	}

	void Group::EnterVehicle(Vehicle^ vehicle, bool WithLeader, bool KeepCurrentDriver)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);
		PedCollection^ m = ToList(false);
		m->OrderByDistanceTo(vehicle->Position);

		if (WithLeader)
		{
			Ped^ l = Leader;
			if (!Object::ReferenceEquals(l, nullptr))
				m->Insert(0, l);
		}

		if (m->Count == 0)
			return;

		if ((KeepCurrentDriver) && (vehicle->isSeatFree(VehicleSeat::Driver)))
			KeepCurrentDriver = false;

		int mid = 0;
		if (!KeepCurrentDriver)
		{
			m->default[mid]->Task->EnterVehicle(vehicle, VehicleSeat::Driver);
			mid++;
		}
		int seats = vehicle->PassengerSeats;
		for (int seat = 0; seat < seats; seat++)
		{
			if (mid >= m->Count)
				return;

			m->default[mid]->Task->EnterVehicle(vehicle, (VehicleSeat)seat);
			mid++;
		}
	}

	bool Group::InternalCheckExists()
	{
		return IVSDKDotNet::Native::Natives::DOES_GROUP_EXIST(pHandle);
	}
	void Group::Delete()
	{
		if (!Exists())
			return;

		SetExistsFalse();
		if (pHandle == 0)
			return;

		IVSDKDotNet::Native::Natives::REMOVE_GROUP(pHandle);
	}

	bool Group::operator == (Group^ left, Group^ right)
	{
		return (left->Handle == right->Handle);
	}
	bool Group::operator != (Group^ left, Group^ right)
	{
		return !(left == right);
	}

}