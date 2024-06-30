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

#include "Console.h"
#include "Game.h"

#include "Player.h"
#include "ContentCache.h"
#include "Script.h"
#include "vGlobals.h"

#pragma managed

namespace GTA
{

	// - - - Constructor - - -
	static Game::Game()
	{
		try
		{
			Diagnostics::FileVersionInfo^ fi = Diagnostics::FileVersionInfo::GetVersionInfo(pExecutableFile);
			pVersion = (GTA::GameVersion)((fi->FileMajorPart << 24) | (fi->FileMinorPart << 16) | (fi->FileBuildPart << 8) | (fi->FilePrivatePart));
		}
		catch (...)
		{
			pVersion = GTA::GameVersion::UnknownVersion;
		}
		pGlobals = gcnew value::Globals();
	}

	// - - - Properties, Methods and Functions - - -
	GTA::GameEpisode Game::CurrentEpisode::get()
	{
		return (GTA::GameEpisode)IVSDKDotNet::Native::Natives::GET_CURRENT_EPISODE();
	}

	GTA::base::Console^ Game::Console::get()
	{
		return GTA::RemoteConsole::Instance;
	}
	GTA::base::Mouse^ Game::Mouse::get()
	{
		return NetHook::Mouse;
	}

	System::Drawing::Size Game::Resolution::get()
	{
		return IVSDKDotNet::IVGame::Resolution;
	}
	bool Game::isFullscreen::get()
	{
		return (Resolution == WinForms::SystemInformation::PrimaryMonitorSize);
	}

	bool Game::isMultiplayer::get()
	{
		return IVSDKDotNet::Native::Natives::NETWORK_IS_SESSION_STARTED();
	}
	bool Game::isRankedMultiplayer::get()
	{
		return IVSDKDotNet::Native::Natives::NETWORK_IS_GAME_RANKED();
	}

	GTA::NetworkMode Game::NetworkMode::get()
	{
		if (!isMultiplayer)
			return GTA::NetworkMode::Singleplayer;
		if (isRankedMultiplayer)
			return GTA::NetworkMode::MultiplayerLiveRanked;

		if (IVSDKDotNet::Native::Natives::IS_IN_LAN_MODE() == 1)
			return GTA::NetworkMode::MultiplayerLAN;
		else
			return GTA::NetworkMode::MultiplayerLive;
	}
	GTA::GameMode Game::MultiplayerGameMode::get()
	{
		return (GTA::GameMode)IVSDKDotNet::Native::Natives::NETWORK_GET_GAME_MODE();
	}

	int Game::PlayerCount::get()
	{
		return IVSDKDotNet::Native::Natives::GET_NUMBER_OF_PLAYERS();
	}
	bool Game::isPlayerActive(int PlayerID)
	{
		return IVSDKDotNet::Native::Natives::IS_NETWORK_PLAYER_ACTIVE(PlayerID);
	}
	GTA::Player^ Game::LocalPlayer::get()
	{
		return ContentCache::GetPlayer((int)IVSDKDotNet::Native::Natives::GET_PLAYER_ID());
	}
	array<GTA::Player^>^ Game::PlayerList::get()
	{
		if ((!isMultiplayer) || (PlayerCount == 1))
		{
			return gcnew array<GTA::Player^>(1)
			{
				LocalPlayer
			};
		}

		List<GTA::Player^>^ list = gcnew List<GTA::Player^>();

		for (int i = 0; i < 32; i++)
		{
			if (isPlayerActive(i))
				list->Add(ContentCache::GetPlayer(i));
		}

		return list->ToArray();
	}

	int Game::GameTime::get()
	{
		u32 g;
		IVSDKDotNet::Native::Natives::GET_GAME_TIMER(g);
		return g;
	}
	float Game::LastFrameTime::get()
	{
		f32 f;
		IVSDKDotNet::Native::Natives::GET_FRAME_TIME(f);
		return f;
	}
	float Game::FPS::get()
	{
		return (1.0f / LastFrameTime);
	}

	GTA::Camera^ Game::DefaultCamera::get()
	{
		int cam;
		IVSDKDotNet::Native::Natives::GET_GAME_CAM_CHILD(cam);
		return ContentCache::GetCamera(cam, false);
	}
	GTA::Camera^ Game::CurrentCamera::get()
	{
		int cam;
		IVSDKDotNet::Native::Natives::GET_ROOT_CAM(cam);
		return ContentCache::GetCamera(cam, false);
	}

	GTA::value::Globals^ Game::Globals::get()
	{
		return pGlobals;
	}

	//int Game::MaxWantedLevel::get(){
	//	u32 val = 0;
	//	Scripting::GetMaxWantedLevel(&val);
	//	return val;
	//}
	//void Game::MaxWantedLevel::set(int value){
	//	Scripting::SetMaxWantedLevel(value);
	//}

	GTA::RadioStation Game::RadioStation::get()
	{
		return (GTA::RadioStation)IVSDKDotNet::Native::Natives::GET_PLAYER_RADIO_STATION_INDEX();
	}
	void Game::RadioStation::set(GTA::RadioStation value)
	{
		IVSDKDotNet::Native::Natives::RETUNE_RADIO_TO_STATION_INDEX((u32)value);
	}

	bool Game::isMinigameInProgress::get()
	{
		return IVSDKDotNet::Native::Natives::IS_MINIGAME_IN_PROGRESS();
	}
	void Game::isMinigameInProgress::set(bool value)
	{
		IVSDKDotNet::Native::Natives::SET_MINIGAME_IN_PROGRESS(value);
	}

	void Game::AllowEmergencyServices::set(bool value)
	{
		IVSDKDotNet::Native::Natives::ALLOW_EMERGENCY_SERVICES(value);
	}
	void Game::DisableMaxAmmoLimit::set(bool value)
	{
		IVSDKDotNet::Native::Natives::ENABLE_MAX_AMMO_CAP(!value);
	}
	void Game::LoadAllPathNodes::set(bool value)
	{
		IVSDKDotNet::Native::Natives::LOAD_ALL_PATH_NODES(value);
	}
	void Game::MadDrivers::set(bool value)
	{
		IVSDKDotNet::Native::Natives::SWITCH_MAD_DRIVERS(value);
	}
	void Game::RadarZoom::set(float value)
	{
		IVSDKDotNet::Native::Natives::SET_RADAR_ZOOM(value);
	}
	void Game::TimeScale::set(float value)
	{
		IVSDKDotNet::Native::Natives::SET_TIME_SCALE(value);
	}
	void Game::WantedMultiplier::set(float value)
	{
		IVSDKDotNet::Native::Natives::SET_WANTED_MULTIPLIER(value);
	}

	Blip^ Game::GetWaypoint()
	{
		int bt = 8; //Scripting::BLIP_TYPE_COORD;

		for (int i = 0; i < 10; i++)
		{
			bt = i;

			int b = IVSDKDotNet::Native::Natives::GET_FIRST_BLIP_INFO_ID(bt);
			while (IVSDKDotNet::Native::Natives::DOES_BLIP_EXIST(b))
			{
				//if (Scripting::DoesBlipExist(b)) {
				if (IVSDKDotNet::Native::Natives::GET_BLIP_SPRITE(b) == 8)
				{ //BLIP_WAYPOINT
					//DisplayText(String::Concat( "Found at ", i.ToString() ));
					return ContentCache::GetBlip(b, false);
				}
				//}
				b = IVSDKDotNet::Native::Natives::GET_NEXT_BLIP_INFO_ID(bt);
			}
		}

		return nullptr;
	}

	bool Game::isKeyPressed(System::Windows::Forms::Keys Key)
	{
		return IVSDKDotNet::Helper::IsKeyPressedAsync(Key);
	}
	bool Game::isGameKeyPressed(GameKey Key)
	{
		if (int(Key) < 1000)
		{
			return IVSDKDotNet::Native::Natives::IS_CONTROL_PRESSED(0, (int)Key);
		}
		else
		{
			int x = 0; int y = 0;
			GetMovement(x, y);
			switch (Key)
			{
				case GameKey::MoveForward: return (y < -32);
				case GameKey::MoveBackward: return (y > 32);
				case GameKey::MoveLeft: return (x < -32);
				case GameKey::MoveRight: return (x > 32);
			}
			return false;
		}
	}
	void Game::GetMovement(int% x, int% y)
	{
		int x2 = 0; int y2 = 0;

		IVSDKDotNet::Native::Natives::GET_POSITION_OF_ANALOGUE_STICKS(0, x, y, x2, y2);

		if ((x == 0) && (y == 0))
			IVSDKDotNet::Native::Natives::GET_KEYBOARD_MOVE_INPUT(x, y);
	}
	GameKeyDirection Game::CurrentGameKeyDirection::get()
	{
		int x = 0; int y = 0;
		GetMovement(x, y);

		GameKeyDirection dir = GameKeyDirection::None;
		if (x < -32) dir = dir | GameKeyDirection::Left;
		if (x > 32) dir = dir | GameKeyDirection::Right;
		if (y < -32) dir = dir | GameKeyDirection::Forward;
		if (y > 32) dir = dir | GameKeyDirection::Backwards;
		return dir;
	}

	void Game::DisplayText(String^ Text, int Duration)
	{
		IVSDKDotNet::IVGame::ShowSubtitleMessage(Text, (u32)Duration);
	}
	void Game::DisplayText(String^ Text)
	{
		DisplayText(Text, 2000);
	}

	void Game::DoAutoSave()
	{
		IVSDKDotNet::Native::Natives::DO_AUTO_SAVE();
	}

	void Game::FadeScreenIn(int time)
	{
		FadeScreenIn(time, false);
	}
	void Game::FadeScreenIn(int time, bool WaitUntilDone)
	{
		IVSDKDotNet::Native::Natives::DO_SCREEN_FADE_IN(time);
		if (WaitUntilDone)
			WaitInCurrentScript(time);
	}

	void Game::FadeScreenOut(int time)
	{
		FadeScreenOut(time, false);
	}
	void Game::FadeScreenOut(int time, bool WaitUntilDone)
	{
		IVSDKDotNet::Native::Natives::DO_SCREEN_FADE_OUT(time);
		if (WaitUntilDone)
			WaitInCurrentScript(time);
	}

	void Game::ShowSaveMenu()
	{
		IVSDKDotNet::Native::Natives::ACTIVATE_SAVE_MENU();
	}

	int Game::GetIntegerStatistic(IntegerStatistic stat)
	{
		return IVSDKDotNet::Native::Natives::GET_INT_STAT((u32)stat);
	}
	void Game::SetIntegerStatistic(IntegerStatistic stat, int value)
	{
		IVSDKDotNet::Native::Natives::SET_INT_STAT((u32)stat, value);
	}
	float Game::GetFloatStatistic(FloatStatistic stat)
	{
		return IVSDKDotNet::Native::Natives::GET_FLOAT_STAT((u32)stat);
	}
	void Game::SetFloatStatistic(FloatStatistic stat, float value)
	{
		IVSDKDotNet::Native::Natives::SET_FLOAT_STAT((u32)stat, value);
	}

	bool Game::isScriptRunning(String^ ScriptName)
	{
		if (!IVSDKDotNet::Native::Natives::DOES_SCRIPT_EXIST(ScriptName))
			return false;
		if (IVSDKDotNet::Native::Natives::GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(ScriptName) <= 0)
			return false;
		return true;
	}

	Script^ Game::GetScript(Guid GUID)
	{
		System::Object^ obj = IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_GetScriptByGUID(GUID);

		if (!obj)
			return nullptr;

		return (Script^)obj;
	}
	Script^ Game::GetScript(String^ GUID)
	{
		return GetScript(Guid(GUID));
	}
	//void Game::SendScriptCommand(GTA::Script^ Script, String^ Command, ... array<System::Object^>^ Parameter) {
	//	if (NetHook::isPrimary)
	//		NetHook::ScriptDomain->SendScriptCommand(Script->GUID, Command, Paramater);
	//	else
	//		RemoteScriptDomain::Instance->SendScriptCommand(Script, Command, Parameter);
	//}
	//void Game::SendScriptCommand(Guid ScriptGUID, String^ Command, ... array<System::Object^>^ Parameter) {
	//	if (NetHook::isPrimary)
	//		NetHook::ScriptDomain->SendScriptCommand(ScriptGUID, Command, Parameter);
	//	else
	//		RemoteScriptDomain::Instance->SendScriptCommand(ScriptGUID, Command, Parameter);
	//}
	bool Game::isScriptRunning(Guid GUID)
	{
		return IVSDKDotNet::Manager::ManagerScript::GetInstance()->SHDN_IsScriptRunning(GUID);
	}
	//bool Game::isScriptRunning(String^ GUID) {
	//	return isScriptRunning(gcnew Guid(GUID));
	//}

	void Game::PlayAudioEvent(String^ EventName)
	{
		IVSDKDotNet::Native::Natives::PLAY_AUDIO_EVENT(EventName);
	}
	void Game::PlayGameSound(String^ SoundName)
	{
		IVSDKDotNet::Native::Natives::PLAY_SOUND(-1, SoundName);
	}
	void Game::PlayFrontendSound(String^ SoundName)
	{
		IVSDKDotNet::Native::Natives::PLAY_SOUND_FRONTEND(-1, SoundName);
	}
	void Game::PlayPhoneKeypadTone(int KeyNum, bool fast)
	{
		if ((KeyNum < 0) || (KeyNum > 11))
			return;

		u32 sid = IVSDKDotNet::Native::Natives::GET_SOUND_ID();

		if (fast)
			IVSDKDotNet::Native::Natives::PLAY_SOUND_FRONTEND(sid, "PHONE_PRESS_KEY_SPEED");
		else
			IVSDKDotNet::Native::Natives::PLAY_SOUND_FRONTEND(sid, "PHONE_PRESS_KEY");

		switch (KeyNum)
		{
			case 0:
				IVSDKDotNet::Native::Natives::SET_VARIABLE_ON_SOUND(sid, "Number", 10.0f);
				break;
			case 11:
				IVSDKDotNet::Native::Natives::SET_VARIABLE_ON_SOUND(sid, "Number", 11.0f);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				IVSDKDotNet::Native::Natives::SET_VARIABLE_ON_SOUND(sid, "Number", (float)(KeyNum - 1));
				break;
		}
		IVSDKDotNet::Native::Natives::RELEASE_SOUND_ID(sid);
	}
	void Game::PlayPhoneKeypadTone(int KeyNum)
	{
		PlayPhoneKeypadTone(KeyNum, false);
	}
	void Game::PlayCreditsMusic()
	{
		IVSDKDotNet::Native::Natives::START_END_CREDITS_MUSIC();
	}
	void Game::StopCreditsMusic()
	{
		IVSDKDotNet::Native::Natives::STOP_END_CREDITS_MUSIC();
	}
	void Game::PreviewRingtone(int RingtoneID)
	{
		IVSDKDotNet::Native::Natives::PREVIEW_RINGTONE(RingtoneID);
	}
	void Game::StopRingtonePreview()
	{
		IVSDKDotNet::Native::Natives::STOP_PREVIEW_RINGTONE();
	}

	void Game::SendChatMessage(String^ Text)
	{
		IVSDKDotNet::Native::Natives::NETWORK_SEND_TEXT_CHAT((int)IVSDKDotNet::Native::Natives::GET_PLAYER_ID(), Text);
	}

	void Game::Pause()
	{
		IVSDKDotNet::Native::Natives::PAUSE_GAME();
	}
	void Game::Unpause()
	{
		IVSDKDotNet::Native::Natives::UNPAUSE_GAME();
	}
	bool Game::Paused::get()
	{
		return IVSDKDotNet::Native::Natives::IS_PAUSE_MENU_ACTIVE();
	}
	void Game::Paused::set(bool value)
	{
		if (value)
			IVSDKDotNet::Native::Natives::PAUSE_GAME();
		else
			IVSDKDotNet::Native::Natives::UNPAUSE_GAME();
	}

	bool Game::CanWaitNow::get()
	{
		// TODO
		//Script^ scr = RemoteScriptDomain::Instance->CurrentScript;
		//if isNotNULL(scr) {
		//	return scr->CanWaitNow;
		//}
		//NetThread^ trd = RemoteScriptDomain::Instance->CurrentThread;
		//if isNotNULL(trd) {
		//	return trd->CanWaitNow;
		//}
		return false;
	}

	void Game::WaitInCurrentScript(int ms)
	{
		// TODO
		//Script^ scr = RemoteScriptDomain::Instance->CurrentScript;
		//if isNotNULL(scr) { 
		//	scr->Wait(ms);
		//	return;
		//}
		//NetThread^ trd = RemoteScriptDomain::Instance->CurrentThread;
		//if isNotNULL(trd) {
		//	return trd->Wait(ms);
		//}
	}

	int Game::GenerateHash(String^ input)
	{
		return IVSDKDotNet::Native::Natives::GET_HASH_KEY(input);
	}

	GTA::Vector3 Game::HeadingToDirection(float Heading)
	{
		return Helper::HeadingToDirection(Heading);
	}

	bool Game::Exists(base::Object^ o)
	{
		if isNULL(o)
			return false;
		return o->Exists();
	}

	void Game::Log(String^ Text)
	{
		IVSDKDotNet::IVGame::Console::Print(Text);
	}

}