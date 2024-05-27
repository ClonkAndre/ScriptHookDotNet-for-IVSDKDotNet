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

#include "Team.h"

#pragma managed

namespace GTA
{
	namespace Multiplayer
	{

		// - - - Constructor - - -
		Team::Team(int ID)
		{
			this->pID = ID;
		}

		// - - - Properties, Methods and Functions - - -
		int Team::ID::get()
		{
			return pID;
		}

		int Team::MemberCount::get()
		{
			return IVSDKDotNet::Native::Natives::GET_NO_OF_PLAYERS_IN_TEAM(pID);
		}

		int Team::ColorID::get()
		{
			NotImplementedYet("Team::ColorID::get");
			//u32 pCol = 0;
			//IVSDKDotNet::Native::Natives::GET_TEAM_COLOUR(pID, pCol);
			//return (int)pCol;
			return 0;
		}
		void Team::ColorID::set(int value)
		{
			NotImplementedYet("Team::ColorID::set");
			//IVSDKDotNet::Native::Natives::SET_TEAM_COLOUR(pID,value);
		}

		Drawing::Color Team::Color::get()
		{
			int R = 0; int G = 0; int B = 0;
			IVSDKDotNet::Native::Natives::GET_TEAM_RGB_COLOUR(pID, R, G, B);
			return Drawing::Color::FromArgb(R, G, B);
		}

	}
}