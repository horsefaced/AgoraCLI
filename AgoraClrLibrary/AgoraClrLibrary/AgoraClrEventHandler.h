#pragma once
#include "..\..\agorasdk\include\IAgoraRtcEngine.h"

using namespace agora::rtc;

namespace AgoraClrLibrary {
	//Native Function Pointer
	using stdCall = void(__stdcall*)();

	template<typename ...T>
	using stdTemplateCall = void(__stdcall*)(T...);

	typedef void(__stdcall * PFOnJoinChannelSuccess)(const char* channel, uid_t uid, int elapsed);
	typedef void(__stdcall * PFOnRejoinChannelSuccess)(const char* channel, uid_t uid, int elapsed);
	typedef void(__stdcall * PFOnWarning)(int warn, const char* msg);
	typedef void(__stdcall * PFOnError)(int err, const char* msg);
	typedef void(__stdcall * PFOnAudioQuality)(uid_t uid, int quality, unsigned short delay, unsigned short lost);
	typedef void(__stdcall * PFOnAudioVolumeIndication)(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
	typedef void(__stdcall * PFOnLeaveChannel)(const agora::rtc::RtcStats& stats);
	typedef void(__stdcall * PFOnRtcStats)(const agora::rtc::RtcStats& stats);
	typedef void(__stdcall * PFOnAudioDeviceStateChanged)(const char* deviceId, int deviceType, int deviceState);
	typedef void(__stdcall * PFOnVideoDeviceStateChanged)(const char* deviceId, int deviceType, int deviceState);
	typedef void(__stdcall * PFOnLastmileQuality)(int quality);
	typedef void(__stdcall * PFOnNetworkQuality)(uid_t uid, int txQuality, int rxQuality);
	typedef void(__stdcall * PFOnFirstLocalVideoFrame)(int width, int height, int elapsed);
	typedef void(__stdcall * PFOnFirstRemoteVideoDecoded)(uid_t uid, int width, int height, int elapsed);
	typedef void(__stdcall * PFOnFirstRemoteVideoFrame)(uid_t uid, int width, int height, int elapsed);
	typedef void(__stdcall * PFOnUserJoined)(uid_t uid, int elapsed);
	typedef void(__stdcall * PFOnUserOffline)(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
	typedef void(__stdcall * PFOnUserMuteAudio)(uid_t uid, bool muted);
	typedef void(__stdcall * PFOnUserMuteVideo)(uid_t uid, bool muted);
	typedef void(__stdcall * PFOnUserEnableVideo)(uid_t uid, bool enabled);
	typedef void(__stdcall * PFOnApiCallExecuted)(int, const char*, const char*);
	typedef void(__stdcall * PFOnLocalVideoStats)(const agora::rtc::LocalVideoStats& stats);
	typedef void(__stdcall * PFOnRemoteVideoStats)(const agora::rtc::RemoteVideoStats& stats);
	typedef void(__stdcall * PFOnCameraReady)();
	typedef void(__stdcall * PFOnVideoStopped)();
	typedef void(__stdcall * PFOnConnectionLost)();
	typedef void(__stdcall * PFOnConnectionInterrupted)();
	typedef void(__stdcall * PFOnConnectionBanned)();

	typedef void(__stdcall * PFOnStreamMessage)(uid_t uid, int streamId, const char* data, size_t length);
	typedef void(__stdcall * PFOnStreamMessageError)(uid_t uid, int streamId, int code, int missed, int cached);
	typedef void(__stdcall * PFOnRequestChannelKey)();
	typedef void(__stdcall * PFOnRequestToken)();

	typedef void(__stdcall * PFOnAudioMixingFinished)();
	typedef void(__stdcall * PFOnActiveSpeaker)(uid_t uid);
	typedef void(__stdcall * PFOnClientRoleChanged)(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole);
	typedef void(__stdcall * PFOnAudioDeviceVolumeChanged)(MEDIA_DEVICE_TYPE, int, bool);

	typedef void(__stdcall * PFOnStreamUnpublished)(const char* url);
	typedef void(__stdcall * PFOnStreamPublished)(const char* url, int error);
	typedef void(__stdcall * PFOnTranscodingUpdated)();

	typedef void(__stdcall * PFOnConnectionStateChanged)(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);
	typedef void(__stdcall * PFOnTokenPrivilegeWillExpire)(const char* token);
	typedef void(__stdcall * PFOnFirstLocalAudioFrame)(int elapsed);
	typedef void(__stdcall * PFOnFirstRemoteAudioFrame)(uid_t uid, int elapsed);
	typedef void(__stdcall * PFOnUserEnableLocalVideo)(uid_t uid, bool enabled);
	typedef void(__stdcall * PFOnVideoSizeChanged)(uid_t uid, int width, int height, int rotation);
	typedef void(__stdcall * PFOnRemoteVideoStateChanged)(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON, int);
	typedef void(__stdcall * PFOnLocalPublishFallbackToAudioOnly)(bool);
	typedef void(__stdcall * PFOnRemoteSubscribeFallbackToAudioOnly)(uid_t, bool);
	typedef void(__stdcall * PFOnRemoteAudioStats)(const RemoteAudioStats&);
	typedef void(__stdcall * PFOnRemoteAudioTransportStats)(uid_t, unsigned short, unsigned short, unsigned short);
	typedef void(__stdcall * PFOnRemoteVideoTransportStats)(uid_t, unsigned short, unsigned short, unsigned short);
	typedef void(__stdcall * PFOnAudioMixingBegin)();
	typedef void(__stdcall * PFOnAudioMixingEnd)();
	typedef void(__stdcall * PFOnAudioEffectFinished)(int);
	typedef void(__stdcall * PFOnStreamInjectedStatus)(const char*, uid_t, int);
	typedef void(__stdcall * PFOnMediaEngineLoadSuccess)();
	typedef void(__stdcall * PFOnMediaEngineStartCallSuccess)();
	typedef void(__stdcall * PFOnNetworkTypeChanged)(NETWORK_TYPE);
	typedef void(__stdcall * PFOnLocalAudioStateChanged)(LOCAL_AUDIO_STREAM_STATE, LOCAL_AUDIO_STREAM_ERROR);
	typedef void(__stdcall* PFOnLocalVideoStateChanged)(LOCAL_VIDEO_STREAM_STATE, LOCAL_VIDEO_STREAM_ERROR);
	typedef void(__stdcall* PFOnRemoteAudioStateChanged)(uid_t, REMOTE_AUDIO_STATE, REMOTE_AUDIO_STATE_REASON, int);
	typedef void(__stdcall* PFOnFirstRemoteAudioDecoded)(uid_t, int);
	typedef void(__stdcall* PFOnLocalAudioStats)(const LocalAudioStats&);
	typedef void(__stdcall* PFOnAudioMixingStateChanged)(AUDIO_MIXING_STATE_TYPE, AUDIO_MIXING_ERROR_TYPE);
	typedef void(__stdcall* PFOnRemoteAudioMixingBegin)();
	typedef void(__stdcall* PFOnRtmpStreamingStateChanged)(const char*, RTMP_STREAM_PUBLISH_STATE, RTMP_STREAM_PUBLISH_ERROR);
	typedef void(__stdcall* PFOnChannelMediaRelayStateChanged)(CHANNEL_MEDIA_RELAY_STATE, CHANNEL_MEDIA_RELAY_ERROR);

	using PFOnChannelMediaRelayEvent = stdTemplateCall<CHANNEL_MEDIA_RELAY_EVENT>;
	using PFOnLastmileProbeResult = stdTemplateCall<const LastmileProbeResult&>;

	//Native delegate	
	delegate void NativeOnJoinChannelSuccessDelegate(const char* channel, uid_t uid, int elapsed);
	delegate void NativeOnRejoinChannelSuccessDelegate(const char* channel, uid_t uid, int elapsed);
	delegate void NativeOnWarningDelegate(int warn, const char* msg);
	delegate void NativeOnErrorDelegate(int err, const char* msg);
	delegate void NativeOnAudioQualityDelegate(uid_t uid, int quality, unsigned short delay, unsigned short lost);
	delegate void NativeOnAudioVolumeIndicationDelegate(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
	delegate void NativeOnLeaveChannelDelegate(const agora::rtc::RtcStats& stats);
	delegate void NativeOnRtcStatsDelegate(const agora::rtc::RtcStats& stats);
	delegate void NativeOnAudioDeviceStateChangedDelegate(const char* deviceId, int deviceType, int deviceState);
	delegate void NativeOnVideoDeviceStateChangedDelegate(const char* deviceId, int deviceType, int deviceState);
	delegate void NativeOnLastmileQualityDelegate(int quality);
	delegate void NativeOnNetworkQualityDelegate(uid_t uid, int txQuality, int rxQuality);
	delegate void NativeOnFirstLocalVideoFrameDelegate(int width, int height, int elapsed);
	delegate void NativeOnFirstRemoteVideoDecodedDelegate(uid_t uid, int width, int height, int elapsed);
	delegate void NativeOnFirstRemoteVideoFrameDelegate(uid_t uid, int width, int height, int elapsed);
	delegate void NativeOnUserJoinedDelegate(uid_t uid, int elapsed);
	delegate void NativeOnUserOfflineDelegate(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
	delegate void NativeOnUserMuteAudioDelegate(uid_t uid, bool muted);
	delegate void NativeOnUserMuteVideoDelegate(uid_t uid, bool muted);
	delegate void NativeOnUserEnableVideoDelegate(uid_t uid, bool enabled);
	delegate void NativeOnApiCallExecutedDelegate(int, const char*, const char*);
	delegate void NativeOnLocalVideoStatsDelegate(const agora::rtc::LocalVideoStats& stats);
	delegate void NativeOnRemoteVideoStatsDelegate(const agora::rtc::RemoteVideoStats& stats);
	delegate void NativeOnCameraReadyDelegate();
	delegate void NativeOnVideoStoppedDelegate();
	delegate void NativeOnConnectionLostDelegate();
	delegate void NativeOnConnectionBannedDelegate();

	delegate void NativeOnConnectionInterruptedDelegate();
	delegate void NativeOnStreamMessageDelegate(uid_t uid, int streamId, const char* data, size_t length);
	delegate void NativeOnStreamMessageErrorDelegate(uid_t uid, int streamId, int code, int missed, int cached);
	delegate void NativeOnRequestChannelKeyDelegate();
	delegate void NativeOnRequestTokenDelegate();

	delegate void NativeOnAudioMixingFinishedDelegate();
	delegate void NativeOnActiveSpeakerDelegate(uid_t uid);
	delegate void NativeOnClientRoleChangedDelegate(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole);
	delegate void NativeOnAudioDeviceVolumeChangedDelegate(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted);

	delegate void NativeOnStreamPublishedDelegate(const char* url, int error);
	delegate void NativeOnStreamUnpublishedDelegate(const char* url);
	delegate void NativeOnTranscodingUpdatedDelegate();

	delegate void NativeOnConnectionStateChangedDelegate(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);
	delegate void NativeOnTokenPrivilegeWillExpireDelegate(const char* token);
	delegate void NativeOnFirstLocalAudioFrameDelegate(int elasped);
	delegate void NativeOnFirstRemoteAudioFrameDelegate(uid_t uid, int elapsed);
	delegate void NativeOnUserEnableLocalVideoDelegate(uid_t uid, bool enabled);
	delegate void NativeOnVideoSizeChangedDelegate(uid_t uid, int width, int height, int rotation);
	delegate void NativeOnRemoteVideoStateChangedDelegate(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed);
	delegate void NativeOnLocalPublishFallbackToAudioOnlyDelegate(bool);
	delegate void NativeOnRemoteSubscribeFallbackToAudioOnlyDelegate(uid_t, bool);
	delegate void NativeOnRemoteAudioStatsDelegate(const RemoteAudioStats&);
	delegate void NativeOnRemoteAudioTransportStatsDelegate(uid_t, unsigned short, unsigned short, unsigned short);
	delegate void NativeOnRemoteVideoTransportStatsDelegate(uid_t, unsigned short, unsigned short, unsigned short);
	delegate void NativeOnAudioMixingBeginDelegate();
	delegate void NativeOnAudioMixingEndDelegate();
	delegate void NativeOnAudioEffectFinishedDelegate(int);
	delegate void NativeOnStreamInjectedStatusDelegate(const char*, uid_t, int);
	delegate void NativeOnMediaEngineLoadSuccessDelegate();
	delegate void NativeOnMediaEngineStartCallSuccessDelegate();

	delegate void NativeOnNetworkTypeChangedDelegate(NETWORK_TYPE type);
	delegate void NativeOnLocalAudioStateChangedDelegate(LOCAL_AUDIO_STREAM_STATE, LOCAL_AUDIO_STREAM_ERROR);
	delegate void NativeOnLocalVideoStateChangedDelegate(LOCAL_VIDEO_STREAM_STATE, LOCAL_VIDEO_STREAM_ERROR);
	delegate void NativeOnRemoteAudioStateChangedDelegate(uid_t, REMOTE_AUDIO_STATE, REMOTE_AUDIO_STATE_REASON, int);
	delegate void NativeOnFirstRemoteAudioDecodedDelegate(uid_t, int);
	delegate void NativeOnLocalAudioStatsDelegate(const LocalAudioStats&);
	delegate void NativeOnAudioMixingStateChangedDelegate(AUDIO_MIXING_STATE_TYPE, AUDIO_MIXING_ERROR_TYPE);
	delegate void NativeOnRtmpStreamingStateChangedDelegate(const char*, RTMP_STREAM_PUBLISH_STATE, RTMP_STREAM_PUBLISH_ERROR);
	delegate void NativeOnChannelMediaRelayStateChangedDelegate(CHANNEL_MEDIA_RELAY_STATE, CHANNEL_MEDIA_RELAY_ERROR);
	delegate void NativeOnChannelMediaRelayEventDelegate(CHANNEL_MEDIA_RELAY_EVENT);
	delegate void NativeOnLastmileProbeResultDelegate(const LastmileProbeResult&);

	public class AgoraClrEventHandler : public agora::rtc::IRtcEngineEventHandler
	{
	public:
		AgoraClrEventHandler();
		~AgoraClrEventHandler();

		PFOnJoinChannelSuccess onJoinChannelSuccessEvent = nullptr;
		PFOnRejoinChannelSuccess onRejoinChannelSuccessEvent = nullptr;
		PFOnWarning onWarningEvent = nullptr;
		PFOnError onErrorEvent = nullptr;
		PFOnAudioQuality onAudioQualityEvent = nullptr;
		PFOnAudioVolumeIndication onAudioVolumeIndicationEvent = nullptr;
		PFOnLeaveChannel onLeaveChannelEvent = nullptr;
		PFOnRtcStats onRtcStatsEvent = nullptr;
		PFOnAudioDeviceStateChanged onAudioDeviceStateChangedEvent = nullptr;
		PFOnVideoDeviceStateChanged onVideoDeviceStateChangedEvent = nullptr;
		PFOnLastmileQuality onLastmileQualityEvent = nullptr;
		PFOnNetworkQuality onNetworkQualityEvent = nullptr;
		PFOnFirstLocalVideoFrame onFirstLocalVideoFrameEvent = nullptr;
		PFOnFirstRemoteVideoDecoded onFirstRemoteVideoDecodedEvent = nullptr;
		PFOnFirstRemoteVideoFrame onFirstRemoteVideoFrameEvent = nullptr;
		PFOnUserJoined onUserJoinedEvent = nullptr;
		PFOnUserOffline onUserOfflineEvent = nullptr;
		PFOnUserMuteAudio onUserMuteAudioEvent = nullptr;
		PFOnUserMuteVideo onUserMuteVideoEvent = nullptr;
		PFOnUserEnableVideo onUserEnableVideoEvent = nullptr;
		PFOnApiCallExecuted onApiCallExecutedEvent = nullptr;
		PFOnLocalVideoStats onLocalVideoStatsEvent = nullptr;
		PFOnRemoteVideoStats onRemoteVideoStatsEvent = nullptr;
		PFOnCameraReady onCameraReadyEvent = nullptr;
		PFOnVideoStopped onVideoStoppedEvent = nullptr;
		PFOnConnectionLost onConnectionLostEvent = nullptr;
		PFOnConnectionBanned onConnectionBannedEvent = nullptr;

		PFOnConnectionInterrupted onConnectionInterruptedEvent = nullptr;
		PFOnStreamMessage onStreamMessageEvent = nullptr;
		PFOnStreamMessageError onStreamMessageErrorEvent = nullptr;
		PFOnRequestChannelKey onRequestChannelKeyEvent = nullptr;
		PFOnRequestToken onRequestTokenEvent = nullptr;

		PFOnAudioMixingFinished onAudioMixingFinishedEvent = nullptr;
		PFOnActiveSpeaker onActiveSpeakerEvent = nullptr;
		PFOnClientRoleChanged onClientRoleChangedEvent = nullptr;
		PFOnAudioDeviceVolumeChanged onAudioDeviceVolumeChangedEvent = nullptr;

		PFOnStreamUnpublished onStreamUnpublishedEvent = nullptr;
		PFOnStreamPublished onStreamPublishedEvent = nullptr;
		PFOnTranscodingUpdated onTranscodingUpdatedEvent = nullptr;

		PFOnConnectionStateChanged onConnectionStateChangedEvent = nullptr;
		PFOnTokenPrivilegeWillExpire onTokenPrivilegeWillExpireEvent = nullptr;
		PFOnFirstLocalAudioFrame onFirstLocalAudioFrameEvent = nullptr;
		PFOnFirstRemoteAudioFrame onFirstRemoteAudioFrameEvent = nullptr;
		PFOnUserEnableLocalVideo onUserEnableLocalVideoEvent = nullptr;
		PFOnVideoSizeChanged onVideoSizeChangedEvent = nullptr;
		PFOnRemoteVideoStateChanged onRemoteVideoStateChangedEvent = nullptr;
		PFOnLocalPublishFallbackToAudioOnly onLocalPublishFallbackToAudioOnlyEvent = nullptr;
		PFOnRemoteSubscribeFallbackToAudioOnly onRemoteSubscribeFallbackToAudioOnlyEvent = nullptr;
		PFOnRemoteAudioStats onRemoteAudioStatsEvent = nullptr;
		PFOnRemoteAudioTransportStats onRemoteAudioTransportStatsEvent = nullptr;
		PFOnRemoteVideoTransportStats onRemoteVideoTransportStatsEvent = nullptr;
		PFOnAudioMixingBegin onAudioMixingBeginEvent = nullptr;
		PFOnAudioMixingEnd onAudioMixingEndEvent = nullptr;
		PFOnAudioEffectFinished onAudioEffectFinishedEvent = nullptr;
		PFOnStreamInjectedStatus onStreamInjectedStatusEvent = nullptr;
		PFOnMediaEngineLoadSuccess onMediaEngineLoadSuccessEvent = nullptr;
		PFOnMediaEngineStartCallSuccess onMediaEngineStartCallSuccessEvent = nullptr;
		PFOnNetworkTypeChanged onNetworkTypeChangedEvent = nullptr;

		PFOnLocalAudioStateChanged onLocalAudioStateChangedEvent = nullptr;
		PFOnLocalVideoStateChanged onLocalVideoStateChangedEvent = nullptr;
		PFOnRemoteAudioStateChanged onRemoteAudioStateChangedEvent = nullptr;
		PFOnFirstRemoteAudioDecoded onFirstRemoteAudioDecodedEvent = nullptr;
		PFOnLocalAudioStats onLocalAudioStatsEvent = nullptr;
		PFOnAudioMixingStateChanged onAudioMixingStateChangedEvent = nullptr;
		PFOnRemoteAudioMixingBegin onRemoteAudioMixingBeginEvent = nullptr;
		stdCall onRemoteAudioMixingEndEvent = nullptr;
		PFOnRtmpStreamingStateChanged onRtmpStreamingStateChangedEvent = nullptr;
		PFOnChannelMediaRelayStateChanged onChannelMediaRelayStateChangedEvent = nullptr;
		PFOnChannelMediaRelayEvent onChannelMediaRelayEventEvnet = nullptr;
		PFOnLastmileProbeResult onLastmileProbeResultEvent = nullptr;

		void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;
		void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;
		void onWarning(int warn, const char* msg) override;
		void onError(int err, const char* msg) override;
		void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) override;
		void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) override;
		void onLeaveChannel(const agora::rtc::RtcStats& stats) override;
		void onRtcStats(const agora::rtc::RtcStats& stats) override;
		void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;
		void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) override;
		void onLastmileQuality(int quality) override;
		void onNetworkQuality(uid_t uid, int txQuality, int rxQuality) override;
		void onFirstLocalVideoFrame(int width, int height, int elapsed) override;
		void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) override;
		void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) override;
		void onUserJoined(uid_t uid, int elapsed) override;
		void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) override;
		void onUserMuteAudio(uid_t uid, bool muted) override;
		void onUserMuteVideo(uid_t uid, bool muted) override;
		void onUserEnableVideo(uid_t uid, bool enabled) override;
		void onApiCallExecuted(int err, const char* api, const char* result) override;
		void onLocalVideoStats(const agora::rtc::LocalVideoStats& stats) override;
		void onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats) override;
		void onCameraReady() override;
		void onVideoStopped() override;
		void onConnectionLost() override;
		void onConnectionInterrupted() override;
		void onConnectionBanned() override;

		void onStreamMessage(uid_t uid, int streamId, const char* data, size_t length) override;
		void onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached) override;
		void onRequestToken() override;

		void onAudioMixingFinished() override;
		void onActiveSpeaker(uid_t uid) override;
		void onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole) override;
		void onAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted) override;

		void onStreamUnpublished(const char* url) override;
		void onStreamPublished(const char* url, int error) override;
		void onTranscodingUpdated() override;

		void onConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason) override;
		void onTokenPrivilegeWillExpire(const char* token) override;
		void onFirstLocalAudioFrame(int elapsed) override;
		void onFirstRemoteAudioFrame(uid_t uid, int elapsed) override;
		void onUserEnableLocalVideo(uid_t uid, bool enabled) override;
		void onVideoSizeChanged(uid_t uid, int width, int height, int rotation) override;
		void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) override;
		void onLocalPublishFallbackToAudioOnly(bool) override;
		void onRemoteSubscribeFallbackToAudioOnly(uid_t, bool) override;
		void onRemoteAudioStats(const RemoteAudioStats& stats) override;
		void onRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) override;
		void onRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate) override;
		void onAudioEffectFinished(int soundId) override;
		void onStreamInjectedStatus(const char* url, uid_t uid, int status) override;
		void onMediaEngineLoadSuccess() override;
		void onMediaEngineStartCallSuccess() override;

		void onNetworkTypeChanged(NETWORK_TYPE type) override;
		void onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error) override;
		void onLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error) override;
		void onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed) override;
		void onFirstRemoteAudioDecoded(uid_t uid, int elapsed) override;
		void onLocalAudioStats(const LocalAudioStats& stats) override;
		void onAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE error) override;
		void onRemoteAudioMixingBegin() override;
		void onRemoteAudioMixingEnd() override;
		void onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error) override;
		void onChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error) override;
		void onChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event) override;
		void onLastmileProbeResult(const LastmileProbeResult& result) override;
	};

}