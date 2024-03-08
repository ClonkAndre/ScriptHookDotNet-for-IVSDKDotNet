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

#include "vPedSkin.h"

#include "Ped.h"
#include "Player.h"
#include "SkinTemplate.h"
#include "vPedComponent.h"

#pragma managed

namespace GTA
{
	namespace value
	{

		// PLAYER SKIN
		PlayerSkin::PlayerSkin(Player^ player)
			:PedSkin(player->Character)
		{
			this->player = player;
		}

		void PlayerSkin::Model::set(GTA::Model value)
		{
			player->Model = value;
		}
		void PlayerSkin::Template::set(SkinTemplate^ value)
		{
			if isNULL(value)
				player->Model = GTA::Model("PLAYER");
			else
				value->ApplyToPlayer(player);
		}

		// PED SKIN
		value::PedComponentCollection^ PedSkin::Component::get()
		{
			if isNULL(pComponent)
				pComponent = gcnew PedComponentCollection(ped);

			return pComponent;
		}

		GTA::Model PedSkin::Model::get()
		{
			return ped->Model;
		}

		SkinTemplate^ PedSkin::Template::get()
		{
			return gcnew SkinTemplate(this);
		}
		void PedSkin::Template::set(SkinTemplate^ value)
		{
			if (Model.Hash != value->Model.Hash)
				throw gcnew Exception("The model of a Ped cannot be changed!");

			value->ApplyToPed(ped);
		}

		int PedSkin::GetPropIndex(PedProp proptype)
		{
			OBJECT_NON_EXISTING_CHECK(ped, 0);
			int value = 0;
			IVSDKDotNet::Native::Natives::GET_CHAR_PROP_INDEX(ped->Handle, (int)proptype, value);
			return value;
		}
		void PedSkin::SetPropIndex(PedProp proptype, int index)
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::SET_CHAR_PROP_INDEX(ped->Handle, (u32)proptype, (u32)index);
		}

		PedSkin::operator SkinTemplate ^ (PedSkin^ source)
		{
			return source->Template;
		}

	}
}