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

#include "NmMessage.h"

#include "Ped.h"

#pragma managed

namespace GTA
{
	namespace Euphoria
	{

		void BaseMessage::pApplyTo(GTA::Ped^ TargetPed, int EnforceRagdollDuration)
		{
			if (EnforceRagdollDuration != 0)
				General::EnforceRagdoll(TargetPed, EnforceRagdollDuration);

			pApplyTo(TargetPed);
		}

		void BaseMessage::pApplyTo(GTA::Ped^ TargetPed)
		{
			if (!TargetPed->isRagdoll)
				General::EnforceRagdoll(TargetPed, -1);

			IVSDKDotNet::Native::Natives::CREATE_NM_MESSAGE(true, (u32)pMessageID);

			if (isNotNULL(ListInteger) && (ListInteger->Count > 0))
			{
				for each (KeyValuePair<int, int> item in ListInteger)
				{
					IVSDKDotNet::Native::Natives::SET_NM_MESSAGE_INT(item.Key, item.Value);
				}
			}
			if (isNotNULL(ListBoolean) && (ListBoolean->Count > 0))
			{
				for each (KeyValuePair<int, bool> item in ListBoolean)
				{
					IVSDKDotNet::Native::Natives::SET_NM_MESSAGE_BOOL(item.Key, item.Value);
				}
			}
			if (isNotNULL(ListFloat) && (ListFloat->Count > 0))
			{
				for each (KeyValuePair<int, float> item in ListFloat)
				{
					IVSDKDotNet::Native::Natives::SET_NM_MESSAGE_FLOAT(item.Key, item.Value);
				}
			}
			if (isNotNULL(ListString) && (ListString->Count > 0))
			{
				for each (KeyValuePair<int, String^> item in ListString)
				{
					IVSDKDotNet::Native::Natives::SET_NM_MESSAGE_STRING(item.Key, item.Value);
				}
			}
			if (isNotNULL(ListVector3) && (ListVector3->Count > 0))
			{
				for each (KeyValuePair<int, GTA::Vector3> item in ListVector3)
				{
					IVSDKDotNet::Native::Natives::SET_NM_MESSAGE_VEC3(item.Key, item.Value.X, item.Value.Y, item.Value.Z);
				}
			}
			if (isNotNULL(ListHandle) && (ListHandle->Count > 0))
			{
				for each (KeyValuePair<int, u32> item in ListHandle)
				{
					IVSDKDotNet::Native::Natives::SET_NM_MESSAGE_INSTANCE_INDEX(item.Key, 0, item.Value, 0);
				}
			}

			OBJECT_NON_EXISTING_CHECK_NO_RETURN(TargetPed);
			IVSDKDotNet::Native::Natives::SEND_NM_MESSAGE(TargetPed->Handle);
		}

		void General::Abort(GTA::Ped^ TargetPed, nmMessageID MessageID)
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(TargetPed);
			IVSDKDotNet::Native::Natives::CREATE_NM_MESSAGE(false, (u32)MessageID);
			IVSDKDotNet::Native::Natives::SEND_NM_MESSAGE(TargetPed->Handle);
		}

		void General::EnforceRagdoll(GTA::Ped^ Ped, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(Ped);
			IVSDKDotNet::Native::Natives::SWITCH_PED_TO_RAGDOLL(Ped->Handle, 10000, duration, 1, 1, 1, 0);
		}

		bool General::GetFeedback(GTA::Ped^ TargetPed, nmString FeedbackID, int FeedbackNum)
		{
			OBJECT_NON_EXISTING_CHECK(TargetPed, false);
			return IVSDKDotNet::Native::Natives::CHECK_NM_FEEDBACK(TargetPed->Handle, (u32)FeedbackID, FeedbackNum);
		}

	}
}