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

#pragma once
#pragma managed

namespace GTA
{

	// TODO: Continue with the cleanup
	//		 Figure something out with the metadata stuff

	CLASS_ATTRIBUTES
	public ref class ContentCache sealed
	{
	public:
		static const int MAX_FIRES = 100;
		
		static Dictionary<String^,System::Object^>^ metadata = gcnew Dictionary<String^,System::Object^>();

	public:

		// IV-SDK .NET ScriptHookDotNet Cache stuff
		static void AddEntity(GTA::base::Object^ obj);

		generic <class T>
		static T GetEntity(int handle, HandleType type);

		static void RemoveEntity(GTA::base::Object^ obj);
		static void RemoveEntity(int handle);

		// Ped
		static void AddPed(GTA::Ped^ p);
		static GTA::Ped^ GetPed(int Handle);
		//static void RemovePed(int Handle);
		static void RemovePed(GTA::Ped^ p);
		
		// Vehicle
		static void AddVehicle(GTA::Vehicle^ v);
		static GTA::Vehicle^ GetVehicle(int Handle);
		//static void RemoveVehicle(int Handle);
		//static void RemoveVehicle(GTA::Vehicle^ v);

		// Object
		static void AddObject(GTA::Object^ o);
		static GTA::Object^ GetObject(int Handle);
		//static void RemoveObject(int Handle);
		//static void RemoveObject(GTA::Object^ o);

		// Pickup
		static void AddPickup(GTA::Pickup^ p);
		static GTA::Pickup^ GetPickup(int Handle);
		//static void RemovePickup(int Handle);
		//static void RemovePickup(GTA::Pickup^ p);

		// Group
		static void AddGroup(GTA::Group^ g, bool CreatedByMe);
		static GTA::Group^ GetGroup(int Handle, bool CreatedByMe);
		//static void RemoveGroup(int Handle);
		static void RemoveGroup(GTA::Group^ g);

		// Blip
		static void AddBlip(GTA::Blip^ b, bool CreatedByMe);
		static GTA::Blip^ GetBlip(int Handle, bool CreatedByMe);
		//static void RemoveBlip(int Handle);
		//static void RemoveBlip(GTA::Blip^ b);

		// Camera
		static void AddCamera(GTA::Camera^ c, bool CreatedByMe);
		static GTA::Camera^ GetCamera(int Handle, bool CreatedByMe);
		//static void RemoveCamera(int Handle);
		//static void RemoveCamera(GTA::Camera^ c);

		// Fire
		static void AddFire(GTA::ScriptedFire^ f, bool CreatedByMe);
		static GTA::ScriptedFire^ GetFire(int Handle, bool CreatedByMe);
		//static void RemoveFire(int Handle);
		//static void RemoveFire(GTA::ScriptedFire^ f);
		//static void FireAmountCheck();

	public:

		static System::Object^ GetMetaData(int ItemHandle, String^ ValueName) {
			String^ id = ItemHandle.ToString() + "#" + ValueName->ToLower();
			if (!metadata->ContainsKey(id)) return nullptr;
			try {
				return metadata[id];
			} catch(...) {
				return nullptr;
			}
		}

		static void SetMetaData(int ItemHandle, String^ ValueName, System::Object^ Value) {
			String^ id = ItemHandle.ToString() + "#" + ValueName->ToLower();
			metadata[id] = Value;
		}

		static bool HasMetaData(int ItemHandle, String^ ValueName) {
			String^ id = ItemHandle.ToString() + "#" + ValueName->ToLower();
			return metadata->ContainsKey(id);
		}
		
	};

}