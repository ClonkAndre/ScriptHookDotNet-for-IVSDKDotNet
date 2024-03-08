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

#include "TaskSequence.h"

#include "Ped.h"
#include "vTasks.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	TaskSequence::TaskSequence(int Handle)
	{
		this->pHandle = Handle;
		CreatePedNull();
	}
	TaskSequence::TaskSequence()
	{
		int task = 0;
		IVSDKDotNet::Native::Natives::OPEN_SEQUENCE_TASK(task);
		this->pHandle = task;
		CreatePedNull();
	}
	TaskSequence::~TaskSequence()
	{
		IVSDKDotNet::Native::Natives::CLEAR_SEQUENCE_TASK(pHandle);
	}

	// - - - Properties, Methods and Functions - - -
	void TaskSequence::CreatePedNull()
	{
		if (hasPedNull)
			return;

		hasPedNull = true;
		//if (TaskSequence::pednull == nullptr) TaskSequence::pednull = gcnew GTA::Ped(0);
		pednull = gcnew GTA::Ped(0);
		//pednull = gcnew GTA::Ped(0);
	}

	int TaskSequence::Handle::get()
	{
		return pHandle;
	}
	value::Tasks^ TaskSequence::AddTask::get()
	{
		if (bClosed)
		{
			throw gcnew Exception("You can't add Tasks to a closed TaskSequence!");
			return nullptr;
		}

		return pednull->Task;
	}

	void TaskSequence::Perform(GTA::Ped^ TargetPed)
	{
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(TargetPed);

		if (!bClosed)
		{
			bClosed = true;
			IVSDKDotNet::Native::Natives::CLOSE_SEQUENCE_TASK(pHandle);
		}

		IVSDKDotNet::Native::Natives::CLEAR_CHAR_TASKS(TargetPed->Handle);
		//Scripting::SetCharKeepTask(TargetPed->Handle,cbool(true));
		TargetPed->BlockPermanentEvents = true;
		IVSDKDotNet::Native::Natives::_TASK_PERFORM_SEQUENCE(TargetPed->Handle, pHandle);
	}

}