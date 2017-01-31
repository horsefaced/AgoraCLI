#include "stdafx.h"
#include "AgoraClrPacketObserver.h"

using namespace AgoraClrLibrary;

bool AgoraClrLibrary::AgoraClrPacketObserver::onSendAudioPacket(Packet & packet)
{
	if (onSendAudioPacketEvent) return onSendAudioPacketEvent(packet);
	else return true;
}

bool AgoraClrLibrary::AgoraClrPacketObserver::onSendVideoPacket(Packet & packet)
{
	if (onSendVideoPacketEvent) return onSendVideoPacketEvent(packet);
	else return true;
}

bool AgoraClrLibrary::AgoraClrPacketObserver::onReceiveAudioPacket(Packet & packet)
{
	if (onReceiveAudioPacketEvent) return onReceiveAudioPacketEvent(packet);
	else return true;
}

bool AgoraClrLibrary::AgoraClrPacketObserver::onReceiveVideoPacket(Packet & packet)
{
	if (onReceiveVideoPacketEvent) return onReceiveVideoPacketEvent(packet);
	else return true;
}
