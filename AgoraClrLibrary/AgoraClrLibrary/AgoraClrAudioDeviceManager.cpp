#include "stdafx.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrLibrary.h"

using namespace AgoraClrLibrary;
using namespace agora::rtc;

ClrAudioDeviceCollection::ClrAudioDeviceCollection(IAudioDeviceCollection* rawCollection):
	raw(rawCollection)
{

}

ClrAudioDeviceCollection::~ClrAudioDeviceCollection()
{
	this->release();
	this->!ClrAudioDeviceCollection();
}

ClrAudioDeviceCollection::!ClrAudioDeviceCollection()
{
}

int ClrAudioDeviceCollection::getCount()
{
	return raw->getCount();
}

int ClrAudioDeviceCollection::getDevice(int index, String ^% deviceName, String ^% deviceId)
{
	char deviceNameBuffer[MAX_DEVICE_ID_LENGTH] = { 0 }; 
	char deviceIdBuffer[MAX_DEVICE_ID_LENGTH] = { 0 };
	int result = raw->getDevice(index, deviceNameBuffer, deviceIdBuffer);
	if (result != 0) return result;
	deviceName = gcnew String(deviceNameBuffer), deviceId = gcnew String(deviceIdBuffer);
	return result;
	//	return raw->getDevice(index, const_cast<char*>(MarshalString(deviceName).c_str()), const_cast<char*>(MarshalString(deviceId).c_str()));
}

int ClrAudioDeviceCollection::setDevice(String ^ deviceId)
{
	return raw->setDevice(MarshalString(deviceId).c_str());
}

int ClrAudioDeviceCollection::setApplicationVolume(int volume)
{
	return raw->setApplicationVolume(volume);
}

int ClrAudioDeviceCollection::getApplicationVolume(int% volume)
{
	int vol;
	int result = raw->getApplicationVolume(vol);
	volume = vol;
	return result;
}

int ClrAudioDeviceCollection::setApplicationMute(bool mute)
{
	return raw->setApplicationMute(mute);
}

int ClrAudioDeviceCollection::isApplicationMute(bool% mute)
{
	bool mu;
	int result = raw->isApplicationMute(mu);
	mute = mu;
	return result;
}

void ClrAudioDeviceCollection::release()
{
	raw->release();
}

AgoraClrAudioDeviceManager::AgoraClrAudioDeviceManager(IRtcEngine* engine)
{
	this->engine = engine;
}

ClrAudioDeviceCollection ^ AgoraClrAudioDeviceManager::enumeratePlaybackDevices()
{
	AAudioDeviceManager manager(engine);
	return gcnew ClrAudioDeviceCollection(manager->enumeratePlaybackDevices());
}

ClrAudioDeviceCollection ^ AgoraClrAudioDeviceManager::enumerateRecordingDevices()
{
	AAudioDeviceManager manager(engine);
	return gcnew ClrAudioDeviceCollection(manager->enumerateRecordingDevices());
}

int AgoraClrAudioDeviceManager::setPlaybackDevice(String ^ deviceId)
{
	AAudioDeviceManager manager(engine);
	return manager->setPlaybackDevice(MarshalString(deviceId).c_str());
}

int AgoraClrAudioDeviceManager::setRecordingDevice(String ^ deviceId)
{
	AAudioDeviceManager manager(engine);
	return manager->setRecordingDevice(MarshalString(deviceId).c_str());
}

int AgoraClrAudioDeviceManager::setPlaybackDeviceVolume(int volume)
{
	AAudioDeviceManager manager(engine);
	return manager->setPlaybackDeviceVolume(volume);
}

int AgoraClrAudioDeviceManager::getPlaybackDeviceVolume(int % volume)
{
	int v;
	AAudioDeviceManager manager(engine);
	int result = manager->getPlaybackDeviceVolume(&v);
	volume = v;
	return result;
}

int AgoraClrAudioDeviceManager::setRecordingDeviceVolume(int volume)
{
	AAudioDeviceManager manager(engine);
	return manager->setRecordingDeviceVolume(volume);
}

int AgoraClrAudioDeviceManager::getRecordingDeviceVolume(int % volume)
{
	int v, result;
	AAudioDeviceManager manager(engine);
	result = manager->getRecordingDeviceVolume(&v);
	volume = v;
	return result;
}

int AgoraClrAudioDeviceManager::setPlaybackDeviceMute(bool mute)
{
	AAudioDeviceManager manager(engine);
	return manager->setPlaybackDeviceMute(mute);
}

int AgoraClrAudioDeviceManager::getPlaybackDeviceMute(bool % mute)
{
	bool m;
	AAudioDeviceManager manager(engine);
	int result = manager->getPlaybackDeviceMute(&m);
	mute = m;
	return result;
}

int AgoraClrAudioDeviceManager::setRecordingDeviceMute(bool mute)
{
	AAudioDeviceManager manager(engine);
	return manager->setRecordingDeviceMute(mute);
}

int AgoraClrAudioDeviceManager::getRecordingDeviceMute(bool & mute)
{
	bool m;
	AAudioDeviceManager manager(engine);
	int result = manager->getRecordingDeviceMute(&m);
	mute = m;
	return result;
}

int AgoraClrAudioDeviceManager::startPlaybackDeviceTest(String ^ path)
{
	AAudioDeviceManager manager(engine);
	return manager->startPlaybackDeviceTest(MarshalString(path).c_str());
}

int AgoraClrAudioDeviceManager::stopPlaybackDeviceTest()
{
	AAudioDeviceManager manager(engine);
	return manager->stopPlaybackDeviceTest();
}

int AgoraClrAudioDeviceManager::startRecordingDeviceTest(int indicationInterval)
{
	AAudioDeviceManager manager(engine);
	return manager->startRecordingDeviceTest(indicationInterval);
}

int AgoraClrAudioDeviceManager::stopRecordingDeviceTest()
{
	AAudioDeviceManager manager(engine);
	return manager->stopRecordingDeviceTest();
}

int AgoraClrAudioDeviceManager::getPlaybackDevice(String^% deviceId)
{
	AAudioDeviceManager manager(engine);
	char tmp[MAX_DEVICE_ID_LENGTH];
	int result = manager->getPlaybackDevice(tmp);
	if (result == 0) deviceId = gcnew String(tmp);
	else deviceId = nullptr;
	return result;
}

int AgoraClrAudioDeviceManager::getPlaybackDeviceInfo(String^% deviceId, String^% deviceName)
{
	AAudioDeviceManager manager(engine);
	char tmpId[MAX_DEVICE_ID_LENGTH];
	char tmpName[MAX_DEVICE_ID_LENGTH];
	int result = manager->getPlaybackDeviceInfo(tmpId, tmpName);
	if (result == 0) {
		deviceId = gcnew String(tmpId);
		deviceName = gcnew String(tmpName);
	}
	else {
		deviceId = nullptr;
		deviceName = nullptr;
	}
	return result;
}

int AgoraClrAudioDeviceManager::getRecordingDevice(String^% deviceId)
{
	AAudioDeviceManager manager(engine);
	char tmpId[MAX_DEVICE_ID_LENGTH];
	int result = manager->getRecordingDevice(tmpId);
	if (result == 0) deviceId = gcnew String(tmpId);
	else deviceId = nullptr;
	return result;
}

int AgoraClrAudioDeviceManager::getRecordingDeviceInfo(String^% deviceId, String^% deviceName)
{
	AAudioDeviceManager manager(engine);
	char tmpId[MAX_DEVICE_ID_LENGTH];
	char tmpName[MAX_DEVICE_ID_LENGTH];
	int result = manager->getRecordingDeviceInfo(tmpId, tmpName);
	if (result == 0) {
		deviceId = gcnew String(tmpId);
		deviceName = gcnew String(tmpName);
	}
	else {
		deviceId = nullptr;
		deviceName = nullptr;
	}
	return result;
}

int AgoraClrAudioDeviceManager::startAudioDeviceLoopbackTest(int interval)
{
	AAudioDeviceManager manager(engine);
	return manager->startAudioDeviceLoopbackTest(interval);
}

int AgoraClrAudioDeviceManager::stopAudioDeviceLoopbackTest()
{
	AAudioDeviceManager manager(engine);
	return manager->stopAudioDeviceLoopbackTest();
}


