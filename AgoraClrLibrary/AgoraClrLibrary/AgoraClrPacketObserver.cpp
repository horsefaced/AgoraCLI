#include "stdafx.h"
#include "AgoraClrPacketObserver.h"

using namespace AgoraClrLibrary;

bool AgoraClrPacketObserver::onSendAudioPacket(Packet & packet)
{
	if (onSendAudioPacketEvent) return onSendAudioPacketEvent(packet);
	return true;
}

bool AgoraClrPacketObserver::onSendVideoPacket(Packet & packet)
{
	if (onSendVideoPacketEvent) return onSendVideoPacketEvent(packet);
	return true;
}

bool AgoraClrPacketObserver::onReceiveAudioPacket(Packet & packet)
{
	if (onReceiveAudioPacketEvent) return onReceiveAudioPacketEvent(packet);
	return true;
}

bool AgoraClrPacketObserver::onReceiveVideoPacket(Packet & packet)
{
	if (onReceiveVideoPacketEvent) return onReceiveVideoPacketEvent(packet);
	return true;
}
