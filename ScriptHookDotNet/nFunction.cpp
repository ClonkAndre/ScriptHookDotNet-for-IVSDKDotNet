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

#include "nFunction.h"

#include "nParameter.h"
#include "nTemplate.h"

#pragma managed

namespace GTA
{
	namespace Native
	{

		generic <typename T>
		T Function::Call(String^ Name, ... array<Parameter^>^ Arguments)
		{
			try
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
							{
								base::HandleObject^ handleObj = safe_cast<base::HandleObject^>(param->Value);
								args[i] = handleObj->Handle;
							}
							break;

						//case vtype::var_model:
						//	{

						//	}
						//	break;
						//case vtype::var_player:
						//	{

						//	}
						//	break;
						//case vtype::var_pickup:
						//	{

						//	}
						//	break;
	
						//case vtype::var_vector3:
						//	{

						//	}
						//	break;

						default:
							{
								args[i] = param->Value;
							}
							break;
					}


				}

				// Result
				T r = IVSDKDotNet::Native::Function::Call<T>(Name, args);

				// Set new argument values if they are pointers
				for (int i = 0; i < args->Length; i++)
				{
					Parameter^ param = Arguments[i];

					if (param->GetType() == Pointer::typeid)
						Arguments[i]->SetValue(args[i]);
				}

				return r;
			}
			catch (...)
			{
				return T();
			}
		}

		void Function::Call(String^ Name, ... array<Parameter^>^ Arguments)
		{
			Call<Object^>(Name, Arguments);
		}

	}
}