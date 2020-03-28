#pragma once
#include "..\include\common.h"
#include "..\..\agorasdk\include\IAgoraRtcChannel.h"

#include <tuple>
using namespace agora::rtc;

namespace AgoraClrLibrary {

	using OnChannelWarningType = ET<IChannel*, int, const char*>;
	using OnChannelErrorType = ET<IChannel*, int, const char*>;
	using OnJoinChannelSuccessType = ET<IChannel*, uid_t, int>;
	using OnRejoinChanelSuccessType = ET<IChannel*, uid_t, int>;
	using OnLeaveChannelType = ET<IChannel*, const RtcStats&>;
	using OnClientRoleChangedType = ET<IChannel*, CLIENT_ROLE_TYPE, CLIENT_ROLE_TYPE>;
	using OnUserJoinedType = ET<IChannel*, uid_t, int>;
	using OnUserOfflineType = ET<IChannel*, uid_t, USER_OFFLINE_REASON_TYPE>;
	using OnConnectionLostType = ET<IChannel*>;
	using OnRequestTokenType = ET<IChannel*>;
	using OnTokenPrivilegeWillExpireType = ET<IChannel*, const char*>;
	using OnRtcStatsType = ET<IChannel*, const RtcStats&>;
	using OnNetworkQualityType = ET<IChannel*, uid_t, int, int>;
	using OnRemoteVideoStatsType = ET<IChannel*, const RemoteVideoStats&>;
	using OnRemoteAudioStatsType = ET<IChannel*, const RemoteAudioStats&>;
	using OnRemoteAudioStateChangedType = ET<IChannel*, uid_t, REMOTE_AUDIO_STATE, REMOTE_AUDIO_STATE_REASON, int>;
	using OnActiveSpeakerType = ET<IChannel*, uid_t>;
	using OnVideoSizeChangedType = ET<IChannel*, uid_t, int, int, int>;
	using OnRemoteVideoStateChangedType = ET<IChannel*, uid_t, REMOTE_VIDEO_STATE, REMOTE_VIDEO_STATE_REASON, int>;
	using OnStreamMessageType = ET<IChannel*, uid_t, int, const char*, size_t>;
	using OnStreamMessageErrorType = ET<IChannel*, uid_t, int, int, int, int>;
	using OnChannelMediaRelayStateChangedType = ET<IChannel*, CHANNEL_MEDIA_RELAY_STATE, CHANNEL_MEDIA_RELAY_ERROR>;
	using OnChannelMediaRelayEventType = ET<IChannel*, CHANNEL_MEDIA_RELAY_EVENT>;
	using OnRtmpStreamingStateChangedType = ET<IChannel*, const char*, RTMP_STREAM_PUBLISH_STATE, RTMP_STREAM_PUBLISH_ERROR>;
	using OnTranscodingUpdatedType = ET<IChannel*>;
	using OnStreamInjectedStatusType = ET<IChannel*, const char*, uid_t, int>;
	using OnRemoteSubscribeFallbackToAudioOnlyType = ET<IChannel*, uid_t, bool>;
	using OnConnectionStateChangedType = ET<IChannel*, CONNECTION_STATE_TYPE, CONNECTION_CHANGED_REASON_TYPE>;

	
	public class AgoraClrChannelEventHandler: public agora::rtc::IChannelEventHandler
	{
	private:
		template<typename F, typename ...Args>
		inline void call(F&& event, Args&&... args) { 
			if (event) event(std::forward<Args>(args)...); 
		}

	public:
		OnChannelWarningType::Pointer onChannelWarningEvent;
		OnChannelErrorType::Pointer onChannelErrorEvent;
		OnJoinChannelSuccessType::Pointer onJoinChannelSuccessEvent;
		OnRejoinChanelSuccessType::Pointer onRejoinChannelSuccessEvent;	
		OnLeaveChannelType::Pointer onLeaveChannelEvent;
		OnClientRoleChangedType::Pointer onClientRoleChangedEvent;
		OnUserJoinedType::Pointer onUserJoinEvent;
		OnUserOfflineType::Pointer onUserOfflineEvent;
		OnConnectionLostType::Pointer onConnectionLostEvent;
		OnRequestTokenType::Pointer onRequestTokenEvent;
		OnTokenPrivilegeWillExpireType::Pointer onTokePrivilegeWillExpireEvent;
		OnRtcStatsType::Pointer onRtcStatsEvent;
		OnNetworkQualityType::Pointer onNetworkQualityEvent;
		OnRemoteVideoStatsType::Pointer onRemoteVideoStatsEvent;
		OnRemoteAudioStatsType::Pointer onRemoteAudioStatsEvent;
		OnRemoteAudioStateChangedType::Pointer onRemoteAudioStateChangedEvent;
		OnActiveSpeakerType::Pointer onActiveSpeakerEvent;
		OnVideoSizeChangedType::Pointer onVideoSizeChangedEvent;
		OnRemoteVideoStateChangedType::Pointer onRemoteVideoStateChangedEvent;
		OnStreamMessageType::Pointer onStreamMessageEvent;
		OnStreamMessageErrorType::Pointer onStreamMessageErrorEvent;
		OnChannelMediaRelayStateChangedType::Pointer onChannelMediaRelayStateChangedEvent;
		OnChannelMediaRelayEventType::Pointer onChannelMediaRelayEventEvent;
		OnRtmpStreamingStateChangedType::Pointer onRtmpStreamingStateChangedEvent;
		OnTranscodingUpdatedType::Pointer onTranscodingUpdatedEvent;
		OnStreamInjectedStatusType::Pointer onStreamInjectedStatusEvent;
		OnRemoteSubscribeFallbackToAudioOnlyType::Pointer onRemoteSubscribeFallbackToAudioOnlyEvent;
		OnConnectionStateChangedType::Pointer onConnectionStateChangedEvent;

		virtual void onChannelWarning(IChannel* channel, int warn, const char* msg) override { 
			call(onChannelWarningEvent, channel, warn, msg);
		}

		virtual void onChannelError(IChannel* channel, int err, const char* msg) override {
			call(onChannelErrorEvent, channel, err, msg);
		}

		virtual void onJoinChannelSuccess(IChannel* channel, uid_t uid, int elapsed) override {
			call(onJoinChannelSuccessEvent, channel, uid, elapsed);
		}

		virtual void onRejoinChannelSuccess(IChannel* channel, uid_t uid, int elapsed) override {
			call(onRejoinChannelSuccessEvent, channel, uid, elapsed);
		}

		virtual void onLeaveChannel(IChannel* channel, const RtcStats& stats) override {
			call(onLeaveChannelEvent, channel, stats);
		}

		virtual void onClientRoleChanged(IChannel* channel, CLIENT_ROLE_TYPE old, CLIENT_ROLE_TYPE newer) {
			call(onClientRoleChangedEvent, channel, old, newer);
		}

		virtual void onUserJoined(IChannel* channel, uid_t uid, int elapsed) override {
			call(onUserJoinEvent, channel, uid, elapsed);
		}

		virtual void onUserOffline(IChannel* channel, uid_t uid, USER_OFFLINE_REASON_TYPE reason) override {
			call(onUserOfflineEvent, channel, uid, reason);
		}
		
		virtual void onConnectionLost(IChannel* channel) override {
			call(onConnectionLostEvent, channel);
		}

		virtual void onRequestToken(IChannel* channel) override {
			call(onRequestTokenEvent, channel);
		}

		virtual void onTokenPrivilegeWillExpire(IChannel* channel, const char* token) override {
			call(onTokePrivilegeWillExpireEvent, channel, token);
		}

		virtual void onRtcStats(IChannel* channel, const RtcStats& stats) override {
			call(onRtcStatsEvent, channel, stats);
		}

		virtual void onNetworkQuality(IChannel* channel, uid_t uid, int txQuality, int rxQuaity) override {
			call(onNetworkQualityEvent, channel, uid, txQuality, rxQuaity);
		}

		virtual void onRemoteVideoStats(IChannel* channel, const RemoteVideoStats& stats) override {
			call(onRemoteVideoStatsEvent, channel, stats);
		}

		virtual void onRemoteAudioStats(IChannel* channel, const RemoteAudioStats& stats) override {
			call(onRemoteAudioStatsEvent, channel, stats);
		}

		virtual void onRemoteAudioStateChanged(IChannel* channel, uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed) override {
			call(onRemoteAudioStateChangedEvent, channel, uid, state, reason, elapsed);
		}

		virtual void onActiveSpeaker(IChannel* channel, uid_t uid) {
			call(onActiveSpeakerEvent, channel, uid);
		}

		virtual void onVideoSizeChanged(IChannel* channel, uid_t uid, int width, int height, int rotation) override {
			call(onVideoSizeChangedEvent, channel, uid, width, height, rotation);
		}

		virtual void onRemoteVideoStateChanged(IChannel* channel, uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) override {
			call(onRemoteVideoStateChangedEvent, channel, uid, state, reason, elapsed);
		}

		virtual void onStreamMessage(IChannel* channel, uid_t uid, int streamId, const char* data, size_t length) override {
			call(onStreamMessageEvent, channel, uid, streamId, data, length);
		}

		virtual void onStreamMessageError(IChannel* channel, uid_t uid, int streamId, int code, int missed, int cached) override {
			call(onStreamMessageErrorEvent, channel, uid, streamId, code, missed, cached);
		}

		virtual void onChannelMediaRelayStateChanged(IChannel* channel, CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR code) override {
			call(onChannelMediaRelayStateChangedEvent, channel, state, code);
		}

		virtual void onChannelMediaRelayEvent(IChannel* channel, CHANNEL_MEDIA_RELAY_EVENT code) override {
			call(onChannelMediaRelayEventEvent, channel, code);
		}

		virtual void onRtmpStreamingStateChanged(IChannel* channel, const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR code) override {
			call(onRtmpStreamingStateChangedEvent, channel, url, state, code);
		}

		virtual void onTranscodingUpdated(IChannel* channel) override {
			call(onTranscodingUpdatedEvent, channel);
		}

		virtual void onStreamInjectedStatus(IChannel* channel, const char* url, uid_t uid, int status) override {
			call(onStreamInjectedStatusEvent, channel, url, uid, status);
		}

		virtual void onRemoteSubscribeFallbackToAudioOnly(IChannel* channel, uid_t uid, bool isFallbackOrRecover) override {
			call(onRemoteSubscribeFallbackToAudioOnlyEvent, channel, uid, isFallbackOrRecover);
		}

		virtual void onConnectionStateChanged(IChannel* channel, CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason) override {
			call(onConnectionStateChangedEvent, channel, state, reason);
		}


	};

}
