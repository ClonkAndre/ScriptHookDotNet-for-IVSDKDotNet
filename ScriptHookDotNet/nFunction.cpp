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

			// Try convert returned int32 value to expected uint32 value
			if (returnValueType == System::Int32::typeid && expectedType == System::UInt32::typeid)
				return Convert::ToUInt32(returnValue);

			// Try convert returned uint32 value to expected int32 value
			if (returnValueType == System::UInt32::typeid && expectedType == System::Int32::typeid)
				return Convert::ToInt32(returnValue);

			// Try convert returned type value to expected bool value (If returned type is a numeric type)
			if (IVSDKDotNet::Helper::IsNumericType(returnValueType) && expectedType == System::Boolean::typeid)
				return Convert::ToBoolean(returnValue);

			// TODO: Add more if needed

			return returnValue;
		}

		generic <typename T>
		T Function::Call(String^ Name, ... array<Parameter^>^ Arguments)
		{
			// Copy arguments to object array and convert them if necessary
			array<Object^>^ args = gcnew array<Object^>(Arguments->Length);

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

			// Result
			System::Object^ r = IVSDKDotNet::Native::Function::Call<System::Object^>(Name, args);

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