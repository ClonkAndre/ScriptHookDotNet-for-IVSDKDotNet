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

#pragma once

#ifdef DEBUG
#define VERBOSE	IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_VerboseLoggingEnabled()
#define VERBOSENATIVECALL IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_NativeCallLoggingEnabled()
#else
#define VERBOSE false
#define VERBOSENATIVECALL false
#endif

namespace GTA
{
	value class Vector2;
	value class Vector3;
	value class Vector4;
	value class Matrix;
	value class Quaternion;
	value class Model;
	value class Room;
	value class ColorIndex;

	ref class SkinTemplate;
	ref class AnimationSet;

	ref class RemoteScriptDomain;
	ref class Script;

	ref class ContentCache;
	ref class Game;
	ref class Player;
	ref class Ped;
	ref class Vehicle;
	ref class Group;
	ref class World;
	ref class Blip;
	ref class Camera;
	ref class Object;
	ref class Pickup;
	ref class ScriptedFire;

	ref class TaskSequence;
	ref class Graphics;
	ref class Font;
	ref class Texture;
	ref class PedCollection;
	ref class SettingsFile;

	namespace base
	{
		ref class Object;
		ref class HandleObject;
		ref class Console;
		ref class Mouse;

		generic <typename T>
		ref class BaseCollection;
		generic <typename T>
		ref class ReadOnlyCollection;
		generic <typename T>
		ref class Collection;
	}
	namespace Forms
	{
		ref class Button;
		ref class Checkbox;
		ref class Control;
		ref class Form;
		ref class FormHost;
		ref class Keybox;
		ref class Label;
		ref class Mouse;
		ref class Scrollbar;
		ref class Textbox;
	}
	namespace Multiplayer
	{
		ref class Host;
		ref class Team;
	}
	namespace Native
	{
		ref class Parameter;
		ref class Pointer;
		ref class Function;
		ref class Template;
	}
	namespace value
	{
		ref class DynamicMetadata;
		ref class Euphoria;
		ref class Globals;
		ref class PedAnimation;
		ref class PedSkin;
		ref class PedComponent;
		ref class PedComponentCollection;
		ref class PedTasks;
		ref class PlayerSkin;
		ref class Resources;
		ref class Tasks;
		ref class VehicleDoor;
		ref class VehicleExtra;
		ref class Weapon;
		ref class WeaponCollection;
	}
}

typedef unsigned int u32;
typedef int i32;

typedef float f32;

#define Vector3ToGTAVector3(vec) GTA::Vector3(vec.X, vec.Y, vec.Z)
#define GTAVector3ToVector3(vec) System::Numerics::Vector3(vec.X, vec.Y, vec.Z)

#define Vector2ToGTAVector2(vec) GTA::Vector2(vec.X, vec.Y)
#define GTAVector2ToVector2(vec) System::Numerics::Vector2(vec.X, vec.Y)

#define NotImplementedYet(msg) throw gcnew System::NotImplementedException(msg)

#define isNULL(var) (System::Object::ReferenceEquals(var,nullptr))
#define isNotNULL(var) (!System::Object::ReferenceEquals(var,nullptr))

#define GetNameOfCallingScript() System::Reflection::Assembly::GetCallingAssembly()->GetName()->Name->Replace(".net", "")
#define GetCallingScript() IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_GetScriptByName(GetNameOfCallingScript())
#define LateInitializeScript(obj, assemblyFullPath) IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_LateInitializeScript(GetType()->FullName, obj, assemblyFullPath)

#define GetCurrentScript(ofEvent) (GTA::Script^)IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_GetCurrentScript((int)ofEvent);

#define NON_EXISTING_MESSAGE(object) NonExistingObjectException::DEFAULT_MESSAGE + " (" + object->GetType()->Name + " " + object->UID.ToString() + ")" 
//#ifdef DEBUG
//#define NON_EXISTING_MESSAGE(object) NonExistingObjectException::DEFAULT_MESSAGE + " (" + object->GetType()->Name + " " + object->UID.ToString() + ")" 
//#else
//#define NON_EXISTING_MESSAGE(object)
//#endif

// Non existing checks (The NO_RETURN defines mean that this define does not return a value! It will still return out of the method)
#define OBJECT_NON_EXISTING_CHECK(object,returns) if (!object->Exists()) { throw gcnew NonExistingObjectException( NON_EXISTING_MESSAGE(object) ); return returns; }
#define OBJECT_NON_EXISTING_CHECK_ALLOW_NULL(object,returns) if ((object->Handle != 0) && (!object->Exists())) { throw gcnew NonExistingObjectException( NON_EXISTING_MESSAGE(object) ); return returns; }
#define OBJECT_NON_EXISTING_CHECK_RELAXED(object,returns) if (!object->Exists()) return returns

#define OBJECT_NON_EXISTING_CHECK_NO_RETURN(object) if (!object->Exists()) { throw gcnew NonExistingObjectException( NON_EXISTING_MESSAGE(object) ); return; }
#define OBJECT_NON_EXISTING_CHECK_ALLOW_NULL_NO_RETURN(object) if ((object->Handle != 0) && (!object->Exists())) { throw gcnew NonExistingObjectException( NON_EXISTING_MESSAGE(object) ); return; }
#define OBJECT_NON_EXISTING_CHECK_RELAXED_NO_RETURN(object) if (!object->Exists()) return

#define NON_EXISTING_CHECK(returns) OBJECT_NON_EXISTING_CHECK(this,returns)
#define NON_EXISTING_CHECK_RELAXED(returns) OBJECT_NON_EXISTING_CHECK_RELAXED(this,returns)

#define NON_EXISTING_CHECK_NO_RETURN() OBJECT_NON_EXISTING_CHECK_NO_RETURN(this)
#define NON_EXISTING_CHECK_RELAXED_NO_RETURN() OBJECT_NON_EXISTING_CHECK_RELAXED_NO_RETURN(this)

#define V3_NaN Vector3(float::NaN,float::NaN,float::NaN)
#define V3_NULL Vector3()

#define CLASS_ATTRIBUTES [System::Diagnostics::DebuggerNonUserCode()]

// Logging
#ifdef DEBUG

#define VLOG(text) if (VERBOSE) GTA::NetHook::Log(text)
#define LogCount(cache, name, amount) if (VERBOSE && (cache->Count % amount) == 0) GTA::NetHook::Log("WARNING! " + name + " count: " + cache->Count.ToString());

#define WHILE_LOG(sender) if (VERBOSE) GTA::NetHook::Log("IN WHILE LOOP: " + sender)

#define WRITE_TO_DEBUG_OUTPUT(text) if (VERBOSE && System::Diagnostics::Debugger::IsAttached) System::Diagnostics::Debugger::Log(0, "ScriptHookDotNet", text + "\n")
#define LOG_NATIVE_CALL_TO_DEBUG_OUTPUT(text) if (VERBOSENATIVECALL && System::Diagnostics::Debugger::IsAttached) System::Diagnostics::Debugger::Log(0, "ScriptHookDotNet Native Call", text + "\n")
#define LOG_STACK_TRACE() if (VERBOSE) WRITE_TO_DEBUG_OUTPUT((gcnew System::Diagnostics::StackTrace())->ToString())

#else

// nothing to see here
#define VLOG(text) 
#define LogCount(cache, name, amount)

#define WHILE_LOG(sender)

#define WRITE_TO_DEBUG_OUTPUT(text)
#define LOG_NATIVE_CALL_TO_DEBUG_OUTPUT(text)
#define LOG_STACK_TRACE()

#endif

template <typename R, typename T>
inline R force_cast(T value)
{
	return *reinterpret_cast<R*>(&value);
}

#define WinForms System::Windows::Forms

namespace GTA
{
	using namespace System;
	using namespace System::IO;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::InteropServices;
}