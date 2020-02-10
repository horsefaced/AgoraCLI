#pragma once
#include "..\..\agorasdk\include\IAgoraRtcEngine.h"

using namespace agora::rtc;
using namespace System;

namespace AgoraClrLibrary {	

	ref class AgoraClr;

	public ref class ClrAudioDeviceCollection {
	public:
		ClrAudioDeviceCollection(IAudioDeviceCollection* rawCollection);
		~ClrAudioDeviceCollection();
		!ClrAudioDeviceCollection();

		int getCount();
		int getDevice(int index, String^% deviceName, String^% deviceId);
		int setDevice(String^ deviceId);
		int setApplicationVolume(int volume);
		int getApplicationVolume(int% volume);
		int setApplicationMute(bool mute);
		int isApplicationMute(bool% mute);
	private:
		IAudioDeviceCollection* raw;

		void release();
	};

	public ref class AgoraClrAudioDeviceManager
	{
	public:
		AgoraClrAudioDeviceManager(IRtcEngine* engine);

		ClrAudioDeviceCollection^ enumeratePlaybackDevices();
		ClrAudioDeviceCollection^ enumerateRecordingDevices();

		int setPlaybackDevice(String^ deviceId);
		int setRecordingDevice(String^ deviceId);

		int startPlaybackDeviceTest(String^ path);
		int stopPlaybackDeviceTest();

		int setPlaybackDeviceVolume(int volume);
		int getPlaybackDeviceVolume(int %volume);

		int setRecordingDeviceVolume(int volume);
		int getRecordingDeviceVolume(int %volume);

		int setPlaybackDeviceMute(bool mute);
		int getPlaybackDeviceMute(bool% mute);

		int setRecordingDeviceMute(bool mute);
		int getRecordingDeviceMute(bool& mute);

		int startRecordingDeviceTest(int indicationInterval);
		int stopRecordingDeviceTest();

		int getPlaybackDevice(String^% deviceId);
		int getPlaybackDeviceInfo(String^% deviceId, String^% deviceName);

		int getRecordingDevice(String^% deviceId);
		int getRecordingDeviceInfo(String^% deviceId, String^% deviceName);

		int startAudioDeviceLoopbackTest(int interval);
		int stopAudioDeviceLoopbackTest();
	private:
		IRtcEngine* engine;

	};

}