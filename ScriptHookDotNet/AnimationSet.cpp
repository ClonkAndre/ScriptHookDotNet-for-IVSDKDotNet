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

#include "AnimationSet.h"

#include "Game.h"
#include "Ped.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	AnimationSet::AnimationSet(String^ ModelName)
	{
		pName = ModelName;
	}

	// - - - Properties, Methods and Functions - - -
	String^ AnimationSet::Name::get()
	{
		return pName;
	}

	bool AnimationSet::isInMemory::get()
	{
		return IVSDKDotNet::Native::Natives::HAVE_ANIMS_LOADED(pName);
	}

	void AnimationSet::LoadToMemory()
	{
		IVSDKDotNet::Native::Natives::REQUEST_ANIMS(pName);
	}
	bool AnimationSet::LoadToMemoryNow()
	{
		int tries = 0;
		try
		{
			IVSDKDotNet::Native::Natives::REQUEST_ANIMS(pName);
			while (!IVSDKDotNet::Native::Natives::HAVE_ANIMS_LOADED(pName))
			{
				WHILE_LOG("AnimationSet::LoadToMemoryNow");
				Game::WaitInCurrentScript(0);
				IVSDKDotNet::Native::Natives::REQUEST_ANIMS(pName);
				tries++;
				if (tries > 100)
					return false;
			}
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	void AnimationSet::DisposeFromMemoryNow()
	{
		IVSDKDotNet::Native::Natives::REMOVE_ANIMS(pName);
	}
	bool AnimationSet::isPedPlayingAnimation(Ped^ ped, String^ AnimationName)
	{
		OBJECT_NON_EXISTING_CHECK(ped, false);
		return IVSDKDotNet::Native::Natives::IS_CHAR_PLAYING_ANIM(ped->Handle, pName, AnimationName);
	}
	float AnimationSet::GetPedsCurrentAnimationTime(Ped^ ped, String^ AnimationName)
	{
		OBJECT_NON_EXISTING_CHECK(ped, 0.0f);
		float res = 0.0f;
		IVSDKDotNet::Native::Natives::GET_CHAR_ANIM_CURRENT_TIME(ped->Handle, pName, AnimationName, res);
		return res;
	}

	bool AnimationSet::operator == (AnimationSet^ left, AnimationSet^ right)
	{
		if isNULL(left)
			return isNULL(right);
		if isNULL(right)
			return false;
		return (left->Name->Equals(right->Name));
	}
	bool AnimationSet::operator != (AnimationSet^ left, AnimationSet^ right)
	{
		return !(left == right);
	}

	String^ AnimationSet::ToString()
	{
		return Name;
	}

}