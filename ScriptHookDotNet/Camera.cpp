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

#include "Camera.h"

#include "ContentCache.h"
#include "Ped.h"
#include "Object.h"
#include "Vehicle.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	Camera::Camera(int Handle)
		:HandleObject(Handle)
	{
	}
	Camera::Camera() :HandleObject(0)
	{
		int c;
		IVSDKDotNet::Native::Natives::CREATE_CAM(14, c);
		pHandle = c;
		ContentCache::AddCamera(this, true);
		Deactivate();
	}

	// - - - Properties, Methods and Functions - - -
	Vector3 Camera::Position::get()
	{
		NON_EXISTING_CHECK(V3_NaN);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_CAM_POS(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void Camera::Position::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAM_POS(pHandle, value.X, value.Y, value.Z);
	}

	Vector3 Camera::Rotation::get()
	{
		NON_EXISTING_CHECK(V3_NULL);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_CAM_ROT(pHandle, x, y, z);
		return Vector3(x, y, z);
	}
	void Camera::Rotation::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAM_ROT(pHandle, value.X, value.Y, value.Z);
	}

	Vector3 Camera::Direction::get()
	{
		return Helper::RotationToDirection(Rotation);
	}
	void Camera::Direction::set(Vector3 value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		Rotation = Helper::DirectionToRotation(value, Rotation.Y);
	}

	float Camera::Heading::get()
	{
		NON_EXISTING_CHECK(0.0f);
		return Rotation.Z;
	}
	void Camera::Heading::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		Vector3 rot = Rotation;
		rot.Z = value;
		Rotation = rot;
	}

	float Camera::Roll::get()
	{
		NON_EXISTING_CHECK(0.0f);
		return Rotation.Y;
	}
	void Camera::Roll::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		Vector3 rot = Rotation;
		rot.Y = value;
		Rotation = rot;
	}

	float Camera::FOV::get()
	{
		NON_EXISTING_CHECK(0.0f);
		float fov;
		IVSDKDotNet::Native::Natives::GET_CAM_FOV(pHandle, fov);
		return fov;
	}
	void Camera::FOV::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_CAM_FOV(pHandle, value);
	}

	bool Camera::isActive::get()
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::IS_CAM_ACTIVE(pHandle);
	}
	void Camera::isActive::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value)
			Activate();
		else
			Deactivate();
	}

	void Camera::DrunkEffectIntensity::set(float value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		if (value <= 0.0001f)
			IVSDKDotNet::Native::Natives::SET_DRUNK_CAM(pHandle, 0.0f, 0);
		else
			IVSDKDotNet::Native::Natives::SET_DRUNK_CAM(pHandle, value, int::MaxValue);
	}

	void Camera::TargetPed(Ped^ ped)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
		IVSDKDotNet::Native::Natives::SET_CAM_TARGET_PED(pHandle, ped->Handle);
	}
	void Camera::LookAt(GTA::Object^ object)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(object);
		IVSDKDotNet::Native::Natives::POINT_CAM_AT_OBJECT(pHandle, object->Handle);
	}
	void Camera::LookAt(Vehicle^ vehicle)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);
		IVSDKDotNet::Native::Natives::POINT_CAM_AT_VEHICLE(pHandle, vehicle->Handle);
	}
	void Camera::LookAt(Ped^ ped)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
		IVSDKDotNet::Native::Natives::POINT_CAM_AT_PED(pHandle, ped->Handle);
	}
	void Camera::LookAt(Vector3 Position)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::POINT_CAM_AT_COORD(pHandle, Position.X, Position.Y, Position.Z);
	}

	void Camera::Activate()
	{
		NON_EXISTING_CHECK_NO_RETURN();
		//i32 handle = pHandle;
		IVSDKDotNet::Native::Natives::ACTIVATE_SCRIPTED_CAMS(true, true);
		//unmanaged::Native::BeginCamCommands(&handle); // Is this even needed?
		IVSDKDotNet::Native::Natives::SET_CAM_ACTIVE(pHandle, true);
		IVSDKDotNet::Native::Natives::SET_CAM_PROPAGATE(pHandle, true);
	}
	bool Camera::isSphereVisible(Vector3 Position, float Radius)
	{
		NON_EXISTING_CHECK(false);
		return IVSDKDotNet::Native::Natives::CAM_IS_SPHERE_VISIBLE(pHandle, Position.X, Position.Y, Position.Z, Radius);
	}
	void Camera::Deactivate()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		//i32 handle = pHandle;
		IVSDKDotNet::Native::Natives::SET_CAM_ACTIVE(pHandle, false);
		IVSDKDotNet::Native::Natives::SET_CAM_PROPAGATE(pHandle, false);
		//unmanaged::Native::EndCamCommands(&handle); // Still no idea if that's even needed
		IVSDKDotNet::Native::Natives::ACTIVATE_SCRIPTED_CAMS(false, false);
	}
	void Camera::Delete()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		SetExistsFalse();

		if (pHandle == 0)
			return;
		if (isActive)
			Deactivate();

		IVSDKDotNet::Native::Natives::DESTROY_CAM(pHandle);
	}

	bool Camera::InternalCheckExists()
	{
		if (pHandle == 0)
			return false;

		return IVSDKDotNet::Native::Natives::DOES_CAM_EXIST(pHandle);
	}

}