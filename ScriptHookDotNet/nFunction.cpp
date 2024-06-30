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

#include "nFunction.h"

#include "nParameter.h"
#include "nTemplate.h"

//#include "sModel.h"
#include "Object.h"
#include "Ped.h"
#include "Vehicle.h"
#include "Player.h"

#pragma managed

namespace GTA
{
	namespace Native
	{

		System::Object^ Function::ConvertReturnTypeToExpectedType(System::Object^ returnValue, Type^ expectedType)
		{
			if (!returnValue)
				return nullptr;

			// Get type of value returned by the called native function
			Type^ returnValueType = returnValue->GetType();

			LOG_NATIVE_CALL_TO_DEBUG_OUTPUT(String::Format("Trying to convert type '{0}' to expected type '{1}'", returnValueType, expectedType));

			// Try convert returned int32 value to expected uint32 value
			if (returnValueType == System::Int32::typeid && expectedType == System::UInt32::typeid)
				return Convert::ToUInt32(returnValue);

			// Try convert returned uint32 value to expected int32 value
			if (returnValueType == System::UInt32::typeid && expectedType == System::Int32::typeid)
				return Convert::ToInt32(returnValue);

			// Try convert returned boolean value to expected int32 value
			if (returnValueType == System::Boolean::typeid && expectedType == System::Int32::typeid)
				return Convert::ToInt32(returnValue);

			// Try convert returned type value to expected bool value (If returned type is a numeric type)
			if (IVSDKDotNet::Helper::IsNumericType(returnValueType) && expectedType == System::Boolean::typeid)
				return Convert::ToBoolean(returnValue);

			// Try convert returned int32 value to expected GTA.Object value
			if (returnValueType == System::Int32::typeid && expectedType == GTA::Object::typeid)
				return gcnew GTA::Object(Convert::ToInt32(returnValue));

			// Try convert returned int32 value to expected GTA.Ped value
			if (returnValueType == System::Int32::typeid && expectedType == GTA::Ped::typeid)
				return gcnew GTA::Ped(Convert::ToInt32(returnValue));

			// Try convert returned int32 value to expected GTA.Vehicle value
			if (returnValueType == System::Int32::typeid && expectedType == GTA::Vehicle::typeid)
				return gcnew GTA::Vehicle(Convert::ToInt32(returnValue));

			// TODO: Add more if needed

			return returnValue;
		}

		generic <typename T>
		T Function::Call(String^ Name, ... array<Parameter^>^ Arguments)
		{
			// Copy arguments to object array and convert them if necessary
			array<System::Object^>^ args = gcnew array<System::Object^>(Arguments->Length);

			for (int i = 0; i < args->Length; i++)
			{
				Parameter^ param = Arguments[i];

				// If parameter is a pointer, set the object at index X to nullptr
				if (param->GetType() == Pointer::typeid)
				{
					args[i] = nullptr;
					continue;
				}

				// Check if object at index X has to be converted
				vtype argType = Parameter::GetType(param->Value->GetType());

				switch (argType)
				{

					// Handle objects
					case vtype::var_ped:
					case vtype::var_vehicle:
					case vtype::var_group:
					case vtype::var_blip:
					case vtype::var_camera:
					case vtype::var_object:
					case vtype::var_pickup:
						{
							base::HandleObject^ handleObj = safe_cast<base::HandleObject^>(param->Value);
							args[i] = handleObj->Handle;
						}
						break;

					case vtype::var_player:
						{
							Player^ playerObj = safe_cast<Player^>(param->Value);
							args[i] = playerObj->ID;
						}
						break;
	
					// Value objects
					case vtype::var_model:
						{
						Model modelObj = safe_cast<Model>(param->Value);
						args[i] = Convert::ToInt32(modelObj.Hash);
						}
						break;
					case vtype::var_vector3:
						{
							Vector3 pos = safe_cast<Vector3>(param->Value);
							args[i] = GTAVector3ToVector3(pos);
						}
						break;

					// Basic types
					case vtype::var_int:
						{
						args[i] = Convert::ToInt32(param->Value);
						}
						break;
					case vtype::var_float:
						{
						args[i] = Convert::ToSingle(param->Value);
						}
						break;
					case vtype::var_bool:
						{
						args[i] = Convert::ToBoolean(param->Value);
						}
						break;

					case vtype::var_string:
						{
						args[i] = param->Value->ToString();
						}
						break;

					default:
						{
							args[i] = param->Value;
						}
						break;
				}
			}

			// Some hacks for mods that pass some weird arguments to native functions...
			if (Name == "SET_VOICE_ID_FROM_HEAD_COMPONENT")
			{

				// The "DialogueSystem" mod is trying to call the "SET_VOICE_ID_FROM_HEAD_COMPONENT" native passing a string to the "VoiceId" parameter but the native wants an integer?
				// After checking all the sco scripts, none of the scripts using this native pass in a integer instead of a string...
				// Function.Call("SET_VOICE_ID_FROM_HEAD_COMPONENT", ped, "PED_COMPONENT_HEAD", 1);
				if (args[1]->GetType() == System::String::typeid)
					args[1] = 0; // Just default to 0...

			}

			// Result
			LOG_NATIVE_CALL_TO_DEBUG_OUTPUT(String::Format("About to call native function '{0}'", Name));
			System::Object^ r = IVSDKDotNet::Native::Function::Call<System::Object^>(Name, args);
			LOG_NATIVE_CALL_TO_DEBUG_OUTPUT(String::Format("Just called the native function '{0}'", Name));

			// Set new argument values if they are pointers
			for (int i = 0; i < args->Length; i++)
			{
				Parameter^ param = Arguments[i];

				if (param->GetType() == Pointer::typeid)
					Arguments[i]->Set(param->TargetType, args[i]);
			}

			if (!r)
				return T();

			return (T)ConvertReturnTypeToExpectedType(r, T::typeid);
		}

		void Function::Call(String^ Name, ... array<Parameter^>^ Arguments)
		{
			Call<System::Object^>(Name, Arguments);
		}

	}
}