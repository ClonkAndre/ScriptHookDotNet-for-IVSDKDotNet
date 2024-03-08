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

#include "Garage.h"

#include "Vehicle.h"
#include "World.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Garage::Garage(String^ Name)
	{
		this->pName = Name;
	}

	// - - - Properties, Methods and Functions - - -
	void Garage::DontAffectCamera::set(bool value)
	{
		IVSDKDotNet::Native::Natives::SET_GARAGE_LEAVE_CAMERA_ALONE(pName, value);
	}
	void Garage::Type::set(GarageType value)
	{
		NotImplementedYet("Garage::Type::set");
		//IVSDKDotNet::Native::Natives::CHANGE_GARAGE_TYPE(pName, (int)value);
	}

	bool Garage::isClosed::get()
	{
		return IVSDKDotNet::Native::Natives::IS_GARAGE_CLOSED(pName);
	}
	bool Garage::isOpen::get()
	{
		return IVSDKDotNet::Native::Natives::IS_GARAGE_OPEN(pName);
	}

	void Garage::Open()
	{
		IVSDKDotNet::Native::Natives::OPEN_GARAGE(pName);
	}
	void Garage::Close()
	{
		IVSDKDotNet::Native::Natives::CLOSE_GARAGE(pName);
	}

	bool Garage::isVehicleInside(Vehicle^ vehicle)
	{
		OBJECT_NON_EXISTING_CHECK(vehicle, false);
		return IVSDKDotNet::Native::Natives::IS_CAR_IN_GARAGE_AREA(pName, vehicle->Handle);
	}

	array<Vehicle^>^ Garage::GetVehiclesInside()
	{
		List<Vehicle^>^ list = gcnew List<Vehicle^>();
		for each (Vehicle ^ v in World::GetAllVehicles())
		{
			if (isVehicleInside(v))
				list->Add(v);
		}
		return list->ToArray();
	}

	void Garage::AbortAllGarageActivity()
	{
		IVSDKDotNet::Native::Natives::ABORT_ALL_GARAGE_ACTIVITY();
	}

}