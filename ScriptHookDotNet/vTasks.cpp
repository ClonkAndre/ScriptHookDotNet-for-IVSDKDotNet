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

#include "vTasks.h"

#include "AnimationSet.h"
#include "Object.h"
#include "Ped.h"
#include "TaskSequence.h"
#include "Vehicle.h"

#pragma managed

namespace GTA
{
	namespace value
	{

		// - - - Constructor - - -
		Tasks::Tasks(Ped^ ped)
		{
			this->ped = ped;
		}

		// - - - Properties, Methods and Functions - - -
		void Tasks::AimAt(Vector3 target, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_AIM_GUN_AT_COORD(ped->Handle, target.X, target.Y, target.Z, duration);
		}
		void Tasks::AimAt(Ped^ target, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_AIM_GUN_AT_CHAR(ped->Handle, target->Handle, duration);
		}
		void Tasks::CruiseWithVehicle(GTA::Vehicle^ Vehicle, float SpeedMph, bool ObeyTrafficLaws)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(Vehicle);
			IVSDKDotNet::Native::Natives::_TASK_CAR_DRIVE_WANDER(ped->Handle, Vehicle->Handle, SpeedMph, (ObeyTrafficLaws ? 1 : 2));
		}
		void Tasks::Die()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_DIE(ped->Handle);
		}

		void Tasks::DrivePointRoute(GTA::Vehicle^ Vehicle, float Speed, ... array<Vector3>^ RoutePoints)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(Vehicle);

			if (isNULL(RoutePoints) || (RoutePoints->Length == 0))
				return;

			IVSDKDotNet::Native::Natives::_TASK_FLUSH_ROUTE();
			for (int i = 0; i < RoutePoints->Length; i++)
			{
				IVSDKDotNet::Native::Natives::_TASK_EXTEND_ROUTE(RoutePoints[i].X, RoutePoints[i].Y, RoutePoints[i].Z);
			}
			IVSDKDotNet::Native::Natives::_TASK_DRIVE_POINT_ROUTE(ped->Handle, Vehicle->Handle, Speed);
		}

		// MissionIDs for TaskCarMission: 5(wait), 12(follow) and 21(drive to player)
		void Tasks::DriveTo(GTA::Vehicle^ Vehicle, Ped^ TargetPed, float SpeedMph, bool ObeyTrafficLaws, bool AllowToDriveRoadsWrongWay)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(Vehicle);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(TargetPed);
			if (!AllowToDriveRoadsWrongWay)
				IVSDKDotNet::Native::Natives::_TASK_CAR_MISSION_PED_TARGET_NOT_AGAINST_TRAFFIC(ped->Handle, Vehicle->Handle, TargetPed->Handle, 4, SpeedMph, (ObeyTrafficLaws ? 1 : 2), 5, 10);
			else
				IVSDKDotNet::Native::Natives::_TASK_CAR_MISSION_PED_TARGET(ped->Handle, Vehicle->Handle, TargetPed->Handle, 4, SpeedMph, (ObeyTrafficLaws ? 1 : 2), 5, 10);
		}
		void Tasks::DriveTo(GTA::Vehicle^ Vehicle, Ped^ TargetPed, float SpeedMph, bool ObeyTrafficLaws)
		{
			DriveTo(Vehicle, TargetPed, SpeedMph, ObeyTrafficLaws, true);
		}

		void Tasks::DriveTo(GTA::Vehicle^ Vehicle, GTA::Vehicle^ TargetVehicle, float SpeedMph, bool ObeyTrafficLaws, bool AllowToDriveRoadsWrongWay)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(Vehicle);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(TargetVehicle);

			if (!AllowToDriveRoadsWrongWay)
				IVSDKDotNet::Native::Natives::_TASK_CAR_MISSION_NOT_AGAINST_TRAFFIC(ped->Handle, Vehicle->Handle, TargetVehicle->Handle, 1, SpeedMph, (ObeyTrafficLaws ? 1 : 2), 10, 5);
			else
				IVSDKDotNet::Native::Natives::_TASK_CAR_MISSION(ped->Handle, Vehicle->Handle, TargetVehicle->Handle, 1, SpeedMph, (ObeyTrafficLaws ? 1 : 2), 10, 5);
		}
		void Tasks::DriveTo(GTA::Vehicle^ Vehicle, GTA::Vehicle^ TargetVehicle, float SpeedMph, bool ObeyTrafficLaws)
		{
			DriveTo(Vehicle, TargetVehicle, SpeedMph, ObeyTrafficLaws, true);
		}

		void Tasks::DriveTo(GTA::Vehicle^ Vehicle, Vector3 Target, float SpeedMph, bool ObeyTrafficLaws, bool AllowToDriveRoadsWrongWay)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(Vehicle);

			if (!AllowToDriveRoadsWrongWay)
				IVSDKDotNet::Native::Natives::_TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped->Handle, Vehicle->Handle, Target.X, Target.Y, Target.Z, 4, SpeedMph, (ObeyTrafficLaws ? 1 : 2), 5, 10);
			else
				IVSDKDotNet::Native::Natives::_TASK_CAR_MISSION_COORS_TARGET(ped->Handle, Vehicle->Handle, Target.X, Target.Y, Target.Z, 4, SpeedMph, (ObeyTrafficLaws ? 1 : 2), 5, 10);
		}
		void Tasks::DriveTo(GTA::Vehicle^ Vehicle, Vector3 Target, float SpeedMph, bool ObeyTrafficLaws)
		{
			DriveTo(Vehicle, Target, SpeedMph, ObeyTrafficLaws, false);
		}

		void Tasks::DriveTo(Ped^ TargetPed, float SpeedMph, bool ObeyTrafficLaws, bool AllowToDriveRoadsWrongWay)
		{
			DriveTo(Vehicle::AnyVehicle, TargetPed, SpeedMph, ObeyTrafficLaws, AllowToDriveRoadsWrongWay);
		}
		void Tasks::DriveTo(Ped^ TargetPed, float SpeedMph, bool ObeyTrafficLaws)
		{
			DriveTo(Vehicle::AnyVehicle, TargetPed, SpeedMph, ObeyTrafficLaws);
		}
		void Tasks::DriveTo(GTA::Vehicle^ TargetVehicle, float SpeedMph, bool ObeyTrafficLaws, bool AllowToDriveRoadsWrongWay)
		{
			DriveTo(Vehicle::AnyVehicle, TargetVehicle, SpeedMph, ObeyTrafficLaws, AllowToDriveRoadsWrongWay);
		}
		void Tasks::DriveTo(GTA::Vehicle^ TargetVehicle, float SpeedMph, bool ObeyTrafficLaws)
		{
			DriveTo(Vehicle::AnyVehicle, TargetVehicle, SpeedMph, ObeyTrafficLaws);
		}
		void Tasks::DriveTo(Vector3 Target, float SpeedMph, bool ObeyTrafficLaws, bool AllowToDriveRoadsWrongWay)
		{
			DriveTo(Vehicle::AnyVehicle, Target, SpeedMph, ObeyTrafficLaws, AllowToDriveRoadsWrongWay);
		}
		void Tasks::DriveTo(Vector3 Target, float SpeedMph, bool ObeyTrafficLaws)
		{
			DriveTo(Vehicle::AnyVehicle, Target, SpeedMph, ObeyTrafficLaws);
		}
		//void Tasks::EnterVehicle(GTA::Vehicle^ vehicle, int PassengerSeat) {
		//	Scripting::TaskEnterCarAsPassenger(ped->Handle, vehicle->Handle, PassengerSeat, 0);
		//}
		//void Tasks::EnterVehicle(GTA::Vehicle^ vehicle) {
		//	Scripting::TaskEnterCarAsDriver(ped->Handle, vehicle->Handle, 0);
		//}
		void Tasks::EnterVehicle()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_ENTER_CAR_AS_PASSENGER(ped->Handle, 0, 0, -2);
		}
		void Tasks::EnterVehicle(GTA::Vehicle^ vehicle, GTA::VehicleSeat Seat)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(vehicle);

			if (Seat <= VehicleSeat::None)
				return;

			if (Seat == VehicleSeat::Driver)
				IVSDKDotNet::Native::Natives::_TASK_ENTER_CAR_AS_DRIVER(ped->Handle, vehicle->Handle, 0);
			else
				IVSDKDotNet::Native::Natives::_TASK_ENTER_CAR_AS_PASSENGER(ped->Handle, vehicle->Handle, 0, (u32)Seat);
		}

		void Tasks::FightAgainst(Ped^ target, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_COMBAT_TIMED(ped->Handle, target->Handle, duration);
		}
		void Tasks::FightAgainst(Ped^ target)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_COMBAT(ped->Handle, target->Handle);
		}
		void Tasks::FightAgainstHatedTargets(float radius, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_COMBAT_HATED_TARGETS_AROUND_CHAR_TIMED(ped->Handle, radius, duration);
		}
		void Tasks::FightAgainstHatedTargets(float radius)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_COMBAT_HATED_TARGETS_AROUND_CHAR(ped->Handle, radius);
		}
		void Tasks::FleeFromChar(Ped^ target, bool onPavements, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			if (onPavements)
				IVSDKDotNet::Native::Natives::_TASK_SMART_FLEE_CHAR_PREFERRING_PAVEMENTS(ped->Handle, target->Handle, 100.0f, duration);
			else
				IVSDKDotNet::Native::Natives::_TASK_SMART_FLEE_CHAR(ped->Handle, target->Handle, 100.0f, duration);
		}
		void Tasks::FleeFromChar(Ped^ target, bool onPavements)
		{
			FleeFromChar(target, onPavements, -1);
		}
		void Tasks::FleeFromChar(Ped^ target)
		{
			FleeFromChar(target, false, -1);
		}

		void Tasks::GoTo(Ped^ TargetPed, float OffsetRight, float OffsetFront, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(TargetPed);
			IVSDKDotNet::Native::Natives::_TASK_GOTO_CHAR_OFFSET(ped->Handle, TargetPed->Handle, duration, OffsetRight, OffsetFront);
		}
		void Tasks::GoTo(Ped^ TargetPed, float OffsetRight, float OffsetFront)
		{
			GoTo(TargetPed, OffsetRight, OffsetFront, -1);
		}
		void Tasks::GoTo(Ped^ TargetPed)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(TargetPed);
			IVSDKDotNet::Native::Natives::_TASK_GOTO_CHAR_OFFSET(ped->Handle, TargetPed->Handle, -1, 0.0f, 0.0f);
		}
		void Tasks::GoTo(Vector3 Position, bool IgnorePaths)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			if (IgnorePaths)
				IVSDKDotNet::Native::Natives::_TASK_GO_STRAIGHT_TO_COORD(ped->Handle, Position.X, Position.Y, Position.Z, 2, -1);
			else
				IVSDKDotNet::Native::Natives::_TASK_FOLLOW_NAV_MESH_TO_COORD(ped->Handle, Position.X, Position.Y, Position.Z, 2, -1, 1.0f);
		}
		void Tasks::GoTo(Vector3 Position)
		{
			GoTo(Position, false);
		}
		void Tasks::RunTo(Vector3 Position, bool IgnorePaths)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			if (IgnorePaths)
				IVSDKDotNet::Native::Natives::_TASK_GO_STRAIGHT_TO_COORD(ped->Handle, Position.X, Position.Y, Position.Z, 4, -1);
			else
				IVSDKDotNet::Native::Natives::_TASK_FOLLOW_NAV_MESH_TO_COORD(ped->Handle, Position.X, Position.Y, Position.Z, 4, -1, 1.0f);
		}
		void Tasks::RunTo(Vector3 Position)
		{
			RunTo(Position, false);
		}

		void Tasks::GuardCurrentPosition()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_GUARD_CURRENT_POSITION(ped->Handle, 15.0f, 10.0f, 1);
		}
		void Tasks::HandsUp(int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			if (duration < 0)
				duration = MAX_DURATION;

			IVSDKDotNet::Native::Natives::_TASK_HANDS_UP(ped->Handle, duration);
		}
		void Tasks::LandHelicopter(Vehicle^ heli, Vector3 Position)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(heli);
			IVSDKDotNet::Native::Natives::_TASK_HELI_MISSION(ped->Handle, heli->Handle, 0, 0, Position.X, Position.Y, Position.Z, 5, 0.0f, 0, -1.0f, -1, -1);
		}
		void Tasks::LeaveVehicle(Vehicle^ vehicle, bool CloseDoor)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(vehicle);
			if (CloseDoor)
				IVSDKDotNet::Native::Natives::_TASK_LEAVE_CAR(ped->Handle, vehicle->Handle);
			else
				IVSDKDotNet::Native::Natives::_TASK_LEAVE_CAR_DONT_CLOSE_DOOR(ped->Handle, vehicle->Handle);
		}
		void Tasks::LeaveVehicle()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_LEAVE_ANY_CAR(ped->Handle);
		}
		void Tasks::LeaveVehicleImmediately(Vehicle^ vehicle)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(vehicle);
			IVSDKDotNet::Native::Natives::_TASK_LEAVE_CAR_IMMEDIATELY(ped->Handle, vehicle->Handle);
		}

		void Tasks::LookAt(GTA::Vector3 target, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_LOOK_AT_COORD(ped->Handle, target.X, target.Y, target.Z, duration, 0);
		}
		void Tasks::LookAt(GTA::Object^ target, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_LOOK_AT_OBJECT(ped->Handle, target->Handle, duration, 0);
		}
		void Tasks::LookAt(GTA::Vehicle^ target, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_LOOK_AT_VEHICLE(ped->Handle, target->Handle, duration, 0);
		}
		void Tasks::LookAt(GTA::Ped^ target, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_LOOK_AT_CHAR(ped->Handle, target->Handle, duration, 0);
		}
		void Tasks::PlayAnimation(GTA::AnimationSet^ AnimationSet, String^ AnimationName, float Speed, AnimationFlags Flags)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			if (System::Object::ReferenceEquals(AnimationSet, nullptr))
				return;
			if (!AnimationSet->LoadToMemoryNow())
				return;

			IVSDKDotNet::Native::Natives::_TASK_PLAY_ANIM_WITH_FLAGS(ped->Handle, AnimationName, AnimationSet->Name, Speed, -1, (u32)Flags);
		}
		void Tasks::PlayAnimation(GTA::AnimationSet^ AnimationSet, String^ AnimationName, float Speed)
		{
			PlayAnimation(AnimationSet, AnimationName, Speed, AnimationFlags::None);
		}
		void Tasks::PutAwayMobilePhone()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_USE_MOBILE_PHONE(ped->Handle, false);
		}
		void Tasks::ShootAt(Ped^ target, ShootMode mode, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_SHOOT_AT_CHAR(ped->Handle, target->Handle, duration, (int)mode);
		}
		void Tasks::ShootAt(Ped^ target, ShootMode mode)
		{
			ShootAt(target, mode, -1);
		}
		void Tasks::StandStill(int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			if (duration < 0)
				duration = MAX_DURATION;
			IVSDKDotNet::Native::Natives::_TASK_STAND_STILL(ped->Handle, duration);
		}
		void Tasks::SwapWeapon(GTA::Weapon Weapon)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_SWAP_WEAPON(ped->Handle, (u32)Weapon);
		}
		void Tasks::StartScenario(String^ ScenarioName, Vector3 Position)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_START_SCENARIO_AT_POSITION(ped->Handle, ScenarioName, GTAVector3ToVector3(Position), 0);
		}
		void Tasks::TurnTo(Vector3 Position)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_TURN_CHAR_TO_FACE_COORD(ped->Handle, Position.X, Position.Y, Position.Z);
		}
		void Tasks::TurnTo(Ped^ target)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			IVSDKDotNet::Native::Natives::_TASK_TURN_CHAR_TO_FACE_CHAR(ped->Handle, target->Handle);
		}
		void Tasks::UseMobilePhone()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_USE_MOBILE_PHONE(ped->Handle, true);
		}
		void Tasks::UseMobilePhone(int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_USE_MOBILE_PHONE_TIMED(ped->Handle, duration);
		}
		void Tasks::Wait(int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			if (duration < 0)
				duration = MAX_DURATION;
			IVSDKDotNet::Native::Natives::_TASK_PAUSE(ped->Handle, duration);
		}
		void Tasks::WalkRelativeToPed(Ped^ target, float OffsetToRight, float OffsetToFront, int duration)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(target);
			if (duration < 0)
				duration = -1;
			IVSDKDotNet::Native::Natives::_TASK_GOTO_CHAR_OFFSET(ped->Handle, target->Handle, duration, OffsetToRight, OffsetToFront);
		}
		void Tasks::WanderAround()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::_TASK_WANDER_STANDARD(ped->Handle);
		}
		//void Tasks::WarpIntoVehicle(GTA::Vehicle^ vehicle, int PassengerSeat) {
		//	Scripting::TaskWarpCharIntoCarAsPassenger(ped->Handle, vehicle->Handle, PassengerSeat);
		//}
		//void Tasks::WarpIntoVehicle(GTA::Vehicle^ vehicle) {
		//	Scripting::TaskWarpCharIntoCarAsDriver(ped->Handle, vehicle->Handle);
		//}
		void Tasks::WarpIntoVehicle(GTA::Vehicle^ vehicle, GTA::VehicleSeat Seat)
		{
			if (Seat <= VehicleSeat::None)
				return;

			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			OBJECT_NON_EXISTING_CHECK_NO_RETURN(vehicle);

			if (Seat == VehicleSeat::Driver)
				IVSDKDotNet::Native::Natives::_TASK_WARP_CHAR_INTO_CAR_AS_DRIVER(ped->Handle, vehicle->Handle);
			else
				IVSDKDotNet::Native::Natives::_TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER(ped->Handle, vehicle->Handle, (u32)Seat);
		}

		// PED TASK FUNCTIONS
		PedTasks::PedTasks(Ped^ ped)
			: Tasks(ped)
		{
		}

		void PedTasks::AlwaysKeepTask::set(bool value)
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::SET_CHAR_KEEP_TASK(ped->Handle, value);
		}

		void PedTasks::ClearAll()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::CLEAR_CHAR_TASKS(ped->Handle);
		}
		void PedTasks::ClearAllImmediately()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::CLEAR_CHAR_TASKS_IMMEDIATELY(ped->Handle);
		}
		void PedTasks::ClearSecondary()
		{
			OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(ped);
			IVSDKDotNet::Native::Natives::CLEAR_CHAR_SECONDARY_TASK(ped->Handle);
		}

		void PedTasks::PerformSequence(TaskSequence^ sequence)
		{
			if (sequence == nullptr)
				return;

			sequence->Perform(ped);
		}

	}
}