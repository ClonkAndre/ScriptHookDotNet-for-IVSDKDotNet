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

#include "World.h"

#include "ContentCache.h"
#include "Ped.h"
#include "Vehicle.h"

#pragma managed

namespace GTA
{

	GTA::Weather World::Weather::get()
	{
		int w;
		IVSDKDotNet::Native::Natives::GET_CURRENT_WEATHER(w);
		return (GTA::Weather)w;
	}
	void World::Weather::set(GTA::Weather value)
	{
		IVSDKDotNet::Native::Natives::FORCE_WEATHER((u32)value);
	}

	int World::GetDayDiff(TimeSpan time)
	{
		if (time.Ticks >= 0)
			return time.Days;

		int d = time.Days;
		time += TimeSpan(-d, 0, 0, 0);

		if (time.Ticks < 0)
			return (d - 1);

		return d;
	}
	TimeSpan World::GetTimeOfDay(TimeSpan time)
	{
		if (time.Ticks >= 0)
			return TimeSpan(time.Hours, time.Minutes, time.Seconds);

		TimeSpan tod = TimeSpan(-time.Days + 1, 0, 0, 0);
		tod += time;
		return tod;
	}

	TimeSpan World::CurrentDayTime::get()
	{
		int h, m;
		IVSDKDotNet::Native::Natives::GET_TIME_OF_DAY(h, m);
		return TimeSpan(h, m, 0);
	}
	void World::CurrentDayTime::set(TimeSpan value)
	{
		int d = GetDayDiff(value);
		if (d > 0)
		{
			for (int i = 0; i < d; i++)
			{
				IVSDKDotNet::Native::Natives::SET_TIME_ONE_DAY_FORWARD();
			}
		}
		else if (d < 0)
		{
			for (int i = 0; i > d; i--)
			{
				IVSDKDotNet::Native::Natives::SET_TIME_ONE_DAY_BACK();
			}
		}

		value = GetTimeOfDay(value);
		IVSDKDotNet::Native::Natives::SET_TIME_OF_DAY(value.Hours, value.Minutes);
	}

	DateTime World::CurrentDate::get()
	{
		u32 month, day;
		int hour, minute;
		IVSDKDotNet::Native::Natives::GET_TIME_OF_DAY(hour, minute);
		IVSDKDotNet::Native::Natives::GET_CURRENT_DATE(day, month);
		return DateTime(pBaseYear, month, day, hour, minute, 0);
	}

	void World::CarDensity::set(float value)
	{
		IVSDKDotNet::Native::Natives::SET_CAR_DENSITY_MULTIPLIER(value);
	}
	void World::PedDensity::set(float value)
	{
		IVSDKDotNet::Native::Natives::SET_PED_DENSITY_MULTIPLIER(value);
	}

	void World::GravityEnabled::set(bool value)
	{
		IVSDKDotNet::Native::Natives::SET_GRAVITY_OFF(!value);
	}

	void World::OneDayForward()
	{
		IVSDKDotNet::Native::Natives::SET_TIME_ONE_DAY_FORWARD();
	}
	void World::LockDayTime(TimeSpan LockedTime)
	{
		if (LockedTime.Ticks < 0)
			return;

		IVSDKDotNet::Native::Natives::FORCE_TIME_OF_DAY(LockedTime.Hours, LockedTime.Minutes);
	}
	void World::LockDayTime(int Hour, int Minute)
	{
		if ((Hour < 0) || (Hour > 23))
			return;
		if ((Minute < 0) || (Minute > 59))
			return;

		IVSDKDotNet::Native::Natives::FORCE_TIME_OF_DAY(Hour, Minute);
	}
	void World::LockDayTime()
	{
		int w;
		IVSDKDotNet::Native::Natives::GET_CURRENT_WEATHER(w);

		LockDayTime(CurrentDayTime);

		IVSDKDotNet::Native::Natives::FORCE_WEATHER_NOW((u32)w);
	}
	void World::UnlockDayTime()
	{
		IVSDKDotNet::Native::Natives::RELEASE_TIME_OF_DAY();
	}

	void World::LoadEnvironmentNow(GTA::Vector3 Position)
	{
		IVSDKDotNet::Native::Natives::REQUEST_COLLISION_AT_POSN(Position.X, Position.Y, Position.Z);
		IVSDKDotNet::Native::Natives::LOAD_ALL_OBJECTS_NOW();
		IVSDKDotNet::Native::Natives::LOAD_SCENE(Position.X, Position.Y, Position.Z); // WARNING: causes a call to OnRender and thus a Deadlock! // Fine now due to deadlock protection
		IVSDKDotNet::Native::Natives::POPULATE_NOW();
	}

	void World::AddExplosion(Vector3 Position, ExplosionType Type, float Power, bool PlaySound, bool NoVisuals, float CameraShake)
	{
		IVSDKDotNet::Native::Natives::ADD_EXPLOSION(Position.X, Position.Y, Position.Z, (u32)Type, Power, PlaySound, NoVisuals, CameraShake);
	}
	void World::AddExplosion(Vector3 Position, ExplosionType Type, float Power)
	{
		AddExplosion(Position, Type, Power, true, false, 1.0f);
	}
	void World::AddExplosion(Vector3 Position)
	{
		AddExplosion(Position, ExplosionType::Default, 1.0f, true, false, 1.0f);
	}

	void World::DrawCheckpoint(Vector3 Position, float Diameter, Drawing::Color Color)
	{
		IVSDKDotNet::Native::Natives::DRAW_CHECKPOINT_WITH_ALPHA(Position.X, Position.Y, Position.Z, Diameter, Color.R, Color.G, Color.B, Color.A);
	}
	void World::DrawLight(Vector3 Position, Drawing::Color Color, float Range, float Intensity)
	{
		IVSDKDotNet::Native::Natives::DRAW_LIGHT_WITH_RANGE(Position.X, Position.Y, Position.Z, Color.R, Color.G, Color.B, Range, Intensity);
	}

	array<int>^ World::GetValidPedHandles(GTA::Model Model)
	{
		List<int>^ list = gcnew List<int>();

		u32 model = 0;
		int findmodel = Model.Hash;

		IVSDKDotNet::IVPool^ pool = IVSDKDotNet::IVPools::GetPedPool();
		for (int i = 0; i < pool->Count; i++)
		{
			UIntPtr ptr = pool->Get(i);

			// Check if ptr is valid
			if (ptr == UIntPtr::Zero)
				continue;

			// Get the handle
			int handle = (int)pool->GetIndex(ptr);

			// Check if entity exists
			if (!IVSDKDotNet::Native::Natives::DOES_CHAR_EXIST(handle))
				continue;

			// Get the entity model
			IVSDKDotNet::Native::Natives::GET_CHAR_MODEL(handle, model);

			// Compare and add
			if ((model != 0) && ((findmodel == 0) || (findmodel == model)))
				list->Add(handle);
		}

		return list->ToArray();
	}
	array<int>^ World::GetValidVehicleHandles(GTA::Model Model)
	{
		List<int>^ list = gcnew List<int>();

		u32 model = 0;
		int findmodel = Model.Hash;

		IVSDKDotNet::IVPool^ pool = IVSDKDotNet::IVPools::GetVehiclePool();
		for (int i = 0; i < pool->Count; i++)
		{
			UIntPtr ptr = pool->Get(i);

			// Check if ptr is valid
			if (ptr == UIntPtr::Zero)
				continue;

			// Get the handle
			int handle = (int)pool->GetIndex(ptr);

			// Check if entity exists
			if (!IVSDKDotNet::Native::Natives::DOES_VEHICLE_EXIST(handle))
				continue;

			// Get the entity model
			IVSDKDotNet::Native::Natives::GET_CAR_MODEL(handle, model);

			// Compare and add
			if ((model != 0) && ((findmodel == 0) || (findmodel == model)))
				list->Add(handle);
		}

		return list->ToArray();
	}
	array<int>^ World::GetValidObjectHandles(GTA::Model Model)
	{
		List<int>^ list = gcnew List<int>();

		u32 model = 0;
		int findmodel = Model.Hash;

		IVSDKDotNet::IVPool^ pool = IVSDKDotNet::IVPools::GetObjectPool();
		for (int i = 0; i < pool->Count; i++)
		{
			UIntPtr ptr = pool->Get(i);

			// Check if ptr is valid
			if (ptr == UIntPtr::Zero)
				continue;

			// Get the handle
			int handle = (int)pool->GetIndex(ptr);

			// Check if entity exists
			if (!IVSDKDotNet::Native::Natives::DOES_OBJECT_EXIST(handle))
				continue;

			// Get the entity model
			IVSDKDotNet::Native::Natives::GET_OBJECT_MODEL(handle, model);

			// Compare and add
			if ((model != 0) && ((findmodel == 0) || (findmodel == model)))
				list->Add(handle);
		}

		return list->ToArray();
	}

	Ped^ World::GetClosestPed(Vector3 Position, float Radius)
	{
		int ped;
		IVSDKDotNet::Native::Natives::BEGIN_CHAR_SEARCH_CRITERIA();
		IVSDKDotNet::Native::Natives::END_CHAR_SEARCH_CRITERIA();
		IVSDKDotNet::Native::Natives::GET_CLOSEST_CHAR(Position.X, Position.Y, Position.Z, Radius, true, true, ped);

		if (ped == 0)
			return nullptr;

		return ContentCache::GetPed(ped);
	}
	Ped^ World::GetRandomPed(Vector3 Position, float Radius)
	{
		int ped;
		IVSDKDotNet::Native::Natives::BEGIN_CHAR_SEARCH_CRITERIA();
		IVSDKDotNet::Native::Natives::END_CHAR_SEARCH_CRITERIA();

		IVSDKDotNet::Native::Natives::GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE(Position.X - Radius, Position.Y - Radius, Position.Z - Radius, Radius * 2.0f, Radius * 2.0f, Radius * 2.0f, ped);

		if (ped == 0)
			return nullptr;

		return ContentCache::GetPed(ped);
	}

	array<Ped^>^ World::GetPeds(Vector3 Position, float Radius, int MaxAmount)
	{
		List<Ped^>^ list = gcnew List<Ped^>();
		Ped^ p;
		array<int>^ handles = GetValidPedHandles(Model::Null);

		for (int i = 0; i < handles->Length; i++)
		{
			p = ContentCache::GetPed(handles[i]);
			if (p->Position.DistanceTo(Position) <= Radius)
			{
				list->Add(p);
				if (list->Count >= MaxAmount) return list->ToArray();
			}
		}
		return list->ToArray();
	}
	array<Ped^>^ World::GetPeds(Vector3 Position, float Radius)
	{
		return GetPeds(Position, Radius, int::MaxValue);
	}

	array<Ped^>^ World::GetAllPeds(GTA::Model Model)
	{
		array<int>^ handles = GetValidPedHandles(Model);
		array<Ped^>^ list = gcnew array<Ped^>(handles->Length);
		for (int i = 0; i < handles->Length; i++)
		{
			list[i] = ContentCache::GetPed(handles[i]);
			//if ( (!list[i]->Exists()) || (list[i]->MemoryAddress == 0) || (!list[i]->Exists()) ) list[i] = nullptr;
		}
		return list;
	}
	array<Ped^>^ World::GetAllPeds()
	{
		return GetAllPeds(Model::Null);
	}

	array<Vehicle^>^ World::GetVehicles(Vector3 Position, float Radius, GTA::Model Model)
	{
		List<Vehicle^>^ list = gcnew List<Vehicle^>();
		Vehicle^ v;
		array<int>^ handles = GetValidVehicleHandles(Model);
		for (int i = 0; i < handles->Length; i++)
		{
			v = ContentCache::GetVehicle(handles[i]);
			if (v->Position.DistanceTo(Position) <= Radius)
				list->Add(v);
		}
		return list->ToArray();
	}
	array<Vehicle^>^ World::GetVehicles(Vector3 Position, float Radius)
	{
		return GetVehicles(Position, Radius, Model::Null);
	}

	array<Vehicle^>^ World::GetAllVehicles(GTA::Model Model)
	{
		array<int>^ handles = GetValidVehicleHandles(Model);
		array<Vehicle^>^ list = gcnew array<Vehicle^>(handles->Length);
		for (int i = 0; i < handles->Length; i++)
		{
			list[i] = ContentCache::GetVehicle(handles[i]);
		}
		return list;
	}
	array<Vehicle^>^ World::GetAllVehicles()
	{
		return GetAllVehicles(Model::Null);
	}

	Vehicle^ World::GetClosestVehicle(Vector3 Position, float Radius, GTA::Model Model)
	{
		Vehicle^ cv = nullptr;
		Vehicle^ v;
		float cd = float::MaxValue;
		float dist;

		array<int>^ handles = GetValidVehicleHandles(Model);

		for (int i = 0; i < handles->Length; i++)
		{
			v = ContentCache::GetVehicle(handles[i]);

			dist = v->Position.DistanceTo(Position);

			if ((dist <= Radius) && (dist < cd))
			{
				cv = v;
				cd = dist;
			}
		}

		return cv;
	}
	Vehicle^ World::GetClosestVehicle(Vector3 Position, float Radius)
	{
		return GetClosestVehicle(Position, Radius, Model::Null);
	}

	array<GTA::Object^>^ World::GetAllObjects(GTA::Model Model)
	{
		array<int>^ handles = GetValidObjectHandles(Model);
		array<GTA::Object^>^ list = gcnew array<GTA::Object^>(handles->Length);
		for (int i = 0; i < handles->Length; i++)
		{
			list[i] = ContentCache::GetObject(handles[i]);
		}
		return list;
	}
	array<GTA::Object^>^ World::GetAllObjects()
	{
		return GetAllObjects(Model::Null);
	}

	float World::GetGroundZBelow(float x, float y, float z)
	{
		f32 resZ = z;
		IVSDKDotNet::Native::Natives::GET_GROUND_Z_FOR_3D_COORD(x, y, z, resZ);
		return resZ;
	}
	float World::GetGroundZAbove(float x, float y, float z)
	{
		if (z < 0.0f)
			z = 0.0f;

		float lastZ, resZ;
		for (int i = 0; i <= 10; i++)
		{
			lastZ = z + (float)System::Math::Pow(2.0, (double)i);
			resZ = GetGroundZBelow(x, y, lastZ);
			if ((resZ < lastZ) && (resZ > z))
				return resZ;
		}
		return z;
	}
	float World::GetGroundZNext(float x, float y, float z)
	{
		if (z < 0.0f)
			z = 0.0f;

		float lastZ, resZ;
		for (int i = 0; i <= 10; i++)
		{
			lastZ = z + (float)System::Math::Pow(2.0, (double)i);
			resZ = GetGroundZBelow(x, y, lastZ);
			if ((resZ < lastZ) && (resZ > 0.0f))
				return resZ;
		}
		return z;
	}
	float World::GetGroundZ(Vector3 Position, GroundType Type)
	{
		switch (Type)
		{
			case GroundType::Highest:
				return GetGroundZBelow(Position.X, Position.Y, 1024.0f);
			case GroundType::Lowest:
				return GetGroundZAbove(Position.X, Position.Y, 0.0f);
			case GroundType::NextBelowCurrent:
				return GetGroundZBelow(Position.X, Position.Y, Position.Z);
			case GroundType::NextAboveCurrent:
				return GetGroundZAbove(Position.X, Position.Y, Position.Z);
				//case GroundType::Closest:
			default:
				return GetGroundZNext(Position.X, Position.Y, Position.Z); //+5.0f
		}
	}
	float World::GetGroundZ(Vector3 Position)
	{
		return GetGroundZ(Position, GroundType::Closest);
	}
	Vector3 World::GetGroundPosition(Vector3 Position, GroundType Type)
	{
		float z = GetGroundZ(Position, Type);
		return GTA::Vector3(Position.X, Position.Y, z);
	}
	Vector3 World::GetGroundPosition(Vector3 Position)
	{
		return GetGroundPosition(Position, GroundType::Closest);
	}

	Vector3 World::GetNextPositionOnPavement(Vector3 Position)
	{
		f32 x, y, z;
		IVSDKDotNet::Native::Natives::GET_SAFE_POSITION_FOR_CHAR(Position.X, Position.Y, Position.Z, true, x, y, z);
		return Vector3(x, y, z);
	}
	Vector3 World::GetNextPositionOnStreet(Vector3 Position)
	{
		f32 x, y, z, h;
		u32 inarea, outarea;
		Vector3 p = Position;
		inarea = IVSDKDotNet::Native::Natives::GET_MAP_AREA_FROM_COORDS(p.X, p.Y, p.Z);

		IVSDKDotNet::Native::Natives::GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND(p.X, p.Y, p.Z, 1, inarea, x, y, z, h, outarea);

		return Vector3(x, y, z);
	}
	Vector3 World::GetPositionAround(Vector3 Position, float Distance)
	{
		return Position + Vector3::RandomXY() * Distance;
	}

	String^ World::GetStreetName(Vector3 Position)
	{
		u32 strHash0, strHash1;

		IVSDKDotNet::Native::Natives::FIND_STREET_NAME_AT_POSITION(Position.X, Position.Y, Position.Z, strHash0, strHash1);
		String^ str1 = IVSDKDotNet::Native::Natives::GET_STRING_FROM_HASH_KEY(strHash0)->Trim();
		String^ str2 = IVSDKDotNet::Native::Natives::GET_STRING_FROM_HASH_KEY(strHash1)->Trim();

		if (str1->Length == 0)
			return str2;
		if (str2->Length == 0)
			return str1;

		return String::Concat(str1, ", ", str2);
	}
	String^ World::GetZoneName(Vector3 Position)
	{
		return IVSDKDotNet::Native::Natives::GET_NAME_OF_INFO_ZONE(Position.X, Position.Y, Position.Z);
	}

	bool World::isPositionBlockedByMissionEntity(Vector3 Position, float Radius)
	{
		float diam = Radius * 2.0f;
		return IVSDKDotNet::Native::Natives::IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(Position.X, Position.Y, Position.Z, diam, diam, diam);
	}

	void World::SetGroupRelationship(GTA::RelationshipGroup group, Relationship level, GTA::RelationshipGroup targetgroup)
	{
		IVSDKDotNet::Native::Natives::ALLOW_GANG_RELATIONSHIPS_TO_BE_CHANGED_BY_NEXT_COMMAND(true);
		IVSDKDotNet::Native::Natives::SET_RELATIONSHIP((int)level, (int)group, (int)targetgroup);
	}

	ScriptedFire^ World::StartFire(Vector3 Position, int Unknown1, int Unknown2)
	{
		int fire = IVSDKDotNet::Native::Natives::START_SCRIPT_FIRE(GTAVector3ToVector3(Position), Unknown1, Unknown2);

		if (fire == 0)
			return nullptr;

		return ContentCache::GetFire(fire, true);
	}
	ScriptedFire^ World::StartFire(Vector3 Position)
	{
		return StartFire(Position, 1, 1);
	}
	void World::ExtinguishFire(Vector3 Position, float Radius)
	{
		IVSDKDotNet::Native::Natives::EXTINGUISH_FIRE_AT_POINT(Position.X, Position.Y, Position.Z, Radius);
	}
	void World::ExtinguishAllScriptFires()
	{
		NotImplementedYet("World::ExtinguishAllScriptFires");
		//IVSDKDotNet::Native::Natives::REMOVE_ALL_SCRIPT_FIRES();
	}

	void World::UnlockAllIslands()
	{
		IVSDKDotNet::Native::Natives::SET_INT_STAT(363, 3); //STAT_ISLANDS_UNLOCKED
	}

	void World::TriggerCollisionsAt(Vector3 Position)
	{
		IVSDKDotNet::Native::Natives::REQUEST_COLLISION_AT_POSN(Position.X, Position.Y, Position.Z);
	}

	void World::SetDoorState(Model model, Vector3 pos, bool locked, float angle)
	{
		IVSDKDotNet::Native::Natives::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(model.Hash, pos.X, pos.Y, pos.Z, locked, angle);
	}

	Ped^ World::CreatePed(Vector3 Position, GTA::Gender Gender)
	{
		int ped;

		if (Gender == GTA::Gender::Male)
			IVSDKDotNet::Native::Natives::CREATE_RANDOM_MALE_CHAR(Position.X, Position.Y, Position.Z, ped);
		else
			IVSDKDotNet::Native::Natives::CREATE_RANDOM_FEMALE_CHAR(Position.X, Position.Y, Position.Z, ped);

		if (ped == 0)
			return nullptr;

		Ped^ res = ContentCache::GetPed(ped);

		return res;
	}
	Ped^ World::CreatePed(Vector3 Position)
	{
		int ped;
		IVSDKDotNet::Native::Natives::CREATE_RANDOM_CHAR(Position.X, Position.Y, Position.Z, ped);

		if (ped == 0)
			return nullptr;

		Ped^ res = ContentCache::GetPed(ped);

		return res;
	}
	Ped^ World::CreatePed(GTA::Model Model, Vector3 Position, RelationshipGroup Type)
	{
		if (!Model.isPed)
			return nullptr;
		if (!Model.LoadToMemoryNow())
			return nullptr;

		int ped = 0;
		IVSDKDotNet::Native::Natives::CREATE_CHAR((int)Type, Model.Hash, Position.X, Position.Y, Position.Z, ped, true);
		Model.AllowDisposeFromMemory();

		if (ped == 0)
			return nullptr;

		Ped^ res = ContentCache::GetPed(ped);

		return res;
	}
	Ped^ World::CreatePed(GTA::Model Model, Vector3 Position)
	{
		Ped^ res = CreatePed(Model, Position, RelationshipGroup::Civillian_Male);

		if isNULL(res)
			return nullptr;

		if (res->Gender == Gender::Female)
			res->RelationshipGroup = RelationshipGroup::Civillian_Female;

		return res;
	}

	Vehicle^ World::CreateVehicle(Vector3 Position)
	{
		int car;
		u32 model;
		int unknown;

		IVSDKDotNet::Native::Natives::GET_RANDOM_CAR_MODEL_IN_MEMORY(true, model, unknown);
		IVSDKDotNet::Native::Natives::CREATE_CAR(model, Position.X, Position.Y, Position.Z, car, true);

		if (car == 0)
			return nullptr;

		return ContentCache::GetVehicle(car);
	}

	Vehicle^ World::CreateVehicle(GTA::Model Model, Vector3 Position)
	{
		if (!Model.isVehicle)
			return nullptr;
		if (!Model.LoadToMemoryNow())
			return nullptr;

		int car;
		IVSDKDotNet::Native::Natives::CREATE_CAR(Model.Handle, Position.X, Position.Y, Position.Z, car, true);
		Model.AllowDisposeFromMemory();

		if (car == 0)
			return nullptr;

		return ContentCache::GetVehicle(car);
	}
	Vehicle^ World::CreateMissionTrain(Vector3 Position)
	{
		GTA::Model Model = GTA::Model(0x2FBC4D30);

		if (!Model.LoadToMemoryNow())
			return nullptr;

		int car;
		IVSDKDotNet::Native::Natives::CREATE_MISSION_TRAIN(0, Position.X, Position.Y, Position.Z, true, car);
		Model.AllowDisposeFromMemory();

		if (car == 0)
			return nullptr;

		return ContentCache::GetVehicle(car);
	}

	GTA::Object^ World::CreateObject(GTA::Model Model, Vector3 Position)
	{
		if (!Model.LoadToMemoryNow())
			return nullptr;

		int obj;
		IVSDKDotNet::Native::Natives::CREATE_OBJECT(Model.Hash, Position.X, Position.Y, Position.Z, obj, true);
		Model.AllowDisposeFromMemory();

		if (obj == 0)
			return nullptr;

		return ContentCache::GetObject(obj);
	}

}