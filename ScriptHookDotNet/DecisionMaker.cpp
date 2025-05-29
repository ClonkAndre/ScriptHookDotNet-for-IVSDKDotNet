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

#include "DecisionMaker.h"

#include "Ped.h"

#pragma managed

namespace GTA
{

	// Note that we need to set the DecisionMaker category after we created a new instance of it!
	// Before you could instantly set it using the constructor, now we need to set it AFTER it got constructed!

	// - - - Constructor - - -
	DecisionMaker::DecisionMaker(int Handle) :HandleObject(Handle, HandleType::DecisionMaker)
	{
		
	}
	DecisionMaker::~DecisionMaker()
	{
		IVSDKDotNet::Native::Natives::REMOVE_DECISION_MAKER(pHandle);
	}

	// - - - Properties, Methods and Functions - - -
	DecisionMaker^ DecisionMaker::LoadBehavior(BehaviorTemplate Template)
	{
		int dm;
		IVSDKDotNet::Native::Natives::LOAD_CHAR_DECISION_MAKER((uint32_t)Template, dm);

		if (dm == 0)
			return nullptr;

		DecisionMaker^ instance = gcnew DecisionMaker(dm);
		instance->Category = DecisionCategory::Behavior;
		return instance;
	}
	DecisionMaker^ DecisionMaker::LoadCombat(CombatTemplate Template)
	{
		int dm;
		IVSDKDotNet::Native::Natives::LOAD_COMBAT_DECISION_MAKER((uint32_t)Template, dm);

		if (dm == 0)
			return nullptr;

		DecisionMaker^ instance = gcnew DecisionMaker(dm);
		instance->Category = DecisionCategory::Combat;
		return instance;
	}

	DecisionMaker^ DecisionMaker::CopyBehavior(CopyTemplate Template)
	{
		int dm;
		IVSDKDotNet::Native::Natives::COPY_CHAR_DECISION_MAKER((uint32_t)Template, dm);

		if (dm == 0)
			return nullptr;

		DecisionMaker^ instance = gcnew DecisionMaker(dm);
		instance->Category = DecisionCategory::Behavior;
		return instance;
	}
	DecisionMaker^ DecisionMaker::CopyCombat(CopyTemplate Template)
	{
		int dm;
		IVSDKDotNet::Native::Natives::COPY_COMBAT_DECISION_MAKER((uint32_t)Template, dm);

		if (dm == 0)
			return nullptr;

		DecisionMaker^ instance = gcnew DecisionMaker(dm);
		instance->Category = DecisionCategory::Combat;
		return instance;
	}

	DecisionMaker^ DecisionMaker::CopyBehaviorForGroupMembers(CopyTemplate Template)
	{
		int dm;
		IVSDKDotNet::Native::Natives::COPY_GROUP_CHAR_DECISION_MAKER((uint32_t)Template, dm);

		if (dm == 0)
			return nullptr;

		DecisionMaker^ instance = gcnew DecisionMaker(dm);
		instance->Category = DecisionCategory::GroupBehavior;
		return instance;
	}
	DecisionMaker^ DecisionMaker::CopyCombatForGroupMembers(CopyTemplate Template)
	{
		int dm;
		IVSDKDotNet::Native::Natives::COPY_GROUP_COMBAT_DECISION_MAKER((uint32_t)Template, dm);

		if (dm == 0)
			return nullptr;

		DecisionMaker^ instance = gcnew DecisionMaker(dm);
		instance->Category = DecisionCategory::GroupCombat;
		return instance;
	}

	void DecisionMaker::ApplyTo(GTA::Ped^ ped)
	{
		if isNULL(ped)
			return;
		NON_EXISTING_CHECK_NO_RETURN();
		OBJECT_NON_EXISTING_CHECK_NO_RETURN(ped);
		switch (pCategory)
		{
			case DecisionCategory::Behavior:
				IVSDKDotNet::Native::Natives::SET_CHAR_DECISION_MAKER(ped->Handle, pHandle);
				return;
			case DecisionCategory::Combat:
				IVSDKDotNet::Native::Natives::SET_COMBAT_DECISION_MAKER(ped->Handle, pHandle);
				return;
			case DecisionCategory::GroupBehavior:
				IVSDKDotNet::Native::Natives::SET_GROUP_CHAR_DECISION_MAKER(ped->Handle, pHandle);
				return;
			case DecisionCategory::GroupCombat:
				IVSDKDotNet::Native::Natives::SET_GROUP_COMBAT_DECISION_MAKER(ped->Handle, pHandle);
				return;
		}
	}

	bool DecisionMaker::InternalCheckExists()
	{
		return IVSDKDotNet::Native::Natives::DOES_DECISION_MAKER_EXIST(pHandle);
	}

	void DecisionMaker::RemoveEventResponse(int EventID)
	{
		NON_EXISTING_CHECK();
		switch (pCategory)
		{
			case DecisionCategory::Behavior:
			case DecisionCategory::GroupBehavior:
				//Scripting::ClearCharDecisionMakerEventResponse(pHandle,EventID);
				NotImplementedYet("Scripting::ClearCharDecisionMakerEventResponse");
				return;
			case DecisionCategory::Combat:
			case DecisionCategory::GroupCombat:
				//Scripting::ClearCombatDecisionMakerEventResponse(pHandle,EventID);
				NotImplementedYet("Scripting::ClearCombatDecisionMakerEventResponse");
				return;
			//case DecisionCategory::Group:
			//	Scripting::ClearGroupDecisionMakerEventResponse(pHandle,EventID);
			//	return;
		}
	}
	void DecisionMaker::AddEventResponse(int EventID, int ResponseID, float param1, float param2, float param3, float param4)
	{
		NON_EXISTING_CHECK();
		switch (pCategory)
		{
			case DecisionCategory::Behavior:
			case DecisionCategory::GroupBehavior:
				IVSDKDotNet::Native::Natives::ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE(pHandle,EventID,ResponseID,param1,param2,param3,param4,1,1);
				return;
			case DecisionCategory::Combat:
			case DecisionCategory::GroupCombat:
				//Scripting::AddCombatDecisionMakerEventResponse(pHandle,EventID,ResponseID,param1,param2,param3,param4,1,1);
				NotImplementedYet("Scripting::AddCombatDecisionMakerEventResponse");
				return;
			//case DecisionCategory::Group:
			//	Scripting::AddGroupDecisionMakerEventResponse(pHandle,EventID,ResponseID,param1,param2,param3,param4,1,1);
			//	return;
		}
	}

	void DecisionMaker::CanChangeTarget::set(bool value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_CAN_CHANGE_TARGET(pHandle, value);
	}
	void DecisionMaker::Caution::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_CAUTION(pHandle, value);
	}
	void DecisionMaker::FireRate::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_FIRE_RATE(pHandle, value);
	}
	void DecisionMaker::LowHealth::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_LOW_HEALTH(pHandle, value);
	}
	void DecisionMaker::MovementStyle::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_MOVEMENT_STYLE(pHandle, value);
	}
	void DecisionMaker::NavigationStyle::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_NAVIGATION_STYLE(pHandle, value);
	}
	void DecisionMaker::RetreatingBehavior::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_RETREATING_BEHAVIOUR(pHandle, value);
	}
	void DecisionMaker::SightRange::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(pHandle, value);
	}
	void DecisionMaker::StandingStyle::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_STANDING_STYLE(pHandle, value);
	}
	void DecisionMaker::TargetInjuredReaction::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_TARGET_INJURED_REACTION(pHandle, value);
	}
	void DecisionMaker::TargetLossResponse::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_TARGET_LOSS_RESPONSE(pHandle, value);
	}
	void DecisionMaker::Teamwork::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_TEAMWORK(pHandle, value);
	}
	void DecisionMaker::WeaponAccuracy::set(int value)
	{
		NON_EXISTING_CHECK_NO_RETURN();
		IVSDKDotNet::Native::Natives::SET_DECISION_MAKER_ATTRIBUTE_WEAPON_ACCURACY(pHandle, value);
	}

}