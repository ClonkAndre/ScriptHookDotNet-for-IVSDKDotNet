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

#include "sModel.h"

#include "Game.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Model::Model(int Hash)
	{
		pHash = Hash;
		pName = String::Empty;
	}
	Model::Model(u32 Hash)
	{
		pHash = force_cast<int>(Hash);
		pName = String::Empty;
	}
	Model::Model(String^ ModelName)
	{
		pName = ModelName;
		
		//pHash = IVSDKDotNet::Native::Natives::GET_HASH_KEY(ModelName);
		pHash = (int)IVSDKDotNet::RAGE::AtStringHash(ModelName);
	}

	// - - - Properties, Methods and Functions - - -
	u32 Model::Handle::get()
	{
		return force_cast<u32>(pHash);
	}
	int Model::Hash::get()
	{
		return pHash;
	}

	bool Model::isInMemory::get()
	{
		return IVSDKDotNet::Native::Natives::HAS_MODEL_LOADED(pHash);
	}
	bool Model::isCollisionDataInMemory::get()
	{
		return IVSDKDotNet::Native::Natives::HAS_COLLISION_FOR_MODEL_LOADED((u32)pHash);
	}

	bool Model::isValid::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::HAS_MODEL_LOADED((u32)pHash);
	}

	void Model::LoadToMemory()
	{
		if (pHash == 0)
			return;

		IVSDKDotNet::Native::Natives::REQUEST_MODEL(pHash);
	}
	bool Model::LoadToMemoryNow(int timeout)
	{
		if (pHash == 0)
			return false;

		IVSDKDotNet::IVStreaming::ScriptRequestModel(pHash);

		if (isInMemory)
			return true;

		DateTime maxtime;
		if (timeout >= 0)
			maxtime = DateTime::Now + TimeSpan::FromMilliseconds(timeout);
		else
			maxtime = DateTime::MaxValue;

		while (!isInMemory)
		{
			Game::WaitInCurrentScript(0);

			IVSDKDotNet::IVStreaming::ScriptRequestModel(pHash);

			// Timeout. Force model to load if current thread is the main thread
			if (DateTime::Now > maxtime)
			{
				if (GetManagerScript()->GetMainThreadID() == GetCurrentThreadID())
				{
					IVSDKDotNet::IVStreaming::LoadAllRequestedModels(false);
					return true;
				}

				return false;
			}
		}

		return true;
	}
	void Model::LoadCollisionDataToMemory()
	{
		if (pHash == 0)
			return;

		IVSDKDotNet::Native::Natives::REQUEST_COLLISION_FOR_MODEL((u32)pHash);
	}
	bool Model::LoadCollisionDataToMemoryNow(int timeout)
	{
		if (pHash == 0)
			return false;

		IVSDKDotNet::Native::Natives::REQUEST_COLLISION_FOR_MODEL((u32)pHash);

		if (isCollisionDataInMemory)
			return true;

		IVSDKDotNet::Native::Natives::REQUEST_COLLISION_FOR_MODEL((u32)pHash);
		return true;
	}

	void Model::AllowDisposeFromMemory()
	{
		if (pHash == 0)
			return;

		IVSDKDotNet::Native::Natives::MARK_MODEL_AS_NO_LONGER_NEEDED(pHash);
	}

	void Model::GetDimensions(GTA::Vector3% MinVector, GTA::Vector3% MaxVector)
	{
		System::Numerics::Vector3 vec1;
		System::Numerics::Vector3 vec2;

		IVSDKDotNet::Native::Natives::GET_MODEL_DIMENSIONS((u32)pHash, vec1, vec2);

		MinVector = Vector3ToGTAVector3(vec1);
		MaxVector = Vector3ToGTAVector3(vec2);
	}

	GTA::Vector3 Model::GetDimensions()
	{
		System::Numerics::Vector3 vec1;
		System::Numerics::Vector3 vec2;

		IVSDKDotNet::Native::Natives::GET_MODEL_DIMENSIONS((u32)pHash, vec1, vec2);

		return GTA::Vector3(vec2.X - vec1.X, vec2.Y - vec1.Y, vec2.Z - vec1.Z);
	}

	bool Model::isBike::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_BIKE((u32)pHash);
	}
	bool Model::isBoat::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_BOAT((u32)pHash);
	}
	bool Model::isCar::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_CAR((u32)pHash);
	}
	bool Model::isHelicopter::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_HELI((u32)pHash);
	}
	bool Model::isPed::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_PED((u32)pHash);
	}
	bool Model::isPlane::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_PLANE((u32)pHash);
	}
	bool Model::isTrain::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_TRAIN((u32)pHash);
	}
	bool Model::isVehicle::get()
	{
		if (pHash == 0)
			return false;

		return IVSDKDotNet::Native::Natives::IS_THIS_MODEL_A_VEHICLE((u32)pHash);
	}

	Model Model::BasicCopModel::get()
	{
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CURRENT_BASIC_COP_MODEL(val);
		return Model((int)val);
	}
	Model Model::CurrentCopModel::get()
	{
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CURRENT_COP_MODEL(val);
		return Model((int)val);
	}
	Model Model::BasicPoliceCarModel::get()
	{
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CURRENT_BASIC_POLICE_CAR_MODEL(val);
		return Model((int)val);
	}
	Model Model::CurrentPoliceCarModel::get()
	{
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CURRENT_POLICE_CAR_MODEL(val);
		return Model((int)val);
	}
	Model Model::TaxiCarModel::get()
	{
		u32 val;
		IVSDKDotNet::Native::Natives::GET_CURRENT_TAXI_CAR_MODEL(val);
		return Model((int)val);
	}

	Model Model::GetWeaponModel(GTA::Weapon weapon)
	{
		u32 val;
		IVSDKDotNet::Native::Natives::GET_WEAPONTYPE_MODEL((int)weapon, val);
		return Model((int)val);
	}

	Model Model::FromString(String^ string)
	{
		return Helper::StringToModel(string, Model(0));
	}
	String^ Model::ToString()
	{
		if (isNULL(pName) || (pName->Length == 0))
			return ("0x" + Helper::ToHex(pHash));
		else
			return pName;
	}

	bool Model::operator == (Model left, Model right)
	{
		return (left.pHash == right.pHash);
	}
	bool Model::operator != (Model left, Model right)
	{
		return !(left == right);
	}
	Model::operator Model (String^ source)
	{
		return Model(source);
	}
	Model::operator Model (int source)
	{
		return Model(source);
	}
	Model::operator Model (u32 source)
	{
		return Model(source);
	}

}