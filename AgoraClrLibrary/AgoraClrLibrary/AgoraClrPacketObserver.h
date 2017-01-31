#pragma once
#include "include\IAgoraRtcEngine.h"
using namespace agora::rtc;

namespace AgoraClrLibrary {

	typedef bool(__stdcall * PFOnSendAudioPacket)(IPacketObserver::Packet & packet);
	typedef bool(__stdcall * PFOnSendVideoPacket)(IPacketObserver::Packet & packet);
	typedef bool(__stdcall * PFOnReceiveAudioPacket)(IPacketObserver::Packet & packet);
	typedef bool(__stdcall * PFOnReceiveVideoPacket)(IPacketObserver::Packet & packet);	

	//Native delegate
	delegate bool NativeOnSendAudioPacketDelegate(IPacketObserver::Packet & packet);
	delegate bool NativeOnSendVideoPacketDelegate(IPacketObserver::Packet & packet);
	delegate bool NativeOnReceiveAudioPacketDelegate(IPacketObserver::Packet & packet);
	delegate bool NativeOnReceiveVideoPacketDelegate(IPacketObserver::Packet & packet);

	public class AgoraClrPacketObserver : public IPacketObserver {
	public:
		PFOnSendAudioPacket onSendAudioPacketEvent = 0;
		PFOnSendVideoPacket onSendVideoPacketEvent = 0;
		PFOnReceiveAudioPacket onReceiveAudioPacketEvent = 0;
		PFOnReceiveVideoPacket onReceiveVideoPacketEvent = 0;

		// Inherited via IPacketObserver
		virtual bool onSendAudioPacket(Packet & packet) override;
		virtual bool onSendVideoPacket(Packet & packet) override;
		virtual bool onReceiveAudioPacket(Packet & packet) override;
		virtual bool onReceiveVideoPacket(Packet & packet) override;
	};
}

