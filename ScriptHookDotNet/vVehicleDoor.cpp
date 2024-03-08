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

#pragma once
#include "stdafx.h"

#include "vVehicleDoor.h"

#include "Vehicle.h"

#pragma managed

namespace GTA
{
	namespace value
	{

		// - - - Constructor - - -
		VehicleDoor::VehicleDoor(Vehicle^ vehicle, GTA::VehicleDoor door)
		{
			this->vehicle = vehicle;
			this->door = door;
		}

		// - - - Properties, Methods and Functions - - -
		GTA::VehicleDoor VehicleDoor::Index::get()
		{
			return door;
		}

		bool VehicleDoor::isDamaged::get()
		{
			OBJECT_NON_EXISTING_CHECK(vehicle, false);
			return IVSDKDotNet::Native::Natives::IS_CAR_DOOR_DAMAGED(vehicle->Handle, (u32)door);
		}

		float VehicleDoor::Angle::get()
		{
			OBJECT_NON_EXISTING_CHECK(vehicle, 0.0f);
			f32 a;
			IVSDKDotNet::Native::Natives::GET_DOOR_ANGLE_RATIO(vehicle->Handle, (u32)door, a);
			return a;
		}
		void VehicleDoor::Angle::set(float value)
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);

			if (value > 1.0f)
				value = 1.0f;

			if (value > 0.001f)
				IVSDKDotNet::Native::Natives::CONTROL_CAR_DOOR(vehicle->Handle, (u32)door, 1, value);
			else
				Close();
		}

		bool VehicleDoor::isFullyOpen::get()
		{
			OBJECT_NON_EXISTING_CHECK(vehicle, false);
			return IVSDKDotNet::Native::Natives::IS_CAR_DOOR_FULLY_OPEN(vehicle->Handle, (u32)door);
		}

		bool VehicleDoor::isOpen::get()
		{
			return (Angle > 0.001f);
		}
		void VehicleDoor::isOpen::set(bool value)
		{
			if (value)
				Open();
			else
				Close();
		}

		void VehicleDoor::Open()
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);
			IVSDKDotNet::Native::Natives::OPEN_CAR_DOOR(vehicle->Handle, (u32)door);
		}
		void VehicleDoor::Close()
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);
			IVSDKDotNet::Native::Natives::SHUT_CAR_DOOR(vehicle->Handle, (u32)door);
		}
		void VehicleDoor::Break()
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);
			IVSDKDotNet::Native::Natives::BREAK_CAR_DOOR(vehicle->Handle, (u32)door, false);
		}

		VehicleDoor::operator GTA::VehicleDoor(GTA::value::VehicleDoor^ source)
		{
			return source->door;
		}

	}
}