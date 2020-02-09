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
	typedef void(__stdcall * PFOnApiCallExecuted)(const char* api, int error);
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
	typedef void(__stdcall * PFOnCameraFocusAreaChanged)(int, int, int, int);
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
	delegate void NativeOnApiCallExecutedDelegate(const char* api, int error);
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
	delegate void NativeOnCameraFocusAreaChangedDelegate(int, int, int, int);
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

		PFOnJoinChannelSuccess onJoinChannelSuccessEvent = 0;
		PFOnRejoinChannelSuccess onRejoinChannelSuccessEvent = 0;
		PFOnWarning onWarningEvent = 0;
		PFOnError onErrorEvent = 0;
		PFOnAudioQuality onAudioQualityEvent = 0;
		PFOnAudioVolumeIndication onAudioVolumeIndicationEvent = 0;
		PFOnLeaveChannel onLeaveChannelEvent = 0;
		PFOnRtcStats onRtcStatsEvent = 0;
		PFOnAudioDeviceStateChanged onAudioDeviceStateChangedEvent = 0;
		PFOnVideoDeviceStateChanged onVideoDeviceStateChangedEvent = 0;
		PFOnLastmileQuality onLastmileQualityEvent = 0;
		PFOnNetworkQuality onNetworkQualityEvent = 0;
		PFOnFirstLocalVideoFrame onFirstLocalVideoFrameEvent = 0;
		PFOnFirstRemoteVideoDecoded onFirstRemoteVideoDecodedEvent = 0;
		PFOnFirstRemoteVideoFrame onFirstRemoteVideoFrameEvent = 0;
		PFOnUserJoined onUserJoinedEvent = 0;
		PFOnUserOffline onUserOfflineEvent = 0;
		PFOnUserMuteAudio onUserMuteAudioEvent = 0;
		PFOnUserMuteVideo onUserMuteVideoEvent = 0;
		PFOnUserEnableVideo onUserEnableVideoEvent = 0;
		PFOnApiCallExecuted onApiCallExecutedEvent = 0;
		PFOnLocalVideoStats onLocalVideoStatsEvent = 0;
		PFOnRemoteVideoStats onRemoteVideoStatsEvent = 0;
		PFOnCameraReady onCameraReadyEvent = 0;
		PFOnVideoStopped onVideoStoppedEvent = 0;
		PFOnConnectionLost onConnectionLostEvent = 0;
		PFOnConnectionBanned onConnectionBannedEvent = 0;

		PFOnConnectionInterrupted onConnectionInterruptedEvent = 0;
		PFOnStreamMessage onStreamMessageEvent = 0;
		PFOnStreamMessageError onStreamMessageErrorEvent = 0;
		PFOnRequestChannelKey onRequestChannelKeyEvent = 0;
		PFOnRequestToken onRequestTokenEvent = 0;

		PFOnAudioMixingFinished onAudioMixingFinishedEvent = 0;
		PFOnActiveSpeaker onActiveSpeakerEvent = 0;
		PFOnClientRoleChanged onClientRoleChangedEvent = 0;
		PFOnAudioDeviceVolumeChanged onAudioDeviceVolumeChangedEvent = 0;

		PFOnStreamUnpublished onStreamUnpublishedEvent = 0;
		PFOnStreamPublished onStreamPublishedEvent = 0;
		PFOnTranscodingUpdated onTranscodingUpdatedEvent = 0;

		PFOnConnectionStateChanged onConnectionStateChangedEvent = 0;
		PFOnTokenPrivilegeWillExpire onTokenPrivilegeWillExpireEvent = 0;
		PFOnFirstLocalAudioFrame onFirstLocalAudioFrameEvent = 0;
		PFOnFirstRemoteAudioFrame onFirstRemoteAudioFrameEvent = 0;
		PFOnUserEnableLocalVideo onUserEnableLocalVideoEvent = 0;
		PFOnVideoSizeChanged onVideoSizeChangedEvent = 0;
		PFOnRemoteVideoStateChanged onRemoteVideoStateChangedEvent = 0;
		PFOnLocalPublishFallbackToAudioOnly onLocalPublishFallbackToAudioOnlyEvent = 0;
		PFOnRemoteSubscribeFallbackToAudioOnly onRemoteSubscribeFallbackToAudioOnlyEvent = 0;
		PFOnCameraFocusAreaChanged onCameraFocusAreaChangedEvent = 0;
		PFOnRemoteAudioStats onRemoteAudioStatsEvent = 0;
		PFOnRemoteAudioTransportStats onRemoteAudioTransportStatsEvent = 0;
		PFOnRemoteVideoTransportStats onRemoteVideoTransportStatsEvent = 0;
		PFOnAudioMixingBegin onAudioMixingBeginEvent = 0;
		PFOnAudioMixingEnd onAudioMixingEndEvent = 0;
		PFOnAudioEffectFinished onAudioEffectFinishedEvent = 0;
		PFOnStreamInjectedStatus onStreamInjectedStatusEvent = 0;
		PFOnMediaEngineLoadSuccess onMediaEngineLoadSuccessEvent = 0;
		PFOnMediaEngineStartCallSuccess onMediaEngineStartCallSuccessEvent = 0;
		PFOnNetworkTypeChanged onNetworkTypeChangedEvent = 0;

		PFOnLocalAudioStateChanged onLocalAudioStateChangedEvent = 0;
		PFOnLocalVideoStateChanged onLocalVideoStateChangedEvent = 0;
		PFOnRemoteAudioStateChanged onRemoteAudioStateChangedEvent = 0;
		PFOnFirstRemoteAudioDecoded onFirstRemoteAudioDecodedEvent = 0;
		PFOnLocalAudioStats onLocalAudioStatsEvent = 0;
		PFOnAudioMixingStateChanged onAudioMixingStateChangedEvent = 0;
		PFOnRemoteAudioMixingBegin onRemoteAudioMixingBeginEvent = 0;
		stdCall onRemoteAudioMixingEndEvent = 0;
		PFOnRtmpStreamingStateChanged onRtmpStreamingStateChangedEvent = 0;
		PFOnChannelMediaRelayStateChanged onChannelMediaRelayStateChangedEvent = 0;
		PFOnChannelMediaRelayEvent onChannelMediaRelayEventEvnet = 0;
		PFOnLastmileProbeResult onLastmileProbeResultEvent = 0;

		virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
		virtual void onWarning(int warn, const char* msg);
		virtual void onError(int err, const char* msg);
		virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost);
		virtual void onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume);
		virtual void onLeaveChannel(const agora::rtc::RtcStats& stats);
		virtual void onRtcStats(const agora::rtc::RtcStats& stats);
		virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState);
		virtual void onLastmileQuality(int quality);
		virtual void onNetworkQuality(uid_t uid, int txQuality, int rxQuality);
		virtual void onFirstLocalVideoFrame(int width, int height, int elapsed);
		virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed);
		virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed);
		virtual void onUserJoined(uid_t uid, int elapsed);
		virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason);
		virtual void onUserMuteAudio(uid_t uid, bool muted);
		virtual void onUserMuteVideo(uid_t uid, bool muted);
		virtual void onUserEnableVideo(uid_t uid, bool enabled);
		virtual void onApiCallExecuted(const char* api, int error);
		virtual void onLocalVideoStats(const agora::rtc::LocalVideoStats& stats);
		virtual void onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats);
		virtual void onCameraReady();
		virtual void onVideoStopped();
		virtual void onConnectionLost();
		virtual void onConnectionInterrupted();
		virtual void onConnectionBanned();

		virtual void onStreamMessage(uid_t uid, int streamId, const char* data, size_t length);
		virtual void onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached);
		virtual void onRequestChannelKey();
		virtual void onRequestToken();

		virtual void onAudioMixingFinished();
		virtual void onActiveSpeaker(uid_t uid);
		virtual void onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole);
		virtual void onAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted);

		virtual void onStreamUnpublished(const char* url);
		virtual void onStreamPublished(const char* url, int error);
		virtual void onTranscodingUpdated();

		virtual void onConnectionStateChanged(CONNECTION_STATE_TYPE state, CONNECTION_CHANGED_REASON_TYPE reason);
		virtual void onTokenPrivilegeWillExpire(const char* token);
		virtual void onFirstLocalAudioFrame(int elapsed);
		virtual void onFirstRemoteAudioFrame(uid_t uid, int elapsed);
		virtual void onUserEnableLocalVideo(uid_t uid, bool enabled);
		virtual void onVideoSizeChanged(uid_t uid, int width, int height, int rotation);
		virtual void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed);
		virtual void onLocalPublishFallbackToAudioOnly(bool);
		virtual void onRemoteSubscribeFallbackToAudioOnly(uid_t, bool);
		virtual void onCameraFocusAreaChanged(int x, int y, int width, int height);
		virtual void onRemoteAudioStats(const RemoteAudioStats& stats);
		virtual void onRemoteAudioTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate);
		virtual void onRemoteVideoTransportStats(uid_t uid, unsigned short delay, unsigned short lost, unsigned short rxKBitRate);
		virtual void onAudioMixingBegin();
		virtual void onAudioMixingEnd();
		virtual void onAudioEffectFinished(int soundId);
		virtual void onStreamInjectedStatus(const char* url, uid_t uid, int status);
		virtual void onMediaEngineLoadSuccess();
		virtual void onMediaEngineStartCallSuccess();

		virtual void onNetworkTypeChanged(NETWORK_TYPE type);
		virtual void onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error);
		virtual void onLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error);
		virtual void onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed);
		virtual void onFirstRemoteAudioDecoded(uid_t uid, int elapsed);
		virtual void onLocalAudioStats(const LocalAudioStats& stats);
		virtual void onAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE error);
		virtual void onRemoteAudioMixingBegin();
		virtual void onRemoteAudioMixingEnd();
		virtual void onRtmpStreamingStateChanged(const char* url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error);
		virtual void onChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error);
		virtual void onChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT event);
		virtual void onLastmileProbeResult(const LastmileProbeResult& result);
	};

}