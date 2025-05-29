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

	// IV-SDK .NET ScriptHookDotNet Cache stuff
	void ContentCache::AddEntity(GTA::base::Object^ obj)
	{
		GetManagerScript()->SHDNCache_AddEntity(Guid::Empty, obj);
	}

	generic <class T>
	T ContentCache::GetEntity(int handle, HandleType type, bool wasCreatedByScript)
	{
		Guid ownerScriptID = Guid::Empty;

		if (wasCreatedByScript)
			ownerScriptID = GetManagerScript()->SHDN_GetIdOfCurrentExecutingScript();

		System::Object^ obj = GetManagerScript()->SHDNCache_GetEntity(handle, (int)type, ownerScriptID);

		if (!obj)
			return T();

		return safe_cast<T>(obj);
	}

	void ContentCache::RemoveEntity(GTA::base::Object^ obj)
	{
		GetManagerScript()->SHDNCache_RemoveEntity(obj);
	}
	void ContentCache::RemoveEntity(int handle)
	{
		GetManagerScript()->SHDNCache_RemoveEntity(handle);
	}

	// Player
	void ContentCache::AddPlayer(GTA::Player^ p)
	{
		GetManagerScript()->SHDNCache_AddPlayer(p);
	}
	GTA::Player^ ContentCache::GetPlayer(int id)
	{
		System::Object^ obj = GetManagerScript()->SHDNCache_GetPlayer(id);

		if (!obj)
			return nullptr;

		return safe_cast<GTA::Player^>(obj);
	}
	void ContentCache::RemovePlayer(GTA::Player^ p)
	{
		GetManagerScript()->SHDNCache_RemovePlayer(p);
	}

	// Ped
	void ContentCache::AddPed(GTA::Ped^ x)
	{
		AddEntity(x);
	}
	GTA::Ped^ ContentCache::GetPed(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::Ped^>(handle, HandleType::Ped, wasCreatedByScript);
	}
	void ContentCache::RemovePed(GTA::Ped^ x)
	{
		RemoveEntity(x->Handle);
	}

	// Vehicle
	void ContentCache::AddVehicle(GTA::Vehicle^ x)
	{
		AddEntity(x);
	}
	GTA::Vehicle^ ContentCache::GetVehicle(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::Vehicle^>(handle, HandleType::Vehicle, wasCreatedByScript);
	}

	// Object
	void ContentCache::AddObject(GTA::Object^ x)
	{
		AddEntity(x);
	}
	GTA::Object^ ContentCache::GetObject(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::Object^>(handle, HandleType::Object, wasCreatedByScript);
	}

	// Pickup
	void ContentCache::AddPickup(GTA::Pickup^ x)
	{
		AddEntity(x);
	}
	GTA::Pickup^ ContentCache::GetPickup(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::Pickup^>(handle, HandleType::Pickup, wasCreatedByScript);
	}

	// Group
	void ContentCache::AddGroup(GTA::Group^ x, bool wasCreatedByScript)
	{
		AddEntity(x);
	}
	GTA::Group^ ContentCache::GetGroup(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::Group^>(handle, HandleType::Group, wasCreatedByScript);
	}
	void ContentCache::RemoveGroup(GTA::Group^ x)
	{
		RemoveEntity(x->Handle);
	}

	// Blip
	void ContentCache::AddBlip(GTA::Blip^ x, bool wasCreatedByScript)
	{
		AddEntity(x);
	}
	GTA::Blip^ ContentCache::GetBlip(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::Blip^>(handle, HandleType::Blip, wasCreatedByScript);
	}

	// Camera
	void ContentCache::AddCamera(GTA::Camera^ x, bool wasCreatedByScript)
	{
		AddEntity(x);
	}
	GTA::Camera^ ContentCache::GetCamera(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::Camera^>(handle, HandleType::Camera, wasCreatedByScript);
	}

	// Fire
	void ContentCache::AddFire(GTA::ScriptedFire^ x, bool wasCreatedByScript)
	{
		AddEntity(x);
	}
	GTA::ScriptedFire^ ContentCache::GetFire(int handle, bool wasCreatedByScript)
	{
		return GetEntity<GTA::ScriptedFire^>(handle, HandleType::ScriptedFire, wasCreatedByScript);
	}

}