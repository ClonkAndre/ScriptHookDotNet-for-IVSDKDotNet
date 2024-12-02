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

#include "stdafx.h"

#include "ContentCache.h"

#include "Blip.h"
#include "Camera.h"
#include "Group.h"
#include "Object.h"
#include "Ped.h"
#include "Pickup.h"
#include "Player.h"
#include "ScriptedFire.h"
#include "SettingsFile.h"
#include "Vehicle.h"

#pragma managed

namespace GTA
{

	void ContentCache::RemoveAll(bool deletestuff)
	{
		PedCache->Clear();
		VehicleCache->Clear();
		ObjectCache->Clear();
		PickupCache->Clear();
		GroupCache->Clear();
		BlipCache->Clear();
		CameraCache->Clear();
		FireCache->Clear();

		PlayerCache->Clear();
		DeleteCache->Clear();
		metadata->Clear();
	}
	void ContentCache::RemoveNonExisting()
	{
		RemoveNonExisting(PedCache);
		RemoveNonExisting(VehicleCache);
		RemoveNonExisting(ObjectCache);
		RemoveNonExisting(PickupCache);
		RemoveNonExisting(GroupCache); 
		RemoveNonExisting(BlipCache);
		RemoveNonExisting(CameraCache);
		RemoveNonExisting(FireCache);
	}

	generic <class T> where T: base::Object
	void ContentCache::RemoveNonExisting(List<T>^ list)
	{
		for (int i = list->Count-1; i >= 0; i--)
		{
			if (!list[i]->Exists())
			{
				list->RemoveAt(i);
				WRITE_TO_DEBUG_OUTPUT( "Non-existing " + list[i]->GetType()->Name + " " + list[i]->UID.ToString() + " removed!" );
			}
		}
	}
	generic <class T> where T: base::Object
	void ContentCache::RemoveNonExisting(Dictionary<int,T>^ list)
	{
		for each (KeyValuePair<int,T> kvp in list)
		{
			if (!kvp.Value->Exists())
			{
				DeleteQueue->Enqueue(kvp.Key);
				WRITE_TO_DEBUG_OUTPUT( "Non-existing " + kvp.Value->GetType()->Name + " " + kvp.Value->UID.ToString() + " removed!" );
			}
		}

		while (DeleteQueue->Count != 0)
			list->Remove(DeleteQueue->Dequeue());
	}

	// DELETABLES
	void ContentCache::DeleteStuff()
	{
#ifndef DEBUG
		try
		{
#endif

			while (DeleteCache->Count != 0)
				DeleteCache->Dequeue()->Delete();

#ifndef DEBUG
		}
		catch (...)
		{
		}
#endif
	}

	// PLAYER
	void ContentCache::AddPlayer(GTA::Player^ x)
	{
		if (PlayerCache->ContainsKey(x->ID))
			return;
		PlayerCache->Add(x->ID, x);
		LogCount(PlayerCache,"PlayerCache",100);
	}
	GTA::Player^ ContentCache::GetPlayer(int ID)
	{
		GTA::Player^ x;
		if (PlayerCache->TryGetValue(ID, x))
			return x;
		x = gcnew GTA::Player(ID);
		PlayerCache->Add(x->ID, x);
		LogCount(PlayerCache,"PlayerCache",100);
		return x;
	}
	void ContentCache::RemovePlayer(int ID)
	{
		PlayerCache->Remove(ID);
	}
	void ContentCache::RemovePlayer(GTA::Player^ x)
	{
		RemovePlayer(x->ID);
	}

	// PED
	void ContentCache::AddPed(GTA::Ped^ x)
	{
		if (PedCache->ContainsKey(x->Handle))
			return;
		PedCache->Add(x->Handle, x);
		LogCount(PedCache,"PedCache",1000);
	}
	GTA::Ped^ ContentCache::GetPed(int Handle)
	{
		if (Handle == 0)
			return nullptr;

		GTA::Ped^ x;
		if (PedCache->TryGetValue(Handle, x))
			return x;
		x = gcnew GTA::Ped(Handle);
		PedCache->Add(x->Handle, x);

		WRITE_TO_DEBUG_OUTPUT("New Ped added to PedCache! Handle: " + Handle.ToString());

		LogCount(PedCache,"PedCache",1000);
		return x;
	}
	void ContentCache::RemovePed(int Handle)
	{
		PedCache->Remove(Handle);
	}
	void ContentCache::RemovePed(GTA::Ped^ x)
	{
		RemovePed(x->Handle);
	}

	// VEHICLE
	void ContentCache::AddVehicle(GTA::Vehicle^ x)
	{
		if (VehicleCache->ContainsKey(x->Handle))
			return;
		VehicleCache->Add(x->Handle, x);
		LogCount(VehicleCache,"VehicleCache",1000);
	}
	GTA::Vehicle^ ContentCache::GetVehicle(int Handle)
	{
		if (Handle == 0)
			return nullptr;

		//IVSDKDotNet::IVPool^ pool = IVSDKDotNet::IVPools::GetVehiclePool();

		//for (int i = 0; i < pool->Count; i++)
		//{
		//	UIntPtr ptr = pool->Get(i);

		//	// Check if ptr is valid
		//	if (ptr == UIntPtr::Zero)
		//		continue;

		//	// Get the handle
		//	int handle = (int)pool->GetIndex(ptr);

		//	if (Handle != handle)
		//		continue;

		//	// Check if entity exists
		//	if (!IVSDKDotNet::Native::Natives::DOES_VEHICLE_EXIST(handle))
		//		continue;

		//	return gcnew GTA::Vehicle(handle);
		//}

		//return nullptr;

		GTA::Vehicle^ x;
		if (VehicleCache->TryGetValue(Handle, x))
			return x;
		x = gcnew GTA::Vehicle(Handle);
		VehicleCache->Add(x->Handle, x);
		LogCount(VehicleCache,"VehicleCache",1000);
		return x;
	}
	void ContentCache::RemoveVehicle(int Handle)
	{
		VehicleCache->Remove(Handle);
	}
	void ContentCache::RemoveVehicle(GTA::Vehicle^ x)
	{
		RemoveVehicle(x->Handle);
	}

	// OBJECT
	void ContentCache::AddObject(GTA::Object^ x)
	{
		if (ObjectCache->ContainsKey(x->Handle))
			return;
		ObjectCache->Add(x->Handle, x);
		LogCount(ObjectCache,"ObjectCache",1000);
	}
	GTA::Object^ ContentCache::GetObject(int Handle)
	{
		if (Handle == 0)
			return nullptr;

		//IVSDKDotNet::IVPool^ pool = IVSDKDotNet::IVPools::GetObjectPool();

		//for (int i = 0; i < pool->Count; i++)
		//{
		//	UIntPtr ptr = pool->Get(i);

		//	// Check if ptr is valid
		//	if (ptr == UIntPtr::Zero)
		//		continue;

		//	// Get the handle
		//	int handle = (int)pool->GetIndex(ptr);

		//	if (handle != Handle)
		//		continue;

		//	// Check if entity exists
		//	if (!IVSDKDotNet::Native::Natives::DOES_OBJECT_EXIST(handle))
		//		continue;

		//	return gcnew GTA::Object(handle);
		//}

		GTA::Object^ x;
		if (ObjectCache->TryGetValue(Handle, x))
			return x;
		x = gcnew GTA::Object(Handle);
		ObjectCache->Add(x->Handle, x);
		LogCount(ObjectCache,"ObjectCache",1000);
		return x;
	}
	void ContentCache::RemoveObject(int Handle)
	{
		ObjectCache->Remove(Handle);
	}
	void ContentCache::RemoveObject(GTA::Object^ x)
	{
		RemoveObject(x->Handle);
	}

	// PICKUP
	void ContentCache::AddPickup(GTA::Pickup^ x)
	{
		if (PickupCache->ContainsKey(x->Handle))
			return;
		PickupCache->Add(x->Handle, x);
		LogCount(PickupCache,"PickupCache",500);
	}
	GTA::Pickup^ ContentCache::GetPickup(int Handle)
	{
		if (Handle == 0)
			return nullptr;
		GTA::Pickup^ x;
		if (PickupCache->TryGetValue(Handle, x))
			return x;
		x = gcnew GTA::Pickup(Handle);
		PickupCache->Add(x->Handle, x);
		LogCount(PickupCache,"PickupCache",500);
		return x;
	}
	void ContentCache::RemovePickup(int Handle)
	{
		PickupCache->Remove(Handle);
	}
	void ContentCache::RemovePickup(GTA::Pickup^ x)
	{
		RemovePickup(x->Handle);
	}

	// GROUP
	void ContentCache::AddGroup(GTA::Group^ x, bool CreatedByMe)
	{
		if (GroupCache->ContainsKey(x->Handle))
			return;
		GroupCache->Add(x->Handle, x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		LogCount(GroupCache,"GroupCache",100);
	}
	GTA::Group^ ContentCache::GetGroup(int Handle, bool CreatedByMe)
	{
		if (Handle == 0)
			return nullptr;
		GTA::Group^ x;
		if (GroupCache->TryGetValue(Handle, x))
			return x;
		x = gcnew GTA::Group(Handle);
		GroupCache->Add(x->Handle, x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		LogCount(GroupCache,"GroupCache",100);
		return x;
	}
	void ContentCache::RemoveGroup(int Handle)
	{
		GroupCache->Remove(Handle);
	}
	void ContentCache::RemoveGroup(GTA::Group^ x)
	{
		RemoveGroup(x->Handle);
	}

	// BLIP
	void ContentCache::AddBlip(GTA::Blip^ x, bool CreatedByMe)
	{
		if (BlipCache->ContainsKey(x->Handle))
			return;
		BlipCache->Add(x->Handle, x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		LogCount(BlipCache,"BlipCache",200);
	}
	GTA::Blip^ ContentCache::GetBlip(int Handle, bool CreatedByMe)
	{
		if (Handle == 0)
			return nullptr;
		GTA::Blip^ x;
		if (BlipCache->TryGetValue(Handle, x))
			return x;
		x = gcnew GTA::Blip(Handle);
		BlipCache->Add(x->Handle, x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		LogCount(BlipCache,"BlipCache",200);
		return x;
	}
	void ContentCache::RemoveBlip(int Handle)
	{
		BlipCache->Remove(Handle);
	}
	void ContentCache::RemoveBlip(GTA::Blip^ x)
	{
		RemoveBlip(x->Handle);
	}

	// CAMERA
	void ContentCache::AddCamera(GTA::Camera^ x, bool CreatedByMe)
	{
		if (CameraCache->ContainsKey(x->Handle))
			return;
		CameraCache->Add(x->Handle, x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		LogCount(CameraCache,"CameraCache",50);
	}
	GTA::Camera^ ContentCache::GetCamera(int Handle, bool CreatedByMe)
	{
		if (Handle == 0)
			return nullptr;

		GTA::Camera^ x;
		if (CameraCache->TryGetValue(Handle, x))
			return x;
		x = gcnew GTA::Camera(Handle);
		CameraCache->Add(x->Handle, x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		LogCount(CameraCache,"CameraCache",50);
		return x;
	}
	void ContentCache::RemoveCamera(int Handle)
	{
		CameraCache->Remove(Handle);
	}
	void ContentCache::RemoveCamera(GTA::Camera^ x)
	{
		RemoveCamera(x->Handle);
	}

	// FIRE
	void ContentCache::AddFire(GTA::ScriptedFire^ x, bool CreatedByMe)
	{
		if (FireCache->Contains(x))
			return;
		FireAmountCheck();
		FireCache->Add(x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		LogCount(FireCache,"FireCache",1000);
		//NetHook::DisplayText("Fire " + x->Handle + " num " + FireCache->Count,4000);
	}
	GTA::ScriptedFire^ ContentCache::GetFire(int Handle, bool CreatedByMe)
	{
		if (Handle == 0)
			return nullptr;

		for (int i = 0; i < FireCache->Count; i++)
		{
			if (FireCache[i]->Handle == Handle)
				return FireCache[i];
		}
		FireAmountCheck();
		GTA::ScriptedFire^ x = gcnew GTA::ScriptedFire(Handle);
		FireCache->Add(x);
		if (CreatedByMe)
			DeleteCache->Enqueue(x);
		//NetHook::DisplayText("Fire " + x->Handle + " num " + FireCache->Count,4000);
		LogCount(FireCache,"FireCache",1000);
		return x;
	}
	void ContentCache::RemoveFire(int Handle)
	{
		//FireCache->Remove(Handle);
		for (int i = 0; i < FireCache->Count; i++)
		{
			if (FireCache[i]->Handle == Handle)
			{
				FireCache->RemoveAt(i);
				return;
			}
		}
	}
	void ContentCache::RemoveFire(GTA::ScriptedFire^ x)
	{
		//RemoveFire(x->Handle);
		FireCache->Remove(x);
	}
	void ContentCache::FireAmountCheck()
	{
		while (FireCache->Count >= MAX_FIRES)
		{
			FireCache[0]->Delete();
			FireCache->RemoveAt(0);
		}
	}

}