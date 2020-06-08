#include "stdafx.h"
#include "AgoraClrVideoDeviceManager.h"
#include "AgoraClrLibrary.h"
using namespace AgoraClrLibrary;

ClrVideoDeviceCollection::ClrVideoDeviceCollection(IVideoDeviceCollection * rawCollection):
	raw(rawCollection)
{
	
}

ClrVideoDeviceCollection::~ClrVideoDeviceCollection()
{
	this->release();
	this->!ClrVideoDeviceCollection();
}

ClrVideoDeviceCollection::!ClrVideoDeviceCollection()
{
	
}

int ClrVideoDeviceCollection::getCount()
{
	return raw->getCount();
}

int ClrVideoDeviceCollection::getDevice(int index, String ^% deviceName, String ^% deviceId)
{
	char deviceNameBuffer[MAX_DEVICE_ID_LENGTH] = { 0 }; 
	char deviceIdBuffer[MAX_DEVICE_ID_LENGTH] = { 0 };
	int result = raw->getDevice(index, deviceNameBuffer, deviceIdBuffer);
	if (result != 0) return result;
	deviceName = gcnew String(deviceNameBuffer), deviceId = gcnew String(deviceIdBuffer);
	return result;
	// return raw->getDevice(index, const_cast<char*>(MarshalString(deviceName).c_str()), const_cast<char*>(MarshalString(deviceId).c_str()));
}

int ClrVideoDeviceCollection::setDevice(String ^ deviceId)
{
	return raw->setDevice(const_cast<char*>(MarshalString(deviceId).c_str()));
}

void ClrVideoDeviceCollection::release()
{
	raw->release();
}

AgoraClrVideoDeviceManager::AgoraClrVideoDeviceManager(IRtcEngine* engine)
{
	this->engine = engine;
}

ClrVideoDeviceCollection ^ AgoraClrVideoDeviceManager::enumerateVideoDevices()
{
	AVideoDeviceManager manager(engine);
	return gcnew ClrVideoDeviceCollection(manager->enumerateVideoDevices());
}

int AgoraClrVideoDeviceManager::setDevice(String ^ deviceId)
{
	AVideoDeviceManager manager(engine);
	return manager->setDevice(MarshalString(deviceId).c_str());
}

int AgoraClrVideoDeviceManager::getDevice(String ^ deviceId)
{
	AVideoDeviceManager manager(engine);
	return manager->getDevice(const_cast<char*>(MarshalString(deviceId).c_str()));
}

int AgoraClrVideoDeviceManager::startDeviceTest(IntPtr hwnd)
{
	AVideoDeviceManager manager(engine);
	return manager->startDeviceTest(hwnd.ToPointer());
}

int AgoraClrVideoDeviceManager::stopDeviceTest()
{
	AVideoDeviceManager manager(engine);
	return manager->stopDeviceTest();
}
