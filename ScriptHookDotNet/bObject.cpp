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

#include "Player.h"
#include "Ped.h"
#include "Game.h"
#include "bObject.h"

#pragma managed

namespace GTA
{
	namespace base
	{

		bool Object::Exists()
		{
			if (!bExists)
				return false;

			bExists = InternalCheckExists();

			// Some hacks if the function returned false
			// thought the previous method worked.. well it did.. kinda... and apparently only once... ffs...
			if (!bExists /*&& System::Threading::Thread::CurrentThread->ManagedThreadId != IVSDKDotNet::Manager::ManagerScript::GetInstance()->GetMainThreadID()*/)
			{

				// HACK: If the UID is equal to the local player character handle ID then always return true as the local player never stops existing...
				if (UID == Game::LocalPlayer->Character->Handle)
					bExists = true;

			}

			if (bExists)
				return true;

			OnCeasedToExist(EventArgs::Empty);
			return false;
		}

	}
}