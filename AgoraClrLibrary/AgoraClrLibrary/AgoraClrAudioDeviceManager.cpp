#include "stdafx.h"
#include "AgoraClrAudioDeviceManager.h"
#include "AgoraClrLibrary.h"

using namespace AgoraClrLibrary;
using namespace agora::rtc;

ClrAudioDeviceCollection::ClrAudioDeviceCollection(IAudioDeviceCollection* rawCollection):raw(rawCollection)
{

}

AgoraClrLibrary::ClrAudioDeviceCollection::~ClrAudioDeviceCollection()
{
	this->release();
	this->!ClrAudioDeviceCollection();
}

AgoraClrLibrary::ClrAudioDeviceCollection::!ClrAudioDeviceCollection()
{
}

int AgoraClrLibrary::ClrAudioDeviceCollection::getCount()
{
	return raw->getCount();
}

int AgoraClrLibrary::ClrAudioDeviceCollection::getDevice(int index, String ^% deviceName, String ^% deviceId)
{
	char deviceNameBuffer[MAX_DEVICE_ID_LENGTH] = { 0 }; char deviceIdBuffer[MAX_DEVICE_ID_LENGTH] = { 0 };
	int result = raw->getDevice(index, deviceNameBuffer, deviceIdBuffer);
	if (result != 0) return result;
	deviceName = gcnew String(deviceNameBuffer), deviceId = gcnew String(deviceIdBuffer);
	return result;
	//	return raw->getDevice(index, const_cast<char*>(MarshalString(deviceName).c_str()), const_cast<char*>(MarshalString(deviceId).c_str()));
}

int AgoraClrLibrary::ClrAudioDeviceCollection::setDevice(String ^ deviceId)
{
	return raw->setDevice(MarshalString(deviceId).c_str());
}

void AgoraClrLibrary::ClrAudioDeviceCollection::release()
{
	raw->release();
}

AgoraClrLibrary::AgoraClrAudioDeviceManager::AgoraClrAudioDeviceManager(AgoraClr^ engine)
{
	this->engine = engine;
}

ClrAudioDeviceCollection ^ AgoraClrLibrary::AgoraClrAudioDeviceManager::enumeratePlaybackDevices()
{
	AAudioDeviceManager manager(engine->getEngine());
	return gcnew ClrAudioDeviceCollection(manager->enumeratePlaybackDevices());
}

ClrAudioDeviceCollection ^ AgoraClrLibrary::AgoraClrAudioDeviceManager::enumerateRecordingDevices()
{
	AAudioDeviceManager manager(engine->getEngine());
	return gcnew ClrAudioDeviceCollection(manager->enumerateRecordingDevices());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setPlaybackDevice(String ^ deviceId)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->setPlaybackDevice(MarshalString(deviceId).c_str());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setRecordingDevice(String ^ deviceId)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->setRecordingDevice(MarshalString(deviceId).c_str());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setPlaybackDeviceVolume(int volume)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->setPlaybackDeviceVolume(volume);
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::getPlaybackDeviceVolume(int % volume)
{
	int v;
	AAudioDeviceManager manager(engine->getEngine());
	int result = manager->getPlaybackDeviceVolume(&v);
	volume = v;
	return result;
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setRecordingDeviceVolume(int volume)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->setRecordingDeviceVolume(volume);
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::getRecordingDeviceVolume(int % volume)
{
	int v, result;
	AAudioDeviceManager manager(engine->getEngine());
	result = manager->getRecordingDeviceVolume(&v);
	volume = v;
	return result;
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setPlaybackDeviceMute(bool mute)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->setPlaybackDeviceMute(mute);
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::getPlaybackDeviceMute(bool % mute)
{
	bool m;
	AAudioDeviceManager manager(engine->getEngine());
	int result = manager->getPlaybackDeviceMute(&m);
	mute = m;
	return result;
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setRecordingDeviceMute(bool mute)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->setRecordingDeviceMute(mute);
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::getRecordingDeviceMute(bool & mute)
{
	bool m;
	AAudioDeviceManager manager(engine->getEngine());
	int result = manager->getRecordingDeviceMute(&m);
	mute = m;
	return result;
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::startPlaybackDeviceTest(String ^ path)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->startPlaybackDeviceTest(MarshalString(path).c_str());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::stopPlaybackDeviceTest()
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->stopPlaybackDeviceTest();
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::startRecordingDeviceTest(int indicationInterval)
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->startRecordingDeviceTest(indicationInterval);
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::stopRecordingDeviceTest()
{
	AAudioDeviceManager manager(engine->getEngine());
	return manager->stopRecordingDeviceTest();
}


