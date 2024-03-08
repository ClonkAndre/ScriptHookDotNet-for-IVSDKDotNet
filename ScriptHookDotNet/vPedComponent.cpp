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

#include "vPedComponent.h"

#include "Ped.h"

#pragma managed

namespace GTA
{
	namespace value
	{

		// PedComponent
		int PedComponent::AvailableModels::get()
		{
			OBJECT_NON_EXISTING_CHECK(ped, 0);
			return IVSDKDotNet::Native::Natives::GET_NUMBER_OF_CHAR_DRAWABLE_VARIATIONS(ped->Handle, (u32)pID);
		}
		int PedComponent::GetAvailableTextures(int model)
		{
			OBJECT_NON_EXISTING_CHECK(ped, 0);
			return IVSDKDotNet::Native::Natives::GET_NUMBER_OF_CHAR_TEXTURE_VARIATIONS(ped->Handle, (u32)pID, (u32)model);
		}
		int PedComponent::AvailableTextures::get()
		{
			return GetAvailableTextures(ModelIndex);
		}

		int PedComponent::ModelIndex::get()
		{
			OBJECT_NON_EXISTING_CHECK(ped, 0);
			return IVSDKDotNet::Native::Natives::GET_CHAR_DRAWABLE_VARIATION(ped->Handle, (int)pID);
		}
		void PedComponent::ModelIndex::set(int value)
		{
			Change(value, 0);
		}

		int PedComponent::TextureIndex::get()
		{
			OBJECT_NON_EXISTING_CHECK(ped, 0);
			return IVSDKDotNet::Native::Natives::GET_CHAR_TEXTURE_VARIATION(ped->Handle, (u32)pID);
		}
		void PedComponent::TextureIndex::set(int value)
		{
			Change(ModelIndex, value);
		}

		bool PedComponent::isValid(int model, int texture)
		{
			if ((model < 0) || (model >= AvailableModels))
				return false;
			if ((texture < 0) || (texture >= GetAvailableTextures(model)))
				return false;

			return true;
		}

		void PedComponent::Change(int model, int texture)
		{
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
			if ((model < 0) || (model >= AvailableModels))
				throw gcnew ArgumentOutOfRangeException("ModelIndex");
			if ((texture < 0) || (texture >= GetAvailableTextures(model)))
				throw gcnew ArgumentOutOfRangeException("TextureIndex");

			IVSDKDotNet::Native::Natives::SET_CHAR_COMPONENT_VARIATION(ped->Handle, (u32)pID, (u32)model, (u32)texture);
		}

		PedComponent::operator GTA::PedComponent(PedComponent^ source)
		{
			return source->pID;
		}

		bool PedComponent::operator == (PedComponent^ left, PedComponent^ right)
		{
			if isNULL(left)
				return isNULL(right);
			if isNULL(right)
				return false;

			return (left->pID == right->pID);
		}
		bool PedComponent::operator != (PedComponent^ left, PedComponent^ right)
		{
			return !(left == right);
		}

		bool PedComponent::operator == (GTA::PedComponent left, PedComponent^ right)
		{
			if isNULL(right)
				return false;

			return (left == right->pID);
		}
		bool PedComponent::operator != (GTA::PedComponent left, PedComponent^ right)
		{
			return !(left == right);
		}

		bool PedComponent::operator == (PedComponent^ left, GTA::PedComponent right)
		{
			if isNULL(left)
				return false;

			return (right == left->pID);
		}
		bool PedComponent::operator != (PedComponent^ left, GTA::PedComponent right)
		{
			return !(left == right);
		}

		// PedComponentCollection
		value::PedComponent^ PedComponentCollection::Component(GTA::PedComponent component)
		{
			GTA::value::PedComponent^ comp;

			if isNULL(pComponentCache)
				pComponentCache = gcnew Dictionary<GTA::PedComponent, GTA::value::PedComponent^>();
			else
			{
				if (pComponentCache->TryGetValue(component, comp))
					return comp;
			}

			comp = gcnew GTA::value::PedComponent(ped, component);
			pComponentCache->Add(component, comp);

			return comp;
		}

	}
}