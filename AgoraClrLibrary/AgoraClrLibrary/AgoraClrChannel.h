#pragma once

#include "../../agorasdk/include/IAgoraRtcChannel.h"
#include "AgoraClrChannelEventHandler.h"
#include "AgoraClrLibraryTypes.h"
#include "AgoraClrLibraryEnum.h"
#include "AgoraClrMetadataObserver.h"
#include "AgoraClrPacketObserver.h"
#include "AgoraClrLibraryDelegates.h"
#include "..\include\common.h"

using namespace System;
using namespace agora::rtc;
using namespace Collections::Generic;
using namespace Runtime::InteropServices;

namespace AgoraClrLibrary {
	public ref class AgoraClrChannel
	{
	public:
		template<typename ...T>
		ref struct AT {
			delegate void Type(AgoraClrChannel^ channel, T...);
		};

		template<>
		ref struct AT<> {
			delegate void Type(AgoraClrChannel^ channel);
		};

		AgoraClrChannel(IChannel* channel);
		~AgoraClrChannel();

	public:
		int joinChannel(String^ token, String^ info, uid_t uid, ClrChannelMediaOptions^ options);
		int joinChannelWithUserAccount(String^ token, String^ account, ClrChannelMediaOptions^ options);
		int leaveChannel();
		int publish();
		int unpublish();
		String^ channelId();
		int getCallId(String^% callid);
		int renewToken(String^ token);
		int setEncryptionSecret(String^ secret);
		int setEncryptionMode(String^ mode);
		int setClientRole(EnumClientRoleType type);
		int setRemoteVoicePosition(int uid, double pan, double gain);
		int setRemoteRenderMode(uid_t uid, EnumRenderModeType renderMode, EnumVideoMirrorModeType mirrorMode);
		int setDefaultMuteAllRemoteAudioStreams(bool mute);
		int setDefaultMuteAllRemoteVideoStreams(bool mute);
		int muteAllRemoteAudioStreams(bool mute);
		int adjustUserPlaybackSignalVolume(uid_t uid, int volume);
		int muteRemoteAudioStream(uid_t uid, bool mute);
		int muteAllRemoteVideoStreams(bool mute);
		int muteRemoteVideoStream(uid_t uid, bool mute);
		int setRemoteVideoStreamType(uid_t uid, EnumRemoteVideoStreamType type);
		int setRemoteDefaultVideoStreamType(EnumRemoteVideoStreamType type);
		int createDataStream(int% streamId, bool reliable, bool ordered);
		int sendStreamMessage(int streamId, String^ msg);
		int addPublishStreamUrl(String^ url, bool transcodingEnabled);
		int removePublishStreamUrl(String^ url);
		int setLiveTranscoding(ClrLiveTranscoding^ transcoding);
		int addInjectStreamUrl(String^ url, ClrInjectStreamConfig^ config);
		int removeInjectStreamUrl(String^ url);
		int startChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config);
		int updateChannelMediaRelay(ClrChannelMediaRelayConfiguration^ config);
		int stopChannelMediaRelay();

		property EnumConnectionStateType ConnectionState {
			EnumConnectionStateType get(){
				return static_cast<EnumConnectionStateType>(channel->getConnectionState());
			}
		}
	public:
		AT<int, String^>::Type^ onChannelWarning;
		AT<int, String^>::Type^ onChannelError;
		AT<uid_t, int>::Type^ onJoinChannelSuccess;
		AT<uid_t, int>::Type^ onRejoinChannelSuccess;
		AT<ClrRtcStats^>::Type^ onLeaveChannel;
		AT<EnumClientRoleType, EnumClientRoleType>::Type^ onClientRoleChanged;
		AT<uid_t, int>::Type^ onUserJoined;
		AT<uid_t, EnumUserOfflineReasonType>::Type^ onUserOffline;
		AT<>::Type^ onConnectionLost;
		AT<>::Type^ onRequestToken;
		AT<String^>::Type^ onTokenPrivilegeWilExpire;
		AT<ClrRtcStats^>::Type^ onRtcStats;
		AT<uid_t, int, int>::Type^ onNetworkQuality;
		AT<ClrRemoteVideoStats^>::Type^ onRemoteVideoStats;
		AT<ClrRemoteAudioStats^>::Type^ onRemoteAudioStats;
		AT<uid_t, EnumRemoteAudioState, EnumRemoteAudioStateReason, int>::Type^ onRemoteAudioStateChanged;
		AT<uid_t>::Type^ onActiveSpeaker;
		AT<uid_t, int, int, int>::Type^ onVideoSizeChanged;
		AT<uid_t, EnumRemoteVideoState, EnumRemoteVideoStateReason, int>::Type^ onRemoteVideoStateChanged;
		AT<uid_t, int, array<Byte>^>::Type^ onStreamMessage;
		AT<uid_t, int, int, int, int>::Type^ onStreamMessageError;
		AT<EnumChannelMediaRelayState, EnumChannelMediaRelayError>::Type^ onChannelMediaRelayStateChanged;
		AT<EnumChannelMediaRelayEvent>::Type^ onChannelMediaRelayEvent;
		AT<String^, EnumRtmpStreamPublishState, EnumRtmpStreamPublishError>::Type^ onRtmpStreamingStateChanged;
		AT<>::Type^ onTranscodingUpdated;
		AT<String^, uid_t, int>::Type^ onStreamInjectedStatus;
		AT<uid_t, bool>::Type^ onRemoteSubscribeFallbackToAudioOnly;
		AT<EnumConnectionStateType, EnumConnectionChangedReasonType>::Type^ onConnectionStateChanged;

		Func<ClrMetadata^, bool>^ onReadyToSendMetadata;
		Action<ClrMetadata^>^ onMetadataReceived;

		onSendAudioPacket^ onSendAudioPacket;
		onSendVideoPacket^ onSendVideoPacket;
		onReceiveAudioPacket^ onReceiveAudioPacket;
		onReceiveVideoPacket^ onReceiveVideoPacket;
	private:
		IChannel* channel;
		AgoraClrChannelEventHandler* events;
		AgoraClrMetadataObserver* metaObserver;
		AgoraClrPacketObserver* packetObserver;
		List<GCHandle>^ gchs;

	private:
		void NativeOnChannelWarning(IChannel* channel, int warn, const char* msg);
		void NativeOnChannelError(IChannel* channel, int err, const char* msg);
		void NativeOnJoinChannelSuccess(IChannel* channel, uid_t uid, int elapsed);
		void NativeOnRejoinChanelSuccess(IChannel* channel, uid_t uid, int elapsed);
		void NativeOnLeaveChannel(IChannel* channel, const RtcStats& stats);
		void NativeOnClientRoleChanged(IChannel* channel, CLIENT_ROLE_TYPE old, CLIENT_ROLE_TYPE newer);
		void NativeOnUserJoined(IChannel* channel, uid_t uid, int elapsed);
		void NativeOnUserOffline(IChannel* channel, uid_t uid, USER_OFFLINE_REASON_TYPE reason);
		void NativeOnConnectionLost(IChannel* channel);
		void NativeOnRequestToken(IChannel* channel);
		void NativeOnTokenPrivilegeWillExpire(IChannel* channel, const char* token);
		void NativeOnRtcStats(IChannel* channel, const RtcStats& stats);
		void NativeOnNetworkQuality(IChannel* channel, uid_t uid, int txQuality, int rxQuality);
		void NativeOnRemoteVideoStats(IChannel* channel, const RemoteVideoStats& stats);
		void NativeOnRemoteAudioStats(IChannel* channel, const RemoteAudioStats& stats);
		void NativeOnRemoteAudioStateChanged(IChannel* channel, uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed);
		void NativeOnActiveSpeaker(IChannel* channel, uid_t uid);
		void NativeOnVideoSizeChanged(IChannel* channel, uid_t uid, int width, int height, int rotation);
		void NativeOnRemoteVideoStateChanged(IChannel* channel, uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed);
		void NativeOnStreamMessage(IChannel* channel, uid_t uid, int streamId, const char* data, size_t length);
		void NativeOnStreamMessageError(IChannel* channel, uid_t uid, int streamId, int code, int missed, int cached);
		void NativeOnChannelMediaRelayStateChanged(IChannel* channel, CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR code);
		void NativeOnChannelMediaRelayEvent(IChannel* channel, CHANNEL_MEDIA_RELAY_EVENT code);
		void NativeOnRtmpStreamingStateChanged(IChannel* channel, const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR code);
		void NativeOnTranscodingUpdated(IChannel* channel);
		void NativeOnStreamInjectedStatus(IChannel* channel, const char* url, uid_t uid, int status);
		void NativeOnRemoteSubscribeFallbackToAudioOnly(IChannel* channel, uid_t uid, bool isFallbackOrRecover);
		void NativeOnConnectionStateChanged(IChannel* channel, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);


		int NativeGetMaxMetadataSize();
		bool NativeOnReadyToSendMetadata(IMetadataObserver::Metadata& metadata);
		void NativeOnMetadataReceived(const IMetadataObserver::Metadata& metadata);

		bool NativeOnSendAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnSendVideoPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveAudioPacket(agora::rtc::IPacketObserver::Packet& packet);
		bool NativeOnReceiveVideoPacket(agora::rtc::IPacketObserver::Packet& packet);


	private:
		template<typename E, typename D>
		inline void regEvent(E& e, D^ d)
		{
			gchs->Add(GCHandle::Alloc(d));
			e = reinterpret_cast<E>(Marshal::GetFunctionPointerForDelegate(d).ToPointer());
		}

		void bindEventHandler();
		void bindMetaObserver();
		void bindPacketObserver();
	};

}
