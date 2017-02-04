#pragma once
#include "include\IAgoraRtcEngine.h"

using namespace agora::rtc;
using namespace System;

namespace AgoraClrLibrary {

	ref class AgoraClr;

	public ref class ClrVideoDeviceCollection
	{
	public:
		ClrVideoDeviceCollection(IVideoDeviceCollection* rawCollection);
		~ClrVideoDeviceCollection();
		!ClrVideoDeviceCollection();

		int getCount();
		int getDevice(int index, String^ deviceName, String^ deviceId);
		int setDevice(String^ deviceId);
		void release();
	private:
		IVideoDeviceCollection* raw;
	};

	public ref class AgoraClrVideoDeviceManager
	{
	public:
		AgoraClrVideoDeviceManager(AgoraClr^ engine);
		ClrVideoDeviceCollection^ enumerateVideoDevices();
		int setDevice(String^ deviceId);
		int getDevice(String^ deviceId);
		int startDeviceTest(IntPtr hwnd);
		int stopDeviceTest();

	private:
		AgoraClr^ engine;
	};

}

