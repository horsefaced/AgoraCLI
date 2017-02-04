#pragma once
#include "include\IAgoraRtcEngine.h"

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
		int getDevice(int index, String^ deviceName, String^ deviceId);
		int setDevice(String^ deviceId);
		void release();
	private:
		IAudioDeviceCollection* raw;
	};

	public ref class AgoraClrAudioDeviceManager
	{
	public:
		AgoraClrAudioDeviceManager(AgoraClr^ engine);

		ClrAudioDeviceCollection^ enumeratePlaybackDevices();
		ClrAudioDeviceCollection^ enumerateRecordingDevices();
		int setPlaybackDevice(String^ deviceId);
		int setRecordingDevice(String^ deviceId);
		int startPlaybackDeviceTest(String^ path);
		int stopPlaybackDeviceTest();
		int startRecordingDeviceTest(int indicationInterval);
		int stopRecordingDeviceTest();
	private:
		AgoraClr^ engine;

	};

}