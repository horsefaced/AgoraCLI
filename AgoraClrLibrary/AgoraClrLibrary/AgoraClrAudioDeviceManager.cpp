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
	throw gcnew System::NotImplementedException();
}

int AgoraClrLibrary::ClrAudioDeviceCollection::getCount()
{
	return raw->getCount();
}

int AgoraClrLibrary::ClrAudioDeviceCollection::getDevice(int index, String ^ deviceName, String ^ deviceId)
{
	return raw->getDevice(index, const_cast<char*>(MarshalString(deviceName).c_str()), const_cast<char*>(MarshalString(deviceId).c_str()));
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
	AAudioDeviceManager manager(*(engine->getEngine()));
	return gcnew ClrAudioDeviceCollection(manager->enumeratePlaybackDevices());
}

ClrAudioDeviceCollection ^ AgoraClrLibrary::AgoraClrAudioDeviceManager::enumerateRecordingDevices()
{
	AAudioDeviceManager manager(*(engine->getEngine()));
	return gcnew ClrAudioDeviceCollection(manager->enumerateRecordingDevices());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setPlaybackDevice(String ^ deviceId)
{
	AAudioDeviceManager manager(*(engine->getEngine()));
	return manager->setPlaybackDevice(MarshalString(deviceId).c_str());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::setRecordingDevice(String ^ deviceId)
{
	AAudioDeviceManager manager(*(engine->getEngine()));
	return manager->setRecordingDevice(MarshalString(deviceId).c_str());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::startPlaybackDeviceTest(String ^ path)
{
	AAudioDeviceManager manager(*(engine->getEngine()));
	return manager->startPlaybackDeviceTest(MarshalString(path).c_str());
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::stopPlaybackDeviceTest()
{
	AAudioDeviceManager manager(*(engine->getEngine()));
	return manager->stopPlaybackDeviceTest();
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::startRecordingDeviceTest(int indicationInterval)
{
	AAudioDeviceManager manager(*(engine->getEngine()));
	return manager->startRecordingDeviceTest(indicationInterval);
}

int AgoraClrLibrary::AgoraClrAudioDeviceManager::stopRecordingDeviceTest()
{
	AAudioDeviceManager manager(*(engine->getEngine()));
	return manager->stopRecordingDeviceTest();
}

