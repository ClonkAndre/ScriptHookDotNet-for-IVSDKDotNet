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

#include "ScriptedFire.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	ScriptedFire::ScriptedFire(int Handle)
		:HandleObject(Handle)
	{
	}

	// - - - Properties, Methods and Functions - - -
	Vector3 ScriptedFire::Position::get()
	{
		NON_EXISTING_CHECK(V3_NaN);
		float x, y, z;
		IVSDKDotNet::Native::Natives::GET_SCRIPT_FIRE_COORDS(pHandle, x, y, z);
		return Vector3(x, y, z);
	}

	bool ScriptedFire::InternalCheckExists()
	{
		if (pHandle == 0)
			return false;

		return IVSDKDotNet::Native::Natives::DOES_SCRIPT_FIRE_EXIST(pHandle);
	}
	void ScriptedFire::Delete()
	{
		NON_EXISTING_CHECK_RELAXED_NO_RETURN();
		SetExistsFalse();

		if (pHandle == 0)
			return;

		IVSDKDotNet::Native::Natives::REMOVE_SCRIPT_FIRE(pHandle);
	}

}